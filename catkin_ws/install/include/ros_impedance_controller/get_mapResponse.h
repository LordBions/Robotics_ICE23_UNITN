// Generated by gencpp from file ros_impedance_controller/get_mapResponse.msg
// DO NOT EDIT!


#ifndef ROS_IMPEDANCE_CONTROLLER_MESSAGE_GET_MAPRESPONSE_H
#define ROS_IMPEDANCE_CONTROLLER_MESSAGE_GET_MAPRESPONSE_H


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
struct get_mapResponse_
{
  typedef get_mapResponse_<ContainerAllocator> Type;

  get_mapResponse_()
    : row_length(0)
    , height_array()  {
    }
  get_mapResponse_(const ContainerAllocator& _alloc)
    : row_length(0)
    , height_array(_alloc)  {
  (void)_alloc;
    }



   typedef uint32_t _row_length_type;
  _row_length_type row_length;

   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _height_array_type;
  _height_array_type height_array;





  typedef boost::shared_ptr< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> const> ConstPtr;

}; // struct get_mapResponse_

typedef ::ros_impedance_controller::get_mapResponse_<std::allocator<void> > get_mapResponse;

typedef boost::shared_ptr< ::ros_impedance_controller::get_mapResponse > get_mapResponsePtr;
typedef boost::shared_ptr< ::ros_impedance_controller::get_mapResponse const> get_mapResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator1> & lhs, const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator2> & rhs)
{
  return lhs.row_length == rhs.row_length &&
    lhs.height_array == rhs.height_array;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator1> & lhs, const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace ros_impedance_controller

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "49739971fa8e8197eab24ddd3b23174c";
  }

  static const char* value(const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x49739971fa8e8197ULL;
  static const uint64_t static_value2 = 0xeab24ddd3b23174cULL;
};

template<class ContainerAllocator>
struct DataType< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ros_impedance_controller/get_mapResponse";
  }

  static const char* value(const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint32 row_length\n"
"float64[] height_array\n"
"\n"
"\n"
"\n"
;
  }

  static const char* value(const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.row_length);
      stream.next(m.height_array);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct get_mapResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ros_impedance_controller::get_mapResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::ros_impedance_controller::get_mapResponse_<ContainerAllocator>& v)
  {
    s << indent << "row_length: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.row_length);
    s << indent << "height_array[]" << std::endl;
    for (size_t i = 0; i < v.height_array.size(); ++i)
    {
      s << indent << "  height_array[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.height_array[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROS_IMPEDANCE_CONTROLLER_MESSAGE_GET_MAPRESPONSE_H
