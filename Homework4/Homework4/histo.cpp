//Sam Lucas, CMPSC 122, Section 001

//**likely requires changes to account for use of pointer system over char system

#include <iostream>
#include <iomanip>
using namespace std;
#include "process.h"

void displayHistory( Process *history[], int size, int start, int stop ) {
	char data[50], curState;
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
		while ( time <= stop && curState != 'Q' ) {
			while ( time <= stop && time < iter.time() ) {
				data[focus] = curState;
				time += increment;
				focus++;
			}
			curState = iter.state();
			iter.advance();
	
			//catch missing states
			while (curState != 'Q' && time >= iter.time() ) {
				if (curState == 'X')
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

