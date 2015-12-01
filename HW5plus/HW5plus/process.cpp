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
    bursts = 6 + rand() % 4; //increased from 4 & 3
    for (int i=0; i < bursts; i++)
    {
        usages[i] = 300 + rand() % 160; //increased from 200 & 120
		nextRequest[i] = &disk;
    }
    nextRequest[bursts-1] = NULL;
	remainingTime = usages[0];
}
Download::Download( int id ) {
    myId = id;
    bursts = 13; //increased from 9
    for (int i=0; i < bursts; i++)
    {
        usages[i] = 60 + rand() % 30; //increased from 40 & 20
	if (i%2 == 0)
	    nextRequest[i] = &net;
	else
	    nextRequest[i] = &disk;
    }
    nextRequest[bursts-1] = NULL;
	remainingTime = usages[0];
}
Interact::Interact( int id ) {
    myId = id;
    bursts = 6; //increased from 4
    for (int i=0; i < bursts; i++)
    {
        usages[i] = 50 + rand() % 30; //increased from 30 & 20
		nextRequest[i] = const_cast<Console *>(&keyboard);
    }
    nextRequest[bursts-1] = NULL;
	remainingTime = usages[0];
}
