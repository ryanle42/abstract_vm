#ifndef OPERANDFACTORY_HPP
# define OPERANDFACTORY_HPP

#include "Operand.hpp"
#include "Exceptions.hpp"
#include "StringConversion.hpp"

class OperandFactory {

public:

  OperandFactory( void );
  OperandFactory( OperandFactory const & src );
  ~OperandFactory( void );
  OperandFactory & operator=( OperandFactory const & rhs );
  IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:

  IOperand const * createInt8( std::string const & value ) const;
  IOperand const * createInt16( std::string const & value ) const;
  IOperand const * createInt32( std::string const & value ) const;
  IOperand const * createFloat( std::string const & value ) const;
  IOperand const * createDouble( std::string const & value ) const;

};

#endif