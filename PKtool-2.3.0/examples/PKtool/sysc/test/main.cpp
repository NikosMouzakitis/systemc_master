#include "and2_gt.h"
#include "power_module.h"

int sc_main(int ac, char* av[])
{
	sc_clock clock("clock",10,SC_NS);
	sc_signal<sc_uint<16> > i1_sgn,i2_sgn, o_sgn;   // augmented input port


	// our test module
	//and2_gt gt("test");
	//delcare it as POWER_MODULE
	POWER_MODULE(and2_gt) gt("test");

	gt.i1(i1_sgn);
	gt.i2(i2_sgn);
	gt.o(o_sgn);
	gt.clk(clock);


	// Open a trace file for waveform viewing
	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");
	sc_trace(tf, clock, "clk");
	sc_trace(tf, i1_sgn, "input_1");
	sc_trace(tf, i2_sgn, "input_2");
	sc_trace(tf, o_sgn, "output");

	sc_start(sc_time(10,SC_NS));
	i1_sgn.write(0x2);
	i2_sgn.write(0x32);

	sc_start(sc_time(10,SC_NS));

	i1_sgn.write(0x2);
	i2_sgn.write(0x1);

	sc_start(sc_time(10,SC_NS));

	i1_sgn.write(0x2);
	i2_sgn.write(0xff);

	sc_start(sc_time(10,SC_NS));
	sc_close_vcd_trace_file(tf);

	cout << "simulation finished!" << endl;

	return 0;
}


