#include <iostream>
#include <iterator>
#include <string>
#include <unistd.h>
#include <vector>
#include "ThreadExec.h"
#include "UFD.h"
using std::cout;
using std::endl;
// execute corresponding actions according to the commands entered by the user



bool threadExec(std::string command, UFD & user){
  // ls -al:
  if (command == "ls") {
    cout << "list all files:" << endl;
    user.displayFiles();
  }else if (command == "touch") {
    cout << "touch a file:" << endl;
    cout << "please input the file name:";

    std::string file_name;
    std::cin >> file_name;
    std::string path = file_name;
    FileHandler file(path, user.getName());
    file.openForWriting();

    if (file.isOutputFileopen()) {
      std::cout << "open ok" << std::endl;
    }else {
      std::cout << "open wrong" << std::endl;
    }

  }else if (command == "delete") {
    cout << "delete a file:" <<endl;
  }else if (command == "read") {
    cout << "read a file:" << endl;
  }else if (command == "write") {
    cout << "write a file:" << endl;
  }else if (command == "exit") {
    return false;
  }else {
    cout << "wrong command!" << endl;
  }
  return true;
}



void list(char *args[]){

  int result = execve("/bin/ls", args, nullptr);
  if(result == -1){
    std::cerr << "Error executing command!" << std::endl;
  }

}


