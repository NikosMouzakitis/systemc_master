#include "systemc.h"
SC_MODULE(first_counter)
{
	sc_in_clk clock;
	sc_in<sc_bit> reset;
	sc_in<sc_bit> enable;
	sc_out<sc_uint<4>> counter_out; //4bit counter.

	//local vars.
	sc_uint<4>	count;
	void incr_count() {
		if(reset.read() == 1)
		{
			count=0;
			counter_out.write(count);
		} else if(enable.read() == 1) {
			count+=1;
			counter_out.write(count);
			cout << "@"<<sc_time_stamp() << " Counter value: " << counter_out.read() << endl;
		}
	}
	SC_CTOR(first_counter)
	{
		cout << "creating first_counter module" << endl;
		SC_METHOD(incr_count);
		sensitive << reset; //sensitive on reset
		sensitive << clock.pos(); //sensitive on positive clock edge.
	}
};
