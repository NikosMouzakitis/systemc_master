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





#ifndef PK_COMPUTE_COMM_FCS   
#define PK_COMPUTE_COMM_FCS

#define PK_SET_MODEL_LIBRARY 
#include "PKtool/kernel/pk_settings.h"
#undef PK_SET_MODEL_LIBRARY

#include "PKtool/types_aug/pk_bit_size.h"  


namespace pk_core    
{

// ----------------------------------------------------------------------------
//  FUNCTION : pk_compcomm
// ----------------------------------------------------------------------------

inline unsigned pk_compcomm 
   (const sc_dt::sc_lv_base& xor_res, const int& bit_size, unsigned* bit_comm)
{
 unsigned sum = 0;                                                              
 for(int i=0; i<bit_size; ++i)                                                  
 {                                                                              
  if( xor_res[i].value() == sc_dt::Log_1 )                                          
  { ++(bit_comm[i]);     ++sum;      }                                          
 };                                                                             
 return sum;                                                                    
}



// ----------------------------------------------------------------------------
//  CLASS : pk_compute_comm<T>
//
//  template class for the calculation of signal commutations at bit level
// ----------------------------------------------------------------------------


// general template class, empty implementation

template<class T> struct pk_compute_comm
{ };

// class specializations

#undef PK_COMPUTE_COMM_SPEC
#define PK_COMPUTE_COMM_SPEC(type)                                               \
                                                                                 \
template< >  struct pk_compute_comm< type >                                     \
{                                                                                \
 static inline unsigned fc                                                       \
       (const type& curr, const type& old, unsigned* bit_comm)                   \
 {                                                                               \
  const int bit_size = pk_bit_size< type >::bit_size(&curr);                     \
  sc_dt::sc_lv_base val( bit_size );                                             \
  val = curr^old;                                                                \
  return pk_compcomm(val, bit_size, bit_comm);                                   \
 };                                                                              \
};

PK_COMPUTE_COMM_SPEC( sc_dt::sc_bv_base )
PK_COMPUTE_COMM_SPEC( sc_dt::sc_lv_base )
PK_COMPUTE_COMM_SPEC( sc_dt::sc_int_base )
PK_COMPUTE_COMM_SPEC( sc_dt::sc_uint_base )
PK_COMPUTE_COMM_SPEC( sc_dt::sc_signed )
PK_COMPUTE_COMM_SPEC( sc_dt::sc_unsigned )


#undef PK_COMPUTE_COMM_SPEC


#define PK_COMPUTE_COMM_SPEC(type)                                               \
                                                                                 \
template<int n>  struct pk_compute_comm< type >                                 \
{                                                                                \
 static inline unsigned fc                                                       \
       (const type& curr, const type& old, unsigned* bit_comm)                   \
 {                                                                               \
  const int bit_size = pk_bit_size< type >::bit_size;                            \
  sc_dt::sc_lv< bit_size > val(curr^old);                                        \
  return pk_compcomm(val, bit_size, bit_comm);                                   \
 };                                                                              \
};


PK_COMPUTE_COMM_SPEC( sc_bv<n> )
PK_COMPUTE_COMM_SPEC( sc_lv<n> )
PK_COMPUTE_COMM_SPEC( sc_int<n> )
PK_COMPUTE_COMM_SPEC( sc_uint<n> )
PK_COMPUTE_COMM_SPEC( sc_bigint<n> )
PK_COMPUTE_COMM_SPEC( sc_biguint<n> )

#undef PK_COMPUTE_COMM_SPEC


#define PK_COMPUTE_COMM_SPEC(type)                                               \
                                                                                 \
template< >  struct pk_compute_comm< type >                                     \
{                                                                                \
 static inline unsigned fc                                                       \
       (const type& curr, const type& old, unsigned* bit_comm)                   \
 {                                                                               \
  const int bit_size = pk_bit_size< type >::bit_size;                            \
  sc_dt::sc_lv< bit_size > val(curr^old);                                        \
  return pk_compcomm(val, bit_size, bit_comm);                                   \
 };                                                                              \
};


PK_COMPUTE_COMM_SPEC( bool )
PK_COMPUTE_COMM_SPEC( int )
PK_COMPUTE_COMM_SPEC( unsigned )  
PK_COMPUTE_COMM_SPEC( short int )
PK_COMPUTE_COMM_SPEC( long int )


PK_COMPUTE_COMM_SPEC( sc_bit )
PK_COMPUTE_COMM_SPEC( sc_logic )
PK_COMPUTE_COMM_SPEC( int64 )    
PK_COMPUTE_COMM_SPEC( uint64 )   


#undef PK_COMPUTE_COMM_SPEC

//forward declarations

unsigned pk_compute_comm_fx(const float& curr, const float& old, unsigned* bit_comm);
unsigned pk_compute_comm_fx(const double& curr, const double& old, unsigned* bit_comm);


#define PK_COMPUTE_COMM_SPEC(type)                                               \
                                                                                 \
template< >  struct pk_compute_comm< type >                                     \
{                                                                                \
	                                                                             \
 static inline unsigned fc                                                       \
      (const type& curr, const type& old, unsigned* bit_comm)                    \
  {   return pk_compute_comm_fx( curr, old, bit_comm );   }                      \
                                                                                 \
};


#define PK_COMPUTE_COMM_SPEC_2(type)                                             \
                                                                                 \
template<int W, int I, int Q, int O, int N>                                      \
              struct pk_compute_comm< type <W,I,Q,O,N> >                         \
{                                                                                \
	                                                                             \
 static inline unsigned fc                                                       \
      (const type <W,I,Q,O,N> &curr, const type<W,I,Q,O,N> &old, unsigned* bit_comm)                    \
  {   return pk_compute_comm_fx( curr, old, bit_comm );   }                      \
                                                                                 \
};


PK_COMPUTE_COMM_SPEC( float )   
PK_COMPUTE_COMM_SPEC( double )  


#ifdef SC_INCLUDE_FX

unsigned pk_compute_comm_fx
        (const sc_dt::sc_fix& curr, const sc_dt::sc_fix& old, unsigned* bit_comm);

unsigned pk_compute_comm_fx
        (const sc_dt::sc_ufix& curr, const sc_dt::sc_ufix& old, unsigned* bit_comm);

inline unsigned pk_compute_comm_fx
        (const sc_dt::sc_fix_fast& curr, const sc_dt::sc_fix_fast& old, unsigned* bit_comm)
{  return pk_compute_comm_fx( (sc_fix&)curr, (sc_fix&)old, bit_comm );   };

inline unsigned pk_compute_comm_fx
        (const sc_dt::sc_ufix_fast& curr, const sc_dt::sc_ufix_fast& old, unsigned* bit_comm)
{  return pk_compute_comm_fx( (sc_ufix&)curr, (sc_ufix&)old, bit_comm );   };



template<int W, int I, int Q, int O, int N>  
unsigned pk_compute_comm_fx
    (const sc_fixed<W, I, Q, O, N>& curr, const sc_fixed<W, I, Q, O, N>& old, unsigned* bit_comm)
{  return pk_compute_comm_fx( (sc_fix&)curr, (sc_fix&)old, bit_comm );   };

template<int W, int I, int Q, int O, int N>  
unsigned pk_compute_comm_fx
    (const sc_ufixed<W, I, Q, O, N>& curr, const sc_ufixed<W, I, Q, O, N>& old, unsigned* bit_comm)
{  return pk_compute_comm_fx( (sc_ufix&)curr, (sc_ufix&)old, bit_comm );   };

template<int W, int I, int Q, int O, int N>  
unsigned pk_compute_comm_fx
    (const sc_fixed_fast<W, I, Q, O, N>& curr, const sc_fixed_fast<W, I, Q, O, N>& old, unsigned* bit_comm)
{  return pk_compute_comm_fx( (sc_fix&)curr, (sc_fix&)old, bit_comm );   };


template<int W, int I, int Q, int O, int N>  
unsigned pk_compute_comm_fx
    (const sc_ufixed_fast<W, I, Q, O, N>& curr, const sc_ufixed_fast<W, I, Q, O, N>& old, unsigned* bit_comm)
{  return pk_compute_comm_fx( (sc_ufix&)curr, (sc_ufix&)old, bit_comm );   };



PK_COMPUTE_COMM_SPEC( sc_dt::sc_fix )
PK_COMPUTE_COMM_SPEC( sc_dt::sc_ufix )
PK_COMPUTE_COMM_SPEC( sc_dt::sc_fix_fast )
PK_COMPUTE_COMM_SPEC( sc_dt::sc_ufix_fast )

PK_COMPUTE_COMM_SPEC_2( sc_dt::sc_fixed )
PK_COMPUTE_COMM_SPEC_2( sc_dt::sc_ufixed )  
PK_COMPUTE_COMM_SPEC_2( sc_dt::sc_fixed_fast )
PK_COMPUTE_COMM_SPEC_2( sc_dt::sc_ufixed_fast )  


#endif

#undef PK_COMPUTE_COMM_SPEC
#undef PK_COMPUTE_COMM_SPEC_2


}  //pk_core  


#endif
