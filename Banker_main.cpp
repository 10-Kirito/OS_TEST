#include "Banker.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <vector>

int main() {
    int num_processes, num_resources;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the number of resources: ";
    cin >> num_resources;

    // Initialize available resources
    vector<int> available(num_resources);
    cout << "Enter the available resources: ";
    for (int i = 0; i < num_resources; i++) {
        cin >> available[i];
    }
    

    // Initialize processes
    vector<Process> processes(num_processes);
    for (int i = 0; i < num_processes; i++) {
        processes[i].pid = i;
        processes[i].allocation.resize(num_resources);
        processes[i].max.resize(num_resources);
        processes[i].need.resize(num_resources);
        cout << "Enter the allocation matrix for process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> processes[i].allocation[j];
            // when each process is initialized, the available resources are synchronized at the same time
            available[j] -= processes[i].allocation[j];
        }
        cout << "Enter the max matrix for process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> processes[i].max[j];
            processes[i].need[j] = processes[i].max[j] - processes[i].allocation[j];
        }
    }

    // Print initial state
    cout << "Initial state:" << endl;
    cout << "Available: " << available << endl;

    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << processes[i].pid << ": ";
        cout << "Allocation = " << processes[i].allocation
             << ", Max = " << processes[i].max
             << ", Need = " << processes[i].need << endl;
    }

    // Simulate resource allocation
    bool over = true;
    // cin.get();
    while (over) {
        // system("clear");
        cout << "Begin Simulate resource allocation:" << endl;
        cout << "resources available in the system:" << available << endl;
        display(processes);
        vector<bool> finished(num_resources,false);
        // simulate process apply resources
        cout << "please enter the process that needs to apply for resources: ";
        int index;
        cin >> index;

        // if the id input is wrong
        if (!findProcess(processes, index)) {
            cout << "Wrong pid, please input again!" << endl;
            // cin.get();
            continue;
        }

        cout << "Please enter the resources that process need:";
        vector<int> input(num_processes);
        for (int i = 0; i < num_resources; i++) {
            cin >> input[i];
        }

        input.resize(num_resources);
        vector<Process> pro_temp = processes;
        pro_temp[0].need =  pro_temp[0].need - input;
        // 1. Check whether the resources requested by the process are greater than the number of resources required by the process

        bool flag;
        if(checkLessNeed(processes[index], input))
        {
            cout << "checkLessNeed funciton test passed" << endl;
            // 2. Check if there is a safe state
            if (isSafe(pro_temp, available - input, finished)) {
                cout << "Process " << index << "can apply for resource!"<<endl;
                flag = true;
            }else {
                cout << "Process " << index << "can't apply for resource!"<<endl;
                flag = false;
            }
            // 3. if the state is safe, then agree to the resources requested by the process just now

        }else {
            cout << "Failed to apply for resources!"<<endl;
            flag = false;
        }

        // If the resources requested by the process will cause the system to be unsafe, the process is prohibited from applying
        if(flag){
            deallocateResources(processes[0], available);
        }else {
            cout << "Unsafe application." << endl;
        }

        // cin.get();
    }
    return 0;
}
