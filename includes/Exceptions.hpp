#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <exception>

class OverflowException : public std::exception {

public:

  virtual const char * what() const throw() {
    return "Overflow on a value or operation";
  }

};

class UnderflowException : public std::exception {

public:

  virtual const char * what() const throw() {
    return "Underflow on a value or operation";
  }
  
};

#endif