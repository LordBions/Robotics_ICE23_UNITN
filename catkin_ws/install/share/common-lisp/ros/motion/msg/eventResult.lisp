; Auto-generated. Do not edit!


(cl:in-package motion-msg)


;//! \htmlinclude eventResult.msg.html

(cl:defclass <eventResult> (roslisp-msg-protocol:ros-message)
  ((event_id
    :reader event_id
    :initarg :event_id
    :type cl:integer
    :initform 0)
   (result_id
    :reader result_id
    :initarg :result_id
    :type cl:integer
    :initform 0)
   (extra_data
    :reader extra_data
    :initarg :extra_data
    :type cl:integer
    :initform 0))
)

(cl:defclass eventResult (<eventResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <eventResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'eventResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name motion-msg:<eventResult> is deprecated: use motion-msg:eventResult instead.")))

(cl:ensure-generic-function 'event_id-val :lambda-list '(m))
(cl:defmethod event_id-val ((m <eventResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motion-msg:event_id-val is deprecated.  Use motion-msg:event_id instead.")
  (event_id m))

(cl:ensure-generic-function 'result_id-val :lambda-list '(m))
(cl:defmethod result_id-val ((m <eventResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motion-msg:result_id-val is deprecated.  Use motion-msg:result_id instead.")
  (result_id m))

(cl:ensure-generic-function 'extra_data-val :lambda-list '(m))
(cl:defmethod extra_data-val ((m <eventResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motion-msg:extra_data-val is deprecated.  Use motion-msg:extra_data instead.")
  (extra_data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <eventResult>) ostream)
  "Serializes a message object of type '<eventResult>"
  (cl:let* ((signed (cl:slot-value msg 'event_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'result_id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'extra_data)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <eventResult>) istream)
  "Deserializes a message object of type '<eventResult>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'event_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'result_id) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'extra_data) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<eventResult>)))
  "Returns string type for a message object of type '<eventResult>"
  "motion/eventResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'eventResult)))
  "Returns string type for a message object of type 'eventResult"
  "motion/eventResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<eventResult>)))
  "Returns md5sum for a message object of type '<eventResult>"
  "fd180d3fc58646647eb38b5dc3a7407b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'eventResult)))
  "Returns md5sum for a message object of type 'eventResult"
  "fd180d3fc58646647eb38b5dc3a7407b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<eventResult>)))
  "Returns full string definition for message of type '<eventResult>"
  (cl:format cl:nil "int32 event_id~%int32 result_id~%int32 extra_data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'eventResult)))
  "Returns full string definition for message of type 'eventResult"
  (cl:format cl:nil "int32 event_id~%int32 result_id~%int32 extra_data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <eventResult>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <eventResult>))
  "Converts a ROS message object to a list"
  (cl:list 'eventResult
    (cl:cons ':event_id (event_id msg))
    (cl:cons ':result_id (result_id msg))
    (cl:cons ':extra_data (extra_data msg))
))
