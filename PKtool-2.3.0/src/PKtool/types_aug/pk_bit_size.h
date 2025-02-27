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


#ifndef PK_BIT_SIZE_H
#define PK_BIT_SIZE_H


#include "PKtool/types_aug/pk_types_syscrefs.h"   
 

namespace pk_core    
{


// ----------------------------------------------------------------------------
//  STRUCT : pk_bit_size  
//  auxiliary class for getting the bit size of SystemC/C++ types
// ----------------------------------------------------------------------------



template<class T> struct pk_bit_size
{ };


#define PK_BIT_SIZE_SPEC(type)                         \
                                                       \
 template<> struct pk_bit_size< type >                 \
 {                                                     \
  static int bit_size( const type *sgn_h )             \
  {   return sgn_h->length();    };                    \
                                                       \
 };

PK_BIT_SIZE_SPEC( sc_dt::sc_bv_base )
PK_BIT_SIZE_SPEC( sc_dt::sc_lv_base )
PK_BIT_SIZE_SPEC( sc_dt::sc_int_base )
PK_BIT_SIZE_SPEC( sc_dt::sc_uint_base )
PK_BIT_SIZE_SPEC( sc_dt::sc_signed )
PK_BIT_SIZE_SPEC( sc_dt::sc_unsigned )

#undef PK_BIT_SIZE_SPEC


#define PK_BIT_SIZE_SPEC( type )                       \
                                                       \
 template< int n > struct pk_bit_size< type >          \
 {                                                     \
                                                       \
  enum { bit_size = n };                               \
                                                       \
 };


PK_BIT_SIZE_SPEC( sc_bv<n> )
PK_BIT_SIZE_SPEC( sc_lv<n> )
PK_BIT_SIZE_SPEC( sc_int<n> )
PK_BIT_SIZE_SPEC( sc_uint<n> )
PK_BIT_SIZE_SPEC( sc_bigint<n> )
PK_BIT_SIZE_SPEC( sc_biguint<n> )

#undef PK_BIT_SIZE_SPEC


#define PK_BIT_SIZE_SPEC(type, bit_sz)       \
                                             \
 template<> struct pk_bit_size< type >       \
 {                                           \
                                             \
  enum { bit_size = bit_sz };                \
                                             \
 };

PK_BIT_SIZE_SPEC( sc_bit , 1 )
PK_BIT_SIZE_SPEC( sc_logic , 1 )
PK_BIT_SIZE_SPEC( int64 , 64 )    
PK_BIT_SIZE_SPEC( uint64 , 64 )   

PK_BIT_SIZE_SPEC( bool , 1 )
PK_BIT_SIZE_SPEC( int , PK_INT_BIT_NUMBER )
PK_BIT_SIZE_SPEC( unsigned , PK_UNSIGNED_BIT_NUMBER )
PK_BIT_SIZE_SPEC( short int , PK_SHORT_BIT_NUMBER )
PK_BIT_SIZE_SPEC( long int , PK_LONG_BIT_NUMBER )
PK_BIT_SIZE_SPEC( unsigned long , PK_ULONG_BIT_NUMBER )
PK_BIT_SIZE_SPEC( unsigned short , PK_USHORT_BIT_NUMBER )
PK_BIT_SIZE_SPEC( float , PK_FLOAT_BIT_NUMBER )
PK_BIT_SIZE_SPEC( double , PK_DOUBLE_BIT_NUMBER )




#undef PK_BIT_SIZE_SPEC


#ifdef SC_INCLUDE_FX

 template<> struct pk_bit_size< sc_dt::sc_fxnum >                 
 {                                                     
  static int bit_size( const sc_dt::sc_fxnum *sgn_h )             
  {   
   const int wl_ = sgn_h->wl(); 
   const int iwl_ = sgn_h->iwl();
   if(iwl_ < 0) return wl_ + (-1)*iwl_ ;
   else if( wl_ < iwl_ ) return iwl_;
   else return wl_ ;  
  };                    
                                                       
 };



#define PK_BIT_SIZE_SPEC(type)                                 \
                                                               \
 template<> struct pk_bit_size< type >                         \
 {                                                             \
                                                               \
  static int bit_size( const type *sgn_h )                     \
  { return pk_bit_size<sc_dt::sc_fxnum>::bit_size(sgn_h); }    \
														       \
 }; 

#define PK_BIT_SIZE_SPEC_2(type)                                             \
	                                                                         \
template<int W, int I, int Q, int O, int N>                                  \
	             struct pk_bit_size< type <W,I,Q,O,N> >                      \
{                                                                            \
                                                                             \
  static int bit_size( const type <W,I,Q,O,N>  *sgn_h )                      \
  { return pk_bit_size<sc_dt::sc_fxnum>::bit_size(sgn_h); }                  \
														                     \
 }; 


PK_BIT_SIZE_SPEC( sc_dt::sc_fix )
PK_BIT_SIZE_SPEC( sc_dt::sc_ufix )                                                                         
PK_BIT_SIZE_SPEC_2( sc_dt::sc_fixed )
PK_BIT_SIZE_SPEC_2( sc_dt::sc_ufixed )


#undef PK_BIT_SIZE_SPEC
#undef PK_BIT_SIZE_SPEC_2


 template<> struct pk_bit_size< sc_dt::sc_fxnum_fast >                 
 {                                                     
  static int bit_size( const sc_dt::sc_fxnum_fast *sgn_h )             
  {   
   const int wl_ = sgn_h->wl(); 
   const int iwl_ = sgn_h->iwl();
   if(iwl_ < 0) return wl_ + (-1)*iwl_ ;
   else if( wl_ < iwl_ ) return iwl_;
   else return wl_ ;  
  };                    
                                                       
 };



#define PK_BIT_SIZE_SPEC(type)                                      \
                                                                    \
 template<> struct pk_bit_size< type >                              \
 {                                                                  \
                                                                    \
  static int bit_size( const type *sgn_h )                          \
  { return pk_bit_size<sc_dt::sc_fxnum_fast>::bit_size(sgn_h); }    \
														            \
 }; 

#define PK_BIT_SIZE_SPEC_2(type)                                             \
	                                                                         \
template<int W, int I, int Q, int O, int N>                                  \
	             struct pk_bit_size< type <W,I,Q,O,N> >                      \
{                                                                            \
                                                                             \
  static int bit_size( const type <W,I,Q,O,N>  *sgn_h )                      \
  { return pk_bit_size<sc_dt::sc_fxnum_fast>::bit_size(sgn_h); }             \
														                     \
 }; 


PK_BIT_SIZE_SPEC( sc_dt::sc_fix_fast )
PK_BIT_SIZE_SPEC( sc_dt::sc_ufix_fast )                                                                         
PK_BIT_SIZE_SPEC_2( sc_dt::sc_fixed_fast )
PK_BIT_SIZE_SPEC_2( sc_dt::sc_ufixed_fast )


#undef PK_BIT_SIZE_SPEC
#undef PK_BIT_SIZE_SPEC_2

#endif


}  //pk_core  


#endif

