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
 
  main.cpp -- This is the top level file instantiating the modules and
              binding ports to signals.
 
  Original Author: Amit Rao, Synopsys, Inc.
 
 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG 

  Name: Pedale Raffaele, Maria Celeste Rago.
  Affiliation: Università Politecnica delle Marche (Italy).
  Date: 7 Jan 2009.

  Description of Modification:  stage1, stage2 and stage3 converted 
                                into power_modules.

 *****************************************************************************/

#include "systemc.h"
#include "power_modules.h"
#include "display.h"
#include "numgen.h"





int sc_main(int ac, char *av[])
{
  

  //Signals
  sc_signal<double> in1;
  sc_signal<double> in2;
  sc_signal<double> sum;
  sc_signal<double> diff;
  sc_signal<double> prod;
  sc_signal<double> quot;
  sc_signal<double> powr;  
  //Clock
  sc_signal<bool>   clk;
  
  numgen N("numgen");               //instance of `numgen' module
  N(in1, in2, clk );                //Positional port binding
  
  POWER_MODULE(stage1) S1("stage1");              //instance of `stage1' power_module
  
  //Named port binding
  S1.in1(in1);
  S1.in2(in2);
  S1.sum(sum);
  S1.diff(diff);
  S1.clk(clk);
  
  POWER_MODULE(stage2) S2("stage2");              //instance of `stage2' power_module
  S2(sum, diff, prod, quot, clk );  //Positional port binding

  POWER_MODULE(stage3) S3("stage3");              //instance of `stage3' power_module
  S3( prod, quot, powr, clk);       //Positional port binding
  
  display D("display");             //instance of `display' module
  D(powr, clk);                     //Positional port binding 

  sc_start(0, SC_NS);               //Initialize simulation
  for(int i = 0; i < 50; i++){
      clk.write(1);
      sc_start( 10, SC_NS );
      clk.write(0);
      sc_start( 10, SC_NS );
  }

  return 0;
}

