#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

#include <vector>
#include <map>
#include "IOperand.hpp"
#include "Operand.hpp"
#include "Exceptions.hpp"

class VirtualMachine {

public:

  VirtualMachine( void );
  VirtualMachine( VirtualMachine const & src );
  ~VirtualMachine( void );
  VirtualMachine & operator=( VirtualMachine const & rhs );
  void addCommand( std::string line );
  void printCommands( void ) const;

private:

  std::vector<IOperand *> _stack;
  std::vector<std::pair<std::string,IOperand *>> _cmds;
  void _parseLine( std::string line );
  std::string _getCommand( std::string line ) const;
  IOperand * _getOperand( std::string line ) const;
  eOperandType _getType( std::string ) const;
  void _removeSubstring( std::string & str, std::string const subStr ) const;
  std::string _getValue( std::string ) const;
  void _trimWhitespace( std::string & line );

};

#endif