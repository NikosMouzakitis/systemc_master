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


#include "PKtool/kernel/pk_settings.h"

#ifdef PK_ENABLE_TLM

#include "PKtool/kernel/power_kernel.h"
#include "PKtool/kernel/pk_kernel_impl.h"
#include "PKtool/kernel/power_module_b.h"

#include "PKtool/tlm/pk_tlm_socket_base.h"
#include "PKtool/tlm/pk_tlm_power_model_b.h"




namespace pk_tlm
{

 const char* pk_fc_names[pk_tlmfc_nb] = {"b_transport", "nb_transport_fw", "nb_transport_bw", 
                                          "get_direct_mem_ptr", "invalidate_direct_mem_ptr" };
 
  pk_enable_tlmfc::pk_enable_tlmfc(int fc)  
  {
	pk_core::power_module_b* mod = pk_core::power_module_b::curr_powmod();                                
	if(!mod)                                                                            
	{                                                                                   
	 cout<<"ERROR"<<endl;                                                               
     exit(1);                                                                           
	}  
	if( mod->pk.k_impl->TLM_on == false )  mod->pk.k_impl->TLM_on = true;
    if( mod->pk.k_impl->target_on == false )  mod->pk.k_impl->target_on = true;
	mod->pk.k_impl->target_fc_data.TLMfc_on[fc] = true;
  }

 void pk_TLMfc_data::do_estimation(int TLM_fc)      
 { 
  if( TLMfc_on[TLM_fc] )                            
  {
   ++TLMfc_calls[TLM_fc];
   TLMfc_est[TLM_fc] += TLMfc_pm[TLM_fc]->get_estimation();
  }
 }

 void pk_TLMfc_data::set_estype(pk_core::pk_est_type et)
 {  
  for(int i=0; i<pk_tlmfc_nb; ++i)  
	  if(TLMfc_on[i]) TLMfc_est[i].set_type(et);
 }


};

#endif

