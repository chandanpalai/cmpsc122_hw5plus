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
	virtual void chooseProcess(int &procId)//changed to virtual
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
	virtual void runScheduler(Process*[], int[], int);//changed to virtual
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

	Process *ready[20];

	Process newValue;
	int pos;

	Process *buckets[10000];
	int bucketSize[10000];
	int fillPos;
	int which;
	int divisor;

public:
	SRT() { name = "SRT"; }

	void runScheduler(Process* tasks[], int arrival[], int size) {
		procs = tasks;
		Scheduler::runScheduler(tasks, arrival, size);
	}

	void insertSort(Process [], int);
	void sort(Process [], int);

	void addProcess(int procId) {
		int i;
		while (i < 20 && ready[i] != NULL) { i++; }
		ready[i] = procs[procId];
	}
	void chooseProcess(int &procId) {
		// to be updated for ready[]
	}
	bool noneReady() {
		return ready[0] == NULL;
	}
};