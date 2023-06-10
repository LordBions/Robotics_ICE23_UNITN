#!/usr/bin/python3

# Authors: Filippo Conti, Mattia Meneghin e Nicola Gianuzzi

from pathlib import Path
import rospy as ros
import sys
import os
import torch
from IPython.display import display
from PIL import Image
from recogniseArea import RecogniseArea

resize_width = 75

# strings
file_path = Path(__file__).resolve()
root_path = file_path.parents[0]
if str(root_path) not in sys.path:
    sys.path.append(str(root_path))
root_path = Path(os.path.relpath(root_path, Path.cwd())) 
pkg_vision_path = os.path.abspath(os.path.join(root_path, ".."))
zed_roi_image = os.path.join(pkg_vision_path, "../../src/vision/images/img_Area.png")

# yolo settings
weights_path = os.path.join(pkg_vision_path, "../../install/include/vision/include/best.pt")
pkg_yolo_path = os.path.join(pkg_vision_path, "include/yolo5")
lego_model = torch.hub.load('ultralytics/yolov5', 'custom', weights_path)

min_level_confidence = 0.75 # minimum confidence

lego_models_list = [  'X1-Y1-Z2',
                'X1-Y2-Z1',
                'X1-Y2-Z2',
                'X1-Y2-Z2-CHAMFER',
                'X1-Y2-Z2-TWINFILLET',
                'X1-Y3-Z2',
                'X1-Y3-Z2-FILLET',
                'X1-Y4-Z1',
                'X1-Y4-Z2',
                'X2-Y2-Z2',
                'X2-Y2-Z2-FILLET']

class RecogniseLego:
    
    def __init__(self, img_path):
        
        lego_model.conf = min_level_confidence
        lego_model.multi_label = False
    
        self.lego_list = []
        self.detectLegos(img_path)

        choice = '0'
        while True:
            while (choice != 'a' and choice != 't' and choice != ''):
                ask =  ('\n Press [ENTER] to continue...'+
                        '\n Press [a] to detect the full image again'+
                        '\n Press [t] to detect the table area only'+
                        '\n \n Your choice: ')
                choice = input(ask)

            if choice == '':
                break

            if choice == 'a':
                print('Full image again selected!')
                self.detectLegos(img_path)
                choice = '0'

            if choice == 't':
                print('Table area only selected!')
                self.detectArea(img_path)
                choice = '0'

    def detectArea(self, img_path):
        
        roi = RecogniseArea(img_path, zed_roi_image)
        roi.run_auto()
        print('Detecting the working area...')
        self.detectLegos(zed_roi_image)

    def detectLegos(self, img_path):

        detect_time = ros.get_rostime()   
        
        self.lego_list.clear()

        self.results = lego_model(img_path)
        self.results.show()
        img = Image.open(img_path)
        print(img_path)
        print('img size:', img.width, 'x', img.height)

        bboxes = self.results.pandas().xyxy[0].to_dict(orient="records")
        for bbox in bboxes:
            name = bbox['name']
            conf = bbox['confidence']
            x1 = int(bbox['xmin'])
            y1 = int(bbox['ymin'])
            x2 = int(bbox['xmax'])
            y2 = int(bbox['ymax'])

            self.lego_list.append(Lego(name, conf, x1, y1, x2, y2, img_path))

        detect_time = ros.get_rostime() - detect_time
        print("\n Vision recognition KPI: ", detect_time.secs ,",", detect_time.nsecs ," seconds! \n")

        print('Detected', len(self.lego_list), 'object(s)\n')
        self.showImg()

    def showImg(self):

        for index, lego in enumerate(self.lego_list, start=1):
            print(index)
            lego.showImg()

class Lego:

    def __init__(self, name, conf, x1, y1, x2, y2, img_source_path):

        self.name = name
        self.class_id = lego_models_list.index(name)
        self.confidence = conf
        self.xmin = x1
        self.ymin = y1
        self.xmax = x2
        self.ymax = y2
        self.img_source_path = img_source_path
        self.img_source = Image.open(self.img_source_path)
        self.center_point = (int((x1+x2)/2), int((y1+y2)/2))
        self.center_point_uv = (self.img_source.width - self.center_point[0], self.center_point[1])
        self.point_cloud = ()
        self.point_world = ()

    def showImg(self):
        
        self.img = self.img_source.crop((self.xmin, self.ymin, self.xmax, self.ymax))

        aspect_ratio = self.img.size[1] / self.img.size[0]
        new_width = resize_width 
        new_size = (new_width, int(new_width * aspect_ratio))
        self.img = self.img.resize(new_size, Image.LANCZOS)

        display(self.img)
        print('Lego name =', self.name)
        print('class id =', self.class_id)
        print('detection confidence =', '%.2f' %self.confidence)
        print('center point =', self.center_point)
        print('center point uv =', self.center_point_uv)
        print('point cloud data =', self.point_cloud)
        print('point in world =', self.point_world)
        print()

if __name__ == '__main__':

    legoDetect = LegoDetect(img_origin_path=sys.argv[1])