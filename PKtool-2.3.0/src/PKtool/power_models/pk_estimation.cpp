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

#include "PKtool/power_models/pk_estimation.h"
#include "PKtool/kernel/power_module_fcs.h"
#include "PKtool/kernel/power_kernel.h"
#include "PKtool/kernel/pk_kernel_impl.h"
#include "PKtool/kernel/power_module_b.h"
#include "PKtool/power_models/pk_model_lib_decl.h"


namespace pk_core    
{


const char* pk_est_type_name[] = {"", "energy", "commutations"};



// ----------------------------------------------------------------------------
//  CLASS : pk_set_estype_b
// ----------------------------------------------------------------------------


pk_set_estype_b::pk_set_estype_b( const pk_est_type et )
{
 power_module_b* pmb = power_module_b::curr_powmod();
 if(pmb->monitored)
 {
  
  switch(et)
  {
   case pk_energy:
    pmb->pk.k_impl->modlib_h = &(pk_used_energy_lib::model_library());
    break;
   case pk_comm:
    pmb->pk.k_impl->modlib_h = &(pk_used_comm_lib::model_library());
	break;
   default:
	  ;
  }
 
 };
};


// ----------------------------------------------------------------------------
//  CLASS : pk_estimation
// ----------------------------------------------------------------------------


void pk_estimation::set_type( const pk_est_type tp )  
{
 switch(tp)
 {
  case pk_no_estype :
	pvalue = 0;
  break;
  case pk_energy :
    pvalue = new pk_energy_type();
  break;
  case pk_comm :
    pvalue = new pk_comm_type();
 };
};


pk_estimation& pk_estimation::operator=(const pk_estimation& e)
{
 pvalue->assign(*e.pvalue);
 return *this;
};

pk_estimation& pk_estimation::operator+=(const pk_estimation& e)
{
 pvalue->add(*e.pvalue);
 return *this;
};


ostream& operator<<(ostream& os,const pk_estimation& est)
{  return est.print_estim(os);};


}  //pk_core  




