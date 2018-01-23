#include "VirtualMachine.hpp"
VirtualMachine::VirtualMachine( void ) {
  return ;
}

VirtualMachine::VirtualMachine( VirtualMachine const & src ) :
  _stack(src._stack),
  _cmds(src._cmds)
{
  return ;
}

VirtualMachine::~VirtualMachine( void ) {
  return ;
}

VirtualMachine & VirtualMachine::operator=( 
  VirtualMachine const & rhs 
) {
  this->_stack = rhs._stack;
  this->_cmds = rhs._cmds;
  return *this;
}

void VirtualMachine::addCommand( std::string line ) {
  IOperand const * operand;
  std::string cmd;
  
  if (line[0] == ';') {
    return ;
  }
  this->_trimWhitespace(line);
  cmd = this->_getCommand(line);
  if (cmd == "push" || cmd == "assert") {
    operand = this->_getOperand(line);
    this->_cmds.push_back(std::pair<std::string, IOperand const *>(cmd, operand));
  } else {
    this->_cmds.push_back(std::pair<std::string, IOperand const *>(cmd, NULL));
  }
  return ;
}

std::string VirtualMachine::_getCommand( std::string & line ) const {
  std::string cmd = "";

  if (
    line == "pop" || 
    line == "dump" || 
    line == "add" || 
    line == "sub" || 
    line == "mul" || 
    line == "div" || 
    line == "mod" || 
    line == "print" || 
    line == "exit"
  ) {
    return line;
  }
  for (int i = 0; i < (int)line.length() && line[i] != ' '; i++) {
    cmd += line[i];
  }
  this->_removeSubstring(line, cmd + " ");
  if (cmd == "push") {
    return cmd;
  } else if (cmd == "assert") {
    return cmd;
  } else {
    throw UnknownInstructionException();
  }
}

IOperand const * VirtualMachine::_getOperand( std::string line ) const {
  OperandFactory factory;
  
  eOperandType type = this->_getType(line);
  std::string value = this->_getValue(line);
  
  this->_validateValue(type, value);
  return factory.createOperand(type, value);
}

void VirtualMachine::_validateValue( 
  eOperandType type, 
  std::string value 
) const {

  if (type == Double || type == Float) {
    _validateInt(value);
  } else {
    _validateFloat(value);
  }
  return ;
}

void VirtualMachine::_validateFloat( std::string value ) const {
  int decimal = 0;

  for (int i = 0; i < (int)value.length(); i++) {
    if (
      !(value[i] >= '0' && value[i] <= '9') && 
      !(value[i] == '-' && i == 0)
    ) {
      if (
        value[i] == '.' && 
        decimal == 0 && 
        i != 0 && 
        i != (int)value.length() - 1 
      ) {
        decimal++;
      } else {
        throw UnknownInstructionException();
      }
    }
  }
  return ;
}

void VirtualMachine::_validateInt( std::string value ) const {
  for (int i = 0; i < (int)value.length(); i++) {
    if (
      !(value[i] >= '0' && value[i] <= '9') && 
      !(value[i] == '-' && i == 0)
    ) {
      throw UnknownInstructionException();
    }
  }
  return ;
}

eOperandType VirtualMachine::_getType( std::string & line ) const {
  std::string type = "";

  for (int i = 0; i < (int)line.length(); i++) {
    if (line[i] == '(') {
      break;
    }
    type += line[i];
  }
  this->_removeSubstring(line, type + "(");
  if (type == "int8") {
    return Int8;
  } else if (type == "int16") {
    return Int16;
  } else if (type == "int32") {
    return Int32;
  } else if (type == "float") {
    return Float;
  } else if (type == "double") {
    return Double;    
  } else {
    throw UnknownInstructionException();
  }
}

std::string VirtualMachine::_getValue( std::string line ) const {
  std::string value = "";

  for (int i = 0; i < (int)line.length(); i++) {
    if (line[i] == ')') {
      break;
    }
    value += line[i];
  }
  this->_removeSubstring(line, value + ")");
  return value;
}

void VirtualMachine::printCommands( void ) const {
  for (unsigned int i = 0; i < this->_cmds.size(); i++) {
    std::cout << std::get<0>(this->_cmds[i]);
    if (std::get<1>(this->_cmds[i])) {
      std::cout << " " << (std::get<1>(this->_cmds[i]))->toString();
    } else {
      std::cout << " NULL";
    }
    std::cout << std::endl;
  }
}

void VirtualMachine::_trimWhitespace( std::string & str ) {
  while (str.length() > 0) {
    if (str.front() != ' ' && str.front() != '\t') {
      break;
    }
    str.erase(str.begin());
  }
  while (str.length() > 0) {
    if (str.back() != ' ' && str.back() != '\t') {
      break;
    }
    str.erase(str.end() - 1);
  }
}

void VirtualMachine::_removeSubstring( 
  std::string & str, 
  std::string const subStr 
) const {
  for (int i = 0; i < (int)subStr.length(); i++) {
    if (str.front() == subStr[i]) {
      str.erase(str.begin());
    }
  }
}