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

#ifndef SC_SIGNAL_RV_PORTS_AUG_H
#define SC_SIGNAL_RV_PORTS_AUG_H

#include "PKtool/types_aug/pk_aug_signals.h"

#ifdef PK_ENABLE_OPMODELS  

#include "PKtool/types_aug/pk_proxy_opmod.h"

#endif



namespace pk_core    
{


// ---------------------------------------------------------------------------------
//  CLASS : sc_in_resolved_aug   
//
// class for augmented signals related to the SystemC port type sc_in_resolved
// ---------------------------------------------------------------------------------



class sc_in_resolved_aug: public sc_core::sc_in_resolved, 
	                         public pk_inport<sc_dt::sc_logic>
{
 
 public:

 // typedefs

 typedef sc_dt::sc_logic                  data_type;

 typedef sc_in_resolved_aug               this_type;
 typedef sc_in_resolved                   sc_in_res;
 typedef sc_in_res::base_type             base_type;  

 typedef base_type::in_if_type            in_if_type;
 typedef base_type::in_port_type          in_port_type;
 typedef base_type::inout_port_type       inout_port_type;

 typedef pk_inport<data_type>              pk_base;


 //constructors 

 sc_in_resolved_aug()
 : sc_in_res()
 { };

 explicit sc_in_resolved_aug( const char* name_)
 : sc_in_res(name_)
 { };

 explicit sc_in_resolved_aug( const in_if_type& interface_)
 : sc_in_res(interface_)
 { };

 sc_in_resolved_aug( const char* name_, const in_if_type& interface_)
 : sc_in_res(name_, interface_)
 { };

 explicit sc_in_resolved_aug( in_port_type& parent_)
 : sc_in_res(parent_)
 { };

 sc_in_resolved_aug( const char* name_, in_port_type& parent_ )
 : sc_in_res(name_,parent_)
 { };

 explicit sc_in_resolved_aug( inout_port_type& parent_ )
 : sc_in_res(parent_)
 { };

 sc_in_resolved_aug( const char* name_, inout_port_type& parent_)
 : sc_in_res(name_, parent_)
 { };

 sc_in_resolved_aug( this_type& parent_)
 : sc_in_res( parent_ )
 { };

 sc_in_resolved_aug( const char* name_, this_type& parent_ )
 : sc_in_res( name_, parent_ )
 { };

 sc_in_resolved_aug( sc_in_res& parent_ )
 : sc_in_res( parent_ )
 { };

 sc_in_resolved_aug( const char* name_, sc_in_res& parent_ )
 : sc_in_res( name_, parent_ )
 { };

 #ifdef PK_ENABLE_OPMODELS

 void set_opmod(pk_default_energy_lib::pk_opmodel_b* op)
 {
  pk_base::set_opmod_(op);
  return_val.set_opm(op);
 }

 private: 

 using sc_in_res::read; 

 mutable pk_proxy_opmod< data_type > return_val;

 public:

 const pk_proxy_opmod< data_type >& read() const
 {
   return_val.set( static_cast< const sc_in_res * >( this )->read() );
   return return_val;
 };

 #endif

 // destructor (does nothing)

 virtual ~sc_in_resolved_aug()
 {}




 private:
 
 // disabled 

 sc_in_resolved_aug(const this_type&);
 this_type& operator = (const this_type&);
 
};



// ----------------------------------------------------------------------------
//  CLASS : sc_inout_resolved_aug 
//
// class for augmented signals related to the SystemC port type 
// sc_inout_resolved
// ----------------------------------------------------------------------------


class sc_inout_resolved_aug: public sc_core::sc_inout_resolved, 
	                         public pk_inoutport<sc_dt::sc_logic>
{

 public:

 // typedefs

   
 typedef sc_dt::sc_logic                 data_type;

 typedef sc_inout_resolved_aug           this_type;  
 typedef sc_inout_resolved               sc_inout_res;
 typedef sc_inout_res::base_type         base_type;

 typedef sc_inout_res::in_if_type        in_if_type;
 typedef sc_inout_res::in_port_type      in_port_type;  
 typedef sc_inout_res::inout_if_type     inout_if_type;
 typedef sc_inout_res::inout_port_type   inout_port_type;

 typedef pk_inoutport<sc_dt::sc_logic>   pk_base;
 

 // constructors

 sc_inout_resolved_aug( )
 : sc_inout_res()
 { };

 explicit sc_inout_resolved_aug( const char* name_)
 : sc_inout_res(name_)
 { };

 explicit sc_inout_resolved_aug( inout_if_type& interface_ )
 : sc_inout_res(interface_)
 { };

 sc_inout_resolved_aug( const char* name_, inout_if_type& interface_)
 : sc_inout_res(name_, interface_)
 { };

 explicit sc_inout_resolved_aug( inout_port_type& parent_ )
 : sc_inout_res(parent_)
 { };


 sc_inout_resolved_aug( const char* name_, inout_port_type& parent_ )
 : sc_inout_res(name_,parent_)
 { };

 sc_inout_resolved_aug( this_type& parent_)
 : sc_inout_res( parent_ )
 { };

 sc_inout_resolved_aug( const char* name_, this_type& parent_)
 : sc_inout_res( name_, parent_ )
 { };

 sc_inout_resolved_aug( sc_inout_res& parent_)
 : sc_inout_res( parent_ )
 { };

 sc_inout_resolved_aug( const char* name_, sc_inout_res& parent_)
 : sc_inout_res( name_, parent_ )
 { };


 // destructor (does nothing)

 virtual ~sc_inout_resolved_aug()
 {}


 inline void initialize_()  
 {
  if(pk_base::enabled) 
  {  
   pk_base::augdata_T.reset_data();
   pk_base::augdata_T.init_value( sc_inout_res::read() );   
  }
  return;  
 };


 inline void update_data()
 {
  pk_base::augdata_T.update_value( sc_inout_res::read() );   
  pk_aug_base<sc_dt::sc_logic>::compute_data(); 
 };


 inline void write( const data_type& value_ )
 {
  sc_inout_res::write( value_ );
  if(pk_base::enabled)  pk_base::compute_data( value_ );
 }


 this_type& operator = ( const data_type& value_ )
 { write( value_ );  return *this; }

 this_type& operator = ( const in_if_type& interface_ )
 { write( interface_.read() ); return *this; }

 this_type& operator = ( const in_port_type& port_ )
 { write( port_->read() ); return *this; }

 this_type& operator = ( const inout_port_type& port_ )
 { write( port_->read() ); return *this; }

 this_type& operator = ( const this_type& port_ )
 { write( port_->read() ); return *this; }

 this_type& operator = ( const sc_inout_res& port_ )
 { write( port_->read() ); return *this; }



 private:

 // disabled 

 sc_inout_resolved_aug(const this_type&);


};



 
// ----------------------------------------------------------------------------
//  CLASS : sc_out_resolved_aug   
//
// class for augmented signals related to the SystemC port type 
// sc_out_resolved
// ----------------------------------------------------------------------------



class sc_out_resolved_aug : public sc_core::sc_out_resolved, 
	                          public pk_outport<sc_dt::sc_logic>  
{
 
 public:

 //typedefs
 
 typedef sc_dt::sc_logic                data_type;

 typedef sc_out_resolved_aug            this_type;
 typedef sc_out_resolved                sc_out_res;
 typedef sc_out_res::base_type          base_type;

 typedef sc_out_res::in_if_type         in_if_type;
 typedef sc_out_res::in_port_type       in_port_type;
 typedef sc_out_res::inout_if_type      inout_if_type; 
 typedef sc_out_res::inout_port_type    inout_port_type; 

 typedef pk_outport<sc_dt::sc_logic>    pk_base;

 
// constructors
 
 sc_out_resolved_aug()
 : sc_out_res()
 { };

 explicit sc_out_resolved_aug( const char* name_)
 : sc_out_res(name_)
 { };

 explicit sc_out_resolved_aug( inout_if_type& interface_)
 : sc_out_res(interface_)
 { };

 sc_out_resolved_aug( const char* name_, inout_if_type& interface_)
 : sc_out_res(name_, interface_)
 { };

 explicit sc_out_resolved_aug( inout_port_type& parent_ )
 : sc_out_res(parent_)
 { };

 sc_out_resolved_aug( const char* name_, inout_port_type& parent_ )
 : sc_out_res(name_,parent_)
 { };

 sc_out_resolved_aug( this_type& parent_)
 : sc_out_res( parent_ )
 { };

 sc_out_resolved_aug( const char* name_, this_type& parent_ )
 : sc_out_res( name_, parent_ )
 { };

 sc_out_resolved_aug( sc_out_res& parent_)
 : sc_out_res(parent_)
 { };

 sc_out_resolved_aug( const char* name_, sc_out_res& parent_ )
 : sc_out_res(name_,parent_)
 { };


 // destructor (does nothing)

 virtual ~sc_out_resolved_aug()
 {}


 void initialize_()  
 {
  if(pk_base::enabled) 
  {  
   pk_base::augdata_T.reset_data();
   pk_base::augdata_T.init_value( sc_out_res::read() );   
  }
  return;  
 };


 inline void write( const data_type& value_ )
 {
  sc_out_res::write( value_);
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

  this_type& operator = ( const sc_out_res& port_ )
  { write(port_->read()); return *this; }

  this_type& operator = ( const this_type& port_ )
  { write(port_->read()); return *this; }
   

 private:

 // disabled
 
 sc_out_resolved_aug( const this_type& );
 
};


// ---------------------------------------------------------------------------------
//  CLASS : sc_in_rv_aug<n>   
//
// class for augmented signals related to the SystemC port type sc_in_rv<n>
// ---------------------------------------------------------------------------------


template <int n>
class sc_in_rv_aug: public sc_core::sc_in_rv<n>, public pk_inport<sc_dt::sc_lv<n> >
{
 
 public:
 
 // typedefs

 typedef sc_dt::sc_lv<n>                      data_type;

 typedef sc_in_rv_aug<n>                      this_type;
 typedef sc_core::sc_in_rv<n>                 sc_in_rv;
 typedef typename sc_in_rv::base_type         base_type; 

 typedef typename sc_in_rv::in_if_type        in_if_type;
 typedef typename sc_in_rv::in_port_type      in_port_type;
 typedef typename sc_in_rv::inout_port_type   inout_port_type;

 typedef pk_inport<data_type>                  pk_base;

 
 //constructors 

 sc_in_rv_aug()
 : sc_in_rv()   
 { };

 explicit sc_in_rv_aug( const char* name_)
 : sc_in_rv(name_)
 { };

 explicit sc_in_rv_aug( const in_if_type& interface_)
 : sc_in_rv(interface_)
 { };

 sc_in_rv_aug( const char* name_, const in_if_type& interface_)
 : sc_in_rv(name_, interface_)
 { };

 explicit sc_in_rv_aug( in_port_type& parent_)
 : sc_in_rv(parent_)
 { };

 sc_in_rv_aug( const char* name_, in_port_type& parent_ )
 : sc_in_rv(name_,parent_)
 { };

 explicit sc_in_rv_aug( inout_port_type& parent_ )
 : sc_in_rv(parent_)
 { };

 sc_in_rv_aug( const char* name_, inout_port_type& parent_)
 : sc_in_rv(name_, parent_)
 { };

 sc_in_rv_aug( this_type& parent_)
 : sc_in_rv( parent_ )
 { };

 sc_in_rv_aug( const char* name_, this_type& parent_ )
 : sc_in_rv( name_, parent_ )
 { };

 sc_in_rv_aug( sc_in_rv& parent_ )
 : sc_in_rv( parent_ )
 { };

 sc_in_rv_aug( const char* name_, sc_in_rv& parent_ )
 : sc_in_rv( name_, parent_ )
 { };



 #ifdef PK_ENABLE_OPMODELS

 void set_opmod(pk_default_energy_lib::pk_opmodel_b* op)
 {
  pk_base::set_opmod_(op);
  return_val.set_opm(op);
 }

 private: 

 using sc_in_rv::read; 

 mutable pk_proxy_opmod< data_type > return_val;

 public:

 const pk_proxy_opmod< data_type >& read() const
 {
   return_val.set( static_cast< const sc_in_rv * >( this )->read() );
   return return_val;
 };

 #endif

 // destructor (does nothing)

 virtual ~sc_in_rv_aug()
 {}


 private:
 
 // disabled 

 sc_in_rv_aug(const this_type&);
 this_type& operator = (const this_type&);
 
};


// ---------------------------------------------------------------------------------
//  CLASS : sc_inout_rv_aug<n>   
//
// class for augmented signals related to the SystemC port type sc_inout_rv<n>
// ---------------------------------------------------------------------------------


template<int n>
class sc_inout_rv_aug
	:public sc_core::sc_inout_rv<n>, public pk_inoutport<sc_dt::sc_lv<n> >
{

  public:

 // typedefs

 typedef sc_dt::sc_lv<n>                         data_type;

 typedef sc_inout_rv_aug<n>                      this_type;
 typedef sc_core::sc_inout_rv<n>                 sc_inout_rv;
 typedef typename sc_inout_rv::base_type         base_type;  

 typedef typename sc_inout_rv::in_if_type        in_if_type;
 typedef typename sc_inout_rv::in_port_type      in_port_type;
 typedef typename sc_inout_rv::inout_if_type     inout_if_type;
 typedef typename sc_inout_rv::inout_port_type   inout_port_type;

 typedef pk_inoutport<data_type>                 pk_base;


 //constructors 

 sc_inout_rv_aug()
 : sc_inout_rv()   
 { };

 explicit sc_inout_rv_aug( const char* name_)
 : sc_inout_rv(name_)
 { };

 explicit sc_inout_rv_aug( const inout_if_type& interface_)
 : sc_inout_rv(interface_)
 { };

 sc_inout_rv_aug( const char* name_, const inout_if_type& interface_)
 : sc_inout_rv(name_, interface_)
 { };

 explicit sc_inout_rv_aug( inout_port_type& parent_)
 : sc_inout_rv(parent_)
 { };

 sc_inout_rv_aug( const char* name_, inout_port_type& parent_ )
 : sc_inout_rv(name_,parent_)
 { };

 sc_inout_rv_aug( this_type& parent_)
 : sc_inout_rv( parent_ )
 { };

 sc_inout_rv_aug( const char* name_, this_type& parent_ )
 : sc_inout_rv( name_, parent_ )
 { };

 sc_inout_rv_aug( sc_inout_rv& parent_ )
 : sc_inout_rv( parent_ )
 { };

 sc_inout_rv_aug( const char* name_, sc_inout_rv& parent_ )
 : sc_inout_rv( name_, parent_ )
 { };

 // destructor (does nothing)

 virtual ~sc_inout_rv_aug()
 {}


 inline void initialize_()  
 {
  if(pk_base::enabled) 
  {  
   pk_base::augdata_T.reset_data();
   pk_base::augdata_T.init_value( sc_inout_rv::read() );   
  }
  return;  
 };


 inline void update_data()
 {
  pk_base::augdata_T.update_value( sc_inout_rv::read() );   
  pk_aug_base<sc_dt::sc_logic>::compute_data(); 
 };


 inline void write( const data_type& value_ )
 {
  sc_inout_rv::write( value_ );
  if(pk_base::enabled)  pk_base::compute_data( value_ );
 }


 this_type& operator = ( const data_type& value_ )
 { (*this)->write( value_ ); return *this; }

 this_type& operator = ( const in_if_type& interface_ )
 { (*this)->write( interface_.read() ); return *this; }

 this_type& operator = ( const in_port_type& port_ )
 { (*this)->write( port_->read() ); return *this; }

 this_type& operator = ( const inout_port_type& port_ )
 { (*this)->write( port_->read() ); return *this; }

 this_type& operator = ( const this_type& port_ )
 { (*this)->write( port_->read() ); return *this; }

 this_type& operator = ( const sc_inout_rv& port_ )
 { (*this)->write( port_->read() ); return *this; }


 private:
 
 // disabled 

 sc_inout_rv_aug(const this_type&);


};


// ---------------------------------------------------------------------------------
//  CLASS : sc_out_rv_aug<n>   
//
// class for augmented signals related to the SystemC port type sc_out_rv<n>
// ---------------------------------------------------------------------------------


template<int n>
class sc_out_rv_aug
	:public sc_core::sc_out_rv<n>, public pk_outport<sc_dt::sc_lv<n> >
{

  public:

 // typedefs

 typedef sc_dt::sc_lv<n>                       data_type;

 typedef sc_out_rv_aug<n>                      this_type;
 typedef sc_core::sc_out_rv<n>                 sc_out_rv;
 typedef typename sc_out_rv::base_type         base_type; 


 typedef typename sc_out_rv::in_if_type        in_if_type;
 typedef typename sc_out_rv::in_port_type      in_port_type;
 typedef typename sc_out_rv::inout_if_type     inout_if_type;
 typedef typename sc_out_rv::inout_port_type   inout_port_type;

 typedef pk_outport<data_type>                 pk_base;


 //constructors 

 sc_out_rv_aug()
 : sc_out_rv()   
 { };

 explicit sc_out_rv_aug( const char* name_)
 : sc_out_rv(name_)
 { };

 explicit sc_out_rv_aug( const inout_if_type& interface_)
 : sc_out_rv(interface_)
 { };

 sc_out_rv_aug( const char* name_, const inout_if_type& interface_)
 : sc_out_rv(name_, interface_)
 { };

 explicit sc_out_rv_aug( inout_port_type& parent_)
 : sc_out_rv(parent_)
 { };

 sc_out_rv_aug( const char* name_, inout_port_type& parent_ )
 : sc_out_rv(name_,parent_)
 { };

 sc_out_rv_aug( this_type& parent_)
 : sc_out_rv( parent_ )
 { };

 sc_out_rv_aug( const char* name_, this_type& parent_ )
 : sc_out_rv( name_, parent_ )
 { };

 sc_out_rv_aug( sc_out_rv& parent_ )
 : sc_out_rv( parent_ )
 { };

 sc_out_rv_aug( const char* name_, sc_out_rv& parent_ )
 : sc_out_rv( name_, parent_ )
 { };

 // destructor (does nothing)

 virtual ~sc_out_rv_aug()
 {}


 inline void initialize_()  
 {
  if(pk_base::enabled) 
  {  
   pk_base::augdata_T.reset_data();
   pk_base::augdata_T.init_value( sc_out_rv::read() );   
  }
  return;  
 };


 inline void write( const data_type& value_ )
 {
  sc_out_rv::write( value_ );
  if(pk_base::enabled)  pk_base::compute_data( value_ );
 }


 this_type& operator = ( const data_type& value_ )
 { (*this)->write( value_ ); return *this; }

 this_type& operator = ( const in_if_type& interface_ )
 { (*this)->write( interface_.read() ); return *this; }

 this_type& operator = ( const in_port_type& port_ )
 { (*this)->write( port_->read() ); return *this; }

 this_type& operator = ( const inout_port_type& port_ )
 { (*this)->write( port_->read() ); return *this; }

 this_type& operator = ( const this_type& port_ )
 { (*this)->write( port_->read() ); return *this; }

 this_type& operator = ( const sc_out_rv& port_ )
 { (*this)->write( port_->read() ); return *this; }


 private:
 
 // disabled 

 sc_out_rv_aug(const this_type&);


};


}    //pk_core  


#endif

