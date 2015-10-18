//Sam Lucas, CMPSC 122, Section 001
#include "device.h"
#include "scheduler.h"

Device convert(char act) { //converts the char to equivilant device
	if (act == 'D')
		return disk;
	else if (act == 'N')
		return net;
	else if (act == 'I')
		return console;
	else
		return cpu;
}
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
	cpu.restart();
	disk.restart();
	net.restart();
	console.restart();

	while (!future.empty() || !noneReady()) {
		if (noneReady()) {
			clock = future.leadTime();
			future.popFront(pid, nextAct);
			addProcess(pid);
		}
		else {
			chooseProcess(pid);
			Device *nextD = &convert(nextAct);
			tasks[pid]->run(clock, allowance(pid), nextD);

			while (!future.empty() && clock >= future.leadTime()) {
				future.popFront(newpid, nextAct);
				addProcess(newpid);
			}
			if (nextAct == 'X')
				addProcess(pid);
			else
				nextD->request(pid, clock, tasks, future);
		}
	}	
}
