// Auto-generated. Do not edit!

// (in-package motion.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class legoFound {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.command_id = null;
      this.send_ack = null;
      this.lego_class = null;
      this.coord_x = null;
      this.coord_y = null;
      this.coord_z = null;
      this.rot_roll = null;
      this.rot_pitch = null;
      this.rot_yaw = null;
    }
    else {
      if (initObj.hasOwnProperty('command_id')) {
        this.command_id = initObj.command_id
      }
      else {
        this.command_id = 0;
      }
      if (initObj.hasOwnProperty('send_ack')) {
        this.send_ack = initObj.send_ack
      }
      else {
        this.send_ack = 0;
      }
      if (initObj.hasOwnProperty('lego_class')) {
        this.lego_class = initObj.lego_class
      }
      else {
        this.lego_class = 0;
      }
      if (initObj.hasOwnProperty('coord_x')) {
        this.coord_x = initObj.coord_x
      }
      else {
        this.coord_x = 0.0;
      }
      if (initObj.hasOwnProperty('coord_y')) {
        this.coord_y = initObj.coord_y
      }
      else {
        this.coord_y = 0.0;
      }
      if (initObj.hasOwnProperty('coord_z')) {
        this.coord_z = initObj.coord_z
      }
      else {
        this.coord_z = 0.0;
      }
      if (initObj.hasOwnProperty('rot_roll')) {
        this.rot_roll = initObj.rot_roll
      }
      else {
        this.rot_roll = 0.0;
      }
      if (initObj.hasOwnProperty('rot_pitch')) {
        this.rot_pitch = initObj.rot_pitch
      }
      else {
        this.rot_pitch = 0.0;
      }
      if (initObj.hasOwnProperty('rot_yaw')) {
        this.rot_yaw = initObj.rot_yaw
      }
      else {
        this.rot_yaw = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type legoFound
    // Serialize message field [command_id]
    bufferOffset = _serializer.int32(obj.command_id, buffer, bufferOffset);
    // Serialize message field [send_ack]
    bufferOffset = _serializer.int32(obj.send_ack, buffer, bufferOffset);
    // Serialize message field [lego_class]
    bufferOffset = _serializer.int32(obj.lego_class, buffer, bufferOffset);
    // Serialize message field [coord_x]
    bufferOffset = _serializer.float64(obj.coord_x, buffer, bufferOffset);
    // Serialize message field [coord_y]
    bufferOffset = _serializer.float64(obj.coord_y, buffer, bufferOffset);
    // Serialize message field [coord_z]
    bufferOffset = _serializer.float64(obj.coord_z, buffer, bufferOffset);
    // Serialize message field [rot_roll]
    bufferOffset = _serializer.float64(obj.rot_roll, buffer, bufferOffset);
    // Serialize message field [rot_pitch]
    bufferOffset = _serializer.float64(obj.rot_pitch, buffer, bufferOffset);
    // Serialize message field [rot_yaw]
    bufferOffset = _serializer.float64(obj.rot_yaw, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type legoFound
    let len;
    let data = new legoFound(null);
    // Deserialize message field [command_id]
    data.command_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [send_ack]
    data.send_ack = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [lego_class]
    data.lego_class = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [coord_x]
    data.coord_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [coord_y]
    data.coord_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [coord_z]
    data.coord_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rot_roll]
    data.rot_roll = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rot_pitch]
    data.rot_pitch = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [rot_yaw]
    data.rot_yaw = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 60;
  }

  static datatype() {
    // Returns string type for a message object
    return 'motion/legoFound';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '045b9797291f5ffb29a17a6c98e3287e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 command_id
    int32 send_ack
    int32 lego_class
    float64 coord_x
    float64 coord_y
    float64 coord_z
    float64 rot_roll
    float64 rot_pitch
    float64 rot_yaw
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new legoFound(null);
    if (msg.command_id !== undefined) {
      resolved.command_id = msg.command_id;
    }
    else {
      resolved.command_id = 0
    }

    if (msg.send_ack !== undefined) {
      resolved.send_ack = msg.send_ack;
    }
    else {
      resolved.send_ack = 0
    }

    if (msg.lego_class !== undefined) {
      resolved.lego_class = msg.lego_class;
    }
    else {
      resolved.lego_class = 0
    }

    if (msg.coord_x !== undefined) {
      resolved.coord_x = msg.coord_x;
    }
    else {
      resolved.coord_x = 0.0
    }

    if (msg.coord_y !== undefined) {
      resolved.coord_y = msg.coord_y;
    }
    else {
      resolved.coord_y = 0.0
    }

    if (msg.coord_z !== undefined) {
      resolved.coord_z = msg.coord_z;
    }
    else {
      resolved.coord_z = 0.0
    }

    if (msg.rot_roll !== undefined) {
      resolved.rot_roll = msg.rot_roll;
    }
    else {
      resolved.rot_roll = 0.0
    }

    if (msg.rot_pitch !== undefined) {
      resolved.rot_pitch = msg.rot_pitch;
    }
    else {
      resolved.rot_pitch = 0.0
    }

    if (msg.rot_yaw !== undefined) {
      resolved.rot_yaw = msg.rot_yaw;
    }
    else {
      resolved.rot_yaw = 0.0
    }

    return resolved;
    }
};

module.exports = legoFound;
