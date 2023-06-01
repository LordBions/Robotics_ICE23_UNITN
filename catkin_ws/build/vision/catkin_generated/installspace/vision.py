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

allow_receive_image = True
allow_receive_pointcloud = False
vision_ready = False
pos_msg_list = []
lego_list = []

no_command = 0
command_detect = 1
command_quit = 2

default_queque_size = 10

file_path = Path(__file__).resolve()
root_path = file_path.parents[0]

if str(root_path) not in sys.path:
    sys.path.append(str(root_path))  # add root to PATH

root_path = Path(os.path.relpath(root_path, Path.cwd()))  # relative
pkg_vision_path = os.path.abspath(os.path.join(root_path, ".."))
zed_image_file = os.path.join(pkg_vision_path, "../../src/vision/images/img_lego.png")

w_R_c = np.matrix([[0, -0.499, 0.866], [-1, 0, 0], [0, -0.866, -0.499]])
x_c = np.array([-0.9, 0.24, -0.35])

base_offset = np.array([0.5, 0.35, 1.75])
table_coord_z = 0.86 + 0.1

is_real_robot = 0

def subReceiveImage(data):

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready
    global lego_list
    
    if not allow_receive_image:
        return
    else:
        allow_receive_image = False

    try:
        cv_image = bridge.imgmsg_to_cv2(data, "bgr8")

    except CvBridgeError as e:
        print(e)

    cv.imwrite(zed_image_file, cv_image)
    self.recognise(img_path)

# Let user choose detect method
    ask =  ('\nContinue recognise [ENTER]'+
            '\nDetect legos again [A]'+
            '\nDetect only table area (T)'+
            'Press CTRL + C to EXIT'+
            '\nYour choice is ----> ')
            
    choice = input(ask)

    # Detect again using another image
    if choice == 'A' or choice == 'a':
        print('Detecting again...')
        allow_receive_image = True
        allow_receive_pointcloud = False
        break

    # Detect using area table
    if choice == 'T' or choice == 't':
        self.recogniseArea(img_path)
        choice = '0'

    # Continue
    if choice == '':

        foundLego = RecogniseLego(zed_image_file)
        lego_list = foundLego.lego_list

        allow_receive_pointcloud = True

def pointCloudCallBack(msg):

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready
    global pos_msg_list
    global lego_list
    
    if not allow_receive_pointcloud:
        return
    else:
        allow_receive_pointcloud = False

    for lego in lego_list:

        for data in point_cloud2.read_points(msg, field_names=['x','y','z'], skip_nans=True, uvs=[lego.center_point]):
            lego.point_cloud = (data[0], data[1], data[2])

        if is_real_robot:
            lego.point_world = lego.point_cloud
        else:
            lego.point_world = w_R_c.dot(lego.point_cloud) + x_c + base_offset              # Transform point cloud to world

        lego.show() # Show details

        # Create msg for pos_pub
        pos_msg = legoFound()
        pos_msg.command_id = command_detect
        pos_msg.lego_class = lego.class_id
        pos_msg.send_ack = 1
        pos_msg.coord_x = lego.point_world[0, 0]
        pos_msg.coord_y = lego.point_world[0, 1]
        pos_msg.coord_z = lego.point_world[0, 2]
        pos_msg.rot_pitch = 0
        pos_msg.rot_roll = 0
        pos_msg.rot_yaw = 0

        if pos_msg.coord_z < table_coord_z:
            pos_msg_list.append(pos_msg)

    vision_ready = True
    send_pos_msg()

def detectResulterCallback(ack_ready):

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready

    print('Vision received some data')
    
    if vision_ready == True and ack_ready.event_id == 1 and ack_ready.result_id == 1:
        send_pos_msg()
        
def send_pos_msg():

    global pos_msg_list
    
    try:
        pos_msg = pos_msg_list.pop()
        pos_pub.publish(pos_msg)
        
        print('Lego position sent:', pos_msg)
        exit()
        pass
        
    except IndexError:
        print('All lengo sent to planner!')
        send_quit_planner()
        exit()
        pass

def send_quit_planner():

    pos_msg = legoFound()
    pos_msg.command_id = command_quit
    pos_msg.send_ack = 0

    pos_pub.publish(pos_msg)
    print('Sent the quit command to the planner module')

if __name__ == '__main__':

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

    bridge = CvBridge()

    print("----------------------------")
    print("Vision module ready!")
    print("----------------------------")   

    try:
        ros.spin()

    except KeyboardInterrupt:
        print("Shutting down the vision module")