#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

std::pair<int, int> LRU(std::vector<int> pages_, int num_pages) 
{
    std::list<int> memory;

    unordered_map<int, list<int>::iterator> page_map;  // map pages to their iterator in list

    int num_page_faults = 0;
    int num_page_interruptions = 0;

    int index = 0;
    while (index != pages_.size()) {
        // Check if the page is already in memory
        // If the page is not found in memory, there will be page_map.find == page_map.end
        if (page_map.find(pages_[index]) != page_map.end()) {
            // Indicates that the physical page is already in memory, we need to erase it, and put it in the front
            memory.erase(page_map[pages_[index]]);
            memory.push_front(pages_[index]);
            // update the page's memory
            page_map[pages_[index]] = memory.begin();
        } else {
            // Page fault - add the page to memory
            num_page_faults++;
            // Determine whether the current memory is full
            if (memory.size() == num_pages) {
                // If the memory is full, remove the least recently used page
                page_map.erase(memory.back());
                memory.pop_back();
                num_page_interruptions++;
            }
            // Add the new page to the front of the list
            memory.push_front(pages_[index]);
            page_map[pages_[index]] = memory.begin();
            // page interruption counter++
            
        }

        index++;
    }

    return std::make_pair(num_page_faults, num_page_interruptions);
}
