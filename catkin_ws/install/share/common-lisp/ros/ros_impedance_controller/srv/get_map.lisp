; Auto-generated. Do not edit!


(cl:in-package ros_impedance_controller-srv)


;//! \htmlinclude get_map-request.msg.html

(cl:defclass <get_map-request> (roslisp-msg-protocol:ros-message)
  ((target
    :reader target
    :initarg :target
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (width
    :reader width
    :initarg :width
    :type cl:float
    :initform 0.0)
   (length
    :reader length
    :initarg :length
    :type cl:float
    :initform 0.0)
   (resolution_x
    :reader resolution_x
    :initarg :resolution_x
    :type cl:float
    :initform 0.0)
   (resolution_y
    :reader resolution_y
    :initarg :resolution_y
    :type cl:float
    :initform 0.0))
)

(cl:defclass get_map-request (<get_map-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <get_map-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'get_map-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-srv:<get_map-request> is deprecated: use ros_impedance_controller-srv:get_map-request instead.")))

(cl:ensure-generic-function 'target-val :lambda-list '(m))
(cl:defmethod target-val ((m <get_map-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:target-val is deprecated.  Use ros_impedance_controller-srv:target instead.")
  (target m))

(cl:ensure-generic-function 'width-val :lambda-list '(m))
(cl:defmethod width-val ((m <get_map-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:width-val is deprecated.  Use ros_impedance_controller-srv:width instead.")
  (width m))

(cl:ensure-generic-function 'length-val :lambda-list '(m))
(cl:defmethod length-val ((m <get_map-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:length-val is deprecated.  Use ros_impedance_controller-srv:length instead.")
  (length m))

(cl:ensure-generic-function 'resolution_x-val :lambda-list '(m))
(cl:defmethod resolution_x-val ((m <get_map-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:resolution_x-val is deprecated.  Use ros_impedance_controller-srv:resolution_x instead.")
  (resolution_x m))

(cl:ensure-generic-function 'resolution_y-val :lambda-list '(m))
(cl:defmethod resolution_y-val ((m <get_map-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:resolution_y-val is deprecated.  Use ros_impedance_controller-srv:resolution_y instead.")
  (resolution_y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <get_map-request>) ostream)
  "Serializes a message object of type '<get_map-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'target) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'width))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'length))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'resolution_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'resolution_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <get_map-request>) istream)
  "Deserializes a message object of type '<get_map-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'target) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'width) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'length) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'resolution_x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'resolution_y) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<get_map-request>)))
  "Returns string type for a service object of type '<get_map-request>"
  "ros_impedance_controller/get_mapRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'get_map-request)))
  "Returns string type for a service object of type 'get_map-request"
  "ros_impedance_controller/get_mapRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<get_map-request>)))
  "Returns md5sum for a message object of type '<get_map-request>"
  "553343f2b070acab862180c259ba993a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'get_map-request)))
  "Returns md5sum for a message object of type 'get_map-request"
  "553343f2b070acab862180c259ba993a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<get_map-request>)))
  "Returns full string definition for message of type '<get_map-request>"
  (cl:format cl:nil "geometry_msgs/Point target~%float64 width~%float64 length~%float64 resolution_x~%float64 resolution_y~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'get_map-request)))
  "Returns full string definition for message of type 'get_map-request"
  (cl:format cl:nil "geometry_msgs/Point target~%float64 width~%float64 length~%float64 resolution_x~%float64 resolution_y~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <get_map-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'target))
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <get_map-request>))
  "Converts a ROS message object to a list"
  (cl:list 'get_map-request
    (cl:cons ':target (target msg))
    (cl:cons ':width (width msg))
    (cl:cons ':length (length msg))
    (cl:cons ':resolution_x (resolution_x msg))
    (cl:cons ':resolution_y (resolution_y msg))
))
;//! \htmlinclude get_map-response.msg.html

(cl:defclass <get_map-response> (roslisp-msg-protocol:ros-message)
  ((row_length
    :reader row_length
    :initarg :row_length
    :type cl:integer
    :initform 0)
   (height_array
    :reader height_array
    :initarg :height_array
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass get_map-response (<get_map-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <get_map-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'get_map-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-srv:<get_map-response> is deprecated: use ros_impedance_controller-srv:get_map-response instead.")))

(cl:ensure-generic-function 'row_length-val :lambda-list '(m))
(cl:defmethod row_length-val ((m <get_map-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:row_length-val is deprecated.  Use ros_impedance_controller-srv:row_length instead.")
  (row_length m))

(cl:ensure-generic-function 'height_array-val :lambda-list '(m))
(cl:defmethod height_array-val ((m <get_map-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-srv:height_array-val is deprecated.  Use ros_impedance_controller-srv:height_array instead.")
  (height_array m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <get_map-response>) ostream)
  "Serializes a message object of type '<get_map-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'row_length)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'row_length)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'row_length)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'row_length)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'height_array))))
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
   (cl:slot-value msg 'height_array))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <get_map-response>) istream)
  "Deserializes a message object of type '<get_map-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'row_length)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'row_length)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'row_length)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'row_length)) (cl:read-byte istream))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'height_array) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'height_array)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<get_map-response>)))
  "Returns string type for a service object of type '<get_map-response>"
  "ros_impedance_controller/get_mapResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'get_map-response)))
  "Returns string type for a service object of type 'get_map-response"
  "ros_impedance_controller/get_mapResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<get_map-response>)))
  "Returns md5sum for a message object of type '<get_map-response>"
  "553343f2b070acab862180c259ba993a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'get_map-response)))
  "Returns md5sum for a message object of type 'get_map-response"
  "553343f2b070acab862180c259ba993a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<get_map-response>)))
  "Returns full string definition for message of type '<get_map-response>"
  (cl:format cl:nil "uint32 row_length~%float64[] height_array~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'get_map-response)))
  "Returns full string definition for message of type 'get_map-response"
  (cl:format cl:nil "uint32 row_length~%float64[] height_array~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <get_map-response>))
  (cl:+ 0
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'height_array) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <get_map-response>))
  "Converts a ROS message object to a list"
  (cl:list 'get_map-response
    (cl:cons ':row_length (row_length msg))
    (cl:cons ':height_array (height_array msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'get_map)))
  'get_map-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'get_map)))
  'get_map-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'get_map)))
  "Returns string type for a service object of type '<get_map>"
  "ros_impedance_controller/get_map")