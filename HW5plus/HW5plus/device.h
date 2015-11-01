//Sam Lucas, CMPSC 122, Section 001
#include "proclist.h"

#ifndef DEVICE
#define DEVICE

class Process;
class Scheduler;
class Device {
    private:
		//ProcList requests;	<- not needed?
		char action;
		int duration;
		int readyTime;	
    public:
		Device( char a, int d ) : action(a), duration(d), readyTime(0) { }
		void restart() {
		    readyTime = 0;
		}
		void request( int, int, Process* [], ProcList & );
};
extern Device disk, net, console, cpu;
#endif