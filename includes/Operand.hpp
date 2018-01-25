#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "IOperand.hpp"
#include "Exceptions.hpp"
#include <cstdint>
#include <cmath>
#include <limits>

template <class T>
T convertOperand(IOperand const * operand);

template <class T>
IOperand * add(IOperand const & lhs, IOperand const & rhs);

template <class T>
IOperand * sub(IOperand const & lhs, IOperand const & rhs);

template <class T>
IOperand * mult(IOperand const & lhs, IOperand const & rhs);

template <class T>
IOperand * divide(IOperand const & lhs, IOperand const & rhs);

template <class T>
IOperand * mod(IOperand const & lhs, IOperand const & rhs);

template <class T>
class Operand : public IOperand {

public:

  Operand<T>( T const value ) : _value(value) {}
  Operand<T>( Operand<T> const & src ) : _value(src._value) {}
  ~Operand<T>( void ) {}

  Operand<T> & operator=( Operand<T> const & rhs ) {
    this->_value = rhs._value;
    return *this;
  }

  IOperand const * operator+( IOperand const & rhs ) const {
    int precision = std::max(this->getPrecision(), rhs.getPrecision());

    switch(precision) {
      case Int8:
        return add<int8_t>(*this, rhs);
      case Int16:
        return add<int16_t>(*this, rhs);
      case Int32:
        return add<int32_t>(*this, rhs);
      case Float:
        return add<float>(*this, rhs);
      case Double:
        return add<double>(*this, rhs);
      default:
        throw InvalidIOperandException();
    }
  }

  IOperand const * operator-( IOperand const & rhs ) const {
    int precision = std::max(this->getPrecision(), rhs.getPrecision());

    switch(precision) {
      case Int8:
        return sub<int8_t>(*this, rhs);
      case Int16:
        return sub<int16_t>(*this, rhs);
      case Int32:
        return sub<int32_t>(*this, rhs);
      case Float:
        return sub<float>(*this, rhs);
      case Double:
        return sub<double>(*this, rhs);
      default:
        throw InvalidIOperandException();
    }
  }

  IOperand const * operator*( IOperand const & rhs ) const {
    int precision = std::max(this->getPrecision(), rhs.getPrecision());

    switch(precision) {
      case Int8:
        return mult<int8_t>(*this, rhs);
      case Int16:
        return mult<int16_t>(*this, rhs);
      case Int32:
        return mult<int32_t>(*this, rhs);
      case Float:
        return mult<float>(*this, rhs);
      case Double:
        return mult<double>(*this, rhs);
      default:
        throw InvalidIOperandException();
    }
  }

  IOperand const * operator/( IOperand const & rhs ) const {
    int precision = std::max(this->getPrecision(), rhs.getPrecision());

    switch(precision) {
      case Int8:
        return divide<int8_t>(*this, rhs);
      case Int16:
        return divide<int16_t>(*this, rhs);
      case Int32:
        return divide<int32_t>(*this, rhs);
      case Float:
        return divide<float>(*this, rhs);
      case Double:
        return divide<double>(*this, rhs);
      default:
        throw InvalidIOperandException();
    }
  }
  
  IOperand const * operator%( IOperand const & rhs ) const {
    int precision = std::max(this->getPrecision(), rhs.getPrecision());

    switch(precision) {
      case Int8:
        return mod<int8_t>(*this, rhs);
      case Int16:
        return mod<int16_t>(*this, rhs);
      case Int32:
        return mod<int32_t>(*this, rhs);
      case Float:
        return mod<float>(*this, rhs);
      case Double:
        return mod<double>(*this, rhs);
      default:
        throw InvalidIOperandException();
    }
  }
  
  eOperandType getType( void ) const;
  int getPrecision( void ) const {
    return this->getType();
  }

  T getValue( void ) const {
    return _value;
  }

  std::string const & toString( void ) const {
    std::stringstream ss;
    std::string *str;

    if (this->getType() == Int8) {
      ss << static_cast<int16_t>(this->_value);
    } else {
      ss << this->_value;
    }
    str = new std::string(ss.str());
    return *str;
  }

private:

  T _value;
  Operand<T>( void ) : _value(0) {}

};

template <>
inline eOperandType Operand<int8_t>::getType( void ) const {
  return Int8;
}

