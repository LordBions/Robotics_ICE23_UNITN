;; Auto-generated. Do not edit!


(when (boundp 'motion::legoFound)
  (if (not (find-package "MOTION"))
    (make-package "MOTION"))
  (shadow 'legoFound (find-package "MOTION")))
(unless (find-package "MOTION::LEGOFOUND")
  (make-package "MOTION::LEGOFOUND"))

(in-package "ROS")
;;//! \htmlinclude legoFound.msg.html


(defclass motion::legoFound
  :super ros::object
  :slots (_command_id _send_ack _lego_class _coord_x _coord_y _coord_z _rot_roll _rot_pitch _rot_yaw ))

(defmethod motion::legoFound
  (:init
   (&key
    ((:command_id __command_id) 0)
    ((:send_ack __send_ack) 0)
    ((:lego_class __lego_class) 0)
    ((:coord_x __coord_x) 0.0)
    ((:coord_y __coord_y) 0.0)
    ((:coord_z __coord_z) 0.0)
    ((:rot_roll __rot_roll) 0.0)
    ((:rot_pitch __rot_pitch) 0.0)
    ((:rot_yaw __rot_yaw) 0.0)
    )
   (send-super :init)
   (setq _command_id (round __command_id))
   (setq _send_ack (round __send_ack))
   (setq _lego_class (round __lego_class))
   (setq _coord_x (float __coord_x))
   (setq _coord_y (float __coord_y))
   (setq _coord_z (float __coord_z))
   (setq _rot_roll (float __rot_roll))
   (setq _rot_pitch (float __rot_pitch))
   (setq _rot_yaw (float __rot_yaw))
   self)
  (:command_id
   (&optional __command_id)
   (if __command_id (setq _command_id __command_id)) _command_id)
  (:send_ack
   (&optional __send_ack)
   (if __send_ack (setq _send_ack __send_ack)) _send_ack)
  (:lego_class
   (&optional __lego_class)
   (if __lego_class (setq _lego_class __lego_class)) _lego_class)
  (:coord_x
   (&optional __coord_x)
   (if __coord_x (setq _coord_x __coord_x)) _coord_x)
  (:coord_y
   (&optional __coord_y)
   (if __coord_y (setq _coord_y __coord_y)) _coord_y)
  (:coord_z
   (&optional __coord_z)
   (if __coord_z (setq _coord_z __coord_z)) _coord_z)
  (:rot_roll
   (&optional __rot_roll)
   (if __rot_roll (setq _rot_roll __rot_roll)) _rot_roll)
  (:rot_pitch
   (&optional __rot_pitch)
   (if __rot_pitch (setq _rot_pitch __rot_pitch)) _rot_pitch)
  (:rot_yaw
   (&optional __rot_yaw)
   (if __rot_yaw (setq _rot_yaw __rot_yaw)) _rot_yaw)
  (:serialization-length
   ()
   (+
    ;; int32 _command_id
    4
    ;; int32 _send_ack
    4
    ;; int32 _lego_class
    4
    ;; float64 _coord_x
    8
    ;; float64 _coord_y
    8
    ;; float64 _coord_z
    8
    ;; float64 _rot_roll
    8
    ;; float64 _rot_pitch
    8
    ;; float64 _rot_yaw
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _command_id
       (write-long _command_id s)
     ;; int32 _send_ack
       (write-long _send_ack s)
     ;; int32 _lego_class
       (write-long _lego_class s)
     ;; float64 _coord_x
       (sys::poke _coord_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _coord_y
       (sys::poke _coord_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _coord_z
       (sys::poke _coord_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rot_roll
       (sys::poke _rot_roll (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rot_pitch
       (sys::poke _rot_pitch (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _rot_yaw
       (sys::poke _rot_yaw (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _command_id
     (setq _command_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _send_ack
     (setq _send_ack (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _lego_class
     (setq _lego_class (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _coord_x
     (setq _coord_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _coord_y
     (setq _coord_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _coord_z
     (setq _coord_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rot_roll
     (setq _rot_roll (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rot_pitch
     (setq _rot_pitch (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _rot_yaw
     (setq _rot_yaw (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get motion::legoFound :md5sum-) "045b9797291f5ffb29a17a6c98e3287e")
(setf (get motion::legoFound :datatype-) "motion/legoFound")
(setf (get motion::legoFound :definition-)
      "int32 command_id
int32 send_ack
int32 lego_class
float64 coord_x
float64 coord_y
float64 coord_z
float64 rot_roll
float64 rot_pitch
float64 rot_yaw

")



(provide :motion/legoFound "045b9797291f5ffb29a17a6c98e3287e")


