//Sam Lucas, CMPSC 122, Section 001
#include <iostream>
using namespace std;
#include "histo.h"//correct

class Scheduler {
protected:
	ProcList readySet;	// set of processes ready to run
	ProcList future;	// list of future events
	int clock;		// current clock time for simulation
	string name;		// name of the scheduling algorithm
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
		/* code for comparison
		ProcList newHead;
		ProcIterator iter = readySet.begin();
		newHead.pushBack(procId, 0, 'X');
		while (iter != readySet.end()) {
			newHead.pushBack(iter.process(), iter.time(), iter.state());
			iter.advance();
		}
		readySet = newHead; 
		*/
		ProcList newList;
		ProcIterator iter = readySet.begin();
		while (iter != readySet.end() && iter.process() > procId) {
			newList.pushBack(iter.process(), iter.time(), iter.state());
			iter.advance();
		}
		newList.pushBack(procId, 0, 'X');
		while (iter != readySet.end()) {
			newList.pushBack(iter.process(), iter.time(), iter.state());
			iter.advance();
		}
		readySet = newList;
	}
};

class Preempt : public Priority { //rework
public:
	Preempt() { name = "Preemptive Priority"; }
	int allowance() {
		int tempId = 0;
		int maxId = 0;
		int headTime = 0;
		ProcList newHead;
		ProcIterator iter = readySet.begin();
		while (iter != readySet.end()) {
			tempId = iter.process();
			if (tempId > maxId) {
				maxId = tempId;
				headTime = iter.time();
			}
			iter.advance();
		}
		iter = readySet.begin();
		while (iter != readySet.end() && iter.process() != maxId) {
			iter.advance();
		}
		if (iter != readySet.end()) {
			newHead.pushBack(maxId, iter.time(), iter.state());
		}

		iter = readySet.begin();
		int timesFound = 0; //check for duplicate ProcIds
		while (iter != readySet.end()) {
			if (iter.process() != maxId || timesFound > 0) {
				newHead.pushBack(iter.process(), iter.time(), iter.state());
			}
			else {
				timesFound++; //found head
			}
			iter.advance();
		}
		readySet = newHead;
		return headTime;
	}
};
