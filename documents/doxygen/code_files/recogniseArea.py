#!/usr/bin/python3

##
# @file recogniseArea.py
# @authors Filippo Conti, Mattia Meneghin e Nicola Gianuzzi
#

# Imports
from pathlib import Path
import sys
import os
import cv2
import numpy

# strings
## path of file
file_path = Path(__file__).resolve()

## directory which contains recogniseArea.py
root_path = file_path.parents[0]
if str(root_path) not in sys.path:
    sys.path.append(str(root_path))  # add ROOT to PATH
root_path = Path(os.path.relpath(root_path, Path.cwd()))  # relative

## flag used to indicate if execute the robot in simulation or real world
is_real_robot = False

## @brief Defines custom area
class RecogniseArea:
    ## @brief Class constructor
    ## @param img_path: path of input image
    ## @param output_path: path of output image
    def __init__(self, image_path, output_path):
        ## input image path
        self.img_path = image_path
        
        ## output image path
        self.output_path = output_path
        
        ## loads an image from the input image path
        self.img = cv2.imread(self.img_path)

    ## @brief crops the pixels to outline the area
    ## @note Creates a mask of the same size of the image
    ## @note Checks if the image is from real or simulation camera
    ## @note Defines the region without aliasing
    ## @note Apply the mask to the image
    ## @note Save the image on the output path
    def execute(self):
        mask = numpy.zeros(self.img.shape[0:2], dtype=numpy.uint8)

        if is_real_robot:
            cam_points = numpy.array([[[457,557], [555,272], [779,267], [960,532]]])
        else:
            cam_points = numpy.array([[[845,409], [1201,412], [1545,913], [658, 921]]])

        cv2.drawContours(mask, [cam_points], -1, (255, 255, 255), -1, cv2.LINE_AA)
        output = cv2.bitwise_and(self.img,self.img,mask = mask)
        cv2.imwrite(self.output_path, output)
        cv2.destroyAllWindows()

if __name__ == '__main__':
    """! Main program entry.
    @note to execute: python3 recogniseArea.py /path/to/input/img /path/to/output/img
    """
    ## roi Image
    roi = RecogniseArea(img_path=sys.argv[1], output_path=sys.argv[2])
    roi.run()