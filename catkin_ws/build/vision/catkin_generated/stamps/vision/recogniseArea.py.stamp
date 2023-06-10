#!/usr/bin/python3

# Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi

import cv2
import numpy as np
from pathlib import Path
import sys
import os

file_path = Path(__file__).resolve()
root_path = file_path.parents[0]
if str(root_path) not in sys.path:
    sys.path.append(str(root_path))  # add ROOT to PATH

root_path = Path(os.path.relpath(root_path, Path.cwd()))  # relative
is_real_robot = False

class RecogniseArea:
    # @brief This class defines custom Region Of Interest

    def __init__(self, image_path, output_path):
        # @brief Class constructor
        # @param img_path (String): path of input image
        # @param output_path (String): path of out image
        
        self.img_path = image_path
        self.output_path = output_path
        self.img = cv2.imread(self.img_path)

    def run_auto(self):
        # @brief automatically crop the region of interest depending on real camera or simulation camera

        #create a mask of the same size of the image
        mask = np.zeros(self.img.shape[0:2], dtype=np.uint8)
        # check if the image is from real camera or simulation camera
        if is_real_robot:
            points = np.array([[[457,557], [555,272], [779,267], [960,532]]])
        else:
            points = np.array([[[845,409], [1201,412], [1545,913], [658, 921]]])

        # define the region of interest without aliasing
        cv2.drawContours(mask, [points], -1, (255, 255, 255), -1, cv2.LINE_AA)
    
        # apply the mask to the image
        res = cv2.bitwise_and(self.img,self.img,mask = mask)

        # save the image on the output path
        cv2.imwrite(self.output_path, res)

        # cv2.imshow("Samed Size White Image", dst)
        # cv2.waitKey(0)
        cv2.destroyAllWindows()

if __name__ == '__main__':

    roi = RecogniseArea(img_path=sys.argv[1], output_path=sys.argv[2])
    roi.run()