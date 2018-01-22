#include "OperandFactory.hpp"
#include <iostream>

OperandFactory::OperandFactory( void ) {
  return ;
}

OperandFactory::OperandFactory( OperandFactory const & src  ) {
  (void)src;
  return ;
}

OperandFactory::~OperandFactory( void ) {
  return ;
}

OperandFactory & OperandFactory::operator=( OperandFactory const & rhs ) {
  (void)rhs;
  return *this;
}

IOperand const * OperandFactory::createOperand( 
  eOperandType type, 
  std::string const & value 
) const 
{
  switch(type) {
    case Int8:
      return this->createInt8(value);
    case Int16:
      return this->createInt16(value);
    case Int32:
      return this->createInt32(value);
    case Float:
      return this->createFloat(value);
    case Double:
      return this->createDouble(value);
    default:
      return NULL;
  }
  return NULL;
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const {
  return new Operand<int8_t>(convertFromString<int8_t>(value));
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const {
  return new Operand<int16_t>(convertFromString<int16_t>(value));
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const {
  return new Operand<int32_t>(convertFromString<int32_t>(value));
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const {
  return new Operand<float>(convertFromString<float>(value));
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const {
  return new Operand<double>(convertFromString<double>(value));
}