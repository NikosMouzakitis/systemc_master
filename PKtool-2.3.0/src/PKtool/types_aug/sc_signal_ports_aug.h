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

#ifndef SC_SIGNAL_PORTS_AUG_H
#define SC_SIGNAL_PORTS_AUG_H

#include "PKtool/types_aug/pk_aug_signals.h"

#ifdef PK_ENABLE_OPMODELS  

#include "PKtool/types_aug/pk_proxy_opmod.h"

#endif



namespace pk_core    
{


// ----------------------------------------------------------------------------
//  CLASS : sc_in_aug<T>   
//
// class for the augmented signals related to the SystemC port type sc_in<T>
// ----------------------------------------------------------------------------





template <class T>
class sc_in_aug: public sc_core::sc_in<T>, public pk_inport<T> 
{
 
 public:

	 // typedefs

 typedef T                                                           data_type;

 typedef sc_core::sc_signal_in_if<data_type>                         if_type;
 typedef sc_core::sc_port<if_type,1,sc_core::SC_ONE_OR_MORE_BOUND>   base_type;
 typedef sc_in_aug<data_type>                                        this_type;
 typedef sc_core::sc_in<T>                                           sc_in_T;

 typedef if_type                                                     in_if_type;
 typedef base_type                                                   in_port_type;
 typedef sc_core::sc_signal_inout_if<data_type>                      inout_if_type;
 typedef sc_core::sc_port<inout_if_type,1, sc_core::SC_ONE_OR_MORE_BOUND>  inout_port_type;

 typedef pk_inport<T> pk_base;


 //constructors 

 sc_in_aug()
 : sc_in_T()
 { };

 explicit sc_in_aug( const char* name_)
 : sc_in_T(name_)
 { };

 explicit sc_in_aug( const in_if_type& interface_)
 : sc_in_T(interface_)
 { };

 sc_in_aug( const char* name_, const in_if_type& interface_)
 : sc_in_T(name_, interface_)
 { };

 explicit sc_in_aug( in_port_type& parent_)
 : sc_in_T(parent_)
 { };

 sc_in_aug( const char* name_, in_port_type& parent_ )
 : sc_in_T(name_,parent_)
 { };

 explicit sc_in_aug( inout_port_type& parent_)
 : sc_in_T(parent_)
 { };

 sc_in_aug( const char* name_, inout_port_type& parent_)
 : sc_in_T(name_,parent_)
 { };

 sc_in_aug( this_type& parent_)
 : sc_in_T(parent_)
 { };

 sc_in_aug( const char* name_, this_type& parent_ )
 : sc_in_T(name_,parent_)
 { };

 sc_in_aug( sc_in_T& parent_)
 : sc_in_T(parent_)
 { };

 sc_in_aug( const char* name_, sc_in_T& parent_ )
 : sc_in_T(name_,parent_)
 { };


 inline void initialize_()  
 {
  if(pk_base::enabled)
  {  
   pk_base::augdata_T.reset_data();
   pk_base::augdata_T.init_value( sc_in_T::read() );   
  }
  return;
 };

 inline void update_data()
 {
  pk_base::augdata_T.update_value( sc_in_T::read() );   
  pk_aug_base<T>::compute_data();   
 };

 #ifdef PK_ENABLE_OPMODELS

 void set_opmod(pk_default_energy_lib::pk_opmodel_b* op)
 {
  pk_base::set_opmod_(op);
  return_val.set_opm(op);
 }

 private: 

 using sc_in_T::read; 

 mutable pk_proxy_opmod< T > return_val;

 public:

 const pk_proxy_opmod< T >& read() const
 {
   return_val.set( static_cast< const sc_core::sc_in< T >* >( this )->read() );
   return return_val;
 };

 #endif


 // destructor

 virtual ~sc_in_aug()
 {}

 private:
 
 // disabled 

 sc_in_aug(const this_type&);
 this_type& operator = (const this_type&);
 
};


// ----------------------------------------------------------------------------
//  CLASS : sc_inout_aug<T>  
//
// class for the augmented signals related to the SystemC port type sc_inout<T>
// ----------------------------------------------------------------------------

template <class T>
class sc_inout_aug: public sc_core::sc_inout<T>, public pk_inoutport<T>
{

 public:

 // typedefs

   
 typedef T                                                               data_type;

 typedef sc_inout_aug<data_type>                                         this_type;
 typedef sc_core::sc_signal_inout_if<data_type>                          if_type;
 typedef sc_core::sc_port<if_type, 1, sc_core::SC_ONE_OR_MORE_BOUND>     base_type;
 typedef sc_core::sc_inout<T>                                            sc_inout_T;

 typedef sc_core::sc_signal_in_if<data_type>                             in_if_type;
 typedef sc_core::sc_port<in_if_type, 1, sc_core::SC_ONE_OR_MORE_BOUND>  in_port_type;
 typedef if_type                                                         inout_if_type;
 typedef base_type                                                       inout_port_type;

 typedef pk_inoutport<T>                                                 pk_base;
 

 // constructors

 sc_inout_aug()
 : sc_inout_T()
 { };

 explicit sc_inout_aug( const char* name_)
 : sc_inout_T(name_)
 { };

 explicit sc_inout_aug( inout_if_type& interface_ )
 : sc_inout_T(interface_)
 { };

