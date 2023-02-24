// The purpose of this code file is to implement a multiple threads and interact
//
#include <cstdlib>
#include <iterator>
#include <string>
#include <thread>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
#include <mutex>
#include <algorithm>
#include <map>
#include <chrono>
#include <condition_variable>
#include "ThreadExec.h"
#include "UFD.h"

using std::cout;
using std::endl;
using std::cin;

// define all user's workspace
std::vector<UFD> user_field;

// define 10 std::condition_variable to call other thread
std::vector<std::condition_variable> thread_status(10);

// set a global variable to store all thread IDS
//
std::vector<std::thread::id> g_threadIds;
// set the mutex to protect the system
std::mutex g_mutex;

std::vector<std::mutex> thread_change(10);
// bind the user_name and PID
std::map<std::string, std::thread::id> map_name_id;

enum class status {RUNNING, WAITING, EXIT};
//
std::map<std::string, status> map_name_status;
// custom the thread function
//
void thread_function(std::string user_name){
  bool flag = false;
  std::thread::id pid = std::this_thread::get_id();
  std::string command;
  
  // lock the resources
  {
    std::lock_guard<std::mutex> lock(g_mutex);
    map_name_id.emplace(std::make_pair(user_name, pid));
    g_threadIds.push_back(pid);
  }

  int index = std::distance(map_name_status.begin(),map_name_status.find(user_name));

  // 
  std::unique_lock<std::mutex> uniq_lock(thread_change[index]);
  thread_status[index].wait(uniq_lock, [&]{ return map_name_status.at(user_name) == status::RUNNING;});
  cout << index << endl;


  //
  // the main interface of each user
  //
  // RUNNING : Running status, create file , edit file, file access
  // WAITING : Blocked state
  // EXIT : Finish




  while (true) {
    switch (map_name_status.at(user_name)) {
      case status::RUNNING:
        {
          bool run = true;
          std::string command;
          //cout << "Hello, " << user_name << endl;
          std::system("clear");
          while (run) {
            cout << user_name << "@Ubuntu: ~ $ " ;
            cin >> command;
            if(!threadExec(command,user_field.at(index))){
              uniq_lock.unlock();
              return ;
            }


          }
          break;
        }
      case status::WAITING:
        {
          cout << "test" << endl;
          break;
        }
      case status::EXIT:
        {
          auto ite = std::find(g_threadIds.begin(), g_threadIds.end(), pid);
          g_threadIds.erase(ite);
          return;
        }
    }
  }

}


int main (int argc, char *argv[])
{
  // acquire all locks to block all threads
  std::vector<std::unique_lock<std::mutex>> lck;
  for (auto &e : thread_change) {
    lck.emplace_back(e);
  }
  // all threads
  std::vector<std::thread> vector_list;
  // all thread's name
  std::vector<std::string> name_list = {"Kirito", "Sam", "Kate", "Tom", "Amy", "Daming", "Arch", "Ubuntu", "Kali", "Pop"};
  // initialize 10 threads 
  for (int i = 0; i < 10; i++) {
    vector_list.emplace_back(thread_function, std::ref(name_list[i])); 
    map_name_status.emplace(std::make_pair(name_list[i], status::WAITING));
    user_field.emplace_back(name_list[i]);
  }
  // all threads run indenpendently
  // for (int i = 0; i < 10; i++)
  //   vector_list[i].detach();


  bool flag = true;

  // process main program loop 
  std::string input_name;

  while (flag) {
    cout << "Please input the user's name:";
    cin >> input_name;

    auto result = std::find(name_list.begin(), name_list.end(), input_name);
    int index ;
    if(result == name_list.end()){
      cout << "can't find the user, please try again!" << endl;
    }else{
      cout << "find the user:" << endl;
      index = std::distance(name_list.begin(), result);

      // unlock the corresponding lock to allow the corresponding process to run
      lck[index].unlock();
      
      map_name_status.at(input_name) = status::RUNNING;

      vector_list[index].join();

      cout << "user@" << name_list[index] << " successfully exit." << endl;
    }

    // when all threads over, the main thread will over too.
    if (g_threadIds.empty()) {
      return 1;
    }

  }

  return 0;
}
