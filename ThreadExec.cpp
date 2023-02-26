#include <algorithm>
#include <cstdio>
#include <fstream>
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

std::vector<FileHandler> allFiles;

bool checkIsmine(const std::string &file_name, const std::string &user){
  for (auto & a : allFiles) {
    if (a.getName() == file_name && a.getUsername() == user) {
      return true;
    }
  }
  return false;
}

void deleteFile(std::string &file_name){
  for (std::vector<FileHandler>::iterator ite; ite != allFiles.end(); ite++) {
    if ((*ite).getName() == file_name) {
      allFiles.erase(ite);
    }
  }
}



bool threadExec(std::string command, UFD & user){
  sleep(1);
  std::string file_name;
  std::ofstream out_file;
  std::ifstream in_file;
  char ch;
  // ls -al:
  if (command == "ls") {
    cout << "list all files:" << endl;
    user.displayFiles();
  }else if (command == "touch") {
    cout << "touch a file:" << endl;
    cout << "please input the file name:";

    std::cin >> file_name;

    if (!checkIsmine(file_name, user.getName())) {
      FileHandler file(file_name, user.getName());
      out_file.open(file_name);
      if(out_file.is_open()){
        cout << "Enter file content (terminate with '$'):";
        while ((ch = getchar()) != '$') {
          out_file << ch;
        }

        out_file.close();
        std::cout << "create file: " << file_name << "successfully"<< std::endl;
        user.addFile(std::move(file));
        allFiles.push_back(file);
      } else {
        cout << "Unable to create file" << endl;
      }
    }else {
      cout << "This file already exists!" << endl;
    }

  }else if (command == "delete") {
    cout << "Enter a file name: ";
    std::cin >> file_name;
    if (checkIsmine(file_name, user.getName())) {
      if (remove(file_name.c_str()) == 0) {
        cout << "File deleted successfully." << endl;
        deleteFile(file_name);
      }else {
        cout << "Ubable to delete file." << endl;
      }
    }else {
      cout << "You do not have sufficient permissions" << endl;
    }

  }else if (command == "read") {
    cout << "Enter a file name: ";
    std::cin >> file_name;
    in_file.open(file_name);

    if(in_file.is_open()){
      while (in_file.get(ch)) {
        cout << ch;
      }
      in_file.close();
    }else {
      cout << "Unable to open file." << endl;
    }
  }else if (command == "write") {
    cout << "Enter a file name:";
    std::cin >> file_name;

    if (checkIsmine(file_name, user.getName())) {
      out_file.open(file_name);

      if (out_file.is_open()) {
        cout << "Enter file content (terminate with '$')";

        while ((ch = getchar()) != '$') {
          out_file << ch;
        }
        out_file.close();
        cout << "File updated successfully." << endl;
      }
    }else {
      cout << "You do not have sufficient permissions" << endl;
    }

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


