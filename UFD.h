#ifndef __FILE_SYSTEM__ 
#define __FILE_SYSTEM__

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
// declare an enum variable to display file permission
enum class Limits {read, write, exec , none};

class FileHandler {
public:
  FileHandler() = default;
  FileHandler(const std::string & filename, const std::string & owner_) 
        : file_name(filename), 
          owner(owner_),
          permission({Limits::read, Limits::write, Limits::none}),
          length(0)
  {}
  FileHandler(const FileHandler& file){
    file_name = file.file_name;
    owner = file.owner;
    permission = file.permission;
    length = file.length;
  }

  std::string getName(){ return file_name;}
  std::vector<Limits> getPermission() {return permission;}
  std::size_t getLength() { return length;}
  std::string getUsername() { return owner;}

private:
  std::string file_name;
  std::string owner;
  // cin >> 
  // std::ifstream file_in;
  // cout << 
  // std::ofstream file_out;

  //Limits permission[3];
  std::vector<Limits> permission;
  std::size_t length;
};

class UFD
{
public:
  UFD();
  UFD(const std::string & name_):user_name(name_) {};
  void addFile(FileHandler && file);
  std::string getName()const {return user_name;};
  void displayFiles();
  UFD(UFD &&) = default;
  UFD(const UFD &) = default;
  UFD &operator=(UFD &&) = default;
  UFD &operator=(const UFD &) = default;
  ~UFD();

private:
  std::string user_name;
  std::vector<FileHandler> file_vector;
};

#endif // !__FILE_SYSTEM__








