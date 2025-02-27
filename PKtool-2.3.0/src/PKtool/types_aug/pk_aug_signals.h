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


#ifndef PK_SIGNALS_H
#define PK_SIGNALS_H

#include "PKtool/types_aug/pk_aug_base.h" 
#include "PKtool/types_aug/pk_compute_comm_fcs.h"
#include "PKtool/types_aug/pk_aug_local.h"
#include <map>



namespace pk_core    
{
 

 extern std::map<const char*, pk_aug_local*> locdata_mod;  
 

// ----------------------------------------------------------------------------
//  CLASS : pk_internal_sgn<T>
//
//  base class for internal augmented signals 
// ----------------------------------------------------------------------------


template< class T > class pk_internal_sgn: public pk_aug_base<T>
{
 protected:
 
 typedef pk_aug_if aug_if;
 typedef pk_aug_base<T> aug_base;
 
 
 pk_internal_sgn(T* sgn_h): pk_aug_base<T>( pk_aug_if::internal_sgn, sgn_h ),
	                        sign_h(sgn_h), local_sgn(false)    
 {
  if( !(sc_core::sc_start_of_simulation_invoked()) )
  {
   aug_if::intsignal_aug.push_back(this);
   aug_base::ind = unsigned( aug_if::intsignal_aug.size() );
  }
  else 
  {
   mod_name = (sc_core::sc_get_current_process_handle()).get_parent_object()->name();
   local_sgn = true;  
   pk_aug_local* lcdt = locdata_mod.find(mod_name)->second;
   if(lcdt != 0)
   {
    this->enabled = lcdt->enabled_signals;    
    if(this->enabled)
    {
     lcdt->localsign_aug.push_front(this);
     if(lcdt->enabled_totcomm)
	 this->augdata->enable_augdata(pk_aug_if::total_comm);
    
     #ifdef PK_ENABLE_OPMODELS
	   this->set_opmod( lcdt->opm );
     #endif
    }
   }
  }
 };

 inline void initialize_()  
 {
  if(this->enabled) 
  {
   this->augdata_T.reset_data();
   this->augdata_T.init_value( *sign_h );   
  }
  return;  
 };
 
 inline void compute_data()   
 {
 if(this->enabled) aug_base::compute_data();
 };

 ~pk_internal_sgn()
 {
  if(this->enabled && local_sgn)
  { 
    pk_aug_local* lcdt = (locdata_mod.find(mod_name))->second;  
    lcdt->partial_comm += aug_if::data().total_comm();
    lcdt->localsign_aug.remove(this);
  }
 };
 

 private:

 T* sign_h;  

 bool local_sgn;  
 const char* mod_name;

 private:   
 
 // disabled 
 pk_internal_sgn(const pk_internal_sgn&);
 pk_internal_sgn operator=(const pk_internal_sgn&);

};

// ----------------------------------------------------------------------------
//  CLASS : pk_inport<T>
//
//  base class for input augmented ports 
// ----------------------------------------------------------------------------



template<class T> class pk_inport:public pk_aug_base<T>
{

 typedef pk_aug_if aug_if;
 typedef pk_aug_base<T> aug_base;
 
 protected:
 
 pk_inport(): pk_aug_base<T>(pk_aug_if::inport)
 {
  aug_if::inport_aug.push_back(this);
  aug_base::ind = unsigned( aug_if::inport_aug.size() );
 };


 private:  
	 
 // disabled  
 
 pk_inport(const pk_inport&);
 pk_inport& operator=(const pk_inport&);

};

// ----------------------------------------------------------------------------
//  CLASS : pk_outport<T>
//
//  base class for output augmented ports 
// ----------------------------------------------------------------------------



template<class T> class pk_outport:public pk_aug_base<T>
{

 typedef pk_aug_if aug_if;
 typedef pk_aug_base<T> aug_base;
 
 protected:  
 
 pk_outport(): pk_aug_base<T>(pk_aug_if::outport)
 {
  aug_if::outport_aug.push_back(this);
  aug_base::ind = unsigned( aug_if::outport_aug.size() );
 };


 inline void compute_data(T new_val)    
 {
  this->augdata_T.update_value( new_val );   
  aug_base::compute_data();
 }
  

 private:  

 // disabled 
 
 pk_outport(const pk_outport&);
 pk_outport& operator=(const pk_outport&);

};


// ----------------------------------------------------------------------------
//  CLASS : pk_inoutport<T>
//
//  base class for inout augmented ports 
// ----------------------------------------------------------------------------


template<class T> class pk_inoutport:public pk_aug_base<T>
{

 typedef pk_aug_if aug_if;
 typedef pk_aug_base<T> aug_base;
 
 protected:
 
 pk_inoutport(): pk_aug_base<T>(pk_aug_if::inoutport)
 {
  aug_if::inoutport_aug.push_back(this);
  aug_base::ind = unsigned(aug_if::inoutport_aug.size());
 };


 inline void compute_data(T new_val)
 {
  this->augdata_T.update_value( new_val );   
  aug_base::compute_data();   
 }


 private:
 
 // disabled  

 pk_inoutport(const pk_inoutport&);
 pk_inoutport& operator=(const pk_inoutport&);

};

}  //pk_core 



#endif
