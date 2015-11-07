//Sam Lucas, CMPSC 122, Section 001
#include <iostream>
using namespace std;
#include "histo.h"

class Scheduler {
protected:
	ProcList readySet;	
	ProcList future;
	int clock;
	string name;
public:
	virtual void addProcess(int procId)
	{
		readySet.pushBack(procId, 0, 'X');
	}
	virtual void chooseProcess(int &procId)
	{
		char hold;
		readySet.popFront(procId, hold);
	}
	virtual int allowance()
	{
		return 100000;	// a long time
	}
	virtual bool noneReady()
	{
		return readySet.empty();
	}
	virtual void runScheduler(Process*[], int[], int);
};
class FCFS : public Scheduler {
public:
	FCFS() { name = "First Come First Served"; }
};

class RoundRobin : public Scheduler {
public:
	RoundRobin() { name = "Round Robin"; }
	int allowance() {
		return 70;
	}
};
class Priority : public Scheduler {
public:
	Priority() { name = "Priority"; }
	
	void addProcess(int procId) {
		readySet.insert(procId, -procId, 'X');
	}
};

class Preempt : public Priority {
public:
	Preempt() { name = "Preemptive Priority"; }
	int allowance() {
		return 1;
	}
};

class SRT : public Preempt {
private:
	Process **procs;	// this scheduler's way of getting to process info

						// declare additional variables as needed here

public:
	SRT() { name = "SRT"; } 	// also initialize anything else you need here

	//  grabs the process information, and then runs the simulation
	void runScheduler(Process* tasks[], int arrival[], int size) {
		procs = tasks;
		Scheduler::runScheduler(tasks, arrival, size);
	}

	//  declare whatever you plan to override here
	//  and implement it here or in scheduler.cpp

	//override chooseProcess( int &procId )
	//must find lowest remaining time process in O(1)-O(log n) time, no worse than O(n)
	//assume no more than 20 processes at a time

	//probably override addProcess(int procId) too since readySet cannot be used

};