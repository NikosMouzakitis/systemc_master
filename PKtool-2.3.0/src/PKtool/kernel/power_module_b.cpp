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

#include "PKtool/kernel/power_module_b.h"
#include "PKtool/kernel/pk_kernel_impl.h"
#include "PKtool/utils/pk_report_ids.h"  
#include "PKtool/utils/pk_report.h"
#include "PKtool/utils/pk_report_fcs.h" 
#include "PKtool/power_models/pk_library_handler.h"

#ifdef PK_ENABLE_TLM   

#include "PKtool/tlm/pk_tlm_socket_base.h"

#endif


namespace
{
 std::string message;


 const char* error_msg1()
 { 
   message.clear();
   message += " a pk_final_action_helper object ";
   message += " has been instanced in the design.";
   return message.c_str();
 };

 const char* error_msg2()
 { 
   message.clear();

   message += "A null pointer parameter has been passed  ";
   message += "to the static method power_module_b::curr_powmod ";
   message += "in its first invocation. ";  message += "\n";

   return message.c_str();
 };

};



namespace pk_core    
{

 


 extern const sc_core::sc_time& pk_simtime();




 std::map<const char*, pk_aug_local*> locdata_mod;  
 

// ----------------------------------------------------------------------------
//  CLASS : pk_final_action_helper  
// ----------------------------------------------------------------------------


power_module_b* pk_final_action_helper::powmod_h[PK_MAX_POWER_MODULE_NB];

int pk_final_action_helper::counter = 0;


 pk_final_action_helper::pk_final_action_helper()
 { 
  ++counter;
  if(counter>1)
  { PK_REPORT_ERROR( PK_NON_ALLOWED_OBJECT_INSTANCED_, error_msg1() );  }
  for(int i=0; i<PK_MAX_POWER_MODULE_NB; ++i) powmod_h[i] = 0; 
 
 }


pk_final_action_helper::~pk_final_action_helper()
{
 for(int i=0; i<PK_MAX_POWER_MODULE_NB; ++i) 
 {
  if(powmod_h[i]) powmod_h[i]->final_action();
 };

};

pk_final_action_helper final_action_obj;



// ----------------------------------------------------------------------------
//  CLASS : power_module_b
// ----------------------------------------------------------------------------


const char* power_module_b::curr_modname=""; 


power_module_b* power_module_b::curr_powmod( power_module_b* pmb )
{
 static power_module_b* curr_pmb = pmb;
 if(pmb)
 {
  curr_pmb = pmb;
  return curr_pmb;
 }
 else
 {
  if(!curr_pmb)
  { PK_REPORT_ERROR( PK_WRONG_FUNCTION_USE_, error_msg2() );  };
  return curr_pmb;
 };
};

//constructor

power_module_b::power_module_b(const char* nm): 
	   sc_module( compose_pmb_nm(nm) ), scp(this), initialized(false), 
	   one_state(pk.k_impl->one_state), final_action_done(false),  stabilization_deltas(PK_STABILIZATION_DELTAS)
	   #ifdef PK_ENABLE_TLM
	      ,TLMfc_pmodels(pk.k_impl->target_fc_data)  
       #endif
	   
 { 
  if(monitored)
    locdata_mod[nm] = &(pk.k_impl->local_aug);  
  else
     locdata_mod[nm] = 0;
  psh = new pk_sensitivity_handler(pk);  
 };

void power_module_b::initialize()   
{  
 initialized = true;
 
 if(monitored)         
 {
  pk_core::pk_read_cfg_data rcdata_obj(pk.k_impl);   
  int option = rcdata_obj.read_options();                               
  if(option == 3) 
  {
   monitored = false;
   rcdata_obj.no_monitoring();
  }
  else monitored = true;
 
   
  if(monitored)
  {
   for(int i=0; i<PK_MAX_POWER_MODULE_NB; ++i)    
   {
	if(!pk_final_action_helper::powmod_h[i]) 
	      { pk_final_action_helper::powmod_h[i] = this; break; }
   }; 


   pk_kernel_impl* k_impl = pk.k_impl;   
   if( pk_kernel_impl::pk_code_cfg_reg[pk.index].state_nb == 0) 
	      pk_kernel_impl::pk_code_cfg_reg[pk.index].state_nb = 1; 
    k_impl->state_nb = pk_kernel_impl::pk_code_cfg_reg[pk.index].state_nb;
   if(k_impl->state_nb == 1) k_impl->one_state = true;


   k_impl->est_type = k_impl->modlib_h->est_type.est_type();  

   rcdata_obj.read_cfg_data_();

   unsigned st_nb = k_impl->state_nb;  
   for(unsigned j=0; j<=st_nb; ++j)  
   {  
    k_impl->state_fc_pnts[j] = pk_kernel_impl::pk_code_cfg_reg[pk.index].state_fc_pnts[j];   
    k_impl->dyndata_fc_pnts[j] = pk_kernel_impl::pk_code_cfg_reg[pk.index].dyndata_fc_pnts[j];  
   };
 
   k_impl->total_est.set_type(k_impl->est_type);  
   k_impl->partial_est.set_type(k_impl->est_type); 
   #ifdef PK_ENABLE_TLM
   k_impl->TLM_total_est.set_type(k_impl->est_type);  
   for(int i=0; i<pk_tlmfc_nb; ++i)    
   {	if( k_impl->target_fc_data.TLMfc_on[i] ) 
		      k_impl->target_fc_data.TLMfc_est[i].set_type(k_impl->est_type);
   }
   for(int i=0; i<k_impl->socket_nb; ++i)  
		      k_impl->socket_aug[i]->fc_data.set_estype(k_impl->est_type);
		 
   #endif

   k_impl->check_state(); 
  }
 }
};


sc_core::sc_module_name power_module_b::compose_pmb_nm(const char* mod_nm)
{
   static std::string name;
   static const std::string prefix = "pk_";
   curr_modname = mod_nm;
   name.assign(mod_nm);
   unsigned sz = name.length();
   for(unsigned i=0; i<sz; ++i)  if(name[i]==char('.')) name[i]=char('_');
   name.insert(name.begin(),prefix.begin(),prefix.end());
   return name.c_str();
  };


void power_module_b::end_of_elaboration()
{  if(monitored) this->make_base_procs();  };  



void power_module_b::start_of_simulation()                 
{ };


}  
