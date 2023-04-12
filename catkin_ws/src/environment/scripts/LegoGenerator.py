#!/usr/bin/python3

from tf.transformations import quaternion_from_euler
from geometry_msgs.msg import *
from gazebo_msgs.msg import ModelStates

import xml.etree.ElementTree as ET
import random

import rospy, rospkg
path = rospkg.RosPack().get_path("vision")

legobuilds = ['build-1', 'build-2']

def randomBuild():
	return random.choice(legobuilds)

def getPose(modelEl):
	return modelEl.find('pose').text

def get_Name_Type(modelEl):
	if modelEl.tag == 'model':
		name = modelEl.attrib['name']
	else:
		name = modelEl.find('name').text
	return name, name.split('_')[0]
	

def get_Parent_Child(jointEl):
	parent = jointEl.find('parent').text.split('::')[0]
	child = jointEl.find('child').text.split('::')[0]
	return parent, child


def getLego4Build(select=None):
	nome_cost = randomBuild()
	if select is not None: nome_cost = legobuilds[select]

	tree = ET.parse(f'{path}/worls/models/{nome_cost}/model.sdf')
	root = tree.getroot()
	costruzioneEl = root.find('model')

	brickEls = []
	for modEl in costruzioneEl:
		if modEl.tag in ['model', 'include']:
			brickEls.append(modEl)

	models = ModelStates()
	for bEl in brickEls:
		pose = getPose(bEl)
		models.name.append(get_Name_Type(bEl))
		rot = Quaternion(quaternion_from_euler(*pose[3:]))
		models.pose.append(Pose(Point(*pose[:3]), rot))

	rospy.init_node("environment")
	istruzioni = rospy.Publisher("buildInstructions", ModelStates, queue_size=1)
	istruzioni.publish(models)

	return models


def changeModelColor(model_xml, color):
	root = ET.XML(model_xml)
	root.find('.//material/script/name').text = color
	return ET.tostring(root, encoding='unicode')	
