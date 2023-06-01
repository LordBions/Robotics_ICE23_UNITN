;; Auto-generated. Do not edit!


(when (boundp 'ros_impedance_controller::pid)
  (if (not (find-package "ROS_IMPEDANCE_CONTROLLER"))
    (make-package "ROS_IMPEDANCE_CONTROLLER"))
  (shadow 'pid (find-package "ROS_IMPEDANCE_CONTROLLER")))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::PID")
  (make-package "ROS_IMPEDANCE_CONTROLLER::PID"))

(in-package "ROS")
;;//! \htmlinclude pid.msg.html


(defclass ros_impedance_controller::pid
  :super ros::object
  :slots (_joint_name _p_value _i_value _d_value ))

(defmethod ros_impedance_controller::pid
  (:init
   (&key
    ((:joint_name __joint_name) "")
    ((:p_value __p_value) 0.0)
    ((:i_value __i_value) 0.0)
    ((:d_value __d_value) 0.0)
    )
   (send-super :init)
   (setq _joint_name (string __joint_name))
   (setq _p_value (float __p_value))
   (setq _i_value (float __i_value))
   (setq _d_value (float __d_value))
   self)
  (:joint_name
   (&optional __joint_name)
   (if __joint_name (setq _joint_name __joint_name)) _joint_name)
  (:p_value
   (&optional __p_value)
   (if __p_value (setq _p_value __p_value)) _p_value)
  (:i_value
   (&optional __i_value)
   (if __i_value (setq _i_value __i_value)) _i_value)
  (:d_value
   (&optional __d_value)
   (if __d_value (setq _d_value __d_value)) _d_value)
  (:serialization-length
   ()
   (+
    ;; string _joint_name
    4 (length _joint_name)
    ;; float32 _p_value
    4
    ;; float32 _i_value
    4
    ;; float32 _d_value
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _joint_name
       (write-long (length _joint_name) s) (princ _joint_name s)
     ;; float32 _p_value
       (sys::poke _p_value (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _i_value
       (sys::poke _i_value (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _d_value
       (sys::poke _d_value (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _joint_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _joint_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32 _p_value
     (setq _p_value (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _i_value
     (setq _i_value (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _d_value
     (setq _d_value (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get ros_impedance_controller::pid :md5sum-) "e3368fa16036af8f3c3db35abdf0a2df")
(setf (get ros_impedance_controller::pid :datatype-) "ros_impedance_controller/pid")
(setf (get ros_impedance_controller::pid :definition-)
      "string joint_name
float32 p_value
float32 i_value
float32 d_value

")



(provide :ros_impedance_controller/pid "e3368fa16036af8f3c3db35abdf0a2df")


