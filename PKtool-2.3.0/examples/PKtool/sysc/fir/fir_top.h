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
 
  fir_top.h --
 
  Original Author: Rocco Jonack, Synopsys, Inc.
 
 *****************************************************************************/
 
/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
      
	  Name, Affiliation, Date:  Giovanni B. Vece, UniversitÓ Politecnoca
	                            delle Marche (Italy).

  Description of Modification:  - Inclusion of the header "power_modules.h";
                                - Inclusion of the conditional macro PK_FIR_RTL;
                                - fir_data1 converted into a power_module.
    
 *****************************************************************************/

#include <systemc.h>
#include "fir_fsm.h"
#include "fir_data.h"
#include "power_modules.h"


#ifdef PK_FIR_RTL

SC_MODULE(fir_top) {

  sc_in<bool>       CLK;
  sc_in<bool>       RESET;
  sc_in<bool>       IN_VALID;
  sc_in<int>        SAMPLE;
  sc_out<bool>      OUTPUT_DATA_READY;
  sc_out<int>       RESULT;

  sc_signal<unsigned> state_out;
  
  fir_fsm  *fir_fsm1;
  POWER_MODULE(fir_data) *fir_data1;    //power_module instance

  SC_CTOR(fir_top) {

      fir_fsm1 = new fir_fsm("FirFSM");
      fir_fsm1->clock(CLK);
      fir_fsm1->reset(RESET);
      fir_fsm1->in_valid(IN_VALID);
      fir_fsm1->state_out(state_out);

      fir_data1 = new POWER_MODULE(fir_data)("FirData");
      fir_data1 -> reset(RESET);
      fir_data1 -> state_out(state_out);
      fir_data1 -> sample(SAMPLE);
      fir_data1 -> result(RESULT);
      fir_data1 -> output_data_ready(OUTPUT_DATA_READY);

    }
};


#endif

