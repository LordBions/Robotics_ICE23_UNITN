;; Auto-generated. Do not edit!


(when (boundp 'ros_impedance_controller::ContactsState)
  (if (not (find-package "ROS_IMPEDANCE_CONTROLLER"))
    (make-package "ROS_IMPEDANCE_CONTROLLER"))
  (shadow 'ContactsState (find-package "ROS_IMPEDANCE_CONTROLLER")))
(unless (find-package "ROS_IMPEDANCE_CONTROLLER::CONTACTSSTATE")
  (make-package "ROS_IMPEDANCE_CONTROLLER::CONTACTSSTATE"))

(in-package "ROS")
;;//! \htmlinclude ContactsState.msg.html


(defclass ros_impedance_controller::ContactsState
  :super ros::object
  :slots (_FL _FR _HL _HR ))

(defmethod ros_impedance_controller::ContactsState
  (:init
   (&key
    ((:FL __FL) nil)
    ((:FR __FR) nil)
    ((:HL __HL) nil)
    ((:HR __HR) nil)
    )
   (send-super :init)
   (setq _FL __FL)
   (setq _FR __FR)
   (setq _HL __HL)
   (setq _HR __HR)
   self)
  (:FL
   (&optional (__FL :null))
   (if (not (eq __FL :null)) (setq _FL __FL)) _FL)
  (:FR
   (&optional (__FR :null))
   (if (not (eq __FR :null)) (setq _FR __FR)) _FR)
  (:HL
   (&optional (__HL :null))
   (if (not (eq __HL :null)) (setq _HL __HL)) _HL)
  (:HR
   (&optional (__HR :null))
   (if (not (eq __HR :null)) (setq _HR __HR)) _HR)
  (:serialization-length
   ()
   (+
    ;; bool _FL
    1
    ;; bool _FR
    1
    ;; bool _HL
    1
    ;; bool _HR
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _FL
       (if _FL (write-byte -1 s) (write-byte 0 s))
     ;; bool _FR
       (if _FR (write-byte -1 s) (write-byte 0 s))
     ;; bool _HL
       (if _HL (write-byte -1 s) (write-byte 0 s))
     ;; bool _HR
       (if _HR (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _FL
     (setq _FL (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _FR
     (setq _FR (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _HL
     (setq _HL (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _HR
     (setq _HR (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get ros_impedance_controller::ContactsState :md5sum-) "9c1b6206dc127b95cf027c31c258fa92")
(setf (get ros_impedance_controller::ContactsState :datatype-) "ros_impedance_controller/ContactsState")
(setf (get ros_impedance_controller::ContactsState :definition-)
      "bool FL
bool FR
bool HL
bool HR

")



(provide :ros_impedance_controller/ContactsState "9c1b6206dc127b95cf027c31c258fa92")


