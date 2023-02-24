#include "UFD.h"
#include "MFD.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

int main (int argc, char *argv[])
{
  MFD main_directory;
  // initialize 10 users
  UFD user_directory[10] = {{"Kirito"}, {"Tom"}, {"Sam"}, {"Amy"}, {"Kate"}, {"Lane"}, {"Zone"}, {"Yam"}, {"Kai"}, {"Arch"}};
  
  for (auto e : user_directory) {
    main_directory.addUser(e);
  }

  std::cout << "Please log in:" ;
  std::string input_name;
  std::cin >> input_name;

  for (auto var : main_directory.getUser()) {
    std ::cout << var.getName() << std::endl;
  }

  std::vector<UFD> user = main_directory.getUser();
  // check if the users exits in the current system
  auto results = std::find_if(user.begin(), user.end(),
      [&] (const UFD & user){
          return user.getName() == input_name;
        // return user.getName() == input_name;
      });
  if (results == user.end()) {
    std::cout << "Failed to found! Please try again:(q for quit)" << std::endl;
  }else {
    std::cout << "Success to find the user!" << std::endl;
  }
  
  return 0;
}
