;; Auto-generated. Do not edit!


(when (boundp 'ros_impedance_controller::set_pids)
  (if (not (find-package "ROS_IMPEDANCE_CONTROLLER"))
    (make-package "ROS_IMPEDANCE_CONTROLLER"))
  (shadow 'set_pids (find-package "ROS_IMPEDANCE_CONTROLLER")))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::SET_PIDS")
  (make-package "ROS_IMPEDANCE_CONTROLLER::SET_PIDS"))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::SET_PIDSREQUEST")
  (make-package "ROS_IMPEDANCE_CONTROLLER::SET_PIDSREQUEST"))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::SET_PIDSRESPONSE")
  (make-package "ROS_IMPEDANCE_CONTROLLER::SET_PIDSRESPONSE"))

(in-package "ROS")





(defclass ros_impedance_controller::set_pidsRequest
  :super ros::object
  :slots (_data ))

(defmethod ros_impedance_controller::set_pidsRequest
  (:init
   (&key
    ((:data __data) ())
    )
   (send-super :init)
   (setq _data __data)
   self)
  (:data
   (&rest __data)
   (if (keywordp (car __data))
       (send* _data __data)
     (progn
       (if __data (setq _data (car __data)))
       _data)))
  (:serialization-length
   ()
   (+
    ;; ros_impedance_controller/pid[] _data
    (apply #'+ (send-all _data :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; ros_impedance_controller/pid[] _data
     (write-long (length _data) s)
     (dolist (elem _data)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; ros_impedance_controller/pid[] _data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _data (let (r) (dotimes (i n) (push (instance ros_impedance_controller::pid :init) r)) r))
     (dolist (elem- _data)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(defclass ros_impedance_controller::set_pidsResponse
  :super ros::object
  :slots (_ack ))

(defmethod ros_impedance_controller::set_pidsResponse
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

(defclass ros_impedance_controller::set_pids
  :super ros::object
  :slots ())

(setf (get ros_impedance_controller::set_pids :md5sum-) "8b825b98503459e2c6dd4e723c0dcb96")
(setf (get ros_impedance_controller::set_pids :datatype-) "ros_impedance_controller/set_pids")
(setf (get ros_impedance_controller::set_pids :request) ros_impedance_controller::set_pidsRequest)
(setf (get ros_impedance_controller::set_pids :response) ros_impedance_controller::set_pidsResponse)

(defmethod ros_impedance_controller::set_pidsRequest
  (:response () (instance ros_impedance_controller::set_pidsResponse :init)))

(setf (get ros_impedance_controller::set_pidsRequest :md5sum-) "8b825b98503459e2c6dd4e723c0dcb96")
(setf (get ros_impedance_controller::set_pidsRequest :datatype-) "ros_impedance_controller/set_pidsRequest")
(setf (get ros_impedance_controller::set_pidsRequest :definition-)
      "pid[] data

================================================================================
MSG: ros_impedance_controller/pid
string joint_name
float32 p_value
float32 i_value
float32 d_value
---
bool ack

")

(setf (get ros_impedance_controller::set_pidsResponse :md5sum-) "8b825b98503459e2c6dd4e723c0dcb96")
(setf (get ros_impedance_controller::set_pidsResponse :datatype-) "ros_impedance_controller/set_pidsResponse")
(setf (get ros_impedance_controller::set_pidsResponse :definition-)
      "pid[] data

================================================================================
MSG: ros_impedance_controller/pid
string joint_name
float32 p_value
float32 i_value
float32 d_value
---
bool ack

")



(provide :ros_impedance_controller/set_pids "8b825b98503459e2c6dd4e723c0dcb96")


