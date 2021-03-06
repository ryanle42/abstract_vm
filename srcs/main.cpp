#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "VirtualMachine.hpp"
#include <iostream>
#include <fstream>

int main( int argc, char **argv ) {
  VirtualMachine vm;
  std::string line;
  std::ifstream file;
  int lineNb = 1;

  if (argc == 1) {
    std::getline(std::cin, line);
    while (line != ";;") {
      vm.addCommand(line, lineNb);
      std::getline(std::cin, line);
      lineNb++;
    }
    try {
      vm.executeCommands();
    } catch (std::exception & e) {
      std::cout << "Error : " << e.what()
                << std::endl;
    }
  } else if (argc == 2) {
      file.open(argv[1]);
      while(!file.eof()) {
        std::getline(file, line);
        vm.addCommand(line, lineNb);
        lineNb++;
      }
      file.close();
      try {
        vm.executeCommands();
      } catch (std::exception & e) {
        std::cout << "Error : " << e.what()
                  << std::endl;
      }
  }
}