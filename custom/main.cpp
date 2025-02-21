#include "systemc.h"


//or 2bit module
SC_MODULE(or2)
{
	
	sc_in <sc_bit> i1,i2;
	sc_out <sc_bit> o;

	void update()
	{
		o = i1 | i2;
	}

	SC_CTOR(or2)
	{
		cout << "creating or2 module" << endl;
		SC_METHOD(update);
		sensitive << i1 << i2;
	}

};

//and 2 bit module
SC_MODULE(and2)
{
	
	sc_in <sc_bit> i1,i2;
	sc_out <sc_bit> o;

	void update()
	{
		o = i1 & i2;
	}

	SC_CTOR(and2)
	{
		cout << "creating and2 module" << endl;
		SC_METHOD(update);
		sensitive << i1 << i2;
	}

};

int sc_main(int argc, char *argv[])
{
	
	sc_signal <sc_bit> i1;
	sc_signal <sc_bit> i2;
	sc_signal <sc_bit> or_out;
	sc_signal <sc_bit> and_out;
		
	//creation of an and2 and an or2 gates	
	or2 gate_or("OR2");
	and2 gate_and("AND2");
	
	//binding of ports and signals of the modules
	gate_or.i1(i1);
	gate_or.i2(i2);
	gate_or.o(or_out);

	gate_and.i1(or_out);
	gate_and.i2(i1);
	gate_and.o(and_out);

	//open vcd file.


	//simulation start	
	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");

	sc_trace(tf,i1,"i1");
	sc_trace(tf,i2,"i2");
	sc_trace(tf,and_out,"out");
	
	sc_start(sc_time(10,SC_NS));
	i1=sc_bit('0');
	i2=sc_bit('0');

	sc_start(sc_time(10,SC_NS));
	i1=sc_bit('0');
	i2=sc_bit('1');

	sc_start(sc_time(10,SC_NS));
	i1=sc_bit('1');
	i2=sc_bit('0');

	sc_start(sc_time(10,SC_NS));
	i1=sc_bit('1');
	i2=sc_bit('1');

	sc_start(sc_time(10,SC_NS));
	i1=sc_bit('0');
	i2=sc_bit('0');

	sc_start(sc_time(10,SC_NS));
	i1=sc_bit('0');
	i2=sc_bit('1');

	sc_start(sc_time(10,SC_NS));
	i1=sc_bit('1');
	i2=sc_bit('0');

	sc_start(sc_time(10,SC_NS));
	i1=sc_bit('1');
	i2=sc_bit('1');


	return (0);
}

