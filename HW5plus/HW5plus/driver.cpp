//Sam Lucas, CMPSC 122, Section 001
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "scheduler.h"
#include "device.h"

void reset(Process *arr[]) { //resets the array of processes for each simulation
	arr[0] = new Interact(0);
	for (int h = 1; h < 10; h++) { arr[h] = NULL; }
}
int main()
{
	Scheduler *scheds[] =
	{ new FCFS(), new RoundRobin(), new Priority(), new Preempt(), new SRT() };
	Process *tasks[10]; //up to 10 potential processes
	int arrival[] = { 0 };

	for (int i=0; i<5; i++) {
		reset(tasks);
		scheds[i]->runScheduler( tasks, arrival, 1 );//run each scheduler

		//find # of non-null pointers
		int j = 0;
		while (tasks[j] != NULL) { j++; }

		cout << setw(8) << "[" << scheds[i]->name << "]" << endl; //print name
		displayHistory( tasks, j-1, 0, 20000 );
   }
}