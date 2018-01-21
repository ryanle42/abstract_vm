#ifndef VIRTUALMACHINE_HPP
# define VIRTUALMACHINE_HPP

class VirtualMachine {

public:

  VirtualMachine( void );
  VirtualMachine( VirtualMachine const & src );
  ~VirtualMachine( void );
  VirtualMachine & operator=( VirtualMachine const & rhs );

};

#endif