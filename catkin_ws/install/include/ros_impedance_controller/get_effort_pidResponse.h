// Generated by gencpp from file ros_impedance_controller/get_effort_pidResponse.msg
// DO NOT EDIT!


#ifndef ROS_IMPEDANCE_CONTROLLER_MESSAGE_GET_EFFORT_PIDRESPONSE_H
#define ROS_IMPEDANCE_CONTROLLER_MESSAGE_GET_EFFORT_PIDRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace ros_impedance_controller
{
template <class ContainerAllocator>
struct get_effort_pidResponse_
{
  typedef get_effort_pidResponse_<ContainerAllocator> Type;

  get_effort_pidResponse_()
    : ack(false)  {
    }
  get_effort_pidResponse_(const ContainerAllocator& _alloc)
    : ack(false)  {
  (void)_alloc;
    }



   typedef uint8_t _ack_type;
  _ack_type ack;





  typedef boost::shared_ptr< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> const> ConstPtr;

}; // struct get_effort_pidResponse_

typedef ::ros_impedance_controller::get_effort_pidResponse_<std::allocator<void> > get_effort_pidResponse;

typedef boost::shared_ptr< ::ros_impedance_controller::get_effort_pidResponse > get_effort_pidResponsePtr;
typedef boost::shared_ptr< ::ros_impedance_controller::get_effort_pidResponse const> get_effort_pidResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator1> & lhs, const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator2> & rhs)
{
  return lhs.ack == rhs.ack;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator1> & lhs, const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace ros_impedance_controller

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8f5729177853f34b146e2e57766d4dc2";
  }

  static const char* value(const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8f5729177853f34bULL;
  static const uint64_t static_value2 = 0x146e2e57766d4dc2ULL;
};

template<class ContainerAllocator>
struct DataType< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ros_impedance_controller/get_effort_pidResponse";
  }

  static const char* value(const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool ack\n"
"\n"
;
  }

  static const char* value(const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ack);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct get_effort_pidResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ros_impedance_controller::get_effort_pidResponse_<ContainerAllocator>& v)
  {
    s << indent << "ack: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.ack);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROS_IMPEDANCE_CONTROLLER_MESSAGE_GET_EFFORT_PIDRESPONSE_H
