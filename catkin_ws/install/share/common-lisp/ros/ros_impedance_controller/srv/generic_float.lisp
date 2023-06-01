; Auto-generated. Do not edit!


(cl:in-package ros_impedance_controller-srv)


;//! \htmlinclude generic_float-request.msg.html

(cl:defclass <generic_float-request> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type cl:float
    :initform 0.0))
)

(cl:defclass generic_float-request (<generic_float-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <generic_float-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'generic_float-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-srv:<generic_float-request> is deprecated: use ros_impedance_controller-srv:generic_float-request instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <generic_float-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:data-val is deprecated.  Use ros_impedance_controller-srv:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <generic_float-request>) ostream)
  "Serializes a message object of type '<generic_float-request>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <generic_float-request>) istream)
  "Deserializes a message object of type '<generic_float-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'data) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<generic_float-request>)))
  "Returns string type for a service object of type '<generic_float-request>"
  "ros_impedance_controller/generic_floatRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'generic_float-request)))
  "Returns string type for a service object of type 'generic_float-request"
  "ros_impedance_controller/generic_floatRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<generic_float-request>)))
  "Returns md5sum for a message object of type '<generic_float-request>"
  "28f45893a01d82a5ea9c839d84112d68")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'generic_float-request)))
  "Returns md5sum for a message object of type 'generic_float-request"
  "28f45893a01d82a5ea9c839d84112d68")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<generic_float-request>)))
  "Returns full string definition for message of type '<generic_float-request>"
  (cl:format cl:nil "float64 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'generic_float-request)))
  "Returns full string definition for message of type 'generic_float-request"
  (cl:format cl:nil "float64 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <generic_float-request>))
  (cl:+ 0
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <generic_float-request>))
  "Converts a ROS message object to a list"
  (cl:list 'generic_float-request
    (cl:cons ':data (data msg))
))
;//! \htmlinclude generic_float-response.msg.html

(cl:defclass <generic_float-response> (roslisp-msg-protocol:ros-message)
  ((ack
    :reader ack
    :initarg :ack
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass generic_float-response (<generic_float-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <generic_float-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'generic_float-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-srv:<generic_float-response> is deprecated: use ros_impedance_controller-srv:generic_float-response instead.")))

(cl:ensure-generic-function 'ack-val :lambda-list '(m))
(cl:defmethod ack-val ((m <generic_float-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:ack-val is deprecated.  Use ros_impedance_controller-srv:ack instead.")
  (ack m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <generic_float-response>) ostream)
  "Serializes a message object of type '<generic_float-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ack) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <generic_float-response>) istream)
  "Deserializes a message object of type '<generic_float-response>"
    (cl:setf (cl:slot-value msg 'ack) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<generic_float-response>)))
  "Returns string type for a service object of type '<generic_float-response>"
  "ros_impedance_controller/generic_floatResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'generic_float-response)))
  "Returns string type for a service object of type 'generic_float-response"
  "ros_impedance_controller/generic_floatResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<generic_float-response>)))
  "Returns md5sum for a message object of type '<generic_float-response>"
  "28f45893a01d82a5ea9c839d84112d68")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'generic_float-response)))
  "Returns md5sum for a message object of type 'generic_float-response"
  "28f45893a01d82a5ea9c839d84112d68")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<generic_float-response>)))
  "Returns full string definition for message of type '<generic_float-response>"
  (cl:format cl:nil "bool ack~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'generic_float-response)))
  "Returns full string definition for message of type 'generic_float-response"
  (cl:format cl:nil "bool ack~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <generic_float-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <generic_float-response>))
  "Converts a ROS message object to a list"
  (cl:list 'generic_float-response
    (cl:cons ':ack (ack msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'generic_float)))
  'generic_float-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'generic_float)))
  'generic_float-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'generic_float)))
  "Returns string type for a service object of type '<generic_float>"
  "ros_impedance_controller/generic_float")