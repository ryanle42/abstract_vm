#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "VirtualMachine.hpp"
#include <iostream>
#include <fstream>

int main( int argc, char **argv ) {
  VirtualMachine vm;
  std::string line;
  std::ifstream file;

  if (argc == 1) {
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
  } else if (argc == 2) {
      file.open(argv[1]);
      while(!file.eof()) {
        getline(file, line);
        vm.addCommand(line);
      }
      file.close();
      vm.executeCommands();
  }
}