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


#ifndef PK_BIT_TYPES
#define PK_BIT_TYPES

#include "PKtool/types_aug/pk_aug_signals.h" 




namespace sc_dt
{ 
  void b_not(sc_bit&, const sc_bit&);
  void b_and(sc_bit&, const sc_bit&, const sc_bit&);
  void b_and(sc_bit&, const sc_bit&, int);
  void b_and(sc_bit&, const sc_bit&, bool);
  void b_and(sc_bit&, const sc_bit&, char);
  void b_and(sc_bit&, int, const sc_bit&);
  void b_and(sc_bit&, bool, const sc_bit&);
  void b_and(sc_bit&, char, const sc_bit&);
  void b_or(sc_bit&, const sc_bit&, const sc_bit&);
  void b_or(sc_bit&, const sc_bit&, int);
  void b_or(sc_bit&, const sc_bit&, bool);
  void b_or(sc_bit&, const sc_bit&, char);
  void b_or(sc_bit&, int, const sc_bit&);
  void b_or(sc_bit&, bool, const sc_bit&);
  void b_or(sc_bit&, char, const sc_bit&);
  void b_xor(sc_bit&, const sc_bit&, const sc_bit&);
  void b_xor(sc_bit&, const sc_bit&, int);
  void b_xor(sc_bit&, const sc_bit&, bool);
  void b_xor(sc_bit&, const sc_bit&, char);
  void b_xor(sc_bit&, int, const sc_bit&);
  void b_xor(sc_bit&, bool, const sc_bit&);
  void b_xor(sc_bit&, char, const sc_bit&);
 }

namespace pk_dt
{

using pk_core::pk_internal_sgn;


// ----------------------------------------------------------------------------
//  CLASS : sc_bit_aug
//
//  class for the internal augmented signals related to the SystemC type sc_bit
// ----------------------------------------------------------------------------


class sc_bit_aug: public sc_bit, public pk_internal_sgn< sc_bit >
{

 public:

 // constructors

 sc_bit_aug(): sc_bit(), pk_internal_sgn<sc_bit>(this)
 { }

 sc_bit_aug( const sc_bit& a): sc_bit( a ), pk_internal_sgn<sc_bit>(this)
 { }

 sc_bit_aug( const sc_bit_aug& a ): sc_bit( static_cast<const sc_bit& >(a) ),
	                                    pk_internal_sgn<sc_bit>(this)
 { }

 explicit sc_bit_aug( bool a ): sc_bit( a ), pk_internal_sgn<sc_bit>(this)
 { }

 explicit sc_bit_aug( int a ): sc_bit( a ), pk_internal_sgn<sc_bit>(this)
 { }

 explicit sc_bit_aug( char a ): sc_bit( a ), pk_internal_sgn<sc_bit>(this)
 { }

 explicit sc_bit_aug( const sc_logic& a ): sc_bit( a ), pk_internal_sgn<sc_bit>(this)
 { }

 // destructor

 ~sc_bit_aug()
 {}


#define PK_DEFN_ASN_OP_T(op,tp)                               \
    sc_bit_aug& operator op ( tp val )                        \
    {                                                         \
     compute_data();                                           \
     sc_bit::operator op (val);                               \
     return *this;                                            \
    }   

 // assignment operators

 PK_DEFN_ASN_OP_T( =, int )
 PK_DEFN_ASN_OP_T( =, bool )
 PK_DEFN_ASN_OP_T( =, char )
 PK_DEFN_ASN_OP_T( =, const sc_logic& )
 PK_DEFN_ASN_OP_T( =, const sc_bit& )

 sc_bit_aug& operator = ( const sc_bit_aug& val)                    
 {                                                         
  return this->operator = (static_cast< const sc_bit& >(val));                                            
 } 

 // bitwise assignment operators

 PK_DEFN_ASN_OP_T( &=, const sc_bit& )
 PK_DEFN_ASN_OP_T( &=, int )
 PK_DEFN_ASN_OP_T( &=, bool )
 PK_DEFN_ASN_OP_T( &=, char )

