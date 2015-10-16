//Sam Lucas, CMPSC 122, Section 001

//**requires adaption to pointer system

#include "scheduler.h"

const int DISKTIME = 200; // how long a disk action requires

void diskRequest( int pid, int clock, int &diskReady, Process tasks[], ProcList &future ) {
	if (diskReady > clock) {
		tasks[pid].addLog(diskReady, 'D');
		diskReady += DISKTIME+1;
	}
	else {
		tasks[pid].addLog(clock, 'D');
		diskReady = clock + DISKTIME+1;
	}
	tasks[pid].addLog(diskReady, '-');
	future.insert(pid, diskReady, 'X');
}

void Scheduler::runScheduler( Process tasks[], int arrival[], int size, int allowance ) {
	int pid;
	int newpid;
	char nextAct;

	for (int i = 0; i < size; i++) {
		future.insert(i, arrival[i], 'X');
		tasks[i].restart();
		tasks[i].addLog(arrival[i], '-');
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
			tasks[pid].run(clock, allowance, nextAct);

			while (!future.empty() && clock >= future.leadTime()) {
				future.popFront(newpid, nextAct);
				addProcess(newpid);
			}
			if (nextAct == 'X')
				addProcess(pid);
			else if (nextAct == 'D')
				diskRequest(pid, clock, diskReady, tasks, future);
}	}	}
