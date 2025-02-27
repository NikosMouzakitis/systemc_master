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



#ifndef POWER_MODULE_H
#define POWER_MODULE_H

#include "square_input.h"

//uncomment the below macro for enabling a three-power-state configuration.

//#define POWER_STATE_ON   


// ----------------------------------------------------------------------------
//  CLASS : square_input power_module
//
//  power_module associated to square_input sc_module
// -----------------------------------------------------------------------------


POWER_MODULE_CLASS( square_input )
{

 #ifdef POWER_STATE_ON

 #include "powerFSM.h"

 #endif


  PK_USES_ENERGY_MODELS 
  

  // constructor

 
  POWER_MODULE_CTOR(square_input)
  {      
   
   #ifdef POWER_STATE_ON
     stb_cnt = 1;
   #endif


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

 sc_in<bool> standby;
 sc_in<sc_uint<16> > input;   
 sc_out<bool> overflow;
 sc_out<sc_uint<16> > output; 
 sc_in_clk clk;

 // dummy ports for connecting output and overflow ports 

 sc_in<bool> overflow_in;
 sc_in<sc_uint<16> > output_in;


 // power_module pointer 

 POWER_MODULE(square_input)*  dyn_sqin ;


 SC_CTOR(wrapper)
 {
  //power_module creation

  dyn_sqin = new POWER_MODULE(square_input)("dyn_sqin");
  
  //connection instructions

  dyn_sqin->input(input);
  dyn_sqin->standby(standby);
  dyn_sqin->output(output);
  dyn_sqin->overflow(overflow);
  dyn_sqin->clk(clk);	
  
 };

};




#endif



