//Sam Lucas, CMPSC 122, Section 001
#include <iostream>
using namespace std;
#include "proclist.h"

ostream &operator<<( ostream &stream, ProcListElement &ele )
{
	stream << "(" << ele.procID << "," << ele.state << "," << ele.time << ")";
	return stream;
}
ostream &operator<<( ostream &stream, ProcList &hist )
{
	for (ProcListElement *curr = hist.head; curr != NULL; curr = curr->next )
		stream << *curr;
	stream << endl;
	return stream;
}

ProcIterator ProcList::begin(){
	return ProcIterator( this, head );
}
ProcIterator ProcList::end(){
	return ProcIterator( this, NULL );
}

void ProcList::pushBack( int procId, int time, char state ){
	ProcListElement *newEle = new ProcListElement( procId, time, state );
	if (head == NULL)
		head = tail = newEle;
	else{
		newEle->prev = tail;
		tail = tail->next = newEle;
}	}

void ProcList::popFront( int &procId, char &state ){
	ProcListElement *temp = head;
	head = head->next;
	if (head == NULL)
		tail = NULL;
	else 
		head->prev = NULL;

	procId = temp->procID;
	state = temp->state;
	delete temp;
}

void ProcList::insert( int procId, int time, char state ){
	ProcListElement *newEle = new ProcListElement( procId, time, state );
	if (head == NULL)
		head = tail = newEle;
	else if (time >= tail->time) {
		newEle->prev = tail;
		tail = tail->next = newEle;
	}
	else if (time < head->time ){
		newEle->next = head;
		head = newEle;
	}
	else{
		ProcListElement *focus = head;
		while (focus->next->time < time) { focus = focus->next; }
		newEle->next = focus->next;
		newEle->prev = focus;
		focus->next->prev = newEle;
		focus->next = newEle;
}	}

ProcIterator ProcIterator::erase(){
	ProcListElement *temp = current;
	ProcIterator nextIt = ProcIterator( list, temp->next );

	if (temp->next == NULL){
		list->tail = temp->prev;
		list->tail->next = NULL;
	}
	else
		temp->next->prev = temp->prev;
	if (temp->prev == NULL){
		list->head = temp->next;
		list->tail->prev = NULL;
	}
	else
		temp->prev->next = temp->next;
	delete temp;
	return nextIt;
}
