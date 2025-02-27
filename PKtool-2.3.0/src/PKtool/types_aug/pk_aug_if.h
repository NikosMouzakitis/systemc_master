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


#ifndef PK_AUG_IF_H  
#define PK_AUG_IF_H  


#include <vector>  
#include "sysc/kernel/sc_module.h"  
#include "PKtool/utils/pk_macros.h"
#include "PKtool/kernel/pk_settings.h"



#ifdef PK_ENABLE_OPMODELS

namespace pk_default_energy_lib
{
 struct pk_opmodel_b
 {

  virtual void op_task(const char) =0;

 };

}

#endif


namespace pk_core    
{

using std::vector;
using std::cout;
using std::endl;

class power_kernel;
class pk_augdata_base;

class pk_aug_if;


// ----------------------------------------------------------------------------
//  CLASS : pk_aug_if
//
//  Basic class for all the kinds of augmented signals. 
//  It contains the common interface for handling augmented signals, and those 
//  routines not depending on signal type. 
// ----------------------------------------------------------------------------



class pk_aug_if
{

 public:

 friend class power_model_b;
 friend class power_module_b;
 friend class power_kernel;
 friend class pk_kernel_impl;

 enum aug_category {internal_sgn, inport, outport,inoutport };

 enum aug_data { bit_size, bit_values, bit_comm, total_comm, 
	             bit_onetimes, bit_prob, operator_data };

 
 protected:

 //constructor

 pk_aug_if(aug_category at); 



 public:

 inline
 const bool is_enabled() const
 {return enabled;};

 inline
 int index() const 
 {return ind;};

 inline
 const aug_category category() const  
 { return sgn_category; }


 inline
 pk_augdata_base& data() const   
 {return *augdata;};  


 #ifdef PK_ENABLE_OPMODELS

 protected:

 void set_opmod_(pk_default_energy_lib::pk_opmodel_b* op)
 { opmodel = op; }

  
 virtual void set_opmod(pk_default_energy_lib::pk_opmodel_b* op)
 {  set_opmod_(op); };

 private:

 pk_default_energy_lib::pk_opmodel_b* opmodel;

 public:

 inline void opmodel_task(const char c) const
 { opmodel->op_task(c);  }

 inline bool enabled_opmodel() const
 { return ( (opmodel != 0) ? true : false );  }

 #endif  


 virtual ~pk_aug_if()  
 { };



 protected:

 void virtual initialize_()       
 {};

 
 void virtual update_data( ) = 0;   
 
 protected:

 static vector<pk_aug_if*> intsignal_aug;
 static vector<pk_aug_if*> inport_aug; 
 static vector<pk_aug_if*> outport_aug;
 static vector<pk_aug_if*> inoutport_aug;

 const aug_category sgn_category;
 unsigned ind;   
 bool enabled; 

 pk_augdata_base* augdata;  



};  


}    // pk_core    
 



#endif




