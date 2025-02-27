/***********************************************************************

Copyright (C) 2004 - 2015 by Giovanni B. Vece

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

#ifndef POWER_KERNEL_H
#define POWER_KERNEL_H

#include <iostream>
#include <vector>
#include "PKtool/types_aug/pk_aug_if.h"
#include "PKtool/utils/pk_iostream.h"
#include "PKtool/kernel/pk_read_cfg_data.h"

#ifdef PK_ENABLE_TLM  

#include "PKtool/tlm/pk_tlm_socket_base.h"

#endif



namespace pk_core    
{


class power_model_b;
class power_kernel;
class pk_state_fc;
class pk_dyndata_fc;
class pk_kernel_impl;
class pk_estimation_type;
class pk_set_estype_b;



// ----------------------------------------------------------------------------
//  CLASS : power_kernel
//
//  class related to Power Kernel routines
// ----------------------------------------------------------------------------




class power_kernel 
{

 friend class power_model_b;
 friend struct pk_sensitivity_handler;
 friend class power_module_b;
 friend class pk_set_estype_b;
 friend struct pk_initializer;
 friend class pk_state_fc;
 friend class pk_dyndata_fc;
 friend struct pk_set_est_type_b;
 friend class pk_core::pk_read_cfg_data;
 #ifdef PK_ENABLE_TLM  
  friend struct pk_tlm::pk_enable_tlmfc;    
 #endif

 
 private:
   

 bool check_monitored();

 void create_impl();   

 void erase_impl();    

 void initialize();
 
 bool power_state_change();

 void update_inport_augs( );

 void initialize_augs(); 

 void print_partial_result();

 void print_custom_result(); 

 void print_total_result();
                                                    
                                                                                   
 // constructor
 
 power_kernel();

 power_model_b* curr_pm() const;
   

 void powerFSM_task();

 void final_action();    

 // destructor

 ~power_kernel();   


 void initialization_deltas(int);

 void read_initial_data();
 
 static power_kernel* curr_pk( power_kernel* pk = 0 )
 {
  static power_kernel* prev_pk_ = 0;   
  static power_kernel* curr_pk_ = 0;  
  if(pk)
  {
   prev_pk_ = curr_pk_; 
   curr_pk_ = pk; 
   return prev_pk_;    
  }
  else  return curr_pk_;  
  
 };


 private:

 
 void do_cycle_estimation();

 void do_estimation();

 void update_state();

 static int pk_counter;    
 int index;   

 pk_kernel_impl* k_impl;


 private:

 // disabled

 power_kernel(const power_kernel&);
 power_kernel& operator = (const power_kernel&);
 
};


}  //pk_core  


#endif



