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
          permission({Limits::none, Limits::none, Limits::none}),
          length(0)
  {}
  FileHandler(const FileHandler& file){
    file_name = file.file_name;
    owner = file.owner;
    permission = file.permission;
    length = file.length;
  }
  // open the read_only file
  void openForReading(){ file_in.open(file_name);}
  // open write file
  void openForWriting(){ file_out.open(file_name);}
  // close the specified file
  void closeFile(){ file_in.close();}

  // check the file if can read
  bool isInputFIleopen() const { return file_in.is_open();}

  // check the file if can write
  bool isOutputFileopen() const { return file_out.is_open();}
  // return input handler
  //
  std::ifstream & input(){ return file_in;}
  // return output handler
  //
  std::ofstream & output(){ return file_out;}
  std::string getName(){ return file_name;}
  std::vector<Limits> getPermission() {return permission;}
  std::size_t getLength() { return length;}

private:
  std::string file_name;
  std::string owner;
  // cin >> 
  std::ifstream file_in;
  // cout << 
  std::ofstream file_out;

  //Limits permission[3];
  std::vector<Limits> permission;
  std::size_t length;
};


// // declare the file struction
// struct File
// {
//   std::string file_name;
//   //int permission[3] = {1,1,0};
//   Limits permission[3];

//   std::size_t length;
//   // the status of the current file
//   bool status;
  
//   // default construction
//   File(){
//     file_name = "";
//     for(auto &var : permission)
//     {
//       var = Limits::none;
//     }
//     // any file is read-write by default from the start
//     //
//     status = true;
//     length = 0;
//   }
// };


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








