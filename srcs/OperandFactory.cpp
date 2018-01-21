#include "OperandFactory.hpp"

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
) const {
  switch(type) {
    case eOperandType::Int8:
      return this->createInt8(value);
    default:
      return NULL;
  }
  return NULL;
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const {
  IOperand * ret = new Operand<int8_t>(convertFromString<int8_t>(value));
  return ret;
}