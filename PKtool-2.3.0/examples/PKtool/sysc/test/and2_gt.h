#ifndef SQUARE_INPUT_H
#define SQUARE_INPUT_H

#include "systemc.h"
#include "PKtool.h"

// ----------------------------------------------------------------------------
//  CLASS : and2_gt sc_module
//  main sc_module considered in this example
// -----------------------------------------------------------------------------

SC_MODULE(and2_gt)
{


	sc_in_aug<sc_uint<16> > i1,i2;	// augmented input ports
	sc_out_aug<sc_uint<16> > o;		// augmented output port
	sc_in_clk clk;

	void process()
	{
		o.write(i1.read() & i2.read());
	};

	SC_CTOR(and2_gt) {
		std::cout << "and gate constructor" << std::endl;
		SC_METHOD(process);
		sensitive << clk.pos();
	}

};

#endif
