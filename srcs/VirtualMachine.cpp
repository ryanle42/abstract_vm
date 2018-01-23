#include "VirtualMachine.hpp"

VirtualMachine::VirtualMachine( void ) {
  return ;
}
VirtualMachine::VirtualMachine( VirtualMachine const & src ) {
  (void)src;
  return ;
}

VirtualMachine::~VirtualMachine( void ) {
  return ;
}

VirtualMachine & VirtualMachine::operator=( 
  VirtualMachine const & rhs 
) {
  (void)rhs;
  return *this;
}

void VirtualMachine::addCommand( std::string line ) {
  if (line[0] == ';') {
    return ;
  }
  this->_trimWhitespace(line);
  this->_parseLine(line);
  return ;
}

void VirtualMachine::_parseLine( std::string line ) {
  IOperand * value;
  std::string cmd = this->_getCommand(line);

  if (cmd == "push" || cmd == "assert") {
    this->_removeSubstring(line, cmd + " ");
    value = this->_getOperand(line);
    this->_cmds.push_back(std::pair<std::string, IOperand *>(cmd, value));
  } else {
    this->_cmds.push_back(std::pair<std::string, IOperand *>(cmd, NULL));
  }
}

std::string VirtualMachine::_getCommand( std::string line ) const {
  std::string cmd = "";

  for (int i = 0; i < (int)line.length() && line[i] != ' '; i++) {
    cmd += line[i];
  }
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
  } else if (cmd == "push") {
    return cmd;
  } else if (cmd == "assert") {
    return cmd;
  } else {
    throw UnknownInstructionException();
  }
}

IOperand * VirtualMachine::_getOperand( std::string line ) const {
  // eOperandType type = this->_getType(line);
  std::cout << line << std::endl;
  return NULL;
}

eOperandType VirtualMachine::_getType( std::string line ) const {
  // for (int i = 0; i < line.length(); )
  (void)line;
  return Int8;
}

void VirtualMachine::printCommands( void ) const {
  for (unsigned int i = 0; i < this->_cmds.size(); i++) {
    std::cout << std::get<0>(this->_cmds[i]);
    if (std::get<1>(this->_cmds[i])) {
      std::cout << " " << std::get<0>(this->_cmds[i]);
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