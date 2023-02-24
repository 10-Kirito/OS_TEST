#include "UFD.h"
#include <iostream>
#include <ostream>
#include <string>

// default construction
UFD::UFD() :user_name("") {}


// add a file to current user
void UFD::addFile(FileHandler &&file){
  file_vector.push_back(file);
}

// display all files with details
void UFD::displayFiles(){
  if(file_vector.empty()){
    std::cout << "Empty" << std::endl;
    return;
  }
  for (auto & a : file_vector) {
    for (auto & e : a.getPermission()) {
      std::cout << ((e == Limits::write) ? "w": e == Limits::read ? "r" : "-");
    }
    std::cout << " " << user_name << " " << a.getLength() << a.getName() << std::endl;
  }
}

// deconstructor
UFD::~UFD() {file_vector.clear();}


