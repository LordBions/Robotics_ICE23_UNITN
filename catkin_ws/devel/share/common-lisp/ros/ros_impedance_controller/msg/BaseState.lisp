; Auto-generated. Do not edit!


(cl:in-package ros_impedance_controller-msg)


;//! \htmlinclude BaseState.msg.html

(cl:defclass <BaseState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pose
    :reader pose
    :initarg :pose
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (twist
    :reader twist
    :initarg :twist
    :type geometry_msgs-msg:Twist
    :initform (cl:make-instance 'geometry_msgs-msg:Twist)))
)

(cl:defclass BaseState (<BaseState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <BaseState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'BaseState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-msg:<BaseState> is deprecated: use ros_impedance_controller-msg:BaseState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <BaseState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:header-val is deprecated.  Use ros_impedance_controller-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pose-val :lambda-list '(m))
(cl:defmethod pose-val ((m <BaseState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:pose-val is deprecated.  Use ros_impedance_controller-msg:pose instead.")
  (pose m))

(cl:ensure-generic-function 'twist-val :lambda-list '(m))
(cl:defmethod twist-val ((m <BaseState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:twist-val is deprecated.  Use ros_impedance_controller-msg:twist instead.")
  (twist m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <BaseState>) ostream)
  "Serializes a message object of type '<BaseState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pose) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'twist) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <BaseState>) istream)
  "Deserializes a message object of type '<BaseState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pose) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'twist) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<BaseState>)))
  "Returns string type for a message object of type '<BaseState>"
  "ros_impedance_controller/BaseState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'BaseState)))
  "Returns string type for a message object of type 'BaseState"
  "ros_impedance_controller/BaseState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<BaseState>)))
  "Returns md5sum for a message object of type '<BaseState>"
  "a296da29623d3a182b44fee95e8415a4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'BaseState)))
  "Returns md5sum for a message object of type 'BaseState"
  "a296da29623d3a182b44fee95e8415a4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<BaseState>)))
  "Returns full string definition for message of type '<BaseState>"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Pose pose~%geometry_msgs/Twist twist~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'BaseState)))
  "Returns full string definition for message of type 'BaseState"
  (cl:format cl:nil "std_msgs/Header header~%geometry_msgs/Pose pose~%geometry_msgs/Twist twist~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/Twist~%# This expresses velocity in free space broken into its linear and angular parts.~%Vector3  linear~%Vector3  angular~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <BaseState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pose))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'twist))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <BaseState>))
  "Converts a ROS message object to a list"
  (cl:list 'BaseState
    (cl:cons ':header (header msg))
    (cl:cons ':pose (pose msg))
    (cl:cons ':twist (twist msg))
))
