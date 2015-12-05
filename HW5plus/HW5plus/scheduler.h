//Sam Lucas, CMPSC 122, Section 001
#include <iostream>
#include <vector>
using namespace std;
#include "histo.h"

class Scheduler {
protected:
	ProcList readySet;	
	ProcList future;
	int clock;
public:
	string name;

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
	FCFS() { name = "FIRST COME FIRST SERVED"; }
};
class RoundRobin : public Scheduler {
public:
	RoundRobin() { name = "ROUND ROBIN"; }
	int allowance() {
		return 70;
	}
};
class Priority : public Scheduler {
public:
	Priority() { name = "PRIORITY"; }
	
	void addProcess(int procId) {
		readySet.insert(procId, -procId, 'X');
	}
};
class Preempt : public Priority {
public:
	Preempt() { name = "PREEMPTIVE PRIORITY"; }
	int allowance() {
		return 1;
	}
};
class SRT : public Scheduler {
private:
	Process **procs;
	vector<Process*> readySet;

	Process *val;
	int i, j;

public:
	SRT() { name = "SHOREST REMAINING TIME";}

	void runScheduler(Process* tasks[], int arrival[], int size) {
		procs = tasks;
		Scheduler::runScheduler(tasks, arrival, size);
	}

	void sort(vector<Process*>&);//insertion sort

	void addProcess(int procId) {
		readySet.push_back(procs[procId]);
		sort(readySet);
	}
	void chooseProcess(int &procId) {
		procId = readySet[0]->getId();
		vector<Process*> newReadySet;
		for (int x = 1; x < readySet.size(); x++) {
			newReadySet.push_back(readySet[x]);
		}
		readySet = newReadySet;
	}
	bool noneReady() {
		return readySet.empty();
	}
	int allowance() {
		return 1;
	}
};