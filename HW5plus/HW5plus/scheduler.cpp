//Sam Lucas, CMPSC 122, Section 001
#include "device.h"
#include "scheduler.h"

void Scheduler::runScheduler( Process *tasks[], int arrival[], int size ) {
	int pid;
	int newpid;
	char nextAct;
	Device *nextD;

	for (int i = 0; i < size; i++) {
		future.insert(i, arrival[i], 'X');
		tasks[i]->restart();
		tasks[i]->addLog(arrival[i], '-');
	}

	clock = 0;
	cpu.restart();
	disk.restart();
	net.restart();
	keyboard.restart();

	while (!future.empty() || !noneReady()) {
		if (noneReady()) {
			clock = future.leadTime();
			future.popFront(pid, nextAct);
			addProcess(pid);
		}
		else {
			chooseProcess(pid);
			tasks[pid]->run(clock, allowance(), nextD);

			while (!future.empty() && clock >= future.leadTime()) {
				future.popFront(newpid, nextAct);
				addProcess(newpid);
			}
			if(nextD != NULL)
				nextD->request(pid, clock, tasks, future);
		}
	}	
}

void SRT::sort(vector<Process*>& data) {
		for (i = 1; i < data.size(); i++) {
				val = data[i];
				j = i - 1;
				while (j >= 0 && data[j]->getRemainingTime() > val->getRemainingTime()) {
						data[j + 1] = data[j];
						j = j - 1;
				}
				data[j + 1] = val;
		}
}