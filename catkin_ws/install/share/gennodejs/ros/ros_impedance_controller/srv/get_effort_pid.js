// Auto-generated. Do not edit!

// (in-package ros_impedance_controller.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class get_effort_pidRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.name = null;
      this.effort_pid = null;
    }
    else {
      if (initObj.hasOwnProperty('name')) {
        this.name = initObj.name
      }
      else {
        this.name = [];
      }
      if (initObj.hasOwnProperty('effort_pid')) {
        this.effort_pid = initObj.effort_pid
      }
      else {
        this.effort_pid = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type get_effort_pidRequest
    // Serialize message field [name]
    bufferOffset = _arraySerializer.string(obj.name, buffer, bufferOffset, null);
    // Serialize message field [effort_pid]
    bufferOffset = _arraySerializer.float64(obj.effort_pid, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type get_effort_pidRequest
    let len;
    let data = new get_effort_pidRequest(null);
    // Deserialize message field [name]
    data.name = _arrayDeserializer.string(buffer, bufferOffset, null)
    // Deserialize message field [effort_pid]
    data.effort_pid = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    object.name.forEach((val) => {
      length += 4 + _getByteLength(val);
    });
    length += 8 * object.effort_pid.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'ros_impedance_controller/get_effort_pidRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'cb4c22c1f92577e872da1b0bd5fe8258';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string[] name
    float64[] effort_pid
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new get_effort_pidRequest(null);
    if (msg.name !== undefined) {
      resolved.name = msg.name;
    }
    else {
      resolved.name = []
    }

    if (msg.effort_pid !== undefined) {
      resolved.effort_pid = msg.effort_pid;
    }
    else {
      resolved.effort_pid = []
    }

    return resolved;
    }
};

class get_effort_pidResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.ack = null;
    }
    else {
      if (initObj.hasOwnProperty('ack')) {
        this.ack = initObj.ack
      }
      else {
        this.ack = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type get_effort_pidResponse
    // Serialize message field [ack]
    bufferOffset = _serializer.bool(obj.ack, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type get_effort_pidResponse
    let len;
    let data = new get_effort_pidResponse(null);
    // Deserialize message field [ack]
    data.ack = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'ros_impedance_controller/get_effort_pidResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8f5729177853f34b146e2e57766d4dc2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool ack
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new get_effort_pidResponse(null);
    if (msg.ack !== undefined) {
      resolved.ack = msg.ack;
    }
    else {
      resolved.ack = false
    }

    return resolved;
    }
};

module.exports = {
  Request: get_effort_pidRequest,
  Response: get_effort_pidResponse,
  md5sum() { return 'dacbeb9e10802487975fb50ccd59728e'; },
  datatype() { return 'ros_impedance_controller/get_effort_pid'; }
};
