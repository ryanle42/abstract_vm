#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"

template <class T>
class Operand : public IOperand {

public:

  Operand<T>( T const value ) : _value(_value) {}
  Operand<T>( Operand<T> const & src ) : _value(src._value) {}
  ~Operand<T>( void ) {}

  Operand<T> & operator=( Operand<T> const & rhs ) {
    this->_value = rhs._value;
    return *this;
  }

  IOperand const * operator+( IOperand const & rhs ) const;
  IOperand const * operator-( IOperand const & rhs ) const;
  IOperand const * operator*( IOperand const & rhs ) const;
  IOperand const * operator/( IOperand const & rhs ) const;
  IOperand const * operator%( IOperand const & rhs ) const;
  
  eOperandType getType( void ) const;
  int getPrecision( void ) const {
    return this->getType();
  }

  std::string const & toString( void ) const {
    std::stringstream ss;
    std::string * str;

    ss << this->_value;
    str = new std::string(ss.str());
    return *str;
  }

private:

  T _value;
  Operand<T>( void ) : _value(0) {}

};

template <>
inline eOperandType Operand<int8_t>::getType( void ) const {
  return eOperandType::Int8;
}

template <>
inline eOperandType Operand<int16_t>::getType( void ) const {
  return eOperandType::Int16;
}

template <>
inline eOperandType Operand<int32_t>::getType( void ) const {
  return eOperandType::Int32;
}

template <>
inline eOperandType Operand<float>::getType( void ) const {
  return eOperandType::Float;
}

template <>
inline eOperandType Operand<double>::getType( void ) const {
  return eOperandType::Double;
}

#endif