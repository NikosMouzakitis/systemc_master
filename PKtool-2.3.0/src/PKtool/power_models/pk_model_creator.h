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

#ifndef PK_MODEL_CREATOR_H
#define PK_MODEL_CREATOR_H
#include "PKtool/power_models/pk_estimation.h"
#include "PKtool/kernel/pk_settings.h"



namespace pk_core
{


class pk_kernel_impl;  
class power_model_b;
class pk_creator_register;
class pk_model_lib_handler;



// ----------------------------------------------------------------------------
//  CLASS : pk_model_creator
// ----------------------------------------------------------------------------


class pk_model_creator
{

 typedef pk_model_lib_handler& (*lib_h) (); 

 protected:

 pk_model_creator( lib_h lh );

 pk_creator_register& reg;

 public:    

 virtual power_model_b* create(pk_kernel_impl& p) const = 0;   

 virtual ~pk_model_creator()
 {};


 private:
 
 // disabled
 pk_model_creator(const pk_model_creator&);
 pk_model_creator& operator = (const pk_model_creator&);

};



// ----------------------------------------------------------------------------
//  CLASS : pk_creator_register
// ----------------------------------------------------------------------------


class pk_creator_register      
{
 public:
    
 
 pk_creator_register()
 {
  for(int i=0; i<PK_MAX_MODEL_NB; ++i) 
  {
   creator_list[i] = 0;
   energy_pm_creators[i] = 0;
   comm_pm_creators[i] = 0;
  };
 };

 

 public:

 void declare_creator(pk_model_creator* mc, int ind, pk_model_lib_handler* lib_h = 0 );  

 #ifdef PK_ENABLE_TLM
  void declare_TLM_creator(pk_model_creator* mc, int ind, pk_model_lib_handler* lib_h = 0 );         
 #endif

 power_model_b* create_model(int ind, pk_kernel_impl& p);


 private:

 pk_model_creator* creator_list[PK_MAX_MODEL_NB];

 pk_model_creator* energy_pm_creators[PK_MAX_MODEL_NB];

 pk_model_creator* comm_pm_creators[PK_MAX_MODEL_NB];

};

}   // pk_core   


#endif
