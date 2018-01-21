#include "OperandFactory.hpp"
#include "Int8.hpp"
#include "IOperand.hpp"

int main( void ) {
  Int8 test("92");
  Int8 test2("12");
  IOperand const * ptr;
  

  ptr = test + test2;
  if (ptr) {
    std::cout << ptr->toString() << std::endl;
  }
}