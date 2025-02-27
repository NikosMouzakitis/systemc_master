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


#ifndef PK_SENSITIVE_H
#define PK_SENSITIVE_H



// ----------------------------------------------------------------------------
//  CLASS : pk_sensitive
// ----------------------------------------------------------------------------



namespace pk_core  
{

class pk_sensitive
{
   
 friend class power_module_b;
 
 public:

    // typedefs
	typedef sc_core::sc_signal_in_if<bool>     in_if_b_type;
	typedef sc_core::sc_signal_in_if<sc_dt::sc_logic>  in_if_l_type;
    typedef sc_core::sc_in<bool>               in_port_b_type;
    typedef sc_core::sc_in<sc_dt::sc_logic>    in_port_l_type;
    typedef sc_core::sc_inout<bool>            inout_port_b_type;
    typedef sc_core::sc_inout<sc_dt::sc_logic> inout_port_l_type;


 // constructor
 pk_sensitive(): p_obj(0), enabled(true)
 {};

 // destructor, does nothing
 ~pk_sensitive()
 {};

 public:

 void set(const sc_core::sc_sensitive& s, const bool& en)    
 { 
  p_obj = const_cast<sc_core::sc_sensitive*>(&s) ;  
  enabled = en;
 };

 #ifdef PK_SYSC_22   

 pk_sensitive& operator << ( sc_core::sc_process_handle );

 #if 0

    pk_sensitive& operator << ( sc_method_handle );
    pk_sensitive& operator << ( sc_thread_handle );
	
 #endif // 0

 #else

 pk_sensitive& operator << ( sc_method_handle handle_ );
 pk_sensitive& operator << ( sc_thread_handle handle_ );

 #endif 

  pk_sensitive& operator () ( const sc_core::sc_event& );
  pk_sensitive& operator () ( const sc_core::sc_interface& );
  pk_sensitive& operator () ( const sc_core::sc_port_base& );
  pk_sensitive& operator () ( sc_core::sc_event_finder& );

  pk_sensitive& operator << ( const sc_core::sc_event& );
  pk_sensitive& operator << ( const sc_core::sc_interface& );
  pk_sensitive& operator << ( const sc_core::sc_port_base& );
  pk_sensitive& operator << ( sc_core::sc_event_finder& );
  
 
  pk_sensitive& operator () ( sc_core::sc_cthread_handle, sc_core::sc_event_finder& );
  pk_sensitive& operator () ( sc_core::sc_cthread_handle, const in_if_b_type& );
  pk_sensitive& operator () ( sc_core::sc_cthread_handle, const in_if_l_type& );
  pk_sensitive& operator () ( sc_core::sc_cthread_handle, const in_port_b_type& );
  pk_sensitive& operator () ( sc_core::sc_cthread_handle, const in_port_l_type& );
  pk_sensitive& operator () ( sc_core::sc_cthread_handle, const inout_port_b_type& );
  pk_sensitive& operator () ( sc_core::sc_cthread_handle, const inout_port_l_type& );

  private:
    
  sc_core::sc_sensitive* p_obj;
  bool enabled;  

  private:

  // disabled

  pk_sensitive( const pk_sensitive& );
  pk_sensitive& operator = ( const pk_sensitive& );

};


// ----------------------------------------------------------------------------
//  CLASS : pk_sensitive_pos
// ----------------------------------------------------------------------------


class pk_sensitive_pos
{
  
 friend class power_module_b;

 public:

// typedefs

	typedef sc_core::sc_signal_in_if<bool>     in_if_b_type;
    typedef sc_core::sc_signal_in_if<sc_dt::sc_logic> in_if_l_type;
    typedef sc_core::sc_in<bool>               in_port_b_type;
    typedef sc_core::sc_in<sc_dt::sc_logic>    in_port_l_type;
    typedef sc_core::sc_inout<bool>            inout_port_b_type;
    typedef sc_core::sc_inout<sc_dt::sc_logic> inout_port_l_type;


 // constructor
 pk_sensitive_pos(): p_obj(0), enabled(true)
 {};

 // destructor, does nothing

 ~pk_sensitive_pos()
 {};


 void set(const sc_core::sc_sensitive_pos& s, const bool& en)   
 { 
  p_obj = const_cast<sc_core::sc_sensitive_pos*>(&s) ;  
  enabled = en;
 };

 
 #ifdef PK_SYSC_22   

