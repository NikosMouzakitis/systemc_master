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
#include "PKtool/power_models/power_model_b.h"
#include "PKtool/kernel/pk_read_cfg_data.h"

#ifdef PK_ENABLE_OPMODELS

#ifndef PK_AUG_IF_H

namespace pk_default_energy_lib
{
 class pk_opmodel_b
 {
  friend class pk_aug_if;

  protected:

  virtual void op_task(const char) =0;

 };

};

#endif
#endif


namespace pk_core    
{



// ----------------------------------------------------------------------------
//  CLASS : power_model_b
// ----------------------------------------------------------------------------

char power_model_b::tmp_ch = '0';

bool* power_model_b::cycle_acc_ref = 0;

power_model_b::power_model_b(pk_kernel_impl& p): 
   pk_impl(p), cycle_acc(false), infile(*pk_core::pk_read_cfg_data::curr_infile)
{ cycle_acc_ref = &cycle_acc; }



void power_model_b::set_signals(const pk_kernel_impl& p)
{
 intsignal_aug = p.intsignal_aug;
 inoutport_aug = p.inoutport_aug;
 inport_aug = p.inport_aug;
 outport_aug = p.outport_aug;
 local_aug = const_cast<pk_aug_local*>(&p.local_aug);   
 
 int sz = intsignal_aug.size();     
 for(int i=0; i<sz; ++i)
       intsignal_aug[i]->data().disable_augdata();

 sz = inoutport_aug.size();
 for(int i=0; i<sz; ++i)
       inoutport_aug[i]->data().disable_augdata();

 sz = inport_aug.size();
 for(int i=0; i<sz; ++i)
       inport_aug[i]->data().disable_augdata();

 sz = outport_aug.size();
 for(int i=0; i<sz; ++i)
       outport_aug[i]->data().disable_augdata();

 this->set_augdata();

};


void power_model_b::set_augdata_(pk_aug_if::aug_data ad)     
{  
 int size = inport_aug.size();
 for(int i=0; i<size; ++i) inport_aug[i]->augdata->enable_augdata(ad);
 size = outport_aug.size();
 for(int i=0; i<size; ++i) outport_aug[i]->augdata->enable_augdata(ad);
 size = inoutport_aug.size();
 for(int i=0; i<size; ++i) inoutport_aug[i]->augdata->enable_augdata(ad);
 size = intsignal_aug.size();
 for(int i=0; i<size; ++i) intsignal_aug[i]->augdata->enable_augdata(ad);  

 if( (ad == pk_aug_if::total_comm) || (ad == pk_aug_if::operator_data) )   
  locdata_mod.find(pk_impl.mod_name)->second->set_(true, true, 0);
 else
  locdata_mod.find(pk_impl.mod_name)->second->set_(false, false, 0);
 
}

unsigned power_model_b::total_comm()   
{
 unsigned comm = 0;

 int size = inport_aug.size();
 for(int i=0; i<size; ++i) comm += inport_aug[i]->data().total_comm(); 

 size = outport_aug.size();
 for(int i=0; i<size; ++i) comm += outport_aug[i]->data().total_comm();

 size = inoutport_aug.size();
 for(int i=0; i<size; ++i) comm += inoutport_aug[i]->data().total_comm();

 size = intsignal_aug.size();
 for(int i=0; i<size; ++i) comm += intsignal_aug[i]->data().total_comm();

 comm += local_aug->total_comm();  

 return comm;
};   

 

#ifdef PK_ENABLE_OPMODELS

 void power_model_b::set_opmodel_on_augs( pk_default_energy_lib::pk_opmodel_b* opm )
 {
  int sz = intsignal_aug.size();
  for(int i=0; i<sz; ++i)
  { intsignal_aug[i]->set_opmod( opm );  }
  
  sz = inport_aug.size();
  for(int i=0; i<sz; ++i)
  { inport_aug[i]->set_opmod( opm ); }

  sz = outport_aug.size();
  for(int i=0; i<sz; ++i)
  { outport_aug[i]->set_opmod( opm ); }

  sz = inoutport_aug.size();
  for(int i=0; i<sz; ++i)
  { inoutport_aug[i]->set_opmod( opm ); }

  locdata_mod.find(pk_impl.mod_name)->second->opm = opm;
 
 };

#endif


power_model_b::~power_model_b()
 {
  for(unsigned i = 0; i<intsignal_aug.size(); i++) intsignal_aug[i]=0;
  for(unsigned i = 0; i<inport_aug.size(); i++) inport_aug[i]=0;
  for(unsigned i = 0; i<outport_aug.size(); i++) outport_aug[i]=0;
  for(unsigned i = 0; i<inoutport_aug.size(); i++) outport_aug[i]=0;
  };

power_model_b::set_cycle_acc::set_cycle_acc()
{ *power_model_b::cycle_acc_ref = true; }



// ----------------------------------------------------------------------------
//  CLASS : energy_power_model
// ----------------------------------------------------------------------------

pk_estimation energy_power_model::est_obj(pk_energy);



// ----------------------------------------------------------------------------
//  CLASS : energy_power_model
// ----------------------------------------------------------------------------

pk_estimation comm_power_model::est_obj(pk_comm);


}  //pk_core  






