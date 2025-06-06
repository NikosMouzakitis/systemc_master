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
 
  stimulus.h -- 
 
  Original Author: Rocco Jonack, Synopsys, Inc.
 
 *****************************************************************************/
 
/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
 
      Name, Affiliation, Date:
  Description of Modification:
    
 *****************************************************************************/

SC_MODULE(stimulus) {

  sc_out<bool> reset;
  sc_out<bool> input_valid;   
  sc_out<int>  sample;  	    
  sc_in<bool>  CLK;

  sc_int<8>     send_value1;
  unsigned cycle;

  SC_CTOR(stimulus)
  {
      SC_METHOD(entry);
      dont_initialize();
      sensitive << CLK.pos();
      send_value1 = 0;
      cycle       = 0;
  }  
  void entry();
};