template <>
inline eOperandType Operand<int16_t>::getType( void ) const {
  return Int16;
}

template <>
inline eOperandType Operand<int32_t>::getType( void ) const {
  return Int32;
}

template <>
inline eOperandType Operand<float>::getType( void ) const {
  return Float;
}

template <>
inline eOperandType Operand<double>::getType( void ) const {
  return Double;
}

template <class T>
T convertOperand(IOperand const * operand) {
  switch (operand->getPrecision()) {
    case Int8:
      return ((Operand<int8_t>*)operand)->getValue();
    case Int16:
      return ((Operand<int16_t>*)operand)->getValue();
    case Int32:
      return ((Operand<int32_t>*)operand)->getValue();
    case Float:
      return ((Operand<float>*)operand)->getValue();
    case Double:
      return ((Operand<double>*)operand)->getValue();
    default:
      throw InvalidIOperandException();
  }
}

template <class T>
IOperand * add(IOperand const & lhs, IOperand const & rhs) {
  T left = convertOperand<T>(&lhs);
  T right = convertOperand<T>(&rhs);

  if (
    std::numeric_limits<T>::is_signed
    && std::numeric_limits<T>::is_integer
  ) {
    if (right > 0) {
      if (std::numeric_limits<T>::max() - right < left)
        throw OverflowException();
    } else {
      if (std::numeric_limits<T>::min() - right > left)
        throw UnderflowException();
    }
  }
  return new Operand<T>(left + right);
}

template <class T>
IOperand * sub(IOperand const & lhs, IOperand const & rhs) {
  T left = convertOperand<T>(&lhs);
  T right = convertOperand<T>(&rhs);

  if (
    std::numeric_limits<T>::is_signed
    && std::numeric_limits<T>::is_integer
  ) {
    if (right > 0) {
      if (std::numeric_limits<T>::min() + right > left) {
        throw UnderflowException();
      }
    } else if (std::numeric_limits<T>::max() + right < left) {
      throw OverflowException();
    }
  }
  return new Operand<T>(left - right);
}

template <class T>
IOperand * mult(IOperand const & lhs, IOperand const & rhs) {
  T left = convertOperand<T>(&lhs);
  T right = convertOperand<T>(&rhs);

  if (left != 0) {
    if ((left > 0) == (right > 0)) {
      if (std::numeric_limits<T>::max() / left < right) {
        throw OverflowException();
      }
    } else {
      if (left > 0) {
        if (std::numeric_limits<T>::min() / left > right) {
          throw UnderflowException();
        }
      } else {
        if (std::numeric_limits<T>::min() / left < right) {
          throw UnderflowException();
        }
      }
    }
  }
  if (
    (left == -1 && right == std::numeric_limits<T>::min()) || 
    (right == -1 && left == std::numeric_limits<T>::min())
  ) {
    throw OverflowException();
  }
  return new Operand<T>(left * right);
}

template <>
inline IOperand *mult<float>(IOperand const &lhs, IOperand const &rhs) {
    float left = convertOperand<float>(&lhs);
    float right = convertOperand<float>(&rhs);
    float result = left * right;

    if (std::isinf(result)) {
      throw OverflowException();
    }
    return new Operand<float>(result);
}

template <>
inline IOperand *mult<double>(IOperand const &lhs, IOperand const &rhs) {
    double left = convertOperand<double>(&lhs);
    double right = convertOperand<double>(&rhs);
    double result = left * right;

    if (std::isinf(result)) {
      throw OverflowException();
    }
    return new Operand<double>(result);
}


template <class T>
IOperand * divide(IOperand const & lhs, IOperand const & rhs) {
  T left = convertOperand<T>(&lhs);
  T right = convertOperand<T>(&rhs);

  if (right == 0) {
    throw DivideByZeroException();
  }
  if (right == -1 && left == std::numeric_limits<T>::min()) {
    throw OverflowException();
  }
  return new Operand<T>(left / right);
}

template <class T>
IOperand * mod(IOperand const & lhs, IOperand const & rhs) {
  T left = convertOperand<T>(&lhs);
  T right = convertOperand<T>(&rhs);

  if (right == 0) {
    throw DivideByZeroException();
  }
  return new Operand<T>(fmod(left, right));
}

#endif