#include <iostream>
#include "histo.h"
using namespace std;

// Process Scheduler
// This represents the part of an operating system that manages processes,
// choosing which to assign the CPU (assuming a single-processor system).
// It will maintain a collection of processes that are currently ready
// to use the CPU, and then choose which to run next.
//
// The time on the system clock is not required for this object,
// so all of the time fields in the linked list objects are set to zero.

class Scheduler {
    protected:
	ProcList readySet;	// set of processes ready to run
	ProcList future;	// list of future events
	int clock;		// current clock time for simulation
	string name;		// name of the scheduling algorithm
    public:
	virtual void addProcess( int procId ) {
	    readySet.pushBack( procId, 0, 'X');
	}
	void chooseProcess( int &procId ) {
	    char hold;
	    readySet.popFront( procId, hold ); }
	virtual int allowance() {
	    return 100000;	// a long time
	}
	virtual bool noneReady() {
	    return readySet.empty();
	}
    void runScheduler( Process* [], int[], int );
};

class FCFS : public Scheduler {
    public:
	FCFS() { name="First Come First Served"; }
};

class RoundRobin : public Scheduler {
    public:
	RoundRobin() { name="Round Robin"; }

	int allowance() {
	    return 70;
	}   
};

class Priority : public Scheduler {
    public:
	Priority() { name="Priority"; }

	void addProcess( int procId ) {

	}
};

class Preempt : public Priority {
    public:
	Preempt() { name="Preemptive Priority"; }
	
	int allowance() {

	}
};
