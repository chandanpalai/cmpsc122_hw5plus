//Sam Lucas, CMPSC 122, Section 001
#include "device.h"
#include "scheduler.h"

void Scheduler::runScheduler( Process *tasks[], int arrival[], int size ) {
	int pid;
	int newpid;
	Device *nextD;

	for (int i = 0; i < size; i++) {
		future.insert(i, arrival[i], new Device('X', 0));
		tasks[i]->restart();
		tasks[i]->addLog(arrival[i], '-');
	}

	clock = 0;
	cpu.restart();
	disk.restart();
	net.restart();
	console.restart();

	while (!future.empty() || !noneReady()) {
		if (noneReady()) {
			clock = future.leadTime();
			future.popFront(pid, nextD);
			addProcess(pid);
		}
		else {
			chooseProcess(pid);
			tasks[pid]->run(clock, allowance(pid), nextD);

			while (!future.empty() && clock >= future.leadTime()) {
				future.popFront(newpid, nextD);
				addProcess(newpid);
			}
			nextD->request(pid, clock, tasks, future);
		}
	}	
}