 sc_inout_aug( const char* name_, inout_if_type& interface_)
 : sc_inout_T(name_, interface_)
 { };

 explicit sc_inout_aug( inout_port_type& parent_ )
 : sc_inout_T(parent_)
 { };


 sc_inout_aug( const char* name_, inout_port_type& parent_ )
 : sc_inout_T(name_,parent_)
 { };

 sc_inout_aug( this_type& parent_)
 : sc_inout_T(parent_)
 { };

 sc_inout_aug( const char* name_, this_type& parent_)
 : sc_inout_T(name_,parent_)
 { };

 sc_inout_aug( sc_inout_T& parent_)
 : sc_inout_T(parent_)
 { };

 sc_inout_aug( const char* name_, sc_inout_T& parent_)
 : sc_inout_T(name_,parent_)
 { };


 // destructor

 virtual ~sc_inout_aug()
 {}


 inline void initialize_()  
 {
  if(pk_base::enabled) 
  {  
   pk_base::augdata_T.reset_data();
   pk_base::augdata_T.init_value( sc_inout_T::read() );   
  }
  return;  
 };

 inline void update_data()
 {
  pk_base::augdata_T.update_value( sc_inout_T::read() );   
  pk_aug_base<T>::compute_data(); 
 };


 inline void write( const data_type& value_ )
 {
  sc_inout_T::write( value_ );
  if(pk_base::enabled)  pk_base::compute_data( value_ );
 }

 sc_inout_aug<T>& operator = ( const data_type& value_ )
	{ write( value_ );  return *this; }

 sc_inout_aug<T>& operator = ( const in_if_type& interface_ )
	{ write( interface_.read() ); return *this; }

 sc_inout_aug<T>& operator = ( const in_port_type& port_ )
	{ write( port_->read() ); return *this; }

 sc_inout_aug<T>& operator = ( const inout_port_type& port_ )
	{ write( port_->read() ); return *this; }

 sc_inout_aug<T>& operator = ( const this_type& port_ )
	{ write( port_->read() ); return *this; }

 sc_inout_aug<T>& operator = ( const sc_inout_T& port_ )
	{ write( port_->read() ); return *this; }



 private:

 // disabled 

 sc_inout_aug(const this_type&);

};

 
// ----------------------------------------------------------------------------
//  CLASS : sc_out_aug<T>   
//
// class for the augmented signals related to the SystemC port type sc_out<T>
// ----------------------------------------------------------------------------


template <class T>
class sc_out_aug : public sc_core::sc_out<T>, public pk_outport<T>  
{

 public:

 // typedefs
 
 typedef T                                  data_type;   

 typedef sc_out_aug<data_type>              this_type;
 typedef sc_core::sc_out<T>                 sc_out_T;

 typedef typename sc_out_T::in_if_type      in_if_type;
 typedef typename sc_out_T::in_port_type    in_port_type;
 typedef typename sc_out_T::inout_if_type   inout_if_type;
 typedef typename sc_out_T::inout_port_type inout_port_type;

 typedef pk_outport<T>                      pk_base;

 void initialize_()  
 {
  if(pk_base::enabled) 
  {  
   pk_base::augdata_T.reset_data();
   pk_base::augdata_T.init_value( sc_out_T::read() );   
  }
  return;  
 };
 
// constructors
 
 sc_out_aug()
 : sc_out_T()
 { };

 explicit sc_out_aug( const char* name_ )
 : sc_out_T(name_)
 { };

 explicit sc_out_aug( inout_if_type& interface_ )
 : sc_out_T(interface_)
 { };

 sc_out_aug( const char* name_, inout_if_type& interface_ )
 : sc_out_T(name_, interface_)
 { };

 explicit sc_out_aug( inout_port_type& parent_ )
 : sc_out_T(parent_)
 { };

 sc_out_aug( const char* name_, inout_port_type& parent_ )
 : sc_out_T(name_,parent_)
 { };

 sc_out_aug( this_type& parent_)
 : sc_out_T(parent_)
 { };

 sc_out_aug( const char* name_, this_type& parent_ )
 : sc_out_T(name_,parent_)
 { };

 sc_out_aug( sc_out_T& parent_)
 : sc_out_T(parent_)
 { };

 sc_out_aug( const char* name_, sc_out_T& parent_ )
 : sc_out_T(name_,parent_)
 { };


 // destructor (does nothing)

 virtual ~sc_out_aug()
 {}

 inline void write( const data_type& value_ )
 {
  sc_out_T::write( value_);
  if(pk_base::enabled) pk_base::compute_data(value_); 
 }
 

 this_type& operator = ( const data_type& value_ )
 {  write( value_ ); return *this; }


 this_type& operator = ( const in_if_type& interface_ )
 { write(interface_.read()); return *this; }

 this_type& operator = ( const in_port_type& port_ )
 { write(port_->read());  return *this;}

 this_type& operator = ( const inout_port_type& port_ )
 { write(port_->read());  return *this; }

 this_type& operator = ( const sc_out_T& port_ )
 { write(port_->read()); return *this; }

 this_type& operator = ( const this_type& port_ )
 { write(port_->read()); return *this; }
   

 private:

 // disabled
 
 sc_out_aug( const this_type& );

};


}    //pk_core    


#endif





