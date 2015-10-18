#include "device.h"
#include "process.h"

//  Simulate a request to an I/O device
//  Parameters:
//      pid	(input int)		which process is making the request
//      clock	(input int)		time at which request is made
//      tasks	(modified array)	Process information (to record events)
//      future	(modified ProcList)	record when operation is complete
void Device::request( int pid, int clock, Process *tasks[], ProcList &future ) {
	if (readyTime > clock) {
		tasks[pid]->addLog(readyTime, action);
		readyTime += duration + 1;
	}
	else {
		tasks[pid]->addLog(clock, action);
		readyTime = clock + duration + 1;
	}
	tasks[pid]->addLog(readyTime, '-');
	future.insert(pid, readyTime, 'X');
}

Device disk( 'D', 200 ),
        net( 'N', 100 ),
    console( 'I', 1000 ),
        cpu('X',0);