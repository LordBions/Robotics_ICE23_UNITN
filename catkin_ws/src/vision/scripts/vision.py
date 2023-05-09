#!/usr/bin/python3
# Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi

import os
import sys
import rospy as ros
import numpy as np
import cv2 as cv
import sensor_msgs.point_cloud2 as point_cloud2

from std_msgs.msg import Int32
from pathlib import Path
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from sensor_msgs.msg import PointCloud2
from motion.msg import legoFound
from recogniseLego import RecogniseLego

FILE = Path(__file__).resolve()
ROOT = FILE.parents[0]

if str(ROOT) not in sys.path:
    sys.path.append(str(ROOT))

ROOT = Path(os.path.relpath(ROOT, Path.cwd())) 
VISION_PATH = os.path.abspath(os.path.join(ROOT, ".."))
IMG_ZED = os.path.join(VISION_PATH, "../../src/vision/images/img_lego.png")

w_R_c = np.matrix([[0, -0.499, 0.866], [-1, 0, 0], [0, -0.866, -0.499]])
x_c = np.array([-0.9, 0.24, -0.35])

base_offset = np.array([0.5, 0.35, 1.75])
OFF_SET = 0.86 + 0.1

REAL_ROBOT = False

class Vision:
      
    def __init__(self):
   
        ros.init_node('vision', anonymous=True)

        self.lego_list = []
        self.bridge = CvBridge()

        self.allow_receive_image = True
        self.allow_receive_pointcloud = False
        self.vision_ready = False

        # Subscribe and publish to ros nodes
        self.image_sub = ros.Subscriber("/ur5/zed_node/left_raw/image_raw_color", Image, self.receive_image)
        self.pointcloud_sub = ros.Subscriber("/ur5/zed_node/point_cloud/cloud_registered", PointCloud2, self.receive_pointcloud, queue_size=1)
        self.pos_pub = ros.Publisher("/vision/legoDetector", legoFound, queue_size=10)
        self.ack_sub = ros.Subscriber('/planner/readyACK', Int32, self.ackCallbak)
        self.ack_pub = ros.Publisher('/planner/stop', Int32, queue_size=10)
        
    def receive_image(self, data):
        # @brief Callback function whenever take msg from ZED camera
        #  @param data (msg): msg taken from ZED node
        
        # Flag
        if not self.allow_receive_image:
            return
        self.allow_receive_image = False

        # Convert ROS image to OpenCV image
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

        # Save image and detect lego
        cv.imwrite(IMG_ZED, cv_image)
        foundLego = RecogniseLego(IMG_ZED)
        self.lego_list = foundLego.lego_list

        self.allow_receive_pointcloud = True

    def receive_pointcloud(self, msg):
        # @brief Callback function whenever take point_cloud msg from ZED camera
        # @param msg (msg): msg taken from ZED node
        
        # Flag
        if not self.allow_receive_pointcloud:
            return
        self.allow_receive_pointcloud = False
        
        self.pos_msg_list = []

        for lego in self.lego_list:

            # Get point cloud
            for data in point_cloud2.read_points(msg, field_names=['x','y','z'], skip_nans=True, uvs=[lego.center_point]):
                lego.point_cloud = (data[0], data[1], data[2])

            if REAL_ROBOT:
                lego.point_world = lego.point_cloud
            else:
                # Transform point cloud to world
                lego.point_world = w_R_c.dot(lego.point_cloud) + x_c + base_offset

            # Show details
            lego.show()

            # Create msg for pos_pub
            pos_msg = legoFound()
            pos_msg.lego_class = lego.class_id
            pos_msg.coord_x = lego.point_world[0, 0]
            pos_msg.coord_y = lego.point_world[0, 1]
            pos_msg.coord_z = lego.point_world[0, 2]
            pos_msg.rot_pitch = 0
            pos_msg.rot_roll = 0
            pos_msg.rot_yaw = 0

            if pos_msg.coord_z < OFF_SET:
                self.pos_msg_list.append(pos_msg)
            
        print('\nVISION DONE DETECTING LEGO!\nREADY FOR MOTION!')
        self.vision_ready = 1
        self.send_pos_msg()

    def ackCallbak(self, ack_ready):
        # @brief check if the motion planner is ready to receive the position of the lego
        # @param ack_ready (msg): msg from Motion node
        
        if self.vision_ready == 1 and ack_ready.data == 1:
            self.send_pos_msg()
            
    def send_pos_msg(self):
        # @brief send the position of the lego to motion planner
        
        try:
            pos_msg = self.pos_msg_list.pop()
            self.pos_pub.publish(pos_msg)
            print('\nPosition published:\n', pos_msg)
            exit()
            pass
            
        except IndexError:
            print('\nFINISH ALL LEGO\n')
            exit()
            pass
            
# ---------------------- MAIN ----------------------
# To use in command:
# python3 vision.py
 
if __name__ == '__main__':

    vision = Vision()

    try:
        ros.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    
