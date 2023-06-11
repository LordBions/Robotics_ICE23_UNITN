;; Auto-generated. Do not edit!


(when (boundp 'motion::legoTask)
  (if (not (find-package "MOTION"))
    (make-package "MOTION"))
  (shadow 'legoTask (find-package "MOTION")))
(unless (find-package "MOTION::LEGOTASK")
  (make-package "MOTION::LEGOTASK"))

(in-package "ROS")
;;//! \htmlinclude legoTask.msg.html


(defclass motion::legoTask
  :super ros::object
  :slots (_command_id _send_ack _real_robot _w_time _coord_x _coord_y _coord_z _rot_roll _rot_pitch _rot_yaw _gasp_diam _dest_x _dest_y _dest_z _dest_roll _dest_pitch _dest_yaw _ungasp_diam _authkey ))

(defmethod motion::legoTask
  (:init
   (&key
    ((:command_id __command_id) 0)
    ((:send_ack __send_ack) 0)
    ((:real_robot __real_robot) 0)
    ((:w_time __w_time) 0)
    ((:coord_x __coord_x) 0.0)
    ((:coord_y __coord_y) 0.0)
    ((:coord_z __coord_z) 0.0)
    ((:rot_roll __rot_roll) 0.0)
    ((:rot_pitch __rot_pitch) 0.0)
    ((:rot_yaw __rot_yaw) 0.0)
    ((:gasp_diam __gasp_diam) 0.0)
    ((:dest_x __dest_x) 0.0)
    ((:dest_y __dest_y) 0.0)
    ((:dest_z __dest_z) 0.0)
    ((:dest_roll __dest_roll) 0.0)
    ((:dest_pitch __dest_pitch) 0.0)
    ((:dest_yaw __dest_yaw) 0.0)
    ((:ungasp_diam __ungasp_diam) 0.0)
    ((:authkey __authkey) 0)
    )
   (send-super :init)
   (setq _command_id (round __command_id))
   (setq _send_ack (round __send_ack))
   (setq _real_robot (round __real_robot))
   (setq _w_time (round __w_time))
   (setq _coord_x (float __coord_x))
   (setq _coord_y (float __coord_y))
   (setq _coord_z (float __coord_z))
   (setq _rot_roll (float __rot_roll))
   (setq _rot_pitch (float __rot_pitch))
   (setq _rot_yaw (float __rot_yaw))
   (setq _gasp_diam (float __gasp_diam))
   (setq _dest_x (float __dest_x))
   (setq _dest_y (float __dest_y))
   (setq _dest_z (float __dest_z))
   (setq _dest_roll (float __dest_roll))
   (setq _dest_pitch (float __dest_pitch))
   (setq _dest_yaw (float __dest_yaw))
   (setq _ungasp_diam (float __ungasp_diam))
   (setq _authkey (round __authkey))
   self)
  (:command_id
   (&optional __command_id)
   (if __command_id (setq _command_id __command_id)) _command_id)
  (:send_ack
   (&optional __send_ack)
   (if __send_ack (setq _send_ack __send_ack)) _send_ack)
  (:real_robot
   (&optional __real_robot)
   (if __real_robot (setq _real_robot __real_robot)) _real_robot)
  (:w_time
   (&optional __w_time)
   (if __w_time (setq _w_time __w_time)) _w_time)
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
  (:gasp_diam
   (&optional __gasp_diam)
   (if __gasp_diam (setq _gasp_diam __gasp_diam)) _gasp_diam)
  (:dest_x
   (&optional __dest_x)
   (if __dest_x (setq _dest_x __dest_x)) _dest_x)
  (:dest_y
   (&optional __dest_y)
   (if __dest_y (setq _dest_y __dest_y)) _dest_y)
  (:dest_z
   (&optional __dest_z)
   (if __dest_z (setq _dest_z __dest_z)) _dest_z)
  (:dest_roll
   (&optional __dest_roll)
   (if __dest_roll (setq _dest_roll __dest_roll)) _dest_roll)
  (:dest_pitch
   (&optional __dest_pitch)
   (if __dest_pitch (setq _dest_pitch __dest_pitch)) _dest_pitch)
  (:dest_yaw
   (&optional __dest_yaw)
   (if __dest_yaw (setq _dest_yaw __dest_yaw)) _dest_yaw)
  (:ungasp_diam
   (&optional __ungasp_diam)
   (if __ungasp_diam (setq _ungasp_diam __ungasp_diam)) _ungasp_diam)
  (:authkey
   (&optional __authkey)
   (if __authkey (setq _authkey __authkey)) _authkey)
  (:serialization-length
   ()
   (+
    ;; int32 _command_id
    4
    ;; int32 _send_ack
    4
    ;; int32 _real_robot
    4
    ;; int32 _w_time
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
    ;; float64 _gasp_diam
    8
    ;; float64 _dest_x
    8
    ;; float64 _dest_y
    8
    ;; float64 _dest_z
    8
    ;; float64 _dest_roll
    8
    ;; float64 _dest_pitch
    8
    ;; float64 _dest_yaw
    8
    ;; float64 _ungasp_diam
    8
    ;; int32 _authkey
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _command_id
       (write-long _command_id s)
     ;; int32 _send_ack
       (write-long _send_ack s)
     ;; int32 _real_robot
       (write-long _real_robot s)
     ;; int32 _w_time
       (write-long _w_time s)
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
     ;; float64 _gasp_diam
       (sys::poke _gasp_diam (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dest_x
       (sys::poke _dest_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dest_y
       (sys::poke _dest_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dest_z
       (sys::poke _dest_z (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dest_roll
       (sys::poke _dest_roll (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dest_pitch
       (sys::poke _dest_pitch (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dest_yaw
       (sys::poke _dest_yaw (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _ungasp_diam
       (sys::poke _ungasp_diam (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _authkey
       (write-long _authkey s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _command_id
     (setq _command_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _send_ack
     (setq _send_ack (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _real_robot
     (setq _real_robot (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _w_time
     (setq _w_time (sys::peek buf ptr- :integer)) (incf ptr- 4)
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
   ;; float64 _gasp_diam
     (setq _gasp_diam (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dest_x
     (setq _dest_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dest_y
     (setq _dest_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dest_z
     (setq _dest_z (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dest_roll
     (setq _dest_roll (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dest_pitch
     (setq _dest_pitch (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dest_yaw
     (setq _dest_yaw (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _ungasp_diam
     (setq _ungasp_diam (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _authkey
     (setq _authkey (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get motion::legoTask :md5sum-) "decb1f5b883745a241107ee3a143d2b8")
(setf (get motion::legoTask :datatype-) "motion/legoTask")
(setf (get motion::legoTask :definition-)
      "int32 command_id
int32 send_ack
int32 real_robot
int32 w_time
float64 coord_x
float64 coord_y
float64 coord_z
float64 rot_roll
float64 rot_pitch
float64 rot_yaw
float64 gasp_diam
float64 dest_x
float64 dest_y
float64 dest_z
float64 dest_roll
float64 dest_pitch
float64 dest_yaw
float64 ungasp_diam
int32 authkey

")



(provide :motion/legoTask "decb1f5b883745a241107ee3a143d2b8")


