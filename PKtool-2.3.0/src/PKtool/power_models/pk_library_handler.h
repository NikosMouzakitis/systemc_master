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


#ifndef PK_LIBRARY_HANDLER_H
#define PK_LIBRARY_HANDLER_H





#include "PKtool/kernel/pk_settings.h"


namespace pk_core
{

class pk_creator_register;
class pk_model_creator;
class pk_read_cfg_data;
class power_module_b;




// ----------------------------------------------------------------------------
//  CLASS : pk_model_lib_handler
// ----------------------------------------------------------------------------


class pk_model_lib_handler
{
 friend class pk_creator_register;
 friend class pk_model_creator;  
 friend class pk_read_cfg_data;
 friend class power_module_b;

 public:

 pk_creator_register creator_reg;  

 pk_model_lib_handler(pk_estimation_type& et, const char* nm = 0):
  lib_name(nm), model_nb(0), est_type(et)
 {  
  for(int i=0; i<PK_MAX_MODEL_NB; i++) enabled_models[i] = false;
  
  #ifdef PK_ENABLE_TLM
  TLM_model_nb = 0;
  for(int i=0; i<PK_MAX_MODEL_NB; i++) TLM_model_inds[i] = false;
  #endif
 };
  
 const char* name() const
 { return lib_name; };


 unsigned model_number() const
 { return model_nb; };

 void model_indexes( bool* mi) const  //requires an array of PK_MAX_MODEL_NB boolean
 {                                     
  for( int i=0; i<PK_MAX_MODEL_NB; ++i) 
            *(mi + i) = enabled_models[i] ;
 };


 const char* get_name() const
 { return lib_name; };

 template<class T> void print_general_info(T& os)  const
 {
  os<<"estimation type: "<<est_type.type_name()<<endl;
  os<<"model library selected: "<<name()<<endl;
  os<<"available power models: ";
  if(model_nb) os<< model_nb<<endl; 
  else os<<"no power models"<<endl;
  os<<"related indexes: ";
  for(int i=0; i<PK_MAX_MODEL_NB; ++i) if(enabled_models[i]) os<<i<<" ";
  os<<endl<<endl;
 }

 #ifdef PK_ENABLE_TLM
 template<class T> void print_TLM_info(T& os)  const
 {
  os<<endl<<"available TLM power models: ";
  if(TLM_model_nb) os<< TLM_model_nb<<endl; 
  else os<<"no power models"<<endl;
  os<<"related indexes: ";
  for(int i=0; i<PK_MAX_MODEL_NB; ++i) if(TLM_model_inds[i]) os<<i<<" ";
  os<<endl<<endl;
 }

 void model_indexes_in_TLM( bool* mi, bool TLM_on = false) const  //requires an array of PK_MAX_MODEL_NB boolean
 { 
  if(TLM_on)
   for( int i=0; i<PK_MAX_MODEL_NB; ++i) 
            *(mi + i) = TLM_model_inds[i] ;
  else
  for( int i=0; i<PK_MAX_MODEL_NB; ++i) 
            *(mi + i) = ( enabled_models[i] && !(TLM_model_inds[i]) ) ;
 };

 #endif

 private:

 bool enabled_models[PK_MAX_MODEL_NB];  
 const char* lib_name;
 unsigned model_nb;
 pk_estimation_type& est_type;

 #ifdef PK_ENABLE_TLM
 unsigned TLM_model_nb;
 bool TLM_model_inds[PK_MAX_MODEL_NB];
 #endif
 

 private:
   //disabled
 
 pk_model_lib_handler(const pk_model_lib_handler&);
 pk_model_lib_handler& operator = (const pk_model_lib_handler&);

};


}   // pk_core   


#endif
