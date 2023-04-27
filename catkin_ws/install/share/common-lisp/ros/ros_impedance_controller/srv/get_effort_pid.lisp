; Auto-generated. Do not edit!


(cl:in-package ros_impedance_controller-srv)


;//! \htmlinclude get_effort_pid-request.msg.html

(cl:defclass <get_effort_pid-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type (cl:vector cl:string)
   :initform (cl:make-array 0 :element-type 'cl:string :initial-element ""))
   (effort_pid
    :reader effort_pid
    :initarg :effort_pid
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass get_effort_pid-request (<get_effort_pid-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <get_effort_pid-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'get_effort_pid-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-srv:<get_effort_pid-request> is deprecated: use ros_impedance_controller-srv:get_effort_pid-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <get_effort_pid-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:name-val is deprecated.  Use ros_impedance_controller-srv:name instead.")
  (name m))

(cl:ensure-generic-function 'effort_pid-val :lambda-list '(m))
(cl:defmethod effort_pid-val ((m <get_effort_pid-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:effort_pid-val is deprecated.  Use ros_impedance_controller-srv:effort_pid instead.")
  (effort_pid m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <get_effort_pid-request>) ostream)
  "Serializes a message object of type '<get_effort_pid-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'name))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'effort_pid))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'effort_pid))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <get_effort_pid-request>) istream)
  "Deserializes a message object of type '<get_effort_pid-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'name) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'name)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream))))))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'effort_pid) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'effort_pid)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<get_effort_pid-request>)))
  "Returns string type for a service object of type '<get_effort_pid-request>"
  "ros_impedance_controller/get_effort_pidRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'get_effort_pid-request)))
  "Returns string type for a service object of type 'get_effort_pid-request"
  "ros_impedance_controller/get_effort_pidRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<get_effort_pid-request>)))
  "Returns md5sum for a message object of type '<get_effort_pid-request>"
  "dacbeb9e10802487975fb50ccd59728e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'get_effort_pid-request)))
  "Returns md5sum for a message object of type 'get_effort_pid-request"
  "dacbeb9e10802487975fb50ccd59728e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<get_effort_pid-request>)))
  "Returns full string definition for message of type '<get_effort_pid-request>"
  (cl:format cl:nil "string[] name~%float64[] effort_pid~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'get_effort_pid-request)))
  "Returns full string definition for message of type 'get_effort_pid-request"
  (cl:format cl:nil "string[] name~%float64[] effort_pid~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <get_effort_pid-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'name) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'effort_pid) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <get_effort_pid-request>))
  "Converts a ROS message object to a list"
  (cl:list 'get_effort_pid-request
    (cl:cons ':name (name msg))
    (cl:cons ':effort_pid (effort_pid msg))
))
;//! \htmlinclude get_effort_pid-response.msg.html

(cl:defclass <get_effort_pid-response> (roslisp-msg-protocol:ros-message)
  ((ack
    :reader ack
    :initarg :ack
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass get_effort_pid-response (<get_effort_pid-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <get_effort_pid-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'get_effort_pid-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-srv:<get_effort_pid-response> is deprecated: use ros_impedance_controller-srv:get_effort_pid-response instead.")))

(cl:ensure-generic-function 'ack-val :lambda-list '(m))
(cl:defmethod ack-val ((m <get_effort_pid-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:ack-val is deprecated.  Use ros_impedance_controller-srv:ack instead.")
  (ack m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <get_effort_pid-response>) ostream)
  "Serializes a message object of type '<get_effort_pid-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ack) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <get_effort_pid-response>) istream)
  "Deserializes a message object of type '<get_effort_pid-response>"
    (cl:setf (cl:slot-value msg 'ack) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<get_effort_pid-response>)))
  "Returns string type for a service object of type '<get_effort_pid-response>"
  "ros_impedance_controller/get_effort_pidResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'get_effort_pid-response)))
  "Returns string type for a service object of type 'get_effort_pid-response"
  "ros_impedance_controller/get_effort_pidResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<get_effort_pid-response>)))
  "Returns md5sum for a message object of type '<get_effort_pid-response>"
  "dacbeb9e10802487975fb50ccd59728e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'get_effort_pid-response)))
  "Returns md5sum for a message object of type 'get_effort_pid-response"
  "dacbeb9e10802487975fb50ccd59728e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<get_effort_pid-response>)))
  "Returns full string definition for message of type '<get_effort_pid-response>"
  (cl:format cl:nil "bool ack~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'get_effort_pid-response)))
  "Returns full string definition for message of type 'get_effort_pid-response"
  (cl:format cl:nil "bool ack~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <get_effort_pid-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <get_effort_pid-response>))
  "Converts a ROS message object to a list"
  (cl:list 'get_effort_pid-response
    (cl:cons ':ack (ack msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'get_effort_pid)))
  'get_effort_pid-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'get_effort_pid)))
  'get_effort_pid-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'get_effort_pid)))
  "Returns string type for a service object of type '<get_effort_pid>"
  "ros_impedance_controller/get_effort_pid")