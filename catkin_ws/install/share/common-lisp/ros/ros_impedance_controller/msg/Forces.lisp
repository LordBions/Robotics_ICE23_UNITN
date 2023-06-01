; Auto-generated. Do not edit!


(cl:in-package ros_impedance_controller-msg)


;//! \htmlinclude Forces.msg.html

(cl:defclass <Forces> (roslisp-msg-protocol:ros-message)
  ((FL
    :reader FL
    :initarg :FL
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (FR
    :reader FR
    :initarg :FR
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (HL
    :reader HL
    :initarg :HL
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (HR
    :reader HR
    :initarg :HR
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass Forces (<Forces>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Forces>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Forces)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-msg:<Forces> is deprecated: use ros_impedance_controller-msg:Forces instead.")))

(cl:ensure-generic-function 'FL-val :lambda-list '(m))
(cl:defmethod FL-val ((m <Forces>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:FL-val is deprecated.  Use ros_impedance_controller-msg:FL instead.")
  (FL m))

(cl:ensure-generic-function 'FR-val :lambda-list '(m))
(cl:defmethod FR-val ((m <Forces>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:FR-val is deprecated.  Use ros_impedance_controller-msg:FR instead.")
  (FR m))

(cl:ensure-generic-function 'HL-val :lambda-list '(m))
(cl:defmethod HL-val ((m <Forces>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:HL-val is deprecated.  Use ros_impedance_controller-msg:HL instead.")
  (HL m))

(cl:ensure-generic-function 'HR-val :lambda-list '(m))
(cl:defmethod HR-val ((m <Forces>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:HR-val is deprecated.  Use ros_impedance_controller-msg:HR instead.")
  (HR m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Forces>) ostream)
  "Serializes a message object of type '<Forces>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'FL) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'FR) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'HL) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'HR) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Forces>) istream)
  "Deserializes a message object of type '<Forces>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'FL) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'FR) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'HL) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'HR) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Forces>)))
  "Returns string type for a message object of type '<Forces>"
  "ros_impedance_controller/Forces")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Forces)))
  "Returns string type for a message object of type 'Forces"
  "ros_impedance_controller/Forces")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Forces>)))
  "Returns md5sum for a message object of type '<Forces>"
  "169e73725854833f10800dd7f11156c8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Forces)))
  "Returns md5sum for a message object of type 'Forces"
  "169e73725854833f10800dd7f11156c8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Forces>)))
  "Returns full string definition for message of type '<Forces>"
  (cl:format cl:nil "geometry_msgs/Point FL~%geometry_msgs/Point FR~%geometry_msgs/Point HL~%geometry_msgs/Point HR~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Forces)))
  "Returns full string definition for message of type 'Forces"
  (cl:format cl:nil "geometry_msgs/Point FL~%geometry_msgs/Point FR~%geometry_msgs/Point HL~%geometry_msgs/Point HR~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Forces>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'FL))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'FR))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'HL))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'HR))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Forces>))
  "Converts a ROS message object to a list"
  (cl:list 'Forces
    (cl:cons ':FL (FL msg))
    (cl:cons ':FR (FR msg))
    (cl:cons ':HL (HL msg))
    (cl:cons ':HR (HR msg))
))
