#include "OperandFactory.hpp"
#include "IOperand.hpp"

int main( void ) {
  OperandFactory factory;
  
  IOperand const * op1 = factory.createOperand(Float, "-223");
  IOperand const * op2 = factory.createOperand(Int16, "221233");

  IOperand const * test;

  test = *op1 + *op2;

  if (test) {
    std::cout << test->toString() << std::endl;
  }
}