/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2006 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************
 
  fir.h -- 
 
  Original Author: Rocco Jonack, Synopsys, Inc.
 
 *****************************************************************************/
 
/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
      
	  Name, Affiliation, Date:  Giovanni B. Vece, UniversitÓ Politecnoca
	                            delle Marche (Italy).

  Description of Modification:  Inclusion of the PKtool header. 
								
							    
    
 *****************************************************************************/


#ifndef FIR_H
#define FIR_H

#include "PKtool.h"

SC_MODULE(fir) {
  
  sc_in<bool>  reset;
  sc_in<bool>  input_valid;        
  sc_in<int>   sample;  	    
  sc_out<bool> output_data_ready;
  sc_out<int>  result;
  sc_in_clk    CLK;

  sc_int<9> coefs[16];

  SC_CTOR(fir)
     {      
      SC_CTHREAD(entry, CLK.pos());
	  reset_signal_is(reset,true);
      #include "fir_const.h"
    }
  
  void entry();
};



#endif

