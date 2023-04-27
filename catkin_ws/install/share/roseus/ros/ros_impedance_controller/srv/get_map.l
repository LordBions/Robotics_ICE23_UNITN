;; Auto-generated. Do not edit!


(when (boundp 'ros_impedance_controller::get_map)
  (if (not (find-package "ROS_IMPEDANCE_CONTROLLER"))
    (make-package "ROS_IMPEDANCE_CONTROLLER"))
  (shadow 'get_map (find-package "ROS_IMPEDANCE_CONTROLLER")))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GET_MAP")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GET_MAP"))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GET_MAPREQUEST")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GET_MAPREQUEST"))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GET_MAPRESPONSE")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GET_MAPRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))




(defclass ros_impedance_controller::get_mapRequest
  :super ros::object
  :slots (_target _width _length _resolution_x _resolution_y ))

(defmethod ros_impedance_controller::get_mapRequest
  (:init
   (&key
    ((:target __target) (instance geometry_msgs::Point :init))
    ((:width __width) 0.0)
    ((:length __length) 0.0)
    ((:resolution_x __resolution_x) 0.0)
    ((:resolution_y __resolution_y) 0.0)
    )
   (send-super :init)
   (setq _target __target)
   (setq _width (float __width))
   (setq _length (float __length))
   (setq _resolution_x (float __resolution_x))
   (setq _resolution_y (float __resolution_y))
   self)
  (:target
   (&rest __target)
   (if (keywordp (car __target))
       (send* _target __target)
     (progn
       (if __target (setq _target (car __target)))
       _target)))
  (:width
   (&optional __width)
   (if __width (setq _width __width)) _width)
  (:length
   (&optional __length)
   (if __length (setq _length __length)) _length)
  (:resolution_x
   (&optional __resolution_x)
   (if __resolution_x (setq _resolution_x __resolution_x)) _resolution_x)
  (:resolution_y
   (&optional __resolution_y)
   (if __resolution_y (setq _resolution_y __resolution_y)) _resolution_y)
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _target
    (send _target :serialization-length)
    ;; float64 _width
    8
    ;; float64 _length
    8
    ;; float64 _resolution_x
    8
    ;; float64 _resolution_y
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _target
       (send _target :serialize s)
     ;; float64 _width
       (sys::poke _width (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _length
       (sys::poke _length (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _resolution_x
       (sys::poke _resolution_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _resolution_y
       (sys::poke _resolution_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _target
     (send _target :deserialize buf ptr-) (incf ptr- (send _target :serialization-length))
   ;; float64 _width
     (setq _width (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _length
     (setq _length (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _resolution_x
     (setq _resolution_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _resolution_y
     (setq _resolution_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass ros_impedance_controller::get_mapResponse
  :super ros::object
  :slots (_row_length _height_array ))

(defmethod ros_impedance_controller::get_mapResponse
  (:init
   (&key
    ((:row_length __row_length) 0)
    ((:height_array __height_array) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _row_length (round __row_length))
   (setq _height_array __height_array)
   self)
  (:row_length
   (&optional __row_length)
   (if __row_length (setq _row_length __row_length)) _row_length)
  (:height_array
   (&optional __height_array)
   (if __height_array (setq _height_array __height_array)) _height_array)
  (:serialization-length
   ()
   (+
    ;; uint32 _row_length
    4
    ;; float64[] _height_array
    (* 8    (length _height_array)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _row_length
       (write-long _row_length s)
     ;; float64[] _height_array
     (write-long (length _height_array) s)
     (dotimes (i (length _height_array))
       (sys::poke (elt _height_array i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _row_length
     (setq _row_length (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64[] _height_array
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _height_array (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _height_array i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass ros_impedance_controller::get_map
  :super ros::object
  :slots ())

(setf (get ros_impedance_controller::get_map :md5sum-) "553343f2b070acab862180c259ba993a")
(setf (get ros_impedance_controller::get_map :datatype-) "ros_impedance_controller/get_map")
(setf (get ros_impedance_controller::get_map :request) ros_impedance_controller::get_mapRequest)
(setf (get ros_impedance_controller::get_map :response) ros_impedance_controller::get_mapResponse)

(defmethod ros_impedance_controller::get_mapRequest
  (:response () (instance ros_impedance_controller::get_mapResponse :init)))

(setf (get ros_impedance_controller::get_mapRequest :md5sum-) "553343f2b070acab862180c259ba993a")
(setf (get ros_impedance_controller::get_mapRequest :datatype-) "ros_impedance_controller/get_mapRequest")
(setf (get ros_impedance_controller::get_mapRequest :definition-)
      "geometry_msgs/Point target
float64 width
float64 length
float64 resolution_x
float64 resolution_y

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
---
uint32 row_length
float64[] height_array



")

(setf (get ros_impedance_controller::get_mapResponse :md5sum-) "553343f2b070acab862180c259ba993a")
(setf (get ros_impedance_controller::get_mapResponse :datatype-) "ros_impedance_controller/get_mapResponse")
(setf (get ros_impedance_controller::get_mapResponse :definition-)
      "geometry_msgs/Point target
float64 width
float64 length
float64 resolution_x
float64 resolution_y

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
---
uint32 row_length
float64[] height_array



")



(provide :ros_impedance_controller/get_map "553343f2b070acab862180c259ba993a")


