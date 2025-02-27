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

#include "PKtool/kernel/power_module_fcs.h"
#include "PKtool/kernel/power_kernel.h"
#include "PKtool/kernel/pk_kernel_impl.h"
#include "PKtool/kernel/power_module_b.h"


namespace pk_core    
{


// ----------------------------------------------------------------------------
//  CLASS : pk_state_fc
// ----------------------------------------------------------------------------

pk_state_fc::pk_state_fc(int st) : pk_h( power_kernel::curr_pk() ), 
               powmod_h(power_module_b::curr_powmod())
     { 	 
	  if(powmod_h->monitored)
	  {
	   int pk_cnt_ = power_kernel::pk_counter;
	   ++pk_kernel_impl::pk_code_cfg_reg[pk_cnt_].state_nb;  
	   ++powmod_h->pk.k_impl->state_nb;
	   pk_kernel_impl::pk_code_cfg_reg[pk_cnt_].state_fc_pnts[st] = this;    
	  };
	 };   






// ----------------------------------------------------------------------------
//  CLASS : pk_dyndata_fc
// ----------------------------------------------------------------------------


pk_dyndata_fc::pk_dyndata_fc(int st) : pk_h( power_kernel::curr_pk() ),
                                       powmod_h(power_module_b::curr_powmod())
     {  
		if(powmod_h->monitored)
		{
		 int pk_cnt_ = power_kernel::pk_counter;
		 pk_kernel_impl::pk_code_cfg_reg[pk_cnt_].dyndata_fc_pnts[st] = this;  
		};
	 }; 

 power_model_b* pk_dyndata_fc::power_model() const
   { return pk_h->curr_pm();}


}  //pk_core  