 PK_DEFN_ASN_OP_T( |=, const sc_bit& )
 PK_DEFN_ASN_OP_T( |=, int )
 PK_DEFN_ASN_OP_T( |=, bool )
 PK_DEFN_ASN_OP_T( |=, char )

 PK_DEFN_ASN_OP_T( ^=, const sc_bit& )
 PK_DEFN_ASN_OP_T( ^=, int )
 PK_DEFN_ASN_OP_T( ^=, bool )
 PK_DEFN_ASN_OP_T( ^=, char )

 #undef PK_DEFN_ASN_OP_T

 
 
 // friend functions and other writing methods

 sc_bit_aug& b_not()
 {
  compute_data();
  sc_bit:: b_not();
  return *this;
 }
 
 friend void b_not( sc_bit_aug& r, const sc_bit& a)
 {                                                                             
  r.compute_data();   
  sc_dt::b_not( static_cast<sc_bit&>(r), a);  
 }   

 #define PK_DEFN_BIN_FNC_T( fnc, tp1 , tp2)                                    \
 friend void fnc ( sc_bit_aug& r, tp1 a, tp2 b)                                \
 {                                                                             \
  r.compute_data();                                                              \
  sc_dt:: fnc ( static_cast<sc_dt::sc_bit&>(r), a, b);                         \
 }    

#define PK_DEFN_BIN_FNC( fnc )                                                 \
PK_DEFN_BIN_FNC_T( fnc , sc_bit& , sc_bit& )                                   \
PK_DEFN_BIN_FNC_T( fnc , const sc_bit& , int )                                 \
PK_DEFN_BIN_FNC_T( fnc , const sc_bit& , bool )                                \
PK_DEFN_BIN_FNC_T( fnc , const sc_bit& , char )                                \
PK_DEFN_BIN_FNC_T( fnc , int , const sc_bit& )                                 \
PK_DEFN_BIN_FNC_T( fnc , bool , const sc_bit& )                                \
PK_DEFN_BIN_FNC_T( fnc , char , sc_bit& )                                      

PK_DEFN_BIN_FNC( b_or )
PK_DEFN_BIN_FNC( b_and )
PK_DEFN_BIN_FNC( b_xor )

void scan( istream& is=cin)
{compute_data();
 sc_bit::scan(is);
}

#undef PK_DEFN_BIN_FNC_T
#undef PK_DEFN_BIN_FNC

};

inline
istream& operator >> ( istream& is, sc_bit_aug& a)
{
 a.scan( is );
 return is;
}





// ----------------------------------------------------------------------------
//  CLASS : sc_logic_aug
//
//  class for the internal augmented signals related to the SystemC type sc_logic
// ----------------------------------------------------------------------------

using sc_dt::sc_logic_value_t;


class sc_logic_aug: public sc_logic, public pk_internal_sgn< sc_logic >
{


 public:

 // constructors

 sc_logic_aug(): sc_logic(), pk_internal_sgn<sc_logic>(this)
 { }

 sc_logic_aug( const sc_logic& a ): sc_logic( a ), pk_internal_sgn<sc_logic>(this)
 { }

 sc_logic_aug( const sc_logic_aug& a ): sc_logic( static_cast<const sc_logic& >(a) ),
	                                    pk_internal_sgn<sc_logic>(this)
 { }

 sc_logic_aug( const sc_logic_value_t a ): sc_logic( a ), pk_internal_sgn<sc_logic>(this)
 { }

 explicit sc_logic_aug( bool a ): sc_logic( a ), pk_internal_sgn<sc_logic>(this)
 { }

 explicit sc_logic_aug( int a ): sc_logic( a ), pk_internal_sgn<sc_logic>(this)
 { }

 explicit sc_logic_aug( char a ): sc_logic( a ), pk_internal_sgn<sc_logic>(this)
 { }

 explicit sc_logic_aug( const sc_bit& a ): sc_logic( a ), pk_internal_sgn<sc_logic>(this)
 { }

 //destructor 

