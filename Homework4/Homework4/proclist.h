//Sam Lucas, CMPSC 122, Section 001
#include <iostream>
using namespace std;

#ifndef PROCLIST
#define PROCLIST

// List of Process History Information
// This is a simple linked list, all of whose elements record
// information about a process in a simulated process scheduler.
// This list data structure will be used for three different purposes:
// -- a record of the past history of a particular process
// -- a collection for the job scheduler of processes currently wishing to run
// -- a task list for known future events for the simulation
//
class ProcIterator;		// forward type declarations
class ProcList;			// since they all interact

class ProcListElement {
	friend class ProcList;
	friend class ProcIterator;
	friend ostream& operator<<(ostream &, ProcListElement &);
	friend ostream& operator<<(ostream &, ProcList &);

private:
	int  procID;
	int  time;
	char state;
	ProcListElement *next;
	ProcListElement *prev;
	ProcListElement(int i, int t, char s) :
		procID(i), time(t), state(s), next(NULL), prev(NULL) { }
};
class ProcList {
	friend class ProcIterator;
	friend ostream& operator<<(ostream &, ProcList &);
private:
	ProcListElement *head, *tail;

public:
	ProcList() : head(NULL), tail(NULL) { }
	~ProcList() { // destructor
		clear();
	}
	bool empty() {
		return head == NULL;
	}
	int leadTime()	 {
		return head->time;
	}
	int tailTime()	{
		return tail->time;
	}
	void clear() {
		int i; char c; //placeholders
		while (head != NULL)
			popFront(i, c);
	}
	ProcIterator begin();
	ProcIterator end();

	void pushBack(int, int, char);
	void insert(int, int, char);
	void popFront(int&, char&);	
};
class ProcIterator {
	friend class ProcList;
private:
	ProcList *list;
	ProcListElement *current;
	ProcIterator(ProcList *l, ProcListElement *e) :
		list(l), current(e) { }

public:
	bool operator!=(ProcIterator other) {
		return list != other.list || current != other.current;
	}
	int process() const { return current->procID; };
	int time() const { return current->time; };
	char state() const { return current->state; };
	void advance() { current = current->next; }
	ProcIterator erase();
};
#endif