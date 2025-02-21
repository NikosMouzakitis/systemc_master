#include "systemc.h"

SC_MODULE(dff)
{

	sc_in <bool> din;
	sc_in <bool> clk;
	sc_out <bool> out;

	void implement()
	{
		out = din;
	}
	SC_CTOR(dff)
	{
		cout << "creating a new dff" << endl;
		SC_METHOD(implement);
		sensitive_pos << clk; //call implement every pos edge of the clock.
	}
};