 ~sc_logic_aug()
 {}

 

 #define PK_DEFN_ASN_OP_T(op,tp)                               \
    sc_logic& operator op ( tp val )                           \
    {                                                          \
     compute_data();                                             \
     sc_logic::operator op (val);                              \
     return *this;                                             \
    }                                                           

 #define PK_DEFN_ASN_OP( op )                                  \
  PK_DEFN_ASN_OP_T( op, sc_logic& )                            \
  PK_DEFN_ASN_OP_T( op, sc_logic_value_t )                     \
  PK_DEFN_ASN_OP_T( op, bool )                                 \
  PK_DEFN_ASN_OP_T( op, char )                                 \
  PK_DEFN_ASN_OP_T( op, int )                                       

 // assignment operators

 PK_DEFN_ASN_OP( = )

 sc_logic_aug& operator = ( const sc_logic_aug& val)                    
 {                                                         
  return this->operator = (static_cast< const sc_logic& >(val));
 } 

 PK_DEFN_ASN_OP_T( =, const sc_bit& )

 // bitwise assignment operators
 
 PK_DEFN_ASN_OP( &= )
 PK_DEFN_ASN_OP( |= )
 PK_DEFN_ASN_OP( ^= )

 // other writing methods

 sc_logic_aug& b_not()
 {
  compute_data();
  sc_logic:: b_not();
  return *this;
 }

 void scan( istream& is=cin )
 {
  compute_data();
  sc_logic:: scan( is );
 }

 private:  // disabled

 explicit sc_logic_aug( const char* );
 sc_logic_aug& operator = ( const char* );
 

 #undef PK_DEFN_ASN_OP
 #undef PK_DEFN_ASN_OP_T

};







// ----------------------------------------------------------------------------
//  CLASS : sc_bv_aug<n>
//
//  class for the internal augmented signals related to the SystemC type sc_bv<n>
// ----------------------------------------------------------------------------

using sc_dt::sc_bitref;
using sc_dt::sc_subref;
using sc_dt::sc_proxy;

template<int n> class sc_bv_aug: public sc_dt::sc_bv<n>, 
                                 public pk_internal_sgn< sc_bv<n> >
{

 public:

 typedef sc_dt::sc_bv_base                      sc_type_base;
 typedef sc_dt::sc_bv<n>                        sc_type;
 typedef pk_core::pk_internal_sgn< sc_bv<n> >   pk_base;


 // constructors

 sc_bv_aug(): sc_bv<n>(), pk_internal_sgn<sc_bv<n> >(this)
 {}

 explicit sc_bv_aug(bool a): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }
 
