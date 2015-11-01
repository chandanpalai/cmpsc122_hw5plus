#include <iostream>
using namespace std;

#include "scheduler.h"
#include "device.h"

int main()
{
   Scheduler *scheds[] = 	    // make some process schedulers
	{ new FCFS(), new RoundRobin(), new Priority(), new Preempt() };
   Process *tasks[] = 		    // 4 processes
	{ new Interact(0), new Computation(1), new Interact(2), new Download(3) };
   int arrival[] = {10, 40, 80, 120};   // arrive at these times
 
   for (int i=0; i<4; i++)
   {
	scheds[i]->runScheduler( tasks, arrival, 4 );
	displayHistory( tasks, 4, 0, 3000 );
   }
}