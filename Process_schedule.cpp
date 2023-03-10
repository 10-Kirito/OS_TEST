#include "Process.h"
#include "Cpu.h"

#include <cstdlib>
#include <iostream>
#include <list>
#include <thread>
#include <unistd.h>

using namespace std;


void show_process_timely(const Cpu & cpu)
{
    
	while (!cpu.Cpu_status())
	{
        sleep(1);
        system("clear");
        cpu.show_running_waiting();
        cpu.show_process_status();
        cout << "================================================================" << endl;
	}
    cout << "SYSTEM FINISHED!!" << endl;
}


void process_schedule(Cpu &cpu)
{
#ifdef PRIORITY
    cpu.priority_schedule();
#endif
#ifdef ROUND
    cpu.round_schedule();
#endif

}

int main()
{
    #ifdef PRIORITY
    Process process[6];
    // create the list of waiting process
    list<Process> _wlist;
    // create the list of running process 
    list<Process> _rlist;


    for (Process temp : process)
    {
        _wlist.push_back(temp);
    }

	// create the CPU
	Cpu _cpu(_wlist, _rlist);

	thread schedule(process_schedule, ref(_cpu));
    thread show_status(show_process_timely, ref(_cpu));

    schedule.join();
    show_status.join();

    #endif



    #ifdef ROUND
    Process process[6];
    // create the list of waiting process
    list<Process> _wlist;
    // create the list of running process 
    list<Process> _rlist;


    for (Process temp : process)
    {
        _wlist.push_back(temp);
    }

	// create the CPU
	Cpu _cpu(_wlist, _rlist);

	thread schedule(process_schedule, ref(_cpu));
    thread show_status(show_process_timely, ref(_cpu));

    schedule.join();
    show_status.join();

    #endif
  return 0;
}

