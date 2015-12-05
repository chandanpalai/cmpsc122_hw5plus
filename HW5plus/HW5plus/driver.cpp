#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "scheduler.h"
#include "device.h"

int main()
{
	Scheduler *scheds[] =
	{ new FCFS(), new RoundRobin(), new Priority(), new Preempt(), new SRT() };

	Process *tasks[10]; //up to 10 potential processes
	tasks[0] = new Interact(0);

	int arrival[] = {0}; //begin immediately
 
	for (int i=0; i<5; i++) {
		cout << setw(8) << "[" << scheds[i]->name << "]";
		scheds[i]->runScheduler( tasks, arrival, 5 );
		displayHistory( tasks, 5, 0, 3000 );
   }
}