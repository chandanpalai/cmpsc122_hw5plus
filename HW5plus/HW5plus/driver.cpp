#include <iostream>
using namespace std;

#include "scheduler.h"
#include "device.h"

int main()
{
   Scheduler *scheds[] = 	    // make some process schedulers
	{ new FCFS(), new RoundRobin(), new Priority(), new Preempt(), new SRT() };
   Process *tasks[] = 		    // 4 processes
	{ new Computation(0), new Interact(1), new Computation(2), new Download(3), new Computation(4) };
   int arrival[] = {10, 40, 80, 120, 140};   // arrive at these times
 
   for (int i=0; i<5; i++) {
	scheds[i]->runScheduler( tasks, arrival, 5 );
	displayHistory( tasks, 5, 0, 3000 );
   }
}