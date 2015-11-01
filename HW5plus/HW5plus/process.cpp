//Sam Lucas, CMPSC 122, Section 001
#include "process.h"
#include "device.h"

void Process::run( int &clock, int allowance, Device *&next) {
	addLog(clock, 'X');
	if (allowance >= remainingTime) {
		clock += remainingTime;
		next = nextRequest[currentCycle];
		currentCycle++;
		remainingTime = usages[currentCycle];
	}
	else {
		clock += allowance;
		remainingTime -= allowance;
		next = &cpu;
	}
	if (next == NULL)
		addLog(clock, 'Q');
	else
		addLog(clock, '-');
}

Computation::Computation( int id ) {
    myId = id;
    bursts = 4 + rand() % 3;
    for (int i=0; i < bursts; i++)
    {
        usages[i] = 200 + rand() % 120;
		nextRequest[i] = &disk;
    }
    nextRequest[bursts-1] = NULL;
}
Download::Download( int id ) {
    myId = id;
    bursts = 9;
    for (int i=0; i < bursts; i++)
    {
        usages[i] = 40 + rand() % 20;
	if (i%2 == 0)
	    nextRequest[i] = &net;
	else
	    nextRequest[i] = &disk;
    }
    nextRequest[bursts-1] = NULL;
}
Interact::Interact( int id ) {
    myId = id;
    bursts = 4;
    for (int i=0; i < bursts; i++)
    {
        usages[i] = 30 + rand() % 20;
		nextRequest[i] = const_cast<Device *>(&console);
    }
    nextRequest[bursts-1] = NULL;
}