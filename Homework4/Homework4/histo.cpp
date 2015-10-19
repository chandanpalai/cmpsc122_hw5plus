//Sam Lucas, CMPSC 122, Section 001

//**likely requires changes to account for use of pointer system over char system

#include <iostream>
#include <iomanip>
using namespace std;
#include "process.h"

char convert(Device *d) {
	if (d == &cpu) {
		return 'X';
	}
	else if (d == &console) {
		return 'I';
	}
	else if (d == &net) {
		return 'N';
	}
	else if (d == &disk) {
		return 'D';
	}
}

void displayHistory( Process *history[], int size, int start, int stop ) {
	char data[50];
	Device *curState;
	int focus, time;
	int increment = 1 + (stop - start) / 50; //round upwards

	cout << "Time:  " << setw(3) << start << 
	setw( (stop - start)/increment ) << stop << endl;

	for (int a=0; a<size; a++){
		for (int b=0; b<50; b++)
			data[b] = ' ';

		ProcList &log = history[a]->getLog();
		ProcIterator iter = log.begin();

		//remove 0-time intervals
		ProcIterator iter2 = log.begin();
		iter2.advance();
		while (iter2 != log.end()) {
			if (iter.time() == iter2.time())
				iter = iter.erase();
			else
				iter.advance();
			iter2.advance();
		}
	
		//find beginning
		iter = log.begin();
		if (iter.time() > start)
			focus = (iter.time()-start) / increment;
		else
			focus = 0;	
		time = start + focus*increment;	
	
		curState = iter.state();
		while (time <= stop && time >= iter.time()) {
			curState = iter.state();	// 
			iter.advance();
		}
	
		// fill data for output
		while ( time <= stop && curState != NULL ) {
			while ( time <= stop && time < iter.time() ) {
				data[focus] = convert(curState);
				time += increment;
				focus++;
			}
			curState = iter.state();
			iter.advance();
	
			//catch missing states
			while (curState != NULL && time >= iter.time() ) {
				if (curState == &cpu)
					data[focus-1] = 'X';	
				curState = iter.state();
				iter.advance();
		    }
		}
		//print
		cout << "History: ";
		for (int x = 0; x < 50; x++) {
			cout << data[x];
		} cout << endl;
    }
}

