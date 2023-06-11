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

class legoTask {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.command_id = null;
      this.send_ack = null;
      this.real_robot = null;
      this.w_time = null;
      this.coord_x = null;
      this.coord_y = null;
      this.coord_z = null;
      this.rot_roll = null;
      this.rot_pitch = null;
      this.rot_yaw = null;
      this.gasp_diam = null;
      this.dest_x = null;
      this.dest_y = null;
      this.dest_z = null;
      this.dest_roll = null;
      this.dest_pitch = null;
      this.dest_yaw = null;
      this.ungasp_diam = null;
      this.authkey = null;
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
      if (initObj.hasOwnProperty('real_robot')) {
        this.real_robot = initObj.real_robot
      }
      else {
        this.real_robot = 0;
      }
      if (initObj.hasOwnProperty('w_time')) {
        this.w_time = initObj.w_time
      }
      else {
        this.w_time = 0;
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
      if (initObj.hasOwnProperty('gasp_diam')) {
        this.gasp_diam = initObj.gasp_diam
      }
      else {
        this.gasp_diam = 0.0;
      }
      if (initObj.hasOwnProperty('dest_x')) {
        this.dest_x = initObj.dest_x
      }
      else {
        this.dest_x = 0.0;
      }
      if (initObj.hasOwnProperty('dest_y')) {
        this.dest_y = initObj.dest_y
      }
      else {
        this.dest_y = 0.0;
      }
      if (initObj.hasOwnProperty('dest_z')) {
        this.dest_z = initObj.dest_z
      }
      else {
        this.dest_z = 0.0;
      }
      if (initObj.hasOwnProperty('dest_roll')) {
        this.dest_roll = initObj.dest_roll
      }
      else {
        this.dest_roll = 0.0;
      }
      if (initObj.hasOwnProperty('dest_pitch')) {
        this.dest_pitch = initObj.dest_pitch
      }
      else {
        this.dest_pitch = 0.0;
      }
      if (initObj.hasOwnProperty('dest_yaw')) {
        this.dest_yaw = initObj.dest_yaw
      }
      else {
        this.dest_yaw = 0.0;
      }
      if (initObj.hasOwnProperty('ungasp_diam')) {
        this.ungasp_diam = initObj.ungasp_diam
      }
      else {
        this.ungasp_diam = 0.0;
      }
      if (initObj.hasOwnProperty('authkey')) {
        this.authkey = initObj.authkey
      }
      else {
        this.authkey = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type legoTask
    // Serialize message field [command_id]
    bufferOffset = _serializer.int32(obj.command_id, buffer, bufferOffset);
    // Serialize message field [send_ack]
    bufferOffset = _serializer.int32(obj.send_ack, buffer, bufferOffset);
    // Serialize message field [real_robot]
    bufferOffset = _serializer.int32(obj.real_robot, buffer, bufferOffset);
    // Serialize message field [w_time]
    bufferOffset = _serializer.int32(obj.w_time, buffer, bufferOffset);
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
    // Serialize message field [gasp_diam]
    bufferOffset = _serializer.float64(obj.gasp_diam, buffer, bufferOffset);
    // Serialize message field [dest_x]
    bufferOffset = _serializer.float64(obj.dest_x, buffer, bufferOffset);
    // Serialize message field [dest_y]
    bufferOffset = _serializer.float64(obj.dest_y, buffer, bufferOffset);
    // Serialize message field [dest_z]
    bufferOffset = _serializer.float64(obj.dest_z, buffer, bufferOffset);
    // Serialize message field [dest_roll]
    bufferOffset = _serializer.float64(obj.dest_roll, buffer, bufferOffset);
    // Serialize message field [dest_pitch]
    bufferOffset = _serializer.float64(obj.dest_pitch, buffer, bufferOffset);
    // Serialize message field [dest_yaw]
    bufferOffset = _serializer.float64(obj.dest_yaw, buffer, bufferOffset);
    // Serialize message field [ungasp_diam]
    bufferOffset = _serializer.float64(obj.ungasp_diam, buffer, bufferOffset);
    // Serialize message field [authkey]
    bufferOffset = _serializer.int32(obj.authkey, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type legoTask
    let len;
    let data = new legoTask(null);
    // Deserialize message field [command_id]
    data.command_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [send_ack]
    data.send_ack = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [real_robot]
    data.real_robot = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [w_time]
    data.w_time = _deserializer.int32(buffer, bufferOffset);
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
    // Deserialize message field [gasp_diam]
    data.gasp_diam = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dest_x]
    data.dest_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dest_y]
    data.dest_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dest_z]
    data.dest_z = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dest_roll]
    data.dest_roll = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dest_pitch]
    data.dest_pitch = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dest_yaw]
    data.dest_yaw = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [ungasp_diam]
    data.ungasp_diam = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [authkey]
    data.authkey = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 132;
  }

  static datatype() {
    // Returns string type for a message object
    return 'motion/legoTask';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'decb1f5b883745a241107ee3a143d2b8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 command_id
    int32 send_ack
    int32 real_robot
    int32 w_time
    float64 coord_x
    float64 coord_y
    float64 coord_z
    float64 rot_roll
    float64 rot_pitch
    float64 rot_yaw
    float64 gasp_diam
    float64 dest_x
    float64 dest_y
    float64 dest_z
    float64 dest_roll
    float64 dest_pitch
    float64 dest_yaw
    float64 ungasp_diam
    int32 authkey
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new legoTask(null);
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

    if (msg.real_robot !== undefined) {
      resolved.real_robot = msg.real_robot;
    }
    else {
      resolved.real_robot = 0
    }

    if (msg.w_time !== undefined) {
      resolved.w_time = msg.w_time;
    }
    else {
      resolved.w_time = 0
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

    if (msg.gasp_diam !== undefined) {
      resolved.gasp_diam = msg.gasp_diam;
    }
    else {
      resolved.gasp_diam = 0.0
    }

    if (msg.dest_x !== undefined) {
      resolved.dest_x = msg.dest_x;
    }
    else {
      resolved.dest_x = 0.0
    }

    if (msg.dest_y !== undefined) {
      resolved.dest_y = msg.dest_y;
    }
    else {
      resolved.dest_y = 0.0
    }

    if (msg.dest_z !== undefined) {
      resolved.dest_z = msg.dest_z;
    }
    else {
      resolved.dest_z = 0.0
    }

    if (msg.dest_roll !== undefined) {
      resolved.dest_roll = msg.dest_roll;
    }
    else {
      resolved.dest_roll = 0.0
    }

    if (msg.dest_pitch !== undefined) {
      resolved.dest_pitch = msg.dest_pitch;
    }
    else {
      resolved.dest_pitch = 0.0
    }

    if (msg.dest_yaw !== undefined) {
      resolved.dest_yaw = msg.dest_yaw;
    }
    else {
      resolved.dest_yaw = 0.0
    }

    if (msg.ungasp_diam !== undefined) {
      resolved.ungasp_diam = msg.ungasp_diam;
    }
    else {
      resolved.ungasp_diam = 0.0
    }

    if (msg.authkey !== undefined) {
      resolved.authkey = msg.authkey;
    }
    else {
      resolved.authkey = 0
    }

    return resolved;
    }
};

module.exports = legoTask;
