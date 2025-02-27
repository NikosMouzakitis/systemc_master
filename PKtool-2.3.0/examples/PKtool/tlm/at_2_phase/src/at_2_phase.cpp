/**********************************************************************
  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2008 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.
 *********************************************************************/

//=====================================================================
///  @file example_main.cpp
///
///  @brief Example main instantiates the example system top and call 
///  sc_start() 
///
//=====================================================================
//  Original Authors:
//    Bill Bunton, ESLX
//    Anna Keist, ESLX
//    Charles Wilson, ESLX
//    Jack Donovan, ESLX
//=====================================================================

/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
      
	  Name, Affiliation, Date:  Giovanni B. Vece, Universit� Politecnica
	                            delle Marche (Italy).

  Description of Modification:  
                                - Instance of the function pk_set_simtime to
								  set the simulation time in PKtool analysis.
    
 *****************************************************************************/


// define REPORT_DEFINE_GLOBALS in one location only

#define REPORT_DEFINE_GLOBALS

#include "reporting.h"                  // reporting utilities
#include "at_2_phase_top.h"  		    // top module
#include "tlm.h"            			// TLM header


std::ofstream  out_file, data_file;

//=====================================================================
///  @fn sc_main
//  
///  @brief SystemC entry point
//  
///  @details
///    This is the SystemC entry point for the example system.  The argc and argv 
///    parameters are not used.  Simulation runtime is not specified when 
///    �sc_start()� is called, the example�s traffic generator will run to 
///    completion, ending the simulation. 
///
//=====================================================================
int                                     // return status
sc_main                                 // SystemC entry point
  (int   argc                           // argument count
  ,char  *argv[]                        // argument vector
)
{
  out_file.open("out_file.txt");   data_file.open("data_file.txt");
  REPORT_ENABLE_ALL_REPORTING ();

  sc_core::sc_time sim_time(3800, sc_core::SC_NS);
  pk_set_simtime(sim_time);

  example_system_top top("top");        // instantiate a exmaple top module

  sc_core::sc_start();                  // start the simulation

  return 0;                             // return okay status
}
