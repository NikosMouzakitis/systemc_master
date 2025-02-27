/***********************************************************************

Copyright (C) 2004 - 2011 by Giovanni B. Vece

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

************************************************************************/


/***********************************************************************


 Original Author: Giovanni B. Vece

 Affiliation: Università Politecnica delle Marche (Italy)


************************************************************************/

#include "square_input.h"
#include "power_module.h"


int sc_main(int ac, char* av[]) 
{
	sc_signal<bool> standby_sgn, over_sgn, dtready_sgn, over_sgn2;
	sc_signal<sc_uint<16> > data_sgn;
	sc_signal<sc_uint<16> > res_sgn, res_sgn2;
	

	sc_time tclk(50,SC_NS);
	sc_time delay(10,SC_NS);
	sc_clock clock("clock", tclk, 0.5, delay); 
	
	// square_input power_module

	POWER_MODULE(square_input) squin("squin");
	squin.input(data_sgn);
	squin.standby(standby_sgn);
	squin.output(res_sgn);
	squin.overflow(over_sgn);
	squin.clk(dtready_sgn);
    
	// wrapper sc_module 
	wrapper wr("wrp");
	wr.input(data_sgn);
	wr.standby(standby_sgn);
	wr.output(res_sgn2);
	wr.overflow(over_sgn2);
	wr.output_in(res_sgn2);
	wr.overflow_in(over_sgn2);
	wr.clk(dtready_sgn);
	

	testbench tbc("tbc");
	tbc.standby(standby_sgn);
	tbc.data(data_sgn);
	tbc.data_ready(dtready_sgn);
	tbc.clk(clock);
    
	display dsp("dsp");
	dsp.standby(standby_sgn);
	dsp.overflow(over_sgn);
	dsp.input(data_sgn);
	dsp.result(res_sgn);
	dsp.clk(dtready_sgn);

	

	sc_start(sc_time(650,SC_NS));  

	return 0;
    
}


