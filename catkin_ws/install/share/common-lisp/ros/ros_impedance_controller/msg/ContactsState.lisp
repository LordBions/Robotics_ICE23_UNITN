; Auto-generated. Do not edit!


(cl:in-package ros_impedance_controller-msg)


;//! \htmlinclude ContactsState.msg.html

(cl:defclass <ContactsState> (roslisp-msg-protocol:ros-message)
  ((FL
    :reader FL
    :initarg :FL
    :type cl:boolean
    :initform cl:nil)
   (FR
    :reader FR
    :initarg :FR
    :type cl:boolean
    :initform cl:nil)
   (HL
    :reader HL
    :initarg :HL
    :type cl:boolean
    :initform cl:nil)
   (HR
    :reader HR
    :initarg :HR
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass ContactsState (<ContactsState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ContactsState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ContactsState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_impedance_controller-msg:<ContactsState> is deprecated: use ros_impedance_controller-msg:ContactsState instead.")))

(cl:ensure-generic-function 'FL-val :lambda-list '(m))
(cl:defmethod FL-val ((m <ContactsState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:FL-val is deprecated.  Use ros_impedance_controller-msg:FL instead.")
  (FL m))

(cl:ensure-generic-function 'FR-val :lambda-list '(m))
(cl:defmethod FR-val ((m <ContactsState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:FR-val is deprecated.  Use ros_impedance_controller-msg:FR instead.")
  (FR m))

(cl:ensure-generic-function 'HL-val :lambda-list '(m))
(cl:defmethod HL-val ((m <ContactsState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:HL-val is deprecated.  Use ros_impedance_controller-msg:HL instead.")
  (HL m))

(cl:ensure-generic-function 'HR-val :lambda-list '(m))
(cl:defmethod HR-val ((m <ContactsState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_impedance_controller-msg:HR-val is deprecated.  Use ros_impedance_controller-msg:HR instead.")
  (HR m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ContactsState>) ostream)
  "Serializes a message object of type '<ContactsState>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'FL) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'FR) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'HL) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'HR) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ContactsState>) istream)
  "Deserializes a message object of type '<ContactsState>"
    (cl:setf (cl:slot-value msg 'FL) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'FR) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'HL) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'HR) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ContactsState>)))
  "Returns string type for a message object of type '<ContactsState>"
  "ros_impedance_controller/ContactsState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ContactsState)))
  "Returns string type for a message object of type 'ContactsState"
  "ros_impedance_controller/ContactsState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ContactsState>)))
  "Returns md5sum for a message object of type '<ContactsState>"
  "9c1b6206dc127b95cf027c31c258fa92")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ContactsState)))
  "Returns md5sum for a message object of type 'ContactsState"
  "9c1b6206dc127b95cf027c31c258fa92")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ContactsState>)))
  "Returns full string definition for message of type '<ContactsState>"
  (cl:format cl:nil "bool FL~%bool FR~%bool HL~%bool HR~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ContactsState)))
  "Returns full string definition for message of type 'ContactsState"
  (cl:format cl:nil "bool FL~%bool FR~%bool HL~%bool HR~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ContactsState>))
  (cl:+ 0
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ContactsState>))
  "Converts a ROS message object to a list"
  (cl:list 'ContactsState
    (cl:cons ':FL (FL msg))
    (cl:cons ':FR (FR msg))
    (cl:cons ':HL (HL msg))
    (cl:cons ':HR (HR msg))
))
