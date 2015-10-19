//Sam Lucas, CMPSC 122, Section 001
#include <iostream>
using namespace std;
#include "proclist.h"

ostream &operator<<(ostream &stream, ProcListElement &ele) {
	stream << "(" << ele.procID << "," << ele.state << ","
		<< ele.time << ")";
	return stream;
}
ostream &operator<<(ostream &stream, ProcList &hist) {
	for (ProcListElement *curr = hist.head; curr != NULL; curr = curr->next)
		stream << *curr;
	stream << endl;
	return stream;
}
ProcIterator ProcList::begin() {
	return ProcIterator(this, head);
}
ProcIterator ProcList::end() {
	return ProcIterator(this, NULL);
}
void ProcList::pushBack(int procId, int time, char state) {
	ProcListElement *newEle = new ProcListElement(procId, time, state);
	if (head == NULL)
		head = tail = newEle;
	else {
		newEle->prev = tail;
		tail = tail->next = newEle;
	}
}
void ProcList::popFront(int &procId, char &state) {
	ProcListElement *removal = head;
	head = head->next;
	if (head == NULL)
		tail = NULL;
	else
		head->prev = NULL;

	procId = removal->procID;
	state = removal->state;
	delete removal;
}
void ProcList::insert(int procId, int time, char state) {
	ProcListElement *newEle = new ProcListElement(procId, time, state);
	if (head == NULL)
		head = tail = newEle;
	else if (time < head->time) {
		newEle->next = head;
		head = newEle;
	}
	else if (time >= tail->time) {
		newEle->prev = tail;
		tail = tail->next = newEle;
	}
	else {
		ProcListElement *scan;
		for (scan = head; scan->next->time < time; scan = scan->next) {}
		newEle->next = scan->next;
		newEle->prev = scan;
		scan->next->prev = newEle;
		scan->next = newEle;
	}
}
ProcIterator ProcIterator::erase() {
	ProcListElement *focus = current;
	ProcIterator nextEle = ProcIterator(list, focus->next);

	if (focus->next == NULL) {
		list->tail = focus->prev;
		list->tail->next = NULL;
	}
	else
		focus->next->prev = focus->prev;
	if (focus->prev == NULL) {
		list->head = focus->next;
		list->tail->prev = NULL;
	}
	else
		focus->prev->next = focus->next;
	delete focus;
	return nextEle;
}