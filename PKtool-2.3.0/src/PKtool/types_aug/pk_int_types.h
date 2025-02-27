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

#ifndef PK_INT_TYPES
#define PK_INT_TYPES

#include "PKtool/types_aug/pk_aug_signals.h" 


#ifdef PK_ENABLE_OPMODELS 

#include "PKtool/power_models/pk_opmodel_macros.h"

#endif




namespace pk_dt
{ 
using sc_dt::sc_int_bitref;
using sc_dt::sc_int_bitref_r;
using sc_dt::sc_int_subref;
using sc_dt::sc_int_subref_r;
using sc_dt::sc_uint_bitref;
using sc_dt::sc_uint_bitref_r;
using sc_dt::sc_uint_subref;
using sc_dt::sc_uint_subref_r;

using pk_core::pk_internal_sgn;


typedef int64 int_type;
typedef uint64 uint_type;



// ----------------------------------------------------------------------------
//  CLASS : sc_int_aug<n>
//
//  class for the internal augmented signals related to the SystemC type sc_int<n>
// ----------------------------------------------------------------------------

template<int n> class sc_int_aug: public sc_int<n>, 
                                  public pk_core::pk_internal_sgn< sc_int<n> > 
{ 

 public:

 typedef sc_int<n>                     sc_type;
 typedef sc_int_aug<n>&                this_type_r;
 typedef pk_internal_sgn< sc_int<n> >  pk_base; 

 // constructors

 sc_int_aug(): sc_int<n>(), pk_internal_sgn<sc_int<n> >(this)   
 { }
 
 sc_int_aug( int_type v ): sc_int<n>( v ), pk_internal_sgn<sc_int<n> >(this) 
 { }
 
 sc_int_aug( const sc_int<n>& a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( const sc_int_aug<n>& a ): sc_int<n>( static_cast<const sc_int<n>& >(a) ),
	                                    pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( const sc_dt::sc_int_base& a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( const sc_int_subref_r& a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( const sc_dt::sc_signed& a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( const sc_dt::sc_unsigned& a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

#ifdef SC_INCLUDE_FX

 explicit sc_int_aug(sc_fxval& a): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 explicit sc_int_aug(sc_fxval_fast& a): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 explicit sc_int_aug(sc_fxnum& a): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }
 
 explicit sc_int_aug(sc_fxnum_fast& a): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 #endif

 sc_int_aug( const sc_dt::sc_bv_base& a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( const sc_dt::sc_lv_base& a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( const char* a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( unsigned long a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( long a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( unsigned int a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( int a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }

 sc_int_aug( uint64 a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this) 
 { }
 
 sc_int_aug( double a ): sc_int<n>( a ), pk_internal_sgn<sc_int<n> >(this)
 { }

 #ifdef PK_ENABLE_OPMODELS    

 
 #define PK_DEFN_ASN_OPMODEL_T(op,op_sym, tp)                 \
    sc_int_aug<n>& operator op ( tp val )                     \
    {                                                         \
	 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task( op_sym );          \
     pk_base::compute_data();                                 \
     sc_type::operator op ( val );                            \
     return *this;                                            \
    }                                                         \
	PK_OPMODEL_OP7(op, sc_int_aug<n>, op_sym)

#endif

#define PK_DEFN_ASN_OP_T(op,tp)                               \
    sc_int_aug<n>& operator op ( tp val )                     \
    {                                                         \
	 pk_base::compute_data();                                 \
     sc_type::operator op ( val );                            \
     return *this;                                            \
    }                                                            
      

 // assignment operators


 PK_DEFN_ASN_OP_T( =, int_type)
 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_int_base&)
 PK_DEFN_ASN_OP_T( =, const sc_int_subref_r&)
 PK_DEFN_ASN_OP_T( =, const sc_int<n>&)
 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_signed&)
 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_unsigned&)

 sc_int_aug<n>& operator = ( const sc_int_aug<n>& val)                    
 {
  pk_base::compute_data();
  sc_type::operator =( static_cast< const sc_int<n>& >(val) );  
  return *this;
 } 

 #ifdef SC_INCLUDE_FX

 PK_DEFN_ASN_OP_T( =, const sc_fxval&)
 PK_DEFN_ASN_OP_T( =, const sc_fxval_fast&)
 PK_DEFN_ASN_OP_T( =, const sc_fxnum&)
 PK_DEFN_ASN_OP_T( =, const sc_fxnum_fast&)

#endif

 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_bv_base&)
 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_lv_base&)
 PK_DEFN_ASN_OP_T( =, const char*)
 PK_DEFN_ASN_OP_T( =, unsigned long)
 PK_DEFN_ASN_OP_T( =, long)
 PK_DEFN_ASN_OP_T( =, unsigned int)
 PK_DEFN_ASN_OP_T( =, int)
 PK_DEFN_ASN_OP_T( =, uint64)
 PK_DEFN_ASN_OP_T( =, double)
  

 // other assignment operators

 #ifdef PK_ENABLE_OPMODELS
 
 PK_DEFN_ASN_OPMODEL_T( +=, '+', int_type)
 PK_DEFN_ASN_OPMODEL_T( -=, '-', int_type)
 PK_DEFN_ASN_OPMODEL_T( *=, '*', int_type)
 PK_DEFN_ASN_OPMODEL_T( /=, '/', int_type)

 #else

 PK_DEFN_ASN_OP_T( +=, int_type)
 PK_DEFN_ASN_OP_T( -=, int_type)
 PK_DEFN_ASN_OP_T( *=, int_type)
 PK_DEFN_ASN_OP_T( /=, int_type)

 #endif

 PK_DEFN_ASN_OP_T( %=, int_type)
 
 PK_DEFN_ASN_OP_T( &=, int_type)
 PK_DEFN_ASN_OP_T( |=, int_type)
 PK_DEFN_ASN_OP_T( ^=, int_type)
 PK_DEFN_ASN_OP_T( <<=, int_type)
 PK_DEFN_ASN_OP_T( >>=, int_type)


 #ifdef PK_ENABLE_OPMODELS

 PK_OPMODEL_OP6(sc_int)

 #else
 sc_int_aug<n>& operator ++ () 
 {
  pk_base::compute_data(); 
  sc_type::operator ++ ();
  return *this; 
 }

 const sc_int<n> operator ++ (int) 
 {
  pk_base::compute_data(); 
  return sc_type:: operator ++ (0);
 }

 sc_int_aug<n>& operator -- () 
 {
  pk_base::compute_data(); 
  sc_type::operator -- ();
  return *this; 
 }

 const sc_int<n>& operator -- (int) 
 {
  pk_base::compute_data(); 
  return sc_int<n>:: operator -- (0);
 }

#endif
 
 
 sc_int_bitref&   operator [] ( int i )
 {
  pk_base::compute_data();
  return sc_type::operator[](i);
 };


 const sc_int_bitref_r& operator [] ( int i ) const
 {
  pk_base::compute_data();
  return sc_type::operator [](i);
 };

 sc_int_subref range(int left,int right)
 {
  pk_base::compute_data();
  return sc_type::range(left,right);
 };
 
 #undef PK_DEFN_ASN_OPMODEL_T
 #undef PK_DEFN_ASN_OP_T 
};




// ----------------------------------------------------------------------------
//  CLASS : sc_uint_aug<n>
//
//  class for the internal augmented signals related to the SystemC type sc_uint<n>
// ----------------------------------------------------------------------------


template<int n> 
class sc_uint_aug: public sc_uint<n>, public pk_internal_sgn< sc_uint<n> > 
{

 public:
 
 typedef sc_uint<n> sc_type;
 typedef sc_uint_aug<n>& this_type_r;
 typedef pk_internal_sgn< sc_uint<n> > pk_base; 

 // constructors


 sc_uint_aug(): sc_uint<n>(), pk_internal_sgn<sc_uint<n> >(this)   
 { }

 
 sc_uint_aug( uint_type v ): sc_int<n>( v ), pk_internal_sgn<sc_uint<n> >(this)  
 { }
 
 sc_uint_aug( const sc_uint<n>& a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( const sc_uint_aug<n>& a ): sc_uint<n>( static_cast<const sc_uint<n>& >(a)),
	                                      pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( const sc_dt::sc_uint_base& a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( const sc_uint_subref_r& a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }
 
 sc_uint_aug( const sc_dt::sc_signed& a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( const sc_dt::sc_unsigned& a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

#ifdef SC_INCLUDE_FX

 explicit sc_uint_aug(sc_fxval& a): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 explicit sc_uint_aug(sc_fxval_fast& a): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 explicit sc_uint_aug(sc_fxnum& a): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }
 
 explicit sc_uint_aug(sc_fxnum_fast& a): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 #endif

 sc_uint_aug( const sc_dt::sc_bv_base& a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( const sc_dt::sc_lv_base& a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( const char* a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( unsigned long a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( long a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( unsigned int a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( int a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }

 sc_uint_aug( int64 a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }
 
 sc_uint_aug( double a ): sc_uint<n>( a ), pk_internal_sgn<sc_uint<n> >(this) 
 { }


 #ifdef PK_ENABLE_OPMODELS    

 
 #define PK_DEFN_ASN_OPMODEL_T(op,op_sym, tp)                 \
    sc_uint_aug<n>& operator op ( tp val )                     \
    {                                                         \
	 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task( op_sym );          \
     pk_base::compute_data();                                 \
     sc_type::operator op ( val );                            \
     return *this;                                            \
    }                                                         \
    PK_OPMODEL_OP7(op, sc_uint_aug<n>, op_sym)

 #endif


 #define PK_DEFN_ASN_OP_T(op,tp)                              \
    sc_uint_aug<n>& operator op ( tp val )                    \
    {                                                         \
	 pk_base::compute_data();                                 \
     sc_type::operator op (val);                              \
     return *this;                                            \
    }   
   

 // assignment operators
 
 PK_DEFN_ASN_OP_T( =, uint_type)
 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_uint_base&)
 PK_DEFN_ASN_OP_T( =, const sc_uint_subref_r&)
 PK_DEFN_ASN_OP_T( =, const sc_uint<n>&)
 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_signed&)
 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_unsigned&)

 sc_uint_aug<n>& operator = ( const sc_uint_aug<n>& val)                    
 {
  pk_base::compute_data();
  sc_type::operator = (static_cast< const sc_uint<n>& >(val));
  return *this;
 } 

 #ifdef SC_INCLUDE_FX

 PK_DEFN_ASN_OP_T( =, const sc_fxval&)
 PK_DEFN_ASN_OP_T( =, const sc_fxval_fast&)
 PK_DEFN_ASN_OP_T( =, const sc_fxnum&)
 PK_DEFN_ASN_OP_T( =, const sc_fxnum_fast&)

#endif

 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_bv_base&)
 PK_DEFN_ASN_OP_T( =, const sc_dt::sc_lv_base&)
 PK_DEFN_ASN_OP_T( =, const char*)
 PK_DEFN_ASN_OP_T( =, unsigned long)
 PK_DEFN_ASN_OP_T( =, long)
 PK_DEFN_ASN_OP_T( =, unsigned int)
 PK_DEFN_ASN_OP_T( =, int)
 PK_DEFN_ASN_OP_T( =, int64)
 PK_DEFN_ASN_OP_T( =, double)
  
 
 // other writing operators

 #ifdef PK_ENABLE_OPMODELS 

 PK_DEFN_ASN_OPMODEL_T( +=, '+', uint_type)
 PK_DEFN_ASN_OPMODEL_T( -=, '-', uint_type)
 PK_DEFN_ASN_OPMODEL_T( *=, '*', uint_type)
 PK_DEFN_ASN_OPMODEL_T( /=, '/', uint_type)

 #else

 PK_DEFN_ASN_OP_T( +=, uint_type)
 PK_DEFN_ASN_OP_T( -=, uint_type)
 PK_DEFN_ASN_OP_T( *=, uint_type)
 PK_DEFN_ASN_OP_T( /=, uint_type)

#endif

 PK_DEFN_ASN_OP_T( %=, uint_type)
 PK_DEFN_ASN_OP_T( &=, uint_type)
 PK_DEFN_ASN_OP_T( |=, uint_type)
 PK_DEFN_ASN_OP_T( ^=, uint_type)
 PK_DEFN_ASN_OP_T( <<=, uint_type)
 PK_DEFN_ASN_OP_T( >>=, uint_type)



 #ifdef PK_ENABLE_OPMODELS

 PK_OPMODEL_OP6(sc_uint)

 #else

 sc_uint_aug<n>& operator ++ () 
 {
  pk_base::compute_data(); 
  sc_type::operator ++ ();
  return *this; 
 }

 sc_uint<n> operator ++ (int) 
 {
  pk_base::compute_data(); 
  return sc_type::operator ++ (0);
 }

 sc_uint_aug<n>& operator -- () 
 {
  pk_base::compute_data(); 
  sc_type::operator -- ();
  return *this; 
 }

 sc_uint<n> operator -- (int) 
 {
  pk_base::compute_data(); 
  return sc_type::operator -- (0);
 }
 
 #endif

 sc_uint_bitref   operator [] ( int i )
 {
  pk_base::compute_data();
  return sc_type::operator[](i);
 };


 sc_uint_subref range(int left,int right)
 {
  pk_base::compute_data();
  return sc_type::range(left,right);
 };

 #undef PK_DEFN_ASN_OPMODEL_T  
 #undef PK_DEFN_ASN_OP_T 
 
};

// ----------------------------------------------------------------------------
//  CLASS : sc_signed_aug
//
//  class for the internal augmented signals related to the SystemC type sc_signed
// ----------------------------------------------------------------------------

using sc_dt::sc_signed_bitref;
using sc_dt::sc_signed_bitref_r;
using sc_dt::sc_signed_subref;
using sc_dt::sc_signed_subref_r;
using sc_dt::sc_unsigned_subref_r;


class sc_signed_aug: public sc_dt::sc_signed, 
	                 public pk_core::pk_internal_sgn< sc_dt::sc_signed >
{

 public:

 typedef sc_signed sc_type;
 typedef sc_signed_aug& this_type_r;
 typedef pk_internal_sgn< sc_signed > pk_base;

 // constructors

 explicit sc_signed_aug( int nb = sc_dt::sc_length_param().len() ): 
                sc_signed(nb), pk_internal_sgn<sc_signed>(this)   
 { }

 sc_signed_aug(const sc_signed& v ): sc_signed(v), pk_internal_sgn<sc_signed>(this)     
 { }

 sc_signed_aug(const sc_signed_aug& v ): sc_signed(static_cast<const sc_signed&>(v) ), 
	                                     pk_internal_sgn<sc_signed>(this)     
 { }

 sc_signed_aug(const sc_dt::sc_unsigned& v ): sc_signed(v), pk_internal_sgn<sc_signed>(this)     
 { }


 explicit sc_signed_aug(const sc_dt::sc_bv_base& v ): 
              sc_signed(v), pk_internal_sgn<sc_signed>(this)     
 { }

 explicit sc_signed_aug(const sc_dt::sc_lv_base& v ):
               sc_signed(v), pk_internal_sgn<sc_signed>(this)     
 { }

 explicit sc_signed_aug(const sc_int_subref_r& v ): 
               sc_signed(v), pk_internal_sgn<sc_signed>(this)     
 { }

 explicit sc_signed_aug(const sc_uint_subref_r& v ): 
               sc_signed(v), pk_internal_sgn<sc_signed>(this)     
 { }

 explicit sc_signed_aug(const sc_signed_subref_r& v ): 
               sc_signed(v), pk_internal_sgn<sc_signed>(this)     
 { }

 explicit sc_signed_aug(const sc_unsigned_subref_r& v ): 
               sc_signed(v), pk_internal_sgn<sc_signed>(this)    
 { }

 #ifdef PK_ENABLE_OPMODELS    

 
 #define PK_DEFN_ASN_OPMODEL_T(op,tp, op_sym)                 \
    sc_signed_aug& operator op ( tp val )                     \
    {                                                         \
	 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task( op_sym );          \
	 pk_base::compute_data();                                 \
     sc_type::operator op (val);                              \
     return *this;                                            \
    }                                                            

 #define PK_DEFN_ASN_OPMODEL(op, op_sym)                                               \
 PK_DEFN_ASN_OPMODEL_T(op,const sc_dt::sc_signed&, op_sym )                                           \
 PK_DEFN_ASN_OPMODEL_T(op,const sc_dt::sc_unsigned&, op_sym )                                         \
 PK_DEFN_ASN_OPMODEL_T(op,int64, op_sym )                                                      \
 PK_DEFN_ASN_OPMODEL_T(op,uint64, op_sym )                                                     \
 PK_DEFN_ASN_OPMODEL_T(op,long, op_sym )                                                       \
 PK_DEFN_ASN_OPMODEL_T(op,unsigned long, op_sym )                                              \
 PK_DEFN_ASN_OPMODEL_T(op,int, op_sym )                                                        \
 PK_DEFN_ASN_OPMODEL_T(op,unsigned int, op_sym )                                               \
 PK_DEFN_ASN_OPMODEL_T(op,const sc_dt::sc_int_base&, op_sym )                                         \
 PK_DEFN_ASN_OPMODEL_T(op,const sc_dt::sc_uint_base&, op_sym )                                        \
 PK_OPMODEL_OP7(op, sc_signed_aug, op_sym)
 										  											  
	

#endif


 #define PK_DEFN_ASN_OP_T(op,tp)                              \
    sc_signed_aug& operator op ( tp val )                     \
    {                                                         \
	 pk_base::compute_data();                                 \
     sc_type::operator op (val);                              \
     return *this;                                            \
    }                                                            

 #define PK_DEFN_ASN_OP(op)                                                       \
 PK_DEFN_ASN_OP_T(op,const sc_dt::sc_signed& )                                    \
 PK_DEFN_ASN_OP_T(op,const sc_dt::sc_unsigned& )                                  \
 PK_DEFN_ASN_OP_T(op,int64 )                                                      \
 PK_DEFN_ASN_OP_T(op,uint64 )                                                     \
 PK_DEFN_ASN_OP_T(op,long )                                                       \
 PK_DEFN_ASN_OP_T(op,unsigned long )                                              \
 PK_DEFN_ASN_OP_T(op,int )                                                        \
 PK_DEFN_ASN_OP_T(op,unsigned int )                                               \
 PK_DEFN_ASN_OP_T(op,const sc_dt::sc_int_base& )                                  \
 PK_DEFN_ASN_OP_T(op,const sc_dt::sc_uint_base& ) 


 // assignment operators

 PK_DEFN_ASN_OP( = )
 PK_DEFN_ASN_OP_T( = , const char* )
 PK_DEFN_ASN_OP_T( = , double )
 PK_DEFN_ASN_OP_T( = , const sc_dt::sc_bv_base& )
 PK_DEFN_ASN_OP_T( = , const sc_dt::sc_lv_base& )
 PK_DEFN_ASN_OP_T( = , const sc_dt::sc_signed_subref_r& )
 PK_DEFN_ASN_OP_T( = , const sc_dt::sc_unsigned_subref_r& )


 sc_signed_aug& operator = ( const sc_signed_aug& val)                    
 {                                                         
  return this->operator = (static_cast< const sc_signed& >(val));                                            
 } 

 #ifdef SC_INCLUDE_FX
   PK_DEFN_ASN_OP_T( = , const sc_fxval& )
   PK_DEFN_ASN_OP_T( = , const sc_fxval_fast& )
   PK_DEFN_ASN_OP_T( = , const sc_fxnum& )
   PK_DEFN_ASN_OP_T( = , const sc_fxnum_fast& )
 #endif

// destructor  

 virtual ~sc_signed_aug() 
	{ }


 virtual void concat_set(int64 src, int low_i)
 {
  compute_data();
  sc_signed::concat_set(src, low_i);
 };

 virtual void concat_set(const sc_signed& src, int low_i)
 {
  compute_data();
  sc_signed::concat_set(src, low_i);
 };

 virtual void concat_set(const sc_dt::sc_unsigned& src, int low_i)
 {
  compute_data();
  sc_signed::concat_set(src, low_i);
 };

 virtual void concat_set(uint64 src, int low_i)
 {
  compute_data();
  sc_signed::concat_set(src, low_i);
 };

 #ifdef PK_ENABLE_OPMODELS

 PK_OPMODEL_OP5(sc_signed)


 #else

 sc_signed_aug& operator ++ ( )                    
 { 
  compute_data();
  sc_signed::operator ++ ( ); 
  return *this;                                            
 }  

 const sc_signed operator ++ ( int )                    
 {
  compute_data();                                            
  return sc_signed::operator ++ ( 0 );                                                                        
 }  

 sc_signed_aug& operator -- ( )                    
 {
  compute_data();
  sc_signed::operator -- ( );     
  return *this;                                            
 }  

 const sc_signed operator -- ( int )                    
 {                                                         
  compute_data();                                            
  return sc_signed::operator -- ( 0 );                                                                       
 } 

 #endif

 

 sc_signed_bitref& operator [] ( int i )                     
 {                                                         
  compute_data();                                            
  return sc_signed::operator [] (i);                                                                      
 }  

 sc_signed_bitref& bit ( int i )                     
 {                                                         
  compute_data();                                            
  return sc_signed::bit(i);                                                                      
 } 

 sc_signed_subref& operator () ( int i,int j )                     
 {                                                         
  compute_data();                                            
  return sc_signed::operator () (i,j);                                                                      
 }  
 
 void scan ( ::std::istream& is = ::std::cin )                     
 {                                                         
  compute_data();                                            
  sc_signed::scan(is);
  return;
 } 

 void set ( int i )                     
 {                                                         
  compute_data();                                            
  sc_signed::set(i);                                                                      
 } 

 void clear ( int i )                     
 {                                                         
  compute_data();                                            
  sc_signed::clear(i);                                                                      
 }

 void set ( int i, bool v )                     
 {                                                         
  compute_data();                                            
  sc_signed::set(i,v);                                                                      
 } 
 
 void invert ( int i )                     
 {                                                         
  compute_data();                                            
  sc_signed::invert(i);                                                                      
 } 

 void reverse ()                     
 {                                                         
  compute_data();                                            
  sc_signed::reverse();                                                                      
 } 

 void set_packed_rep (                          
                       #ifdef PK_SYSC_22
	                     sc_dt::sc_digit *buf
                       #else
	                      unsigned long *buf 
                       #endif  
					  )                     
 {                                                         
  compute_data();                                            
  sc_signed::set_packed_rep(buf);                                                                      
 } 


 // other assignment operators

 #ifdef PK_ENABLE_OPMODELS

 PK_DEFN_ASN_OPMODEL( +=, '+' )
 PK_DEFN_ASN_OPMODEL( -=, '-' )
 PK_DEFN_ASN_OPMODEL( *=, '*' )
 PK_DEFN_ASN_OPMODEL( /=, '/' )

#else

 PK_DEFN_ASN_OP( += )
 PK_DEFN_ASN_OP( -= )
 PK_DEFN_ASN_OP( *= )
 PK_DEFN_ASN_OP( /= )

#endif


 PK_DEFN_ASN_OP( %= )

 PK_DEFN_ASN_OP( &= )
 PK_DEFN_ASN_OP( |= )
 PK_DEFN_ASN_OP( ^= )
 PK_DEFN_ASN_OP( <<= )
 PK_DEFN_ASN_OP( >>= )
 
 
 #undef  PK_DEFN_ASN_OPMODEL_T
 #undef  PK_DEFN_ASN_OPMODEL

 #undef  PK_DEFN_ASN_OP_T
 #undef  PK_DEFN_ASN_OP

 };




// ----------------------------------------------------------------------------
//  CLASS : sc_unsigned_aug
//
//  class for the internal augmented signals related to the SystemC type sc_unsigned
// ----------------------------------------------------------------------------


using sc_dt::sc_unsigned_bitref;
using sc_dt::sc_unsigned_bitref_r;
using sc_dt::sc_unsigned_subref;
using sc_dt::sc_unsigned_subref_r;


class sc_unsigned_aug: public sc_dt::sc_unsigned, 
	                   public pk_core::pk_internal_sgn< sc_dt::sc_unsigned > 
{
 
 public:

 typedef sc_unsigned sc_type;
 typedef sc_unsigned_aug& this_type_r;
 typedef pk_internal_sgn< sc_unsigned > pk_base;

 // constructors

 explicit sc_unsigned_aug( int nb = sc_dt::sc_length_param().len() ): 
                sc_unsigned(nb), pk_internal_sgn<sc_unsigned>(this)   
 { }

 sc_unsigned_aug(const sc_unsigned& v ): sc_unsigned(v), pk_internal_sgn<sc_unsigned>(this)   
 { }

 sc_unsigned_aug(const sc_unsigned_aug& v ): sc_unsigned(static_cast<const sc_unsigned&>(v) ), 
	                                     pk_internal_sgn<sc_unsigned>(this)  
 { }


 sc_unsigned_aug(const sc_dt::sc_signed& v ): sc_unsigned(v), pk_internal_sgn<sc_unsigned>(this)   
 { }


 explicit sc_unsigned_aug(const sc_dt::sc_bv_base& v ): 
              sc_unsigned(v), pk_internal_sgn<sc_unsigned>(this)   
 { }

 explicit sc_unsigned_aug(const sc_dt::sc_lv_base& v ):
               sc_unsigned(v), pk_internal_sgn<sc_unsigned>(this)   
 { }

 explicit sc_unsigned_aug(const sc_int_subref_r& v ): 
               sc_unsigned(v), pk_internal_sgn<sc_unsigned>(this)   
 { }

 explicit sc_unsigned_aug(const sc_uint_subref_r& v ): 
               sc_unsigned(v), pk_internal_sgn<sc_unsigned>(this)   
 { }

 explicit sc_unsigned_aug(const sc_signed_subref_r& v ): 
               sc_unsigned(v), pk_internal_sgn<sc_unsigned>(this)   
 { }

 explicit sc_unsigned_aug(const sc_unsigned_subref_r& v ): 
               sc_unsigned(v), pk_internal_sgn<sc_unsigned>(this)   
 { }


 // destructor  

 virtual ~sc_unsigned_aug() 
 { }

 #ifdef PK_ENABLE_OPMODELS    

 
 #define PK_DEFN_ASN_OPMODEL_T(op,tp, op_sym)                 \
    sc_unsigned_aug& operator op ( tp val )                   \
    {                                                         \
	 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task( op_sym );          \
     pk_base::compute_data();                                          \
     sc_type::operator op (val);                          \
     return *this;                                            \
    }                                                            

 #define PK_DEFN_ASN_OPMODEL(op, op_sym)                                               \
 PK_DEFN_ASN_OPMODEL_T(op,const sc_dt::sc_signed&, op_sym )                                           \
 PK_DEFN_ASN_OPMODEL_T(op,const sc_dt::sc_unsigned&, op_sym )                                         \
 PK_DEFN_ASN_OPMODEL_T(op,int64, op_sym )                                                      \
 PK_DEFN_ASN_OPMODEL_T(op,uint64, op_sym )                                                     \
 PK_DEFN_ASN_OPMODEL_T(op,long, op_sym )                                                       \
 PK_DEFN_ASN_OPMODEL_T(op,unsigned long, op_sym )                                              \
 PK_DEFN_ASN_OPMODEL_T(op,int, op_sym )                                                        \
 PK_DEFN_ASN_OPMODEL_T(op,unsigned int, op_sym )                                               \
 PK_DEFN_ASN_OPMODEL_T(op,const sc_dt::sc_int_base&, op_sym )                                         \
 PK_DEFN_ASN_OPMODEL_T(op,const sc_dt::sc_uint_base&, op_sym )                                        \
 PK_OPMODEL_OP7(op, sc_unsigned_aug, op_sym)												  											  
												  
#endif

 #define PK_DEFN_ASN_OP_T(op,tp)                              \
    sc_unsigned_aug& operator op ( tp val )                   \
    {                                                         \
     pk_base::compute_data();                                 \
     sc_type::operator op (val);                              \
     return *this;                                            \
    }                                                            

  #define PK_DEFN_ASN_OP(op)                                                      \
 PK_DEFN_ASN_OP_T(op,const sc_dt::sc_signed& )                                    \
 PK_DEFN_ASN_OP_T(op,const sc_dt::sc_unsigned& )                                  \
 PK_DEFN_ASN_OP_T(op,int64 )                                                      \
 PK_DEFN_ASN_OP_T(op,uint64 )                                                     \
 PK_DEFN_ASN_OP_T(op,long )                                                       \
 PK_DEFN_ASN_OP_T(op,unsigned long )                                              \
 PK_DEFN_ASN_OP_T(op,int )                                                        \
 PK_DEFN_ASN_OP_T(op,unsigned int )                                               \
 PK_DEFN_ASN_OP_T(op,const sc_dt::sc_int_base& )                                  \
 PK_DEFN_ASN_OP_T(op,const sc_dt::sc_uint_base& ) 

 // assignment operators

 PK_DEFN_ASN_OP_T( = ,const sc_dt::sc_signed& )  
 PK_DEFN_ASN_OP_T( = ,const sc_signed_subref_r& ) 
 PK_DEFN_ASN_OP_T( = ,const sc_dt::sc_unsigned& )  
 PK_DEFN_ASN_OP_T( = ,const sc_unsigned_subref_r& ) 
 PK_DEFN_ASN_OP_T( = , const char* )
 PK_DEFN_ASN_OP_T( = ,int64 )                                                      
 PK_DEFN_ASN_OP_T( = ,uint64 )                                                     
 PK_DEFN_ASN_OP_T( = ,long )                                                       
 PK_DEFN_ASN_OP_T( = ,unsigned long )                                              
 PK_DEFN_ASN_OP_T( = ,int )                                                        
 PK_DEFN_ASN_OP_T( = ,unsigned int )  
 PK_DEFN_ASN_OP_T( = , double )
 PK_DEFN_ASN_OP_T( = ,const sc_dt::sc_int_base& )                                         
 PK_DEFN_ASN_OP_T( = ,const sc_dt::sc_uint_base& ) 
 PK_DEFN_ASN_OP_T( = , const sc_dt::sc_bv_base& )
 PK_DEFN_ASN_OP_T( = , const sc_dt::sc_lv_base& )


 sc_unsigned_aug& operator = ( const sc_unsigned_aug& val)                    
 { return this->operator = (static_cast< const sc_unsigned& >(val)); } 
 

 #ifdef SC_INCLUDE_FX
   PK_DEFN_ASN_OP_T( = , const sc_fxval& )
   PK_DEFN_ASN_OP_T( = , const sc_fxval_fast& )
   PK_DEFN_ASN_OP_T( = , const sc_fxnum& )
   PK_DEFN_ASN_OP_T( = , const sc_fxnum_fast& )
 #endif

 

 virtual void concat_set(int64 src, int low_i)
 {
  compute_data();
  sc_unsigned::concat_set(src, low_i);
 };

 virtual void concat_set(const sc_dt::sc_signed& src, int low_i)
 {
  compute_data();
  sc_unsigned::concat_set(src, low_i);
 };

 virtual void concat_set(const sc_unsigned& src, int low_i)
 {
  compute_data();
  sc_unsigned::concat_set(src, low_i);
 };

 virtual void concat_set(uint64 src, int low_i)
 {
  compute_data();
  sc_unsigned::concat_set(src, low_i);
 };


 #ifdef PK_ENABLE_OPMODELS

 PK_OPMODEL_OP5(sc_unsigned)

 #else
 
 sc_unsigned_aug& operator ++ ( )                     
 {                                                         
  compute_data();                                            
  sc_unsigned::operator ++ ( );                            
  return *this;                                            
 }  

 const sc_unsigned operator ++ ( int )                     
 {                                                         
  compute_data();                                            
  return sc_unsigned::operator ++ ( 0 );                                                                       
 }  

 sc_unsigned_aug& operator -- ( )                     
 {                                                         
  compute_data();                                            
  sc_unsigned::operator -- ( );                            
  return *this;                                            
 }  

 const sc_unsigned operator -- ( int )                     
 {                                                         
  compute_data();                                            
  return sc_unsigned::operator -- ( 0 );                                                                       
 }  

 #endif


 sc_unsigned_bitref& operator [] ( int i )                     
 {                                                         
  compute_data();                                            
  return sc_unsigned::operator [] (i);                                                                      
 }  

 sc_unsigned_bitref& bit ( int i )                     
 {                                                         
  compute_data();                                            
  return sc_unsigned::bit(i);                                                                      
 } 

 

 sc_unsigned_subref& range ( int i, int j )                     
 {                                                         
  compute_data();                                            
  return sc_unsigned::range(i,j);                                                                      
 } 
 
 sc_unsigned_subref& operator () ( int i,int j )                     
 {                                                         
  compute_data();                                            
  return sc_unsigned::operator () (i,j);                                                                      
 } 


 void scan ( istream& is=cin )                     
 {                                                         
  compute_data();                                            
  sc_unsigned::scan(is);                                                                      
 } 

 void set ( int i )                     
 {                                                         
  compute_data();                                            
  sc_unsigned::set(i);                                                                      
 } 

 void clear ( int i )                     
 {                                                         
  compute_data();                                            
  sc_unsigned::clear(i);                                                                      
 }

 void set ( int i, bool v )                     
 {                                                         
  compute_data();                                            
  sc_unsigned::set(i,v);                                                                      
 } 
 
 void invert ( int i )                     
 {                                                         
  compute_data();                                            
  sc_unsigned::invert(i);                                                                      
 } 

 void reverse ( int i, bool v )                     
 {                                                         
  compute_data();                                            
  sc_unsigned::reverse();                                                                      
 } 

 void set_packed_rep (                      
                       #ifdef PK_SYSC_22
	                      sc_dt::sc_digit *buf
                       #else
	                      unsigned long *buf 
                       #endif  
					  )                      
 {                                                         
  compute_data();                                            
  sc_unsigned::set_packed_rep(buf);                                                                      
 } 

 // other writing operators

 #ifdef PK_ENABLE_OPMODELS

 PK_DEFN_ASN_OPMODEL( +=, '+' )
 PK_DEFN_ASN_OPMODEL( -=, '-' )
 PK_DEFN_ASN_OPMODEL( *=, '*' )
 PK_DEFN_ASN_OPMODEL( /=, '/' )

 #else

 PK_DEFN_ASN_OP( += )
 PK_DEFN_ASN_OP( -= )
 PK_DEFN_ASN_OP( *= )
 PK_DEFN_ASN_OP( /= )

 #endif

 PK_DEFN_ASN_OP( %= )

 PK_DEFN_ASN_OP( &= )
 PK_DEFN_ASN_OP( |= )
 PK_DEFN_ASN_OP( ^= )
 PK_DEFN_ASN_OP( <<= )
 PK_DEFN_ASN_OP( >>= )


 #undef  PK_DEFN_ASN_OPMODEL_T
 #undef  PK_DEFN_ASN_OPMODEL

 #undef  PK_DEFN_ASN_OP_T
 #undef  PK_DEFN_ASN_OP

 };




// ----------------------------------------------------------------------------
//  CLASS : sc_bigint_aug<W>
//
//  class for the internal augmented signals related to the SystemC type sc_bigint<W>
// ----------------------------------------------------------------------------



#ifdef SC_MAX_NBITS
template< int W = SC_MAX_NBITS >
#else
template< int W >
#endif
class sc_bigint_aug: public sc_signed_aug
{
 public:

 // constructors
 
 sc_bigint_aug(): sc_signed_aug( W )  
 { }

 sc_bigint_aug( const sc_bigint<W>& v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug(const sc_bigint_aug<W>& v ): sc_signed_aug( W )  
 { *this=v; } 
 
 sc_bigint_aug( const sc_signed& v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( const sc_signed_subref& v ):sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( const sc_dt::sc_unsigned& v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( const sc_unsigned_subref& v ): sc_signed_aug( W )  
 { *this=v; }
 
 sc_bigint_aug( const char* v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( int64 v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( uint64 v ):sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( long v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( unsigned long v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( int v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( unsigned int v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( double v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( const sc_dt::sc_bv_base& v ): sc_signed_aug( W )  
 { *this=v; }

 sc_bigint_aug( const sc_dt::sc_lv_base& v ): sc_signed_aug( W )  
 { *this=v; }

 #ifdef SC_INCLUDE_FX

 explicit sc_bigint_aug( const sc_fxval& v ): sc_signed_aug( W )  
 { *this=v; }

 explicit sc_bigint_aug( const sc_fxval_fast& v ): sc_signed_aug( W )  
 { *this=v; }

 explicit sc_bigint_aug( const sc_fxnum& v ): sc_signed_aug( W )  
 { *this=v; }

 explicit sc_bigint_aug( const sc_fxnum_fast& v ): sc_signed_aug( W )  
 { *this=v; }

#endif

#ifndef SC_MAX_NBITS

    // destructor  

    ~sc_bigint_aug()
	{}

#endif




  // assignment operators
   
    sc_bigint_aug<W>& operator = ( const sc_bigint<W>& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

	sc_bigint_aug<W>& operator = ( const sc_bigint_aug<W>& val)                    
    { return this->operator = (static_cast< const sc_bigint<W>& >(val)); } 

    sc_bigint_aug<W>& operator = ( const sc_dt::sc_signed& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = (const sc_signed_subref& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( const sc_dt::sc_unsigned& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( const sc_unsigned_subref& v )
	{ sc_signed_aug::operator = ( v ); return *this; }
    
    sc_bigint_aug<W>& operator = ( const char* v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( int64 v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( uint64 v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( long v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( unsigned long v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( int v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( unsigned int v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( double v )
	{ sc_signed_aug::operator = ( v ); return *this; }


    sc_bigint_aug<W>& operator = ( const sc_dt::sc_bv_base& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( const sc_dt::sc_lv_base& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( const sc_dt::sc_int_base& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( const sc_dt::sc_uint_base& v )
	{ sc_signed_aug::operator = ( v ); return *this; }


#ifdef SC_INCLUDE_FX

    sc_bigint_aug<W>& operator = ( const sc_fxval& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( const sc_fxval_fast& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( const sc_fxnum& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_bigint_aug<W>& operator = ( const sc_fxnum_fast& v )
	{ sc_signed_aug::operator = ( v ); return *this; }

#endif


};





// ----------------------------------------------------------------------------
//  CLASS : sc_biguint_aug<W>
//
//  class for the internal augmented signals related to the SystemC type sc_biguint<W>
// ----------------------------------------------------------------------------
 

#ifdef SC_MAX_NBITS
template< int W = SC_MAX_NBITS >
#else
template< int W >
#endif
class sc_biguint_aug: public sc_unsigned_aug
{
 public:

 //constructors
 
 sc_biguint_aug(): sc_unsigned_aug( W )  
 { }

 sc_biguint_aug( const sc_biguint<W>& v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug(const sc_biguint_aug<W>& v ): sc_unsigned_aug( W )  
 { *this=v; } 
 
 sc_biguint_aug( const sc_unsigned& v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( const sc_unsigned_subref& v ):sc_unsigned_aug( W )  
 { *this=v; }
 
 sc_biguint_aug( const sc_dt::sc_signed& v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( const sc_signed_subref& v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( const char* v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( int64 v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( uint64 v ):sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( long v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( unsigned long v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( int v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( unsigned int v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( double v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( const sc_dt::sc_bv_base& v ): sc_unsigned_aug( W )  
 { *this=v; }

 sc_biguint_aug( const sc_dt::sc_lv_base& v ): sc_unsigned_aug( W )  
 { *this=v; }

 #ifdef SC_INCLUDE_FX

 explicit sc_biguint_aug( const sc_fxval& v ): sc_unsigned_aug( W )  
 { *this=v; }

 explicit sc_biguint_aug( const sc_fxval_fast& v ): sc_unsigned_aug( W )  
 { *this=v; }

 explicit sc_biguint_aug( const sc_fxnum& v ): sc_unsigned_aug( W )  
 { *this=v; }

 explicit sc_biguint_aug( const sc_fxnum_fast& v ): sc_unsigned_aug( W )  
 { *this=v; }

#endif

#ifndef SC_MAX_NBITS

    // destructor 

    ~sc_biguint_aug()
	{}

#endif




  // assignment operators

    sc_biguint_aug<W>& operator = ( const sc_biguint<W>& v )   
	{ sc_unsigned_aug::operator = ( v ); return *this; }

	sc_biguint_aug<W>& operator = ( const sc_biguint_aug<W>& val)                    
    { return this->operator = (static_cast< const sc_biguint<W>& >(val)); } 

    sc_biguint_aug<W>& operator = ( const sc_dt::sc_unsigned& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = (const sc_unsigned_subref& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( const sc_dt::sc_signed& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( const sc_signed_subref& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }
    
    sc_biguint_aug<W>& operator = ( const char* v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( int64 v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( uint64 v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( long v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( unsigned long v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( int v )
	{ sc_signed_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( unsigned int v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( double v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }


    sc_biguint_aug<W>& operator = ( const sc_dt::sc_bv_base& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( const sc_dt::sc_lv_base& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( const sc_dt::sc_int_base& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( const sc_dt::sc_uint_base& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }


#ifdef SC_INCLUDE_FX

    sc_biguint_aug<W>& operator = ( const sc_fxval& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( const sc_fxval_fast& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( const sc_fxnum& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

    sc_biguint_aug<W>& operator = ( const sc_fxnum_fast& v )
	{ sc_unsigned_aug::operator = ( v ); return *this; }

#endif

};

} //pk_dt



 
#endif

