; Auto-generated. Do not edit!


(cl:in-package ros_impedance_controller-srv)


;//! \htmlinclude set_pids-request.msg.html

(cl:defclass <set_pids-request> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type (cl:vector ros_impedance_controller-msg:pid)
   :initform (cl:make-array 0 :element-type 'ros_impedance_controller-msg:pid :initial-element (cl:make-instance 'ros_impedance_controller-msg:pid))))
)

(cl:defclass set_pids-request (<set_pids-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <set_pids-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'set_pids-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-srv:<set_pids-request> is deprecated: use ros_impedance_controller-srv:set_pids-request instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <set_pids-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:data-val is deprecated.  Use ros_impedance_controller-srv:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <set_pids-request>) ostream)
  "Serializes a message object of type '<set_pids-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <set_pids-request>) istream)
  "Deserializes a message object of type '<set_pids-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'ros_impedance_controller-msg:pid))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<set_pids-request>)))
  "Returns string type for a service object of type '<set_pids-request>"
  "ros_impedance_controller/set_pidsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_pids-request)))
  "Returns string type for a service object of type 'set_pids-request"
  "ros_impedance_controller/set_pidsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<set_pids-request>)))
  "Returns md5sum for a message object of type '<set_pids-request>"
  "8b825b98503459e2c6dd4e723c0dcb96")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'set_pids-request)))
  "Returns md5sum for a message object of type 'set_pids-request"
  "8b825b98503459e2c6dd4e723c0dcb96")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<set_pids-request>)))
  "Returns full string definition for message of type '<set_pids-request>"
  (cl:format cl:nil "pid[] data~%~%================================================================================~%MSG: ros_impedance_controller/pid~%string joint_name~%float32 p_value~%float32 i_value~%float32 d_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'set_pids-request)))
  "Returns full string definition for message of type 'set_pids-request"
  (cl:format cl:nil "pid[] data~%~%================================================================================~%MSG: ros_impedance_controller/pid~%string joint_name~%float32 p_value~%float32 i_value~%float32 d_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <set_pids-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <set_pids-request>))
  "Converts a ROS message object to a list"
  (cl:list 'set_pids-request
    (cl:cons ':data (data msg))
))
;//! \htmlinclude set_pids-response.msg.html

(cl:defclass <set_pids-response> (roslisp-msg-protocol:ros-message)
  ((ack
    :reader ack
    :initarg :ack
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass set_pids-response (<set_pids-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <set_pids-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'set_pids-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-srv:<set_pids-response> is deprecated: use ros_impedance_controller-srv:set_pids-response instead.")))

(cl:ensure-generic-function 'ack-val :lambda-list '(m))
(cl:defmethod ack-val ((m <set_pids-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:ack-val is deprecated.  Use ros_impedance_controller-srv:ack instead.")
  (ack m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <set_pids-response>) ostream)
  "Serializes a message object of type '<set_pids-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'ack) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <set_pids-response>) istream)
  "Deserializes a message object of type '<set_pids-response>"
    (cl:setf (cl:slot-value msg 'ack) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<set_pids-response>)))
  "Returns string type for a service object of type '<set_pids-response>"
  "ros_impedance_controller/set_pidsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_pids-response)))
  "Returns string type for a service object of type 'set_pids-response"
  "ros_impedance_controller/set_pidsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<set_pids-response>)))
  "Returns md5sum for a message object of type '<set_pids-response>"
  "8b825b98503459e2c6dd4e723c0dcb96")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'set_pids-response)))
  "Returns md5sum for a message object of type 'set_pids-response"
  "8b825b98503459e2c6dd4e723c0dcb96")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<set_pids-response>)))
  "Returns full string definition for message of type '<set_pids-response>"
  (cl:format cl:nil "bool ack~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'set_pids-response)))
  "Returns full string definition for message of type 'set_pids-response"
  (cl:format cl:nil "bool ack~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <set_pids-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <set_pids-response>))
  "Converts a ROS message object to a list"
  (cl:list 'set_pids-response
    (cl:cons ':ack (ack msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'set_pids)))
  'set_pids-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'set_pids)))
  'set_pids-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'set_pids)))
  "Returns string type for a service object of type '<set_pids>"
  "ros_impedance_controller/set_pids")