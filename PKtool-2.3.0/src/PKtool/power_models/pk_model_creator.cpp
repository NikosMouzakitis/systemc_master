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


#include "PKtool/power_models/pk_model_creator.h"
#include "PKtool/power_models/pk_library_handler.h"
#include "PKtool/kernel/pk_kernel_syscrefs.h"
#include "PKtool/kernel/pk_kernel_impl.h"
#include "PKtool/power_models/pk_model_lib_decl.h"
#include "PKtool/utils/pk_report_ids.h"
#include "PKtool/utils/pk_report.h"


namespace
{
 std::string message;

 const char* error_msg1(int index)
 {
  message.clear();
  char index_str[10];  
  message += "you have defined a power model using an integer identifier ";
  message += "\n";
  message += "already used for a pre-exhistent power model.";
  message += "\n";
  message += "integer identifier: ";  
  ::sprintf(index_str, "%d", index);
  message += index_str;
  message += "\n"; 
  return message.c_str();
 };


 const char* error_msg2(int index)
 {
  message.clear();
  char index_str[10];  
  char range_str[10];
  ::sprintf( index_str, "%d", index );
  ::sprintf( range_str, "%d", PK_MAX_MODEL_NB-1 );

  message += "you have specified a power model index ";
  message += "not included in the allowed range: [0 ";  
  message += range_str; message += "]";  
  message += "\n";
  message += "specified index: ";  
  message += index_str;
  message += "\n"; 

  return message.c_str();
 };

 const char* error_msg3(int index)
 {
  message.clear();
  char index_str[10];  
  ::sprintf( index_str, "%d", index );

  message += "you have specified a power model index ";
  message += "not associated to an available power model "; 
  message += "\n";
  message += "specified index: ";  
  message += index_str;
  message += "\n"; 

  cout<<"you have specified a power model index "<<endl; 
   cout<<"not associated to an available power model"<<endl;

  return message.c_str();
 };

};



namespace pk_core  
{


typedef pk_used_energy_lib::pk_lib_model_creator pk_energy_mc ;
typedef pk_used_comm_lib::pk_lib_model_creator pk_comm_mc ;



// ----------------------------------------------------------------------------
//  CLASS : pk_model_creator
// ----------------------------------------------------------------------------



pk_model_creator::pk_model_creator(lib_h lh): reg( lh().creator_reg )
{};



// ----------------------------------------------------------------------------
//  CLASS : pk_creator_register
// ----------------------------------------------------------------------------

void pk_creator_register::declare_creator
(pk_model_creator* mc, int ind, pk_model_lib_handler* lib_h)
{
  if(dynamic_cast<pk_energy_mc*>(mc))
  {
   if(energy_pm_creators[ind]!=0)
   { PK_REPORT_ERROR(PK_BADLY_DEFINED_POWER_MODEL_, error_msg1(ind) ); }
   energy_pm_creators[ind]=mc;
   if( lib_h )   
   {
    ++lib_h->model_nb;
    lib_h->enabled_models[ind] = true;
   }
  }
  else if(dynamic_cast<pk_comm_mc*>(mc))
  {
   if(comm_pm_creators[ind]!=0)
   {  PK_REPORT_ERROR(PK_BADLY_DEFINED_POWER_MODEL_, error_msg1(ind) ); }
   comm_pm_creators[ind] = mc;  
   if( lib_h )   
   {
    ++lib_h->model_nb;
    lib_h->enabled_models[ind] = true;
   }
  };
 };

#ifdef PK_ENABLE_TLM
 void pk_creator_register::declare_TLM_creator
 (pk_model_creator* mc, int ind, pk_model_lib_handler* lib_h)
 {
  declare_creator(mc, ind, lib_h);
  ++lib_h->TLM_model_nb;
  lib_h->TLM_model_inds[ind] = true;
  lib_h->enabled_models[ind] = false;
  --lib_h->model_nb;
 }
#endif



power_model_b* pk_creator_register::create_model(int ind, pk_kernel_impl& p)
 {                                                            
  pk_model_creator* tmp = 0;
  switch(p.est_type)   
  {
   case pk_energy:
   tmp=energy_pm_creators[ind];
   break;
   case pk_comm:
   tmp=comm_pm_creators[ind];
   default:
   ;
  };    
  return tmp->create(p);   
 };


};   // pk_core   




