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

#include "PKtool/types_aug/pk_augdata_base.h"
#include "PKtool/power_models/pk_estimation.h"
#include "PKtool/power_models/pk_model_creator.h"
#include "PKtool/power_models/power_model_b.h"
#include "PKtool/kernel/pk_read_cfg_data.h"
#include "PKtool/kernel/power_module_fcs.h"
#include "PKtool/kernel/power_kernel.h"
#include "PKtool/kernel/pk_kernel_impl.h"
#include "PKtool/kernel/power_module_b.h"



namespace pk_core    
{
     

extern bool pk_error_condition;  

extern bool monitorable_powmod(const char*);
 

static void PK_tool_window_intestation()
{
 static bool first_call = true;
 if(first_call)
 {
  cout<<endl<<endl<<"            PKtool 2.3.0       All rights reserved     "<<endl<<endl<<endl;  
  first_call=false;
 };
};


                                                           

// ----------------------------------------------------------------------------
//  CLASS : power_kernel
// ----------------------------------------------------------------------------
 
 
int power_kernel::pk_counter = -1;     

bool power_kernel::check_monitored()
{ 
 power_module_b* pmb = power_module_b::curr_powmod(); 
 pmb->monitored = pk_core::monitorable_powmod(power_module_b::curr_modname); 
 return pmb->monitored;
};


power_kernel::power_kernel(): index(0), k_impl(0)  
{
 curr_pk(this);
 if( check_monitored() )  initialize(); 
 else
 { create_impl(); k_impl->monitored = false; }                                           
};


void power_kernel::create_impl()   
{ k_impl = new pk_kernel_impl(); };


void power_kernel::erase_impl()  
{ delete k_impl; };


 void power_kernel::initialize()
 { 
  PK_tool_window_intestation();
  ++pk_counter;  
  index = pk_counter;   
  create_impl(); 
 };

 void power_kernel::read_initial_data()
 {  k_impl->read_initial_data();  };
 
 bool power_kernel::power_state_change()
 {  return k_impl->power_state_change(); };
 

 power_model_b* power_kernel::curr_pm() const
 { return k_impl->pm; };


 

 void power_kernel::powerFSM_task()  
 {
  while(true)
  {
   sc_core::wait(sc_core::SC_ZERO_TIME);
   if(power_state_change())
   {
    if( ! curr_pm()->cycle_accurate() ) do_estimation();   
    update_state();  
   }; 
   sc_core::wait();
  };
 };


 void power_kernel::initialize_augs()  
 {
  while(true)
  {
   for(int i=0; i<k_impl->initialization_deltas; ++i) 
                            sc_core::wait(sc_core::SC_ZERO_TIME); 

   unsigned sz = k_impl->inport_aug.size();
   for(unsigned i=0; i<sz; ++i) 
	 k_impl->inport_aug[i]->initialize_();  

   sz = k_impl->inoutport_aug.size();
   for(unsigned i=0; i<sz; ++i) 
	 k_impl->inoutport_aug[i]->initialize_();  

   sz = k_impl->outport_aug.size();
   for(unsigned i=0; i<sz; ++i) 
	 k_impl->outport_aug[i]->initialize_(); 

   sz = k_impl->intsignal_aug.size();
   for(unsigned i=0; i<sz; ++i) 
	 k_impl->intsignal_aug[i]->initialize_(); 
 
   sc_core::wait();
  };
 };



 void power_kernel::update_inport_augs( )
 {
  unsigned size = (k_impl->inport_aug).size();
  for(unsigned i=0; i<size; ++i) 
  {  k_impl->inport_aug[i]->update_data();   };
  size = (k_impl->inoutport_aug).size();
  for(unsigned i=0; i<size; ++i) 
  {  k_impl->inoutport_aug[i]->update_data();   };
 };


 void power_kernel::print_partial_result()
 {
   k_impl->result_file<<"simulation period: [ "<<k_impl->startime<<" - "<<k_impl->endtime<<" ]";
   k_impl->result_file<<"  power state: "<<k_impl->past_st<<endl;
   print_custom_result();
   k_impl->print_partial_est();
 };

 void power_kernel::print_custom_result()    
 {  k_impl->pm->print_custom_result(k_impl->result_file);  }

 void power_kernel::print_total_result()
 {
   k_impl->result_file<<"overall simulation period: [0 - "<<k_impl->endtime<<"]"<<endl<<endl;
   if(!k_impl->one_state) k_impl->result_file<<"total state changes: "<<k_impl->st_changes<<endl<<endl<<endl;
   
   if(k_impl->one_state) print_custom_result();   
   k_impl->pm->print_total_result(k_impl->result_file);
   k_impl->print_total_est();
 };


 power_kernel:: ~power_kernel()  
 { if(k_impl!=0) erase_impl(); };




 void power_kernel::final_action()    
 {
  if( k_impl && (!pk_error_condition) )  
  {
   if(k_impl->monitored)
   {
    #ifdef PK_ENABLE_TLM
    if(k_impl->TLM_on)  k_impl->print_TLM_est();
    else
    {
    #endif
	 
     k_impl->endtime = ( k_impl->set_simtime ? k_impl->sim_time : sc_core::sc_time_stamp() );

     if(!k_impl->one_state) k_impl->set_dynamic_data(k_impl->curr_st); 
     else k_impl->set_dynamic_data(0);
     if( !curr_pm()->cycle_accurate() ) do_estimation();
     if(!k_impl->one_state) this->print_partial_result();
     this->print_total_result();
	#ifdef PK_ENABLE_TLM
    }
   #endif
   }
  }
 }


 void power_kernel::initialization_deltas( int value )
 { k_impl->initialization_deltas = value; };  


 void power_kernel::do_cycle_estimation()
 {  
  k_impl->do_estimation(); 
  k_impl->reset_augs();
 };
 

 void power_kernel::do_estimation()
 {  k_impl->do_estimation(); };


 void power_kernel::update_state()
 {
  this->print_partial_result();
  ++k_impl->st_changes;
  k_impl->update_power_model(); 
  k_impl->past_st = k_impl->curr_st;
  k_impl->startime = k_impl->endtime;    
 };


}  //pk_core  

 











 
