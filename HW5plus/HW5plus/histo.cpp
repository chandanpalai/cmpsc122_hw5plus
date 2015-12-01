//Sam Lucas, CMPSC 122, Section 001
#include <iostream> 
#include <iomanip>
#include "process.h"
using namespace std;

#include <windows.h>
#include <sstream>

void displayHistory(Process *history[], int size, int start, int stop) {
	char data[100], curState;
	int focus, time;
	int increment = 1 + (stop - start) / 100; //round upwards

	//cout << "Time:  " << setw(3) << start <<
	//	setw(((stop - start) / increment)+2) << stop << endl;

	std::cout << "   Time: " << start;
	for (int v = 0; v < ((stop - start) / increment)-3; v++) { std::cout << "_"; }
	std::cout << stop << endl; 
	std::cout << setw(10) << "|" << setw(((stop - start) / increment) + 2) << "|" << endl;

	//cout << "         |";
	//for (int v = 0; v <= ((stop - start) / increment); v++) { cout << "_"; }
	//cout << "|" << endl;

	for (int a = 0; a<size; a++) {
		for (int b = 0; b<100; b++)
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
			focus = (iter.time() - start) / increment;
		else
			focus = 0;
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
			iter.advance();

			//catch missing states
			while (curState != 'Q' && time >= iter.time()) {
				if (curState == 'X')
					data[focus - 1] = 'X';
				curState = iter.state();
				iter.advance();
			}
		}
		//print
		std::cout << "History: |";
		for (int x = 0; x < 100; x++) {
			std::cout << data[x];
		} std::cout << "|" << endl;
	}
	std::cout << setw(10) << "|";
	for (int w = 0; w <= ((stop - start) / increment); w++) { std::cout << "_"; }
	std::cout << "|" << endl;

	int avgTurn = 0; 
	int avgResp = 0, resp = 0;
	int maxResp = 0;
	int interactive = 0, nonInteractive = 0;
	int startTime;
	ProcList interactives;
	for (int a = 0; a < size; a++) {
		ProcList &log = history[a]->getLog();
		ProcIterator iter = log.begin();
		time = startTime = iter.time();
		curState = iter.state();

		if (!(history[a]->isInteractive())) {
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
	std::cout << setw(10) << "";
	if (nonInteractive != 0) {
		avgTurn /= nonInteractive;
		std::cout << "Avg Turnaround: " << avgTurn;
	}
	else {
		std::cout << "Avg Turnaround: n/a";
	}
	std::cout << setw(5) << "";

	if (interactive != 0) {
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
		std::cout << "Avg Response: " << avgResp << setw(5) << "";
		std::cout << "Max Response: " << maxResp << endl << endl;
	}
	else {
		std::cout << "Avg Response: n/a" << setw(5) << "";
		std::cout << "Max Response: n/a" << endl << endl;
	}
}