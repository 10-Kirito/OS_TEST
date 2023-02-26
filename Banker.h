#include <stdexcept>
#include <typeinfo>
#include <vector>
#include <iostream>

using namespace std;

const int MAX_PROCESS = 100;
const int MAX_RESOURCE = 100;

// Class for representing a process
class Process {
public:
    int pid;
    vector<int> allocation;
    vector<int> max;
    vector<int> need;
};

void deallocateResources(Process& process, vector<int>& available);

// Function to find if a process can be allocated resources
// Check the current system if is safe or not

bool isSafe(vector<Process> &processes, vector<int> available, vector<bool> &finished);

// Function to allocate resources to a process, if there are not enough resources
// function will be return with false, Indicates that the process cannot currently allocate resources
bool allocateResources(Process& process, vector<int>& available);

// Function to deallocate resources from a process
void deallocateResources(Process& process, vector<int>& available);

// Check whether the resources requested by the current process are less than 
// the resources required by itself

bool checkLessNeed(Process& process, vector<int> &request);

// Check whether the resources requested by the current process are less than
// the available resources

bool checkLessAvail(vector<int>& available, vector<int> &request);

// display all process's status
void display(const vector<Process> & process);

bool findProcess(const vector<Process> &, int);


vector<int> operator - (const vector<int> & lhs, const vector<int> & rhs);

vector<int> operator -= (const vector<int> & lhs, const vector<int> & rhs);

// overload the 'operator < '
template <typename T>
bool operator <= (const vector<T> &a,const vector<T> &b){
    if (a.size() != b.size()) {
        return false;
    }else {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] > b[i]) {
                return false;
            }
        }
        return true;
    }
};

template<typename T>
ostream & operator << (ostream & out, const vector<T> &a){
  out << "[ ";
  for (auto &e : a) {
    out << e << " ";
  }
  out << "]";
  return out;
}




