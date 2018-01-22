#ifndef STRINGCONVERSION_HPP
# define STRINGCONVERSION_HPP

#include "Exceptions.hpp"

template <class T>
T convertFromString(std::string const &str) {
  T value;
  std::stringstream ss;

  ss << str;
  ss >> value;
  if (ss.fail()) {
    throw OverflowException();
  }
  return value;
};

#endif