//Sam Lucas, CMPSC 122, Section 001
#include "proclist.h"

#ifndef DEVICE
#define DEVICE

class Process;
class Scheduler;
class Console;
class Device {
	friend class Console;
    private:
		char action;
		int duration;
		int readyTime;	
    public:
		Device() {}
		Device( char a, int d ) : action(a), duration(d), readyTime(0) { }
		void restart() {
		    readyTime = 0;
		}
		void request( int, int, Process* [], ProcList & ); //id, clock, *tasks[], &future
};
class Console : public Device {
	private:
		int lastLaunch, procsActive;
		char typeActive;

	public:
		Console(char a, int d) {
			action = a;
			duration = d;
			readyTime = 0;
		}
		void launch() {
			//creates new process at any time
			//do not create new interactive if one is running
			//leave realistic gap between process initiations
		}
		//need to keep track of time elapsed since last input/process launch
		//need to keep track of # processes active and their type
		//see private variables
};
extern Device disk, net, cpu; //removed console here as device type
extern Console keyboard;
#endif