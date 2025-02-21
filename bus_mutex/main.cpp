#include "systemc.h"

SC_MODULE(sc_mutex_example)
{
	sc_in <bool> clock;
	int cnt;
	sc_mutex bus;
	

	void do_bus(int who)
	{
		cout << "@" << sc_time_stamp() << "  bus access by instance[ " << who << " ]" << endl;
	}
	
	void do_test1() {
		while(true)
		{
			wait();
			cout << "@" << sc_time_stamp() << " Checking mutex instance 0" <<endl; ;
			
			if(bus.trylock() != -1) {
				cout << "@" << sc_time_stamp() << " Got mutex for instance 0" << endl;
				cnt++;
				do_bus(0);
				wait(2);
				cout << "@" << sc_time_stamp() << " unlocking mutex by instance 0" << endl;
				bus.unlock();
			}
			if(cnt >= 3)
			{
				sc_stop();
			}
		}
	}
	
	void do_test2() {
		while(true)
		{
			wait();

			cout << "@" << sc_time_stamp() << " Checking mutex instance 1" <<endl; ;
			bus.lock(); //wait till to get it.
			cout << "@" << sc_time_stamp() << " Got mutex for instance 1" << endl;
			do_bus(1);
			wait(3);
			cout << "@" << sc_time_stamp() << " unlocking mutex by instance 1" << endl;
			bus.unlock();
		}
	}



	SC_CTOR(sc_mutex_example)
	{

		cnt = 0;
	//	SC_CTHREAD(do_test1,clock.pos());
	//	SC_CTHREAD(do_test2,clock.pos());
		SC_THREAD(do_test1);
		sensitive << clock.pos();
		SC_THREAD(do_test2);
		sensitive << clock.pos();
	}
};
int sc_main(int argc, char *argv[])
{
	sc_clock clock("my_clock",1,0.5);

	sc_mutex_example object("wait obj");

	object.clock(clock);

	sc_start(sc_time(0,SC_NS));
	sc_start();

	return 0;
}
