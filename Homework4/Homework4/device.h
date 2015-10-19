//#include "proclist.h"

class Process;
class Device {
    private:
		//ProcList requests;	<- not sure if needed
		char action;		// letter used for display
		int duration;		// how long the operation might take
		int readyTime;		// when next operation may start

    public:
		Device( char a, int d ) : action(a), duration(d), readyTime(0) { }
		void restart() {
		    readyTime = 0;
		}
		void request( int, int, Process* [], ProcList & );
};
extern Device disk, net, console, cpu; // extern meaning they are defined elsewhere (in the.cpp file)