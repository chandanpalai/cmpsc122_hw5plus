//Sam Lucas, CMPSC 122, Section 001

//**requires adaption to pointer system
#include "device.h"
#include "scheduler.h"

void Scheduler::runScheduler( Process *tasks[], int arrival[], int size ) {
	int pid;
	int newpid;
	char nextAct;

	for (int i = 0; i < size; i++) {
		future.insert(i, arrival[i], 'X');
		tasks[i]->restart();
		tasks[i]->addLog(arrival[i], '-');
	}

	clock = 0;
	int diskReady = 0;

	while (!future.empty() || !noneReady()) {
		if (noneReady()) {
			clock = future.leadTime();
			future.popFront(pid, nextAct);
			addProcess(pid);
		}
		else {
			chooseProcess(pid);
			tasks[pid]->run(&clock, allowance(), nextAct);

			while (!future.empty() && clock >= future.leadTime()) {
				future.popFront(newpid, nextAct);
				addProcess(newpid);
			}
			if (nextAct == 'X')
				addProcess(pid);
			else if (nextAct == 'D')
				request(pid, clock, tasks, future);
}	}	}
