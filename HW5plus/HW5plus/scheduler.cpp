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
	console.restart();

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
void SRT::insertSort(Process array[], int size) {
	for (int newPos = 1; newPos < size; newPos++) {
		newValue = array[newPos];
		for (pos = newPos; pos > 0 && newValue.getRemainingTime() < array[pos - 1].getRemainingTime(); pos--) {
			array[pos] = array[pos - 1];
		}
		array[pos] = newValue;
	}
}
void SRT::sort(Process array[], int size) {
	divisor = 1 + RAND_MAX / 10000;

	for (int i = 0; i<10000; i++) {
		buckets[i] = new Process[size / 1000];
		bucketSize[i] = 0;
	}
	for (int i = 0; i<size; i++) {
		which = array[i].getRemainingTime() / divisor; //?
		buckets[which][bucketSize[which]]
			= array[i];
		bucketSize[which]++;	
	}
	for (int i = 0; i<10000; i++)
		insertSort(buckets[i], bucketSize[i]);

	fillPos = 0;
	for (which = 0; which < 10000; which++) {
		for (int i = 0; i < bucketSize[which]; i++, fillPos++)
			array[fillPos] = buckets[which][i];
	}
	for (int i = 0; i<10000; i++)
		delete buckets[i];
}