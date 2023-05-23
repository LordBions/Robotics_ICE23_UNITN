#!/usr/bin/python3

# Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi

from pathlib import Path
import sys
import os
import rospy as ros
import numpy as np
import cv2 as cv
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
import sensor_msgs.point_cloud2 as point_cloud2
from sensor_msgs.msg import PointCloud2
from std_msgs.msg import Int32
from motion.msg import legoFound
from motion.msg import eventResult
from recogniseLego import RecogniseLego

node_name = "vision"
sub_detect_resulter = "/planner/detectResulter"
pub_detect_commander = "/vision/detectCommander"
sub_receive_image = "/ur5/zed_node/left_raw/image_raw_color"
sub_receive_pointcloud = "/ur5/zed_node/point_cloud/cloud_registered"

global allow_receive_image
global allow_receive_pointcloud
global vision_ready
global pos_msg_list

command_detect = 1
command_quit = 2

default_queque_size = 10

FILE = Path(__file__).resolve()
ROOT = FILE.parents[0]

if str(ROOT) not in sys.path:
    sys.path.append(str(ROOT))  # add ROOT to PATH

ROOT = Path(os.path.relpath(ROOT, Path.cwd()))  # relative
VISION_PATH = os.path.abspath(os.path.join(ROOT, ".."))
IMG_ZED = os.path.join(VISION_PATH, "../../src/vision/images/img_lego.png")

w_R_c = np.matrix([[0, -0.499, 0.866], [-1, 0, 0], [0, -0.866, -0.499]])
x_c = np.array([-0.9, 0.24, -0.35])

base_offset = np.array([0.5, 0.35, 1.75])
OFF_SET = 0.86 + 0.1

REAL_ROBOT = 0

def subReceiveImage(data):

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready
    # @brief Callback function whenever take msg from ZED camera
    #  @param data (msg): msg taken from ZED node
    
    # Flag
    if not allow_receive_image:
        return

    allow_receive_image = False

    # Convert ROS image to OpenCV image
    try:
        cv_image = bridge.imgmsg_to_cv2(data, "bgr8")
    except CvBridgeError as e:
        print(e)

    # Save image and detect lego
    cv.imwrite(IMG_ZED, cv_image)
    foundLego = RecogniseLego(IMG_ZED)
    lego_list = foundLego.lego_list

    allow_receive_pointcloud = True

def pointCloudCallBack(msg):

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready
    global pos_msg_list
    # @brief Callback function whenever take point_cloud msg from ZED camera
    # @param msg (msg): msg taken from ZED node
    
    # Flag
    if not allow_receive_pointcloud:
        return
    allow_receive_pointcloud = False
    
    pos_msg_list = []

    for lego in lego_list:

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
        pos_msg.command_id = command_detect
        pos_msg.lego_class = lego.class_id
        pos_msg.coord_x = lego.point_world[0, 0]
        pos_msg.coord_y = lego.point_world[0, 1]
        pos_msg.coord_z = lego.point_world[0, 2]
        pos_msg.rot_pitch = 0
        pos_msg.rot_roll = 0
        pos_msg.rot_yaw = 0
        pos_msg.date_time = ros.Time.now()
        pos_msg.comment = "Automatic message by vision module"
        pos_msg.send_ack = 1


        if pos_msg.coord_z < OFF_SET:
            pos_msg_list.append(pos_msg)
        
    print('\nVISION DONE DETECTING LEGO!\nREADY FOR MOTION!')
    vision_ready = 1
    send_pos_msg()

def detectResulterCallback(ack_ready):

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready

    # @brief check if the motion planner is ready to receive the position of the lego
    # @param ack_ready (msg): msg from Motion node
    
    if vision_ready == 1 and ack_ready.eventID == 1 and ack_ready.result_id ==1:
        send_pos_msg()
        
def send_pos_msg():


    # @brief send the position of the lego to motion planner
    
    try:
        pos_msg = pos_msg_list.pop()

        print()
        pos_pub.publish(pos_msg)
        
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

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready

    print("----------------------------")
    print("Starting the vision module!")
    print("----------------------------")

    ros.init_node(node_name, anonymous = True)
    print("Node: " + node_name + " initialized!")
    
    pos_pub = ros.Publisher(pub_detect_commander, legoFound, queue_size = default_queque_size)
    print("Publisher: " + pub_detect_commander + " enabled with queque: " + str(default_queque_size))

    ack_sub = ros.Subscriber(sub_detect_resulter, eventResult, detectResulterCallback, queue_size = default_queque_size)
    print("Subscriber: " + sub_detect_resulter + " enabled with queque: " + str(default_queque_size))
    
    image_sub = ros.Subscriber(sub_receive_image, Image, subReceiveImage, queue_size = default_queque_size)
    print("Subscriber: " + sub_receive_image + " enabled with queque: " + str(default_queque_size))

    pointcloud_sub = ros.Subscriber(sub_receive_pointcloud, PointCloud2, pointCloudCallBack, queue_size = default_queque_size)
    print("Subscriber: " + sub_receive_pointcloud + " enabled with queque: " + str(default_queque_size))

    lego_list = []
    bridge = CvBridge()

    allow_receive_image = True
    allow_receive_pointcloud = False
    vision_ready = False

    print("----------------------------")
    print("Vision module ready! ")
    print("----------------------------")   

    try:
        ros.spin()
    except KeyboardInterrupt:
        print("Shutting down")