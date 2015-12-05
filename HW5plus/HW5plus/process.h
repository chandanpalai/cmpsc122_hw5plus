//Sam Lucas, CMPSC 122, Section 001
#include "proclist.h"
#include <stdlib.h>

class Device;
class Process {
	friend class Console;

protected:
	int myId;
	int bursts;
	int usages[10]; //increased from  10
	Device *nextRequest[10]; //increased from 10
	int currentCycle;
	int remainingTime;
	ProcList log;

public:
	int getId() {
		return myId;
	}
	int getRemainingTime() {
		return remainingTime;
	}
	void restart() {
	    currentCycle = 0;
	    remainingTime = usages[0];
	    log.clear();
	}
	void addLog( int time, char state ) {
	    log.pushBack( myId, time, state );
	}
	ProcList &getLog() {
	    return log;
	}
	virtual bool isInteractive() {
	    return false;	// assume a background job
	}
	void run( int &, int, Device *& );
};
class Computation : public Process {
    public:
	Computation( int id );
};
class Download : public Process {
    public:
	Download( int id );
};
class Interact: public Process {
    public:
	Interact( int id );
	bool isInteractive() {
	    return true;
	}
};	
