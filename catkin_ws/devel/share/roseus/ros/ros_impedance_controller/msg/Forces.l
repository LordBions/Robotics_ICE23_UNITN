;; Auto-generated. Do not edit!


(when (boundp 'ros_impedance_controller::Forces)
  (if (not (find-package "ROS_IMPEDANCE_CONTROLLER"))
    (make-package "ROS_IMPEDANCE_CONTROLLER"))
  (shadow 'Forces (find-package "ROS_IMPEDANCE_CONTROLLER")))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::FORCES")
  (make-package "ROS_IMPEDANCE_CONTROLLER::FORCES"))

(in-package "ROS")
;;//! \htmlinclude Forces.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass ros_impedance_controller::Forces
  :super ros::object
  :slots (_FL _FR _HL _HR ))

(defmethod ros_impedance_controller::Forces
  (:init
   (&key
    ((:FL __FL) (instance geometry_msgs::Point :init))
    ((:FR __FR) (instance geometry_msgs::Point :init))
    ((:HL __HL) (instance geometry_msgs::Point :init))
    ((:HR __HR) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _FL __FL)
   (setq _FR __FR)
   (setq _HL __HL)
   (setq _HR __HR)
   self)
  (:FL
   (&rest __FL)
   (if (keywordp (car __FL))
       (send* _FL __FL)
     (progn
       (if __FL (setq _FL (car __FL)))
       _FL)))
  (:FR
   (&rest __FR)
   (if (keywordp (car __FR))
       (send* _FR __FR)
     (progn
       (if __FR (setq _FR (car __FR)))
       _FR)))
  (:HL
   (&rest __HL)
   (if (keywordp (car __HL))
       (send* _HL __HL)
     (progn
       (if __HL (setq _HL (car __HL)))
       _HL)))
  (:HR
   (&rest __HR)
   (if (keywordp (car __HR))
       (send* _HR __HR)
     (progn
       (if __HR (setq _HR (car __HR)))
       _HR)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _FL
    (send _FL :serialization-length)
    ;; geometry_msgs/Point _FR
    (send _FR :serialization-length)
    ;; geometry_msgs/Point _HL
    (send _HL :serialization-length)
    ;; geometry_msgs/Point _HR
    (send _HR :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _FL
       (send _FL :serialize s)
     ;; geometry_msgs/Point _FR
       (send _FR :serialize s)
     ;; geometry_msgs/Point _HL
       (send _HL :serialize s)
     ;; geometry_msgs/Point _HR
       (send _HR :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _FL
     (send _FL :deserialize buf ptr-) (incf ptr- (send _FL :serialization-length))
   ;; geometry_msgs/Point _FR
     (send _FR :deserialize buf ptr-) (incf ptr- (send _FR :serialization-length))
   ;; geometry_msgs/Point _HL
     (send _HL :deserialize buf ptr-) (incf ptr- (send _HL :serialization-length))
   ;; geometry_msgs/Point _HR
     (send _HR :deserialize buf ptr-) (incf ptr- (send _HR :serialization-length))
   ;;
   self)
  )

(setf (get ros_impedance_controller::Forces :md5sum-) "169e73725854833f10800dd7f11156c8")
(setf (get ros_impedance_controller::Forces :datatype-) "ros_impedance_controller/Forces")
(setf (get ros_impedance_controller::Forces :definition-)
      "geometry_msgs/Point FL
geometry_msgs/Point FR
geometry_msgs/Point HL
geometry_msgs/Point HR

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :ros_impedance_controller/Forces "169e73725854833f10800dd7f11156c8")


