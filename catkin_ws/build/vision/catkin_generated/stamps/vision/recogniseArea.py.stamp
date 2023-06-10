#!/usr/bin/python3

# Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi

from pathlib import Path
import sys
import os
import cv2
import numpy

# strings
file_path = Path(__file__).resolve()
root_path = file_path.parents[0]
if str(root_path) not in sys.path:
    sys.path.append(str(root_path))  # add ROOT to PATH
root_path = Path(os.path.relpath(root_path, Path.cwd()))  # relative
is_real_robot = False

class RecogniseArea:

    def __init__(self, image_path, output_path):
        
        self.img_path = image_path
        self.output_path = output_path
        self.img = cv2.imread(self.img_path)

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

    roi = RecogniseArea(img_path=sys.argv[1], output_path=sys.argv[2])
    roi.run()