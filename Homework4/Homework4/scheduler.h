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
	virtual int allowance(int) {
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
		int id;
		char state;
		ProcIterator focus = readySet.begin();

		if (focus.process() == NULL) {//if the readySet is empty
			readySet.pushBack(procId, 0, 'X');
		}
		else if (focus.process() < procId) { //if procId is the largest
			readySet.pushBack(procId, 0, 'X');
			while (focus.process() != procId ) {
				readySet.popFront(id, state);
				readySet.pushBack(id, 0, state);
				focus = readySet.begin();
			}
		}
		else { //insert it based on id
			int firstId = focus.process(); //keep track of whats in front
			while (focus.process() > procId) {//move all those larger than procId to the back
				readySet.popFront(id, state);
				readySet.pushBack(id, 0, state);
				focus = readySet.begin();
			}
			readySet.pushBack(procId, 0, 'X');//add procId to the back
			while (focus.process() != firstId) {//finally move all those less than procId to the back
				readySet.popFront(id, state);
				readySet.pushBack(id, 0, state);
				focus = readySet.begin();
			}
		}
	}
};

class Preempt : public Priority {
    public:
	Preempt() { name="Preemptive Priority"; }
	
	int allowance(int id) {//look thru future for first element with a higher id and set allowance to the time difference
		ProcIterator search = future.begin();
		while (search.process() < id && search != future.end()) {
			search.advance();
		}
		if (search.process() > id)
			return search.time() - clock;
		else
			return 100000;
	}
};
