//Sam Lucas, CMPSC 122, Section 001
#include "device.h"
#include "process.h"
void Device::request(int pid, int clock, Process *tasks[], ProcList &future) {
	if (readyTime <= clock)
		readyTime = clock;
	tasks[pid]->addLog(readyTime, action);
	readyTime += duration;
	tasks[pid]->addLog(readyTime, '-');
	future.insert(pid, readyTime, 'X');	
}
Device disk('D', 200),
		net('N', 100),
		console('I', 1000),
		cpu('X', 0);