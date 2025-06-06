/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2004 by all Contributors.
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
 
  stage2.h -- This is the interface file for the stage2 module.
 
  Original Author: Amit Rao, Synopsys, Inc.
 
 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG 

  Name: Pedale Raffaele, Maria Celeste Rago.
  Affiliation: UniversitÓ Politecnica delle Marche (Italy).
  Date: 7 Jan 2009.

  Description of Modification: inclusion of the PKtool header;
                               in1 and in2 converted into augmented signals.

 *****************************************************************************/


#ifndef STAGE2_H
#define STAGE2_H

#include "PKtool.h"

struct stage2 : sc_module {							//by this operation the input signals 1-2 on the input ports are increased
    sc_in_aug<double> sum;   //input 1
    sc_in_aug<double> diff;   //input 2
    sc_out<double> prod;     //output port 1
    sc_out<double> quot;     //output port 2
    sc_in<bool>    clk;      //clock

    void multdiv();          //method providing functionality

    //Constructor
    SC_CTOR( stage2 ) {
	SC_METHOD( multdiv );   //Declare multdiv as SC_METHOD and
        dont_initialize();
        sensitive << clk.pos();  //make it sensitive to positive clock edge 
    }

};

#endif

