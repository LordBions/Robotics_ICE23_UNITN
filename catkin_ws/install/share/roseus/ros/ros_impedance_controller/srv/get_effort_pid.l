;; Auto-generated. Do not edit!


(when (boundp 'ros_impedance_controller::get_effort_pid)
  (if (not (find-package "ROS_IMPEDANCE_CONTROLLER"))
    (make-package "ROS_IMPEDANCE_CONTROLLER"))
  (shadow 'get_effort_pid (find-package "ROS_IMPEDANCE_CONTROLLER")))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GET_EFFORT_PID")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GET_EFFORT_PID"))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GET_EFFORT_PIDREQUEST")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GET_EFFORT_PIDREQUEST"))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::GET_EFFORT_PIDRESPONSE")
  (make-package "ROS_IMPEDANCE_CONTROLLER::GET_EFFORT_PIDRESPONSE"))

(in-package "ROS")





(defclass ros_impedance_controller::get_effort_pidRequest
  :super ros::object
  :slots (_name _effort_pid ))

(defmethod ros_impedance_controller::get_effort_pidRequest
  (:init
   (&key
    ((:name __name) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:effort_pid __effort_pid) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _name __name)
   (setq _effort_pid __effort_pid)
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:effort_pid
   (&optional __effort_pid)
   (if __effort_pid (setq _effort_pid __effort_pid)) _effort_pid)
  (:serialization-length
   ()
   (+
    ;; string[] _name
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _name)) 4
    ;; float64[] _effort_pid
    (* 8    (length _effort_pid)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string[] _name
     (write-long (length _name) s)
     (dolist (elem _name)
       (write-long (length elem) s) (princ elem s)
       )
     ;; float64[] _effort_pid
     (write-long (length _effort_pid) s)
     (dotimes (i (length _effort_pid))
       (sys::poke (elt _effort_pid i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string[] _name
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _name (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _name i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; float64[] _effort_pid
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _effort_pid (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _effort_pid i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(defclass ros_impedance_controller::get_effort_pidResponse
  :super ros::object
  :slots (_ack ))

(defmethod ros_impedance_controller::get_effort_pidResponse
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

(defclass ros_impedance_controller::get_effort_pid
  :super ros::object
  :slots ())

(setf (get ros_impedance_controller::get_effort_pid :md5sum-) "dacbeb9e10802487975fb50ccd59728e")
(setf (get ros_impedance_controller::get_effort_pid :datatype-) "ros_impedance_controller/get_effort_pid")
(setf (get ros_impedance_controller::get_effort_pid :request) ros_impedance_controller::get_effort_pidRequest)
(setf (get ros_impedance_controller::get_effort_pid :response) ros_impedance_controller::get_effort_pidResponse)

(defmethod ros_impedance_controller::get_effort_pidRequest
  (:response () (instance ros_impedance_controller::get_effort_pidResponse :init)))

(setf (get ros_impedance_controller::get_effort_pidRequest :md5sum-) "dacbeb9e10802487975fb50ccd59728e")
(setf (get ros_impedance_controller::get_effort_pidRequest :datatype-) "ros_impedance_controller/get_effort_pidRequest")
(setf (get ros_impedance_controller::get_effort_pidRequest :definition-)
      "string[] name
float64[] effort_pid
---
bool ack

")

(setf (get ros_impedance_controller::get_effort_pidResponse :md5sum-) "dacbeb9e10802487975fb50ccd59728e")
(setf (get ros_impedance_controller::get_effort_pidResponse :datatype-) "ros_impedance_controller/get_effort_pidResponse")
(setf (get ros_impedance_controller::get_effort_pidResponse :definition-)
      "string[] name
float64[] effort_pid
---
bool ack

")



(provide :ros_impedance_controller/get_effort_pid "dacbeb9e10802487975fb50ccd59728e")


