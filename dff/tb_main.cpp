#include "systemc.h"
#include "main.cpp"


int sc_main(int argc, char *argv[])
{

	sc_signal<bool> din;
	sc_clock clk("clk",10,SC_NS);	
	sc_signal<bool> out;


	dff ff("dff");
	ff.din(din);
	ff.clk(clk);
	ff.out(out);
	

	sc_trace_file *tf = sc_create_vcd_trace_file("dff_waveform");
	sc_trace(tf,din, "din");
	sc_trace(tf,clk, "clk");
	sc_trace(tf,out, "out");

	//din 0
	din = sc_bit(0);

	sc_start(40,SC_NS);
	//din 1
	din = sc_bit(1);

	sc_start(40,SC_NS);

	sc_close_vcd_trace_file(tf);

	return 0;
}
