//Sam Lucas, CMPSC 122, Section 001
#include "device.h"
#include "process.h"
#include <stdlib.h>
#include <string>

void Device::request(int pid, int clock, Process *tasks[], ProcList &future) {
	if (readyTime <= clock)
		readyTime = clock;
	tasks[pid]->addLog(readyTime, action);
	readyTime += duration;
	tasks[pid]->addLog(readyTime, '-');
	future.insert(pid, readyTime, 'X');	
}

void Console::request(int pid, int clock, Process *tasks[], ProcList &future) {
	if (readyTime <= clock)
		readyTime = clock; //readyTime synced up with clock
	tasks[pid]->addLog(readyTime, action);
	readyTime += duration;
	tasks[pid]->addLog(readyTime, '-');

	int launch = rand() % 7; //0-6; roughly 86% chance of launching new process
	int waitTime = rand() % 600 + 400; //400-1000; range of time delay before new process is started by user

	if (launch > 0) { //launch new process
		int type;
		if (tasks[pid]->nextRequest[tasks[pid]->currentCycle] == NULL)//determine if interactive process is ending
			type = rand() % 7; //0-6; 66% chance for interactive, 33% chance for the other two
		else
			type = rand() % 2;//otherwise 50/50 for Computation or Download

		//find # of non-null pointers
		int j = 0;
		while (tasks[j] != NULL && j < 10) { j++; }

		//choose type of process to insert
		if (j >= 9) {
			//cout << "(*)"; //signifies process overflow of max 10 allowed
		}
		else if (type == 0)
			tasks[j] = new Computation(j);
		else if (type == 1)
			tasks[j] = new Download(j);
		else
			tasks[j] = new Interact(j);
		if (j < 9) {
			//insert new process followed by continued interaction
			future.insert(j, (readyTime + waitTime), 'X');
			tasks[j]->restart();
			tasks[j]->addLog((readyTime + waitTime), '-');
		}
		future.insert(pid, readyTime + waitTime + 1, 'X'); //use same waiting period before reentering interactive process
	}
	else{ //no new process
		future.insert(pid, readyTime, 'X'); //no wait time since no user initiated actions
	}
}

Device disk('D', 200),
		net('N', 100), //removed console('I', 1000)
		cpu('X', 0);
Console keyboard('I', 1000);