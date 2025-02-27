#ifndef POWER_MODULE_H
#define POWER_MODULE_H
#include "and2_gt.h"
// ----------------------------------------------------------------------------
//  CLASS : and2_gt power_module
//  power_module associated to and2_gt sc_module
// -----------------------------------------------------------------------------
POWER_MODULE_CLASS( and2_gt )
{

	PK_USES_ENERGY_MODELS

	// constructor
	POWER_MODULE_CTOR(and2_gt)
	{

		PK_MODULE_SENSITIVITY
		sensitive<<clk.pos();
	};
};

// ----------------------------------------------------------------------------
//  CLASS : wrapper sc_module
//
//  sc_module wrapping a square_input power_module created dynamically
// -----------------------------------------------------------------------------

SC_MODULE(wrapper)
{

	sc_in<sc_uint<16> > i1,i2;
	sc_out<sc_uint<16> > o;
	sc_in_clk clk;


	// power_module pointer
	POWER_MODULE(and2_gt)*  dyn_and2_gt ;
	
	SC_CTOR(wrapper)
	{
		//power_module creation
		dyn_and2_gt = new POWER_MODULE(and2_gt)("dyn_and2_gt");
		//connection instructions
		dyn_and2_gt->i1(i1);
		dyn_and2_gt->i2(i2);
		dyn_and2_gt->o(o);
		dyn_and2_gt->clk(clk);
	};
};
#endif
