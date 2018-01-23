#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "VirtualMachine.hpp"
#include <iostream>
#include <fstream>

int main( int argc, char **argv ) {
  (void)argv;
  if (argc == 1) {
    VirtualMachine vm;
    std::string line;

    std::getline(std::cin, line);
    while (line != ";;") {
      try {
        vm.addCommand(line);
      } catch (std::exception & e) {
        std::cout << e.what() << std::endl;
        return -1;
      }
      std::getline(std::cin, line);
    }
    try {
      vm.executeCommands();
    } catch (std::exception & e) {
      std::cout << e.what() << std::endl;
      return -1;
    }
    return 0;
  }
}