#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

#include <vector>
#include <map>
#include "IOperand.hpp"
#include "Operand.hpp"
#include "OperandFactory.hpp"
#include "Exceptions.hpp"

class VirtualMachine {

public:

  VirtualMachine( void );
  VirtualMachine( VirtualMachine const & src );
  ~VirtualMachine( void );
  VirtualMachine & operator=( VirtualMachine const & rhs );
  void addCommand( std::string line, int const lineNb );
  void printCommands( void ) const;
  void executeCommands( void );

private:

  std::vector<IOperand const *> _stack;
  std::vector<std::pair<std::string, IOperand const *>> _cmds;
  std::string _getCommand( std::string & line ) const;
  IOperand const * _getOperand( std::string line ) const;
  eOperandType  _getType( std::string & line ) const;
  std::string _getValue( std::string line ) const;
  void  _validateValue( eOperandType type, std::string value ) const;
  void  _validateFloat( std::string value ) const;
  void  _validateInt( std::string value ) const;
  void  _trimWhitespace( std::string & line );
  void  _removeSubstring( 
    std::string & str, 
    std::string const subStr 
  ) const;
  void  _push( IOperand const * operand );
  void  _assert( IOperand const * operand );
  void  _pop( void );
  void  _dump( void );
  void  _add( void );
  void  _sub( void );
  void  _mul( void );
  void  _div( void );
  void  _mod( void );
  void  _print( void );
  void  _exit( void );

};

#endif