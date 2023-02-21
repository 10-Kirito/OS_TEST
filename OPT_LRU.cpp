#include "OPT.cpp"
#include "LRU.cpp"
#include <iostream>
#include <list>
#include <utility>
#include <vector>

using std::cout;
using std::cin;
using std::vector;

int main(){
    int n, m;
    cout << "Enter the number of memory frames: ";
    cin >> n;

    cout << "Enter the number of page requests: ";
    cin >> m;

    // simulating CPU request the pages
    vector<int> pages(m);
    cout << "Enter the page requests: ";
    for (int i = 0; i < m; i++) {
        cin >> pages[i];
    } 
    vector<int > memory(n, -1);

    // counter
    int page_faults = 0;
    int page_evivtions = 0;

    std::pair<int, int> result_opt = OPT(pages, memory);

    std::pair<int, int> result_lru = LRU(pages, n);


    cout << "OPT: " << std::endl;
    cout << "pages_fault_number: "<< result_opt.first  << "page_replacement_number: " << result_opt.second<<std::endl;



    cout << "LRU: " << std::endl; 
    cout << "pages_fault_number: "<< result_lru.first  << "page_replacement_number: " << result_lru.second<<std::endl;


}