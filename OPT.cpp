#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m; // n is the number of memory frames, m is the number of page requests
    cout << "Enter the number of memory frames: ";
    cin >> n;
    cout << "Enter the number of page requests: ";
    cin >> m;

    vector<int> pages(m); // vector to store page requests
    cout << "Enter the page requests: ";
    for (int i = 0; i < m; i++) {
        cin >> pages[i];
    }

    vector<int> memory(n, -1); // vector to represent the memory frames, initialized to -1

    int page_faults = 0; // counter for the number of page faults
    int page_interrupts = 0; // counter for the number of page interrupts
    int page_evictions = 0; // counter for the number of page evictions

    // Start simulating CPU access to physical memory pages
    for (int i = 0; i < m; i++) {
        // Get the first physical memory page to be accessed
        int page = pages[i];
        bool found = false;
        for (int j = 0; j < n; j++) {
            if (memory[j] == page) {
                // If the physical memory page to be accessed by the CPU is found in the physical memory
                // set the flag found to true and break
                found = true;
                break;
            }
        }
        // If the CPU does not find the required physical memory page , a page fault interrupt will be 
        // generated, and we will add one to the corresponding counter
        if (!found) {
            page_faults++;
            bool empty_frame = false;
            // Determine whether the current physical memory is full
            for (int j = 0; j < n; j++) {
                if (memory[j] == -1) {
                    // If there is a page with a value of -1 in the physical page , it means that the memory 
                    // is not full
                    memory[j] = page;
                    empty_frame = true;
                    break;
                }
            }

            // If the memory is full, then the os will invoke the page replacement algorithm
            if (!empty_frame) {
                // the corresponding counter ++
                page_evictions++;
                int index = -1;
                int farthest = i;

                // Take out each page number in our memeory and compare it with all subsequent applications
                // so it is a double-layer loop
                for (int j = 0; j < n; j++) {
                    int k;
                    for (k = i+1; k < m; k++) {
                        if (memory[j] == pages[k]) {
                            break;
                        }
                    }
                    if (k > farthest) {
                        farthest = k;
                        // Store the location of the page we will replace later
                        index = j;
                    }
                }
                memory[index] = page;
            }
        } else {
            // normal interruption
            page_interrupts++;
        }
    }

    cout << "Page faults: " << page_faults << endl;
    // cout << "Page interrupts: " << page_interrupts << endl;
    cout << "Page evictions: " << page_evictions << endl;

    return 0;
}
