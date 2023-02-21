#include <stdexcept>
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

bool isSafe(vector<Process> &processes, vector<int> available, vector<bool> &finished) {
    std::vector<Process>::size_type num_processes = processes.size();
    std::vector<int>::size_type num_resources = available.size();

    vector<int> work = available;
    vector<bool> finished_temp = finished;
    int count = 0;
    while (count < num_processes) {
        bool found = false;
        // If no available resources can be found for all current processes,
        // found will be assigned the value false, the function will return with false
        for (int i = 0; i < num_processes; i++) {
            if (!finished_temp[i] && processes[i].need <= work) {
                for (int j = 0; j < num_resources; j++) {
                    work[j] += processes[i].allocation[j];
                }
                finished_temp[i] = true;
                found = true;
                count++;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}



// Function to allocate resources to a process, if there are not enough resources
// function will be return with false, Indicates that the process cannot currently allocate resources
bool allocateResources(Process& process, vector<int>& available) {
    int num_resources = available.size();
    for (int i = 0; i < num_resources; i++) {
        if (process.need[i] > available[i]) {
            return false;
        }
    }

    for (int i = 0; i < num_resources; i++) {
        available[i] -= process.need[i];
        process.allocation[i] += process.need[i];
        process.need[i] = 0;
    }

    //deallocateResources(process,available);

    return true;
}


// Function to deallocate resources from a process
void deallocateResources(Process& process, vector<int>& available) {
    int num_resources = available.size();
    for (int i = 0; i < num_resources; i++) {
        available[i] += process.allocation[i];
        process.allocation[i] = 0;
        process.need[i] = process.max[i];
    }
}


// Check whether the resources requested by the current process are less than 
// the resources required by itself

bool checkLessNeed(Process& process, vector<int> &request){
    return request <= process.need;
}

// Check whether the resources requested by the current process are less than
// the available resources

bool checkLessAvail(vector<int>& available, vector<int> &request){
    return request <= available;
}


vector<int> operator - (const vector<int> & lhs, const vector<int> & rhs){
    if (lhs.size() != rhs.size()) {
        throw runtime_error("Vector must be of the ssame size!");
    }

    vector<int> result;
    // use 'reserve' to pre-allocate memory for the result to improve the performance
    result.reserve(lhs.size());

    for (const auto& x : lhs) {
        result.push_back(x-rhs[&x - &lhs[0]]);
    }

    return result;
}

vector<int> operator -= (const vector<int> & lhs, const vector<int> & rhs){
    return lhs - rhs;
}

// Display the menu:
// Please input the number of process that needs to apply for resources:
void display(){
    int pid;
    cout << "Please input the number of process that needs to apply for resources:";
    cin >> pid;

    
}