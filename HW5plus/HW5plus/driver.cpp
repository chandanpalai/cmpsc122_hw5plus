#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
using namespace std;

#include "scheduler.h"
#include "device.h"

void maximize() {
	HWND cons = GetConsoleWindow();
	RECT r;
	GetWindowRect(cons, &r); //stores the console's current dimensions

	MoveWindow(cons, r.left, r.top, 1100, 600, TRUE); // 1100 width, 600 height
}

int main()
{
	maximize();
	Scheduler *scheds[] = 	    // make some process schedulers
	{ new FCFS(), new RoundRobin(), new Priority(), new Preempt(), new SRT() };
	Process *tasks[] = 		    // 4 processes
	{ new Computation(0), new Interact(1), new Computation(2), new Download(3), new Computation(4) };
	int arrival[] = {10, 40, 80, 120, 140};   // arrive at these times
 
	for (int i=0; i<5; i++) {
		cout << setw(10) << "[" << scheds[i]->name << "]" << endl;
		scheds[i]->runScheduler( tasks, arrival, 5 );
		displayHistory( tasks, 5, 0, 10000 );
   }
}