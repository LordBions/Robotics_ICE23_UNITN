// Auto-generated. Do not edit!

// (in-package ros_impedance_controller.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class ContactsState {
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
        this.FL = false;
      }
      if (initObj.hasOwnProperty('FR')) {
        this.FR = initObj.FR
      }
      else {
        this.FR = false;
      }
      if (initObj.hasOwnProperty('HL')) {
        this.HL = initObj.HL
      }
      else {
        this.HL = false;
      }
      if (initObj.hasOwnProperty('HR')) {
        this.HR = initObj.HR
      }
      else {
        this.HR = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ContactsState
    // Serialize message field [FL]
    bufferOffset = _serializer.bool(obj.FL, buffer, bufferOffset);
    // Serialize message field [FR]
    bufferOffset = _serializer.bool(obj.FR, buffer, bufferOffset);
    // Serialize message field [HL]
    bufferOffset = _serializer.bool(obj.HL, buffer, bufferOffset);
    // Serialize message field [HR]
    bufferOffset = _serializer.bool(obj.HR, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ContactsState
    let len;
    let data = new ContactsState(null);
    // Deserialize message field [FL]
    data.FL = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [FR]
    data.FR = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [HL]
    data.HL = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [HR]
    data.HR = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_impedance_controller/ContactsState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9c1b6206dc127b95cf027c31c258fa92';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool FL
    bool FR
    bool HL
    bool HR
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ContactsState(null);
    if (msg.FL !== undefined) {
      resolved.FL = msg.FL;
    }
    else {
      resolved.FL = false
    }

    if (msg.FR !== undefined) {
      resolved.FR = msg.FR;
    }
    else {
      resolved.FR = false
    }

    if (msg.HL !== undefined) {
      resolved.HL = msg.HL;
    }
    else {
      resolved.HL = false
    }

    if (msg.HR !== undefined) {
      resolved.HR = msg.HR;
    }
    else {
      resolved.HR = false
    }

    return resolved;
    }
};

module.exports = ContactsState;