 explicit sc_bv_aug(char a): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug(const char* a): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this) 
 { } 
 
 sc_bv_aug(const bool* a): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug(const sc_logic* a): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug(const sc_dt::sc_unsigned& a): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug(const sc_dt::sc_signed& a): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug(const sc_dt::sc_uint_base& a): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( const sc_dt::sc_int_base& a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( unsigned long a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( long a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( unsigned int a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( int a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( uint64 a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( int64 a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }
 
 template< class X >
 sc_bv_aug( const sc_proxy<X>& a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( const sc_bv<n>& a ): sc_bv<n>( a ), pk_internal_sgn<sc_bv<n> >(this)
 { }

 sc_bv_aug( const sc_bv_aug<n>& a ): sc_bv<n>( static_cast<const sc_bv<n>& >(a) ),
	                                    pk_internal_sgn<sc_bv<n> >(this)
 { }

 

 #define PK_DEFN_ASN_OP_T(op,tp)                              \
    sc_bv_aug<n>& operator op ( tp val )                      \
    {                                                         \
	 pk_base::compute_data();                                 \
     sc_type::operator op (val);                              \
     return *this;                                            \
    } 

 #define PK_DEFN_ASN_OP( op )                                 \
    PK_DEFN_ASN_OP_T( op, const char* )                       \
	PK_DEFN_ASN_OP_T( op, const bool* )                       \
    PK_DEFN_ASN_OP_T( op, const sc_logic* )                   \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_unsigned& )         \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_signed& )           \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_uint_base& )        \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_int_base& )         \
	PK_DEFN_ASN_OP_T( op, unsigned long )                     \
	PK_DEFN_ASN_OP_T( op, long )                              \
    PK_DEFN_ASN_OP_T( op, unsigned int )                      \
    PK_DEFN_ASN_OP_T( op, int )                               \
    PK_DEFN_ASN_OP_T( op, uint64 )                            \
    PK_DEFN_ASN_OP_T( op, int64 ) 

 // assignment operators

 template <class X>
 PK_DEFN_ASN_OP_T( =, const sc_proxy<X> )

 PK_DEFN_ASN_OP_T( =, const sc_bv<n>& )

 sc_bv_aug<n>& operator = ( const sc_bv_aug<n>& val)                    
 {                                                         
  return this->operator = (static_cast< const sc_type& >(val));                                            
 } 

 PK_DEFN_ASN_OP( = )

 // bitwise assignment operators

 PK_DEFN_ASN_OP( &= )
 PK_DEFN_ASN_OP( |= )
 PK_DEFN_ASN_OP( ^= )



 
 // other writing methods

 sc_bv_aug& b_not( )
 {
  pk_base::compute_data();
  sc_type::b_not();
  return *this;
 }

 PK_DEFN_ASN_OP_T( <<=, int )
 PK_DEFN_ASN_OP_T( >>=, int )

 sc_bv_aug<n>& lrotate ( int a )
 {
  pk_base::compute_data();
  sc_type::lrotate( a ); 
  return *this;
 }

 sc_bv_aug<n>& rrotate ( int a )
 {
  pk_base::compute_data();
  sc_type::rrotate( a ); 
  return *this;
 }

 sc_bv_aug<n>& reverse()
 {
  pk_base::compute_data();
  sc_type::reverse(); 
  return *this;
 }


 void set_bit(int i, sc_logic_value_t value)
 {
  pk_base::compute_data();
  return sc_type::set_bit( i, value ); 
 }

 void set_word(int i, unsigned long w)
 {
  pk_base::compute_data();
  return sc_type::set_word( i, w );  
 }

 void set_cword(int i, unsigned long w)
 {
  pk_base::compute_data();
  return sc_type::set_cword( i, w );  
 }

 void clean_tail()
 {
  pk_base::compute_data();
  return sc_type::clean_tail(); 
 }

 void scan(istream& is=cin)
 {
  pk_base::compute_data();
  return sc_type::scan(is); 
 }


 #define PK_METHOD_DEFN( type)                                          \
 sc_bv_aug<n>& assign_ ( type val)                                      \
 {                                                                      \
  pk_base::compute_data();                                              \
  sc_type::assign_( val );                                              \
  return *this;                                                         \
 }

 PK_METHOD_DEFN( const char*)
 PK_METHOD_DEFN( const bool*)
 PK_METHOD_DEFN( const sc_dt::sc_logic*)
 PK_METHOD_DEFN( const sc_dt::sc_unsigned&)
 PK_METHOD_DEFN( const sc_dt::sc_signed&)
 PK_METHOD_DEFN( const sc_dt::sc_uint_base&)
 PK_METHOD_DEFN( const sc_dt::sc_int_base&)
 PK_METHOD_DEFN( unsigned long)
 PK_METHOD_DEFN( long)
 PK_METHOD_DEFN( unsigned int)
 PK_METHOD_DEFN( int)
 PK_METHOD_DEFN( uint64)
 PK_METHOD_DEFN( int64)

 template <class Y>
 PK_METHOD_DEFN( const sc_proxy<Y>&)


 #undef PK_DEFN_ASN_OP_T
 #undef PK_DEFN_ASN_OP
 #undef PK_METHOD_DEFN

 
  sc_bitref<sc_type_base> operator [] ( int i )
  {
   pk_base::compute_data();
   return sc_type::operator []( i ); 
  }

  sc_bitref<sc_type_base> bit( int i )
  {
   pk_base::compute_data();
   return sc_type::bit( i ); 
  }

  

  sc_subref<sc_type_base> operator() ( int hi, int lo )
  {
   pk_base::compute_data();
   return sc_type::operator ()( hi, lo ); 
  }
  
  sc_subref<sc_type_base> range ( int hi, int lo )
  {
   pk_base::compute_data();
   return sc_type::range(hi,lo ); 
  }

};


// other writing operators and methods

template <class X,int n>
inline
sc_bv_aug<n>& operator &= ( sc_bv_aug<n>& px, const sc_proxy<X>& py )
{ px.compute_data();
  sc_dt::operator &= ( static_cast<sc_proxy<sc_dt::sc_bv_base>& >(px),py);
  return px;
}

template <class X,int n>
inline
sc_bv_aug<n>& operator |= ( sc_bv_aug<n>& px, const sc_proxy<X>& py )
{ px.compute_data();
  sc_dt::operator |= ( static_cast<sc_proxy<sc_dt::sc_bv_base>& >(px),py);
  return px;
}

template <class X,int n>
inline
sc_bv_aug<n>& operator ^= ( sc_bv_aug<n>& px, const sc_proxy<X>& py )
{ px.compute_data();
  sc_dt::operator ^= ( static_cast<sc_proxy<sc_dt::sc_bv_base>& >(px),py);
  return px;
}

template <class X,int n>
inline void assign_p_( sc_bv_aug<n>& px, const sc_proxy<X>& py )
{px.compute_data();
 return sc_dt::assign_p_( static_cast<sc_proxy<sc_dt::sc_bv_base>& >(px),py);
}

template <class X,int n>
inline void assign_v_( sc_bv_aug<n>& px, const sc_proxy<X>& py )
{px.compute_data();
 return sc_dt::assign_v_( static_cast<sc_proxy<sc_dt::sc_bv_base>& >(px),py);
}

template <class X,int n>
inline
sc_bv_aug<n>& b_and_assign_( sc_bv_aug<n>& px, const sc_proxy<X>& py )
{px.compute_data();                
 sc_dt::b_and_assign_( static_cast<sc_proxy<sc_dt::sc_bv_base>& >(px),py);  
 return px; 
}

template <class X,int n>
inline
sc_bv_aug<n>& b_or_assign_( sc_bv_aug<n>& px, const sc_proxy<X>& py )
{px.compute_data();
 sc_dt::b_or_assign_( static_cast<sc_proxy<sc_dt::sc_bv_base>& >(px),py);
 return px;  
}

template <class X, int n>
inline
sc_bv_aug<n>& b_xor_assign_( sc_bv_aug<n>& px, const sc_proxy<X>& py )
{px.compute_data();
 sc_dt::b_xor_assign_( static_cast<sc_proxy<sc_dt::sc_bv_base>& >(px),py);
 return px;  
}



// ----------------------------------------------------------------------------
//  CLASS : sc_lv_aug<n>
//
//  class for the internal augmented signals related to the SystemC type sc_lv_aug<n>
// ----------------------------------------------------------------------------



template<int n> class sc_lv_aug: public sc_lv<n>, 
                                 public pk_internal_sgn< sc_lv<n> >
{

 public:

 typedef sc_dt::sc_lv_base                      sc_type_base;
 typedef sc_dt::sc_lv<n>                        sc_type;
 typedef pk_core::pk_internal_sgn< sc_lv<n> >   pk_type;


 // constructors

 sc_lv_aug(): sc_lv<n>(), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const sc_lv<n>& a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const sc_lv_aug<n>& a ): sc_lv<n>( static_cast<const sc_lv<n>& >(a) ),
	                                    pk_internal_sgn<sc_lv<n> >(this)
 { }

 explicit sc_lv_aug( const sc_logic& init_value ): sc_lv<n>( init_value ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 explicit sc_lv_aug( bool init_value ): sc_lv<n>( init_value ),pk_internal_sgn<sc_lv<n> >(this)
 { }

 explicit sc_lv_aug( char init_value ): sc_lv<n>( init_value ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const char* a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const bool* a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const sc_logic* a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const sc_dt::sc_unsigned& a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const sc_dt::sc_signed& a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const sc_dt::sc_uint_base& a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( const sc_dt::sc_int_base& a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( unsigned long a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( long a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( unsigned int a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( int a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( uint64 a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 sc_lv_aug( int64 a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }

 template <class X>
 sc_lv_aug( const sc_proxy<X>& a ): sc_lv<n>( a ), pk_internal_sgn<sc_lv<n> >(this)
 { }


 
 #define PK_DEFN_ASN_OP_T(op,tp)                              \
    sc_lv_aug<n>& operator op ( tp val )                      \
    {                                                         \
     pk_type::compute_data();                                 \
     sc_type::operator op (val);                              \
     return *this;                                            \
    } 

 #define PK_DEFN_ASN_OP( op )                                 \
    PK_DEFN_ASN_OP_T( op, const char* )                       \
	PK_DEFN_ASN_OP_T( op, const bool* )                       \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_logic* )                   \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_unsigned& )                \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_signed& )           \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_uint_base& )        \
    PK_DEFN_ASN_OP_T( op, const sc_dt::sc_int_base& )         \
	PK_DEFN_ASN_OP_T( op, unsigned long )                     \
	PK_DEFN_ASN_OP_T( op, long )                              \
    PK_DEFN_ASN_OP_T( op, unsigned int )                      \
    PK_DEFN_ASN_OP_T( op, int )                               \
    PK_DEFN_ASN_OP_T( op, uint64 )                            \
    PK_DEFN_ASN_OP_T( op, int64 ) 

 // assignment operators

 template <class X>
 PK_DEFN_ASN_OP_T( =, const sc_proxy<X> )
 PK_DEFN_ASN_OP_T( =, const sc_lv<n>& )

 sc_lv_aug<n>& operator = ( const sc_lv_aug<n>& val)                    
 {                                                         
  return this->operator = (static_cast< const sc_lv<n>& >(val));                                            
 } 

 PK_DEFN_ASN_OP( = )

 // bitwise assignment operators

 PK_DEFN_ASN_OP( &= )
 PK_DEFN_ASN_OP( |= )
 PK_DEFN_ASN_OP( ^= )



 
 // other writing methods 

 sc_lv_aug& b_not( )
 {
  pk_type::compute_data();
  sc_type::b_not();
  return *this;
 }

 PK_DEFN_ASN_OP_T( <<=, int )
 PK_DEFN_ASN_OP_T( >>=, int )

 sc_lv_aug<n>& lrotate ( int a )
 {
  pk_type::compute_data();
  sc_type::lrotate( a ); 
  return *this;
 }

 sc_lv_aug<n>& rrotate ( int a )
 {
  pk_type::compute_data();
  sc_type::rrotate( a ); 
  return *this;
 }

 sc_lv_aug<n>& reverse()
 {
  pk_type::compute_data();
  sc_type::reverse(); 
  return *this;
 }


 void set_bit(int i, sc_logic_value_t value)
 {
  pk_type::compute_data();
  return sc_type::set_bit( i, value ); 
 }

 void set_word(int i, unsigned long w)
 {
  pk_type::compute_data();
  return sc_type::set_word( i, w );  
 }

 void set_cword(int i, unsigned long w)
 {
  pk_type::compute_data();
  return sc_type::set_cword( i, w );  
 }

 void clean_tail()
 {
  pk_type::compute_data();
  return sc_type::clean_tail(); 
 }

 void scan(istream& is=cin)
 {
  pk_type::compute_data();
  return sc_type::scan(is); 
 }


 #define PK_METHOD_DEFN( type)                                          \
 sc_lv_aug<n>& assign_ ( type val)                                      \
 {                                                                      \
  pk_type::compute_data();                                              \
  sc_type::assign_( val );                                              \
  return *this;                                                         \
 }

 PK_METHOD_DEFN( const char*)
 PK_METHOD_DEFN( const bool*)
 PK_METHOD_DEFN( const sc_dt::sc_logic*)
 PK_METHOD_DEFN( const sc_dt::sc_unsigned&)
 PK_METHOD_DEFN( const sc_dt::sc_signed&)
 PK_METHOD_DEFN( const sc_dt::sc_uint_base&)
 PK_METHOD_DEFN( const sc_dt::sc_int_base&)
 PK_METHOD_DEFN( unsigned long)
 PK_METHOD_DEFN( long)
 PK_METHOD_DEFN( unsigned int)
 PK_METHOD_DEFN( int)
 PK_METHOD_DEFN( uint64)
 PK_METHOD_DEFN( int64)

 template <class Y>
 PK_METHOD_DEFN( const sc_proxy<Y>&)


 #undef PK_DEFN_ASN_OP_T
 #undef PK_DEFN_ASN_OP
 #undef PK_METHOD_DEFN


  
  sc_bitref<sc_type_base> operator [] ( int i )
  {
   pk_type::compute_data();
   return sc_type::operator []( i ); 
  }

  sc_bitref<sc_type_base> bit( int i )
  {
   pk_type::compute_data();
   return sc_type::bit( i ); 
  }



  sc_subref<sc_type_base> operator() ( int hi, int lo )
  {
   pk_type::compute_data();
   return sc_type::operator ()( hi, lo ); 
  }
  
  sc_subref<sc_type_base> range ( int hi, int lo )
  {
   pk_type::compute_data();
   return sc_type::range(hi,lo ); 
  }

};

// other writing operators and methods

template <class X,int n>
inline
sc_lv_aug<n>& operator &= ( sc_lv_aug<n>& px, const sc_proxy<X>& py )
{ px.compute_data();
  sc_dt::operator &= ( static_cast<sc_proxy<sc_dt::sc_lv_base>& >(px),py);
  return px;
}

template <class X,int n>
inline
sc_lv_aug<n>& operator |= ( sc_lv_aug<n>& px, const sc_proxy<X>& py )
{ px.compute_data();
  sc_dt::operator |= ( static_cast<sc_proxy<sc_dt::sc_lv_base>& >(px),py);
  return px;
}

template <class X,int n>
inline
sc_lv_aug<n>& operator ^= ( sc_lv_aug<n>& px, const sc_proxy<X>& py )
{ 
  px.compute_data();
  sc_dt::operator ^= ( static_cast<sc_proxy<sc_dt::sc_lv_base>& >(px),py);
  return px;
}

template <class X,int n>
inline void assign_p_( sc_lv_aug<n>& px, const sc_proxy<X>& py )
{
 px.compute_data();
 return sc_dt::assign_p_( static_cast<sc_proxy<sc_dt::sc_lv_base>& >(px),py);
}

template <class X,int n>
inline void assign_v_( sc_lv_aug<n>& px, const sc_proxy<X>& py )
{
 px.compute_data();
 return sc_dt::assign_v_( static_cast<sc_proxy<sc_dt::sc_lv_base>& >(px),py);
}


template <class X,int n>
inline
sc_lv_aug<n>& b_and_assign_( sc_lv_aug<n>& px, const sc_proxy<X>& py )
{
 px.compute_data();
 sc_dt::b_and_assign_( static_cast<sc_proxy<sc_dt::sc_lv_base>& >(px),py);
 return px; 
}

template <class X,int n>
inline
sc_lv_aug<n>& b_or_assign_( sc_lv_aug<n>& px, const sc_proxy<X>& py )
{
 px.compute_data();
 sc_dt::b_or_assign_( static_cast<sc_proxy<sc_dt::sc_lv_base>& >(px),py);
 return px;  
}

template <class X, int n>
inline
sc_lv_aug<n>& b_xor_assign_( sc_lv_aug<n>& px, const sc_proxy<X>& py )
{
 px.compute_data();
 sc_dt::b_xor_assign_( static_cast<sc_proxy<sc_dt::sc_lv_base>& >(px),py);
 return px;  
}


}  //pk_dt








#endif
