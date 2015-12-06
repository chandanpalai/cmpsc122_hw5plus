//Sam Lucas, CMPSC 122, Section 001
#include <iostream> 
#include <iomanip>
#include "process.h"
#include <string>
using namespace std;

void displayHistory(Process *history[], int size, int start, int stop) {
	char data[60], curState;
	int focus, time;
	int increment = 1 + (stop - start) / 60; //range for each char on screen, rounded upwards
	int down = 0, interactive = 0, comp = 0; //for tracking types of processes in history
	int avgTurn = 0, avgResp = 0, maxResp = 0, nonInteractive = 0, startTime; //stats used to calculate turnaround/response times
	ProcList interactives; //list of interactive processes used to calculate repsonse times

	//prints ranges beside the scheduler name
	cout << setw(7) << " " << "Total Time Frame: " << start << "-" << stop;
	cout << "   Time Range Per Char: " << (1 + (stop - start) / 60) << endl;

	//top frame of box
	cout << setw(9);
	for (int v = 0; v < (((stop - start) / increment)+2); v++) { cout << "_"; }
	cout << endl << setw(8) << "|" << setw(((stop - start) / increment) + 3) << "|" << endl;

	//begin processing each scheduler
	for (int a = 0; a<size; a++) {
		for (int b = 0; b<60; b++)
			data[b] = ' ';

		//find beginning of process log
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
			focus = (iter.time() - start) / increment;
		else focus = 0;
			time = start + focus*increment;

		curState = iter.state();
		while (time <= stop && time >= iter.time()) {
			curState = iter.state();	// 
			iter.advance();
		}
		// fill data for output
		while (time <= stop && curState != 'Q') {
			while (time <= stop && time < iter.time()) {
				data[focus] = curState;
				time += increment;
				focus++;
			}
			curState = iter.state();
			if(curState != 'Q') iter.advance();

			//catch missing states
			while (curState != 'Q' && time >= iter.time()) {
				if (curState == 'X')
					data[focus - 1] = 'X';
				curState = iter.state();
				iter.advance();
			}
		}
		//print
		cout << "Proc " << a << ":| ";
		for (int x = 0; x < 60; x++)
			cout << data[x];
		cout << "|" << endl;
	}
	//print bottom frame
	cout << setw(8) << "|";
	for (int w = 0; w <= (((stop - start) / increment)+1); w++) { std::cout << "_"; }
	cout << "|" << endl;

	//look thru processes,count times between, and increment types
	for (int a = 0; a < size; a++) {
		ProcList &log = history[a]->getLog();
		ProcIterator iter = log.begin();
		time = startTime = iter.time();
		curState = iter.state();

		if (!(history[a]->isInteractive())) {
			if (history[a]->isDown()) down++;
			else comp++;
			nonInteractive++;
			time = iter.time();

			//find end
			while (time <= stop && curState != 'Q') {
				iter.advance();
				time = iter.time();
				curState = iter.state();
			}
			avgTurn += (time - startTime);
		}
		else {
			interactive++;
			time = iter.time();
			curState = iter.state();
			while (time <= stop && curState != 'Q') {
				if (curState == 'I') {
					interactives.insert(time, time + 1000, '~');
				}  
				iter.advance();
				time = iter.time();
				curState = iter.state();
			}
		}
	}
	std::cout << setw(7) << "";
	if (nonInteractive != 0) { //if there were non-interactive proocesses print the stats
		avgTurn /= nonInteractive;
		cout << "Avg Turnaround: " << avgTurn;
	}
	else {
		cout << "Avg Turnaround: n/a";
	}
	cout << setw(3) << "";

	if (interactive != 0) { //if there were interactive processes print the stats
		interactives.pushBack(0, 0, 'Q');
		ProcIterator iter = interactives.begin();
		int xEnd = iter.time(); int xStart;
		iter.advance();
		while (iter != interactives.end() && iter.state() != 'Q') {
			xStart = iter.process();
			avgResp += (xStart - xEnd);
			if ((xStart - xEnd) > maxResp)
				maxResp = xStart - xEnd;
			xEnd = iter.time();
			iter.advance();
		}
		avgResp /= interactive;
		cout << "Avg Response: " << avgResp << setw(3) << "";
		cout << "Max Response: " << maxResp;
	}
	else {
		cout << "Avg Response: n/a" << setw(3) << "";
		cout << "Max Response: n/a";
	}
	//print out # of each process type
	cout << endl << setw(7) << " " << "Computations: " << comp << setw(3) << " ";
	cout << "Downloads: " << down << setw(3) << "";
	cout << "Interactives: " << interactive << endl << endl << endl;
}