 pk_sensitive_pos& operator << ( sc_core::sc_process_handle );

 #if 0

    pk_sensitive_pos& operator << ( sc_method_handle );
    pk_sensitive_pos& operator << ( sc_thread_handle );
	
 #endif // 0

 #else

 pk_sensitive_pos& pk_sensitive_pos::operator << ( sc_method_handle handle_ );
 pk_sensitive_pos& pk_sensitive_pos::operator << ( sc_thread_handle handle_ );

 #endif 


 pk_sensitive_pos& operator () ( const in_if_b_type& );
 pk_sensitive_pos& operator () ( const in_if_l_type& );
 pk_sensitive_pos& operator () ( const in_port_b_type& );
 pk_sensitive_pos& operator () ( const in_port_l_type& );
 pk_sensitive_pos& operator () ( const inout_port_b_type& );
 pk_sensitive_pos& operator () ( const inout_port_l_type& );

 pk_sensitive_pos& operator << ( const in_if_b_type& );
 pk_sensitive_pos& operator << ( const in_if_l_type& );
 pk_sensitive_pos& operator << ( const in_port_b_type& );
 pk_sensitive_pos& operator << ( const in_port_l_type& );
 pk_sensitive_pos& operator << ( const inout_port_b_type& );
 pk_sensitive_pos& operator << ( const inout_port_l_type& );

 private:
 
 sc_core::sc_sensitive_pos* p_obj;
 bool enabled;

 private:

 // disabled

 pk_sensitive_pos( const pk_sensitive_pos& );
 pk_sensitive_pos& operator = ( const pk_sensitive_pos& );

};


// ----------------------------------------------------------------------------
//  CLASS : pk_sensitive_neg
// ----------------------------------------------------------------------------

class pk_sensitive_neg
{
  
 friend class power_module_b;

 public:

// typedefs

    typedef sc_core::sc_signal_in_if<bool>     in_if_b_type;
    typedef sc_core::sc_signal_in_if<sc_dt::sc_logic> in_if_l_type;
    typedef sc_core::sc_in<bool>               in_port_b_type;
    typedef sc_core::sc_in<sc_dt::sc_logic>    in_port_l_type;
    typedef sc_core::sc_inout<bool>            inout_port_b_type;
    typedef sc_core::sc_inout<sc_dt::sc_logic> inout_port_l_type;


 // constructor

 pk_sensitive_neg(): p_obj(0), enabled(true)
 {};


 // destructor, does nothing

 ~pk_sensitive_neg()
 {};

 public:


 void set(const sc_core::sc_sensitive_neg& s, const bool& en)   
 { 
  p_obj = const_cast<sc_core::sc_sensitive_neg*>(&s) ;  
  enabled = en;
 };

 
 #ifdef PK_SYSC_22   

 pk_sensitive_neg& operator << ( sc_core::sc_process_handle );

 #if 0

    pk_sensitive_neg& operator << ( sc_method_handle );
    pk_sensitive_neg& operator << ( sc_thread_handle );
	
 #endif // 0

 #else

 pk_sensitive_neg& pk_sensitive_neg::operator << ( sc_method_handle handle_ );
 pk_sensitive_neg& pk_sensitive_neg::operator << ( sc_thread_handle handle_ );

 #endif 
 
 pk_sensitive_neg& operator () ( const in_if_b_type& );
 pk_sensitive_neg& operator () ( const in_if_l_type& );
 pk_sensitive_neg& operator () ( const in_port_b_type& );
 pk_sensitive_neg& operator () ( const in_port_l_type& );
 pk_sensitive_neg& operator () ( const inout_port_b_type& );
 pk_sensitive_neg& operator () ( const inout_port_l_type& );

 pk_sensitive_neg& operator << ( const in_if_b_type& );
 pk_sensitive_neg& operator << ( const in_if_l_type& );
 pk_sensitive_neg& operator << ( const in_port_b_type& );
 pk_sensitive_neg& operator << ( const in_port_l_type& );
 pk_sensitive_neg& operator << ( const inout_port_b_type& );
 pk_sensitive_neg& operator << ( const inout_port_l_type& );

 private:

 sc_core::sc_sensitive_neg* p_obj;
 bool enabled;

 private:

 // disabled

 pk_sensitive_neg( const pk_sensitive_neg& );
 pk_sensitive_neg& operator = ( const pk_sensitive_neg& );

};


}   // pk_core   


#endif
