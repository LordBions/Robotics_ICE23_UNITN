; Auto-generated. Do not edit!


(cl:in-package ros_impedance_controller-msg)


;//! \htmlinclude pid.msg.html

(cl:defclass <pid> (roslisp-msg-protocol:ros-message)
  ((joint_name
    :reader joint_name
    :initarg :joint_name
    :type cl:string
    :initform "")
   (p_value
    :reader p_value
    :initarg :p_value
    :type cl:float
    :initform 0.0)
   (i_value
    :reader i_value
    :initarg :i_value
    :type cl:float
    :initform 0.0)
   (d_value
    :reader d_value
    :initarg :d_value
    :type cl:float
    :initform 0.0))
)

(cl:defclass pid (<pid>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pid>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pid)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-msg:<pid> is deprecated: use ros_impedance_controller-msg:pid instead.")))

(cl:ensure-generic-function 'joint_name-val :lambda-list '(m))
(cl:defmethod joint_name-val ((m <pid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:joint_name-val is deprecated.  Use ros_impedance_controller-msg:joint_name instead.")
  (joint_name m))

(cl:ensure-generic-function 'p_value-val :lambda-list '(m))
(cl:defmethod p_value-val ((m <pid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:p_value-val is deprecated.  Use ros_impedance_controller-msg:p_value instead.")
  (p_value m))

(cl:ensure-generic-function 'i_value-val :lambda-list '(m))
(cl:defmethod i_value-val ((m <pid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:i_value-val is deprecated.  Use ros_impedance_controller-msg:i_value instead.")
  (i_value m))

(cl:ensure-generic-function 'd_value-val :lambda-list '(m))
(cl:defmethod d_value-val ((m <pid>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:d_value-val is deprecated.  Use ros_impedance_controller-msg:d_value instead.")
  (d_value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pid>) ostream)
  "Serializes a message object of type '<pid>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'joint_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'joint_name))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'p_value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'i_value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'd_value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pid>) istream)
  "Deserializes a message object of type '<pid>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'joint_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'joint_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'p_value) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'i_value) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'd_value) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pid>)))
  "Returns string type for a message object of type '<pid>"
  "ros_impedance_controller/pid")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pid)))
  "Returns string type for a message object of type 'pid"
  "ros_impedance_controller/pid")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pid>)))
  "Returns md5sum for a message object of type '<pid>"
  "e3368fa16036af8f3c3db35abdf0a2df")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pid)))
  "Returns md5sum for a message object of type 'pid"
  "e3368fa16036af8f3c3db35abdf0a2df")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pid>)))
  "Returns full string definition for message of type '<pid>"
  (cl:format cl:nil "string joint_name~%float32 p_value~%float32 i_value~%float32 d_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pid)))
  "Returns full string definition for message of type 'pid"
  (cl:format cl:nil "string joint_name~%float32 p_value~%float32 i_value~%float32 d_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pid>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'joint_name))
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pid>))
  "Converts a ROS message object to a list"
  (cl:list 'pid
    (cl:cons ':joint_name (joint_name msg))
    (cl:cons ':p_value (p_value msg))
    (cl:cons ':i_value (i_value msg))
    (cl:cons ':d_value (d_value msg))
))
