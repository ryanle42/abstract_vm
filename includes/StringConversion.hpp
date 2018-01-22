#ifndef STRINGCONVERSION_HPP
# define STRINGCONVERSION_HPP

#include "Exceptions.hpp"
#include <cstdint>
#include <string>
#include <limits>

template <class T>
T convertFromString( std::string const &str ) {
  T value;
  std::stringstream ss;

  ss << str;
  ss >> value;
  if (ss.fail()) {
    throw OverflowException();
  }
  return value;
};

template <>
inline int8_t convertFromString( std::string const & str ) {
  int16_t value = convertFromString<int16_t>(str);

  if (
    value > std::numeric_limits<int8_t>::max() || 
    value < std::numeric_limits<int8_t>::min()
  ) {
    throw OverflowException();
  }
  return (int8_t)value;
}

#endif