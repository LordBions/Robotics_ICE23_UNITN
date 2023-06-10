#!/usr/bin/python3

# Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi

from pathlib import Path
import sys
import os
import rospy
import numpy
import cv2
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
import sensor_msgs.point_cloud2 as pcloud2
from sensor_msgs.msg import PointCloud2
from std_msgs.msg import Int32
from motion.msg import legoFound
from motion.msg import eventResult
from recogniseLego import RecogniseLego

# ros packet settings
node_name = "vision"
sub_detect_resulter = "/planner/detectResulter"
pub_detect_commander = "/vision/detectCommander"
sub_receive_image = "/ur5/zed_node/left_raw/image_raw_color"
sub_receive_pointcloud = "/ur5/zed_node/point_cloud/cloud_registered"

# flags and arrays
is_real_robot = 0
allow_receive_image = True
allow_receive_pointcloud = False
vision_ready = False

# arrays and matrix
lego_position_array = []
lego_list = []
matrixVirtual = numpy.matrix([[0.000, -0.499, 0.866], [-1.000, 0.000, 0.000], [0.000, -0.866, -0.499]])
vectorVirtual = numpy.array([-0.900, 0.240, -0.350])

# command lists
no_command = 0
command_detect = 1
command_quit = 2

# other vars 
default_queque_size = 10
base_offset = numpy.array([0.500, 0.350, 1.750])
table_coord_z = 0.860 + 0.100

# strings
file_path = Path(__file__).resolve()
root_path = file_path.parents[0]
if str(root_path) not in sys.path:
    sys.path.append(str(root_path))
root_path = Path(os.path.relpath(root_path, Path.cwd()))
pkg_vision_path = os.path.abspath(os.path.join(root_path, ".."))
zed_image_file = os.path.join(pkg_vision_path, "../../src/vision/images/img_lego.png")

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
        cv_image_output = bridge.imgmsg_to_cv2(data, "bgr8")
    except CvBridgeError as e:
        print(e)

    cv2.imwrite(zed_image_file, cv_image_output)
    foundLego = RecogniseLego(zed_image_file)
    lego_list = foundLego.lego_list

    allow_receive_pointcloud = True

def pointCloudCallBack(msg):

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready
    global lego_position_array
    global lego_list
    
    if not allow_receive_pointcloud:
        return
    else:
        allow_receive_pointcloud = False

    for lego in lego_list:

        for data in pcloud2.read_points(msg, field_names=['x','y','z'], skip_nans=True, uvs=[lego.center_point]):
            lego.point_cloud = (data[0], data[1], data[2])

        if is_real_robot:
            lego.point_world = lego.point_cloud
        else:
            lego.point_world = matrixVirtual.dot(lego.point_cloud) + vectorVirtual + base_offset           
        
        lego.showImg()

        lego_position_packet = legoFound()
        lego_position_packet.command_id = command_detect
        lego_position_packet.lego_class = lego.class_id
        lego_position_packet.send_ack = 1
        lego_position_packet.coord_x = lego.point_world[0, 0]
        lego_position_packet.coord_y = lego.point_world[0, 1]
        lego_position_packet.coord_z = lego.point_world[0, 2]
        lego_position_packet.rot_pitch = 0
        lego_position_packet.rot_roll = 0
        lego_position_packet.rot_yaw = 0

        if lego_position_packet.coord_z < table_coord_z:
            lego_position_array.append(lego_position_packet)

    vision_ready = True
    pubPlannerCommander()

def detectResulterCallback(ack_ready):

    global allow_receive_image
    global allow_receive_pointcloud
    global vision_ready

    print('Vision received some data')
    
    if vision_ready == True and ack_ready.event_id == 1 and ack_ready.result_id == 1:
        pubPlannerCommander()
        
def pubPlannerCommander():

    global lego_position_array
    
    try:
        lego_position_packet = lego_position_array.pop()
        pos_pub.publish(lego_position_packet)
        
        print('A lego position is sent to planner:', lego_position_packet)
        exit()
        pass
        
    except IndexError:
        print('All lego sent to planner! Request to quit')
        pubPlannerQuitter()
        exit()
        pass

def pubPlannerQuitter():

    lego_position_packet = legoFound()
    lego_position_packet.command_id = command_quit
    lego_position_packet.send_ack = 0

    pos_pub.publish(lego_position_packet)
    print('Sent the quit command to the planner module')

if __name__ == '__main__':

    print("----------------------------")
    print("Starting the vision module!")
    print("----------------------------")

    rospy.init_node(node_name, anonymous = True)
    print("Node: " + node_name + " initialized!")
    
    pos_pub = rospy.Publisher(pub_detect_commander, legoFound, queue_size = default_queque_size)
    print("Publisher: " + pub_detect_commander + " enabled with queque: " + str(default_queque_size))

    ack_sub = rospy.Subscriber(sub_detect_resulter, eventResult, detectResulterCallback, queue_size = default_queque_size)
    print("Subscriber: " + sub_detect_resulter + " enabled with queque: " + str(default_queque_size))
    
    image_sub = rospy.Subscriber(sub_receive_image, Image, subReceiveImage, queue_size = default_queque_size)
    print("Subscriber: " + sub_receive_image + " enabled with queque: " + str(default_queque_size))

    pointcloud_sub = rospy.Subscriber(sub_receive_pointcloud, PointCloud2, pointCloudCallBack, queue_size = default_queque_size)
    print("Subscriber: " + sub_receive_pointcloud + " enabled with queque: " + str(default_queque_size))

    bridge = CvBridge()

    print("----------------------------")
    print("Vision module ready!")
    print("----------------------------")   

    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down the vision module")