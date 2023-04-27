// Auto-generated. Do not edit!

// (in-package ros_impedance_controller.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class get_mapRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.target = null;
      this.width = null;
      this.length = null;
      this.resolution_x = null;
      this.resolution_y = null;
    }
    else {
      if (initObj.hasOwnProperty('target')) {
        this.target = initObj.target
      }
      else {
        this.target = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('width')) {
        this.width = initObj.width
      }
      else {
        this.width = 0.0;
      }
      if (initObj.hasOwnProperty('length')) {
        this.length = initObj.length
      }
      else {
        this.length = 0.0;
      }
      if (initObj.hasOwnProperty('resolution_x')) {
        this.resolution_x = initObj.resolution_x
      }
      else {
        this.resolution_x = 0.0;
      }
      if (initObj.hasOwnProperty('resolution_y')) {
        this.resolution_y = initObj.resolution_y
      }
      else {
        this.resolution_y = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type get_mapRequest
    // Serialize message field [target]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.target, buffer, bufferOffset);
    // Serialize message field [width]
    bufferOffset = _serializer.float64(obj.width, buffer, bufferOffset);
    // Serialize message field [length]
    bufferOffset = _serializer.float64(obj.length, buffer, bufferOffset);
    // Serialize message field [resolution_x]
    bufferOffset = _serializer.float64(obj.resolution_x, buffer, bufferOffset);
    // Serialize message field [resolution_y]
    bufferOffset = _serializer.float64(obj.resolution_y, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type get_mapRequest
    let len;
    let data = new get_mapRequest(null);
    // Deserialize message field [target]
    data.target = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [width]
    data.width = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [length]
    data.length = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [resolution_x]
    data.resolution_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [resolution_y]
    data.resolution_y = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 56;
  }

  static datatype() {
    // Returns string type for a service object
    return 'ros_impedance_controller/get_mapRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '85bcadc0901be97a8de14ebd0011dd79';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Point target
    float64 width
    float64 length
    float64 resolution_x
    float64 resolution_y
    
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
    const resolved = new get_mapRequest(null);
    if (msg.target !== undefined) {
      resolved.target = geometry_msgs.msg.Point.Resolve(msg.target)
    }
    else {
      resolved.target = new geometry_msgs.msg.Point()
    }

    if (msg.width !== undefined) {
      resolved.width = msg.width;
    }
    else {
      resolved.width = 0.0
    }

    if (msg.length !== undefined) {
      resolved.length = msg.length;
    }
    else {
      resolved.length = 0.0
    }

    if (msg.resolution_x !== undefined) {
      resolved.resolution_x = msg.resolution_x;
    }
    else {
      resolved.resolution_x = 0.0
    }

    if (msg.resolution_y !== undefined) {
      resolved.resolution_y = msg.resolution_y;
    }
    else {
      resolved.resolution_y = 0.0
    }

    return resolved;
    }
};

class get_mapResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.row_length = null;
      this.height_array = null;
    }
    else {
      if (initObj.hasOwnProperty('row_length')) {
        this.row_length = initObj.row_length
      }
      else {
        this.row_length = 0;
      }
      if (initObj.hasOwnProperty('height_array')) {
        this.height_array = initObj.height_array
      }
      else {
        this.height_array = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type get_mapResponse
    // Serialize message field [row_length]
    bufferOffset = _serializer.uint32(obj.row_length, buffer, bufferOffset);
    // Serialize message field [height_array]
    bufferOffset = _arraySerializer.float64(obj.height_array, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type get_mapResponse
    let len;
    let data = new get_mapResponse(null);
    // Deserialize message field [row_length]
    data.row_length = _deserializer.uint32(buffer, bufferOffset);
    // Deserialize message field [height_array]
    data.height_array = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 8 * object.height_array.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a service object
    return 'ros_impedance_controller/get_mapResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '49739971fa8e8197eab24ddd3b23174c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint32 row_length
    float64[] height_array
    
    
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new get_mapResponse(null);
    if (msg.row_length !== undefined) {
      resolved.row_length = msg.row_length;
    }
    else {
      resolved.row_length = 0
    }

    if (msg.height_array !== undefined) {
      resolved.height_array = msg.height_array;
    }
    else {
      resolved.height_array = []
    }

    return resolved;
    }
};

module.exports = {
  Request: get_mapRequest,
  Response: get_mapResponse,
  md5sum() { return '553343f2b070acab862180c259ba993a'; },
  datatype() { return 'ros_impedance_controller/get_map'; }
};
