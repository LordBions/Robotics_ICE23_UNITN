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

class eventResult {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.event_id = null;
      this.result_id = null;
      this.authkey = null;
    }
    else {
      if (initObj.hasOwnProperty('event_id')) {
        this.event_id = initObj.event_id
      }
      else {
        this.event_id = 0;
      }
      if (initObj.hasOwnProperty('result_id')) {
        this.result_id = initObj.result_id
      }
      else {
        this.result_id = 0;
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
    // Serializes a message object of type eventResult
    // Serialize message field [event_id]
    bufferOffset = _serializer.int32(obj.event_id, buffer, bufferOffset);
    // Serialize message field [result_id]
    bufferOffset = _serializer.int32(obj.result_id, buffer, bufferOffset);
    // Serialize message field [authkey]
    bufferOffset = _serializer.int32(obj.authkey, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type eventResult
    let len;
    let data = new eventResult(null);
    // Deserialize message field [event_id]
    data.event_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [result_id]
    data.result_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [authkey]
    data.authkey = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'motion/eventResult';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c7c4d92529537e5f02f61be920fd1adf';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 event_id
    int32 result_id
    int32 authkey
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new eventResult(null);
    if (msg.event_id !== undefined) {
      resolved.event_id = msg.event_id;
    }
    else {
      resolved.event_id = 0
    }

    if (msg.result_id !== undefined) {
      resolved.result_id = msg.result_id;
    }
    else {
      resolved.result_id = 0
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

module.exports = eventResult;
