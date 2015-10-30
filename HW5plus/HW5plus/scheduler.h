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
	void chooseProcess(int &procId)
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
	void runScheduler(Process*[], int[], int);
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
