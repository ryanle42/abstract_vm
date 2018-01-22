#ifndef IOPERAND_HPP
# define IOPERAND_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdint>

enum eOperandType { Int8, Int16, Int32, Float, Double };

class IOperand {

public:

  virtual ~IOperand( void ) {}
  virtual IOperand const * operator+( IOperand const & rhs ) const = 0;
  virtual IOperand const * operator-( IOperand const & rhs ) const = 0;
  virtual IOperand const * operator*( IOperand const & rhs ) const = 0;
  virtual IOperand const * operator/( IOperand const & rhs ) const = 0;
  virtual IOperand const * operator%( IOperand const & rhs ) const = 0;
  virtual int getPrecision( void ) const = 0;
  virtual eOperandType getType( void ) const = 0;
  virtual std::string const & toString( void ) const = 0;

};

#endif