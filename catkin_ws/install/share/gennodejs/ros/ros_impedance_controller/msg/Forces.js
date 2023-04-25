// Auto-generated. Do not edit!

// (in-package ros_impedance_controller.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class Forces {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.FL = null;
      this.FR = null;
      this.HL = null;
      this.HR = null;
    }
    else {
      if (initObj.hasOwnProperty('FL')) {
        this.FL = initObj.FL
      }
      else {
        this.FL = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('FR')) {
        this.FR = initObj.FR
      }
      else {
        this.FR = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('HL')) {
        this.HL = initObj.HL
      }
      else {
        this.HL = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('HR')) {
        this.HR = initObj.HR
      }
      else {
        this.HR = new geometry_msgs.msg.Point();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Forces
    // Serialize message field [FL]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.FL, buffer, bufferOffset);
    // Serialize message field [FR]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.FR, buffer, bufferOffset);
    // Serialize message field [HL]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.HL, buffer, bufferOffset);
    // Serialize message field [HR]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.HR, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Forces
    let len;
    let data = new Forces(null);
    // Deserialize message field [FL]
    data.FL = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [FR]
    data.FR = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [HL]
    data.HL = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [HR]
    data.HR = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 96;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_impedance_controller/Forces';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '169e73725854833f10800dd7f11156c8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Point FL
    geometry_msgs/Point FR
    geometry_msgs/Point HL
    geometry_msgs/Point HR
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Forces(null);
    if (msg.FL !== undefined) {
      resolved.FL = geometry_msgs.msg.Point.Resolve(msg.FL)
    }
    else {
      resolved.FL = new geometry_msgs.msg.Point()
    }

    if (msg.FR !== undefined) {
      resolved.FR = geometry_msgs.msg.Point.Resolve(msg.FR)
    }
    else {
      resolved.FR = new geometry_msgs.msg.Point()
    }

    if (msg.HL !== undefined) {
      resolved.HL = geometry_msgs.msg.Point.Resolve(msg.HL)
    }
    else {
      resolved.HL = new geometry_msgs.msg.Point()
    }

    if (msg.HR !== undefined) {
      resolved.HR = geometry_msgs.msg.Point.Resolve(msg.HR)
    }
    else {
      resolved.HR = new geometry_msgs.msg.Point()
    }

    return resolved;
    }
};

module.exports = Forces;
