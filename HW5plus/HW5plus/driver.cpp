#include <iostream>
using namespace std;

#include "scheduler.h"
#include "device.h"

int main()
{
   Scheduler *scheds[] = 	    // make some process schedulers
	{ new FCFS(), new RoundRobin(), new Priority(), new Preempt() };
   Process *tasks[] = 		    // 4 processes
	{ new Computation(0), new Interact(1), new Computation(2), new Computation(3) };
   int arrival[] = {10, 40, 80, 120};   // arrive at these times
 
   for (int i=0; i<4; i++)
   {
	scheds[i]->runScheduler( tasks, arrival, 4 );
	displayHistory( tasks, 4, 0, 3000 );
   }
}