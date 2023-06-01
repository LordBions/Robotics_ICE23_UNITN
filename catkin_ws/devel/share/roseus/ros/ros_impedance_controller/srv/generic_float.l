;; Auto-generated. Do not edit!


(when (boundp 'ros_impedance_controller::generic_float)
  (if (not (find-package "ROS_IMPEDANCE_CONTROLLER"))
    (make-package "ROS_IMPEDANCE_CONTROLLER"))
  (shadow 'generic_float (find-package "ROS_IMPEDANCE_CONTROLLER")))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GENERIC_FLOAT")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GENERIC_FLOAT"))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GENERIC_FLOATREQUEST")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GENERIC_FLOATREQUEST"))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GENERIC_FLOATRESPONSE")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GENERIC_FLOATRESPONSE"))

(in-package "ROS")





(defclass ros_impedance_controller::generic_floatRequest
  :super ros::object
  :slots (_data ))

(defmethod ros_impedance_controller::generic_floatRequest
  (:init
   (&key
    ((:data __data) 0.0)
    )
   (send-super :init)
   (setq _data (float __data))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; float64 _data
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _data
       (sys::poke _data (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _data
     (setq _data (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(defclass ros_impedance_controller::generic_floatResponse
  :super ros::object
  :slots (_ack ))

(defmethod ros_impedance_controller::generic_floatResponse
  (:init
   (&key
    ((:ack __ack) nil)
    )
   (send-super :init)
   (setq _ack __ack)
   self)
  (:ack
   (&optional (__ack :null))
   (if (not (eq __ack :null)) (setq _ack __ack)) _ack)
  (:serialization-length
   ()
   (+
    ;; bool _ack
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _ack
       (if _ack (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _ack
     (setq _ack (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass ros_impedance_controller::generic_float
  :super ros::object
  :slots ())

(setf (get ros_impedance_controller::generic_float :md5sum-) "28f45893a01d82a5ea9c839d84112d68")
(setf (get ros_impedance_controller::generic_float :datatype-) "ros_impedance_controller/generic_float")
(setf (get ros_impedance_controller::generic_float :request) ros_impedance_controller::generic_floatRequest)
(setf (get ros_impedance_controller::generic_float :response) ros_impedance_controller::generic_floatResponse)

(defmethod ros_impedance_controller::generic_floatRequest
  (:response () (instance ros_impedance_controller::generic_floatResponse :init)))

(setf (get ros_impedance_controller::generic_floatRequest :md5sum-) "28f45893a01d82a5ea9c839d84112d68")
(setf (get ros_impedance_controller::generic_floatRequest :datatype-) "ros_impedance_controller/generic_floatRequest")
(setf (get ros_impedance_controller::generic_floatRequest :definition-)
      "float64 data
---
bool ack

")

(setf (get ros_impedance_controller::generic_floatResponse :md5sum-) "28f45893a01d82a5ea9c839d84112d68")
(setf (get ros_impedance_controller::generic_floatResponse :datatype-) "ros_impedance_controller/generic_floatResponse")
(setf (get ros_impedance_controller::generic_floatResponse :definition-)
      "float64 data
---
bool ack

")



(provide :ros_impedance_controller/generic_float "28f45893a01d82a5ea9c839d84112d68")


