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

#define SC_INCLUDE_FX

#include "systemc"
#include "PKtool/types_aug/pk_compute_comm_fcs.h" 



namespace pk_core    
{

 using sc_dt::sc_fix;


inline const int pk_integer_part_bits( const float& )
{ return PK_FLOAT_INTEGER_BITS;   };


inline const int pk_integer_part_bits( const double& )
{ return PK_DOUBLE_INTEGER_BITS;   };

inline const int pk_integer_part_bits( const sc_fix& val )
{ return val.iwl();   };
 


template<class T> unsigned pk_compute_comm_fx_(const T& curr, const T& old, unsigned* bit_comm)
{                                                                               
  const int bit_size = pk_bit_size<T>::bit_size;                            
  const int i_bit_size = pk_integer_part_bits( curr );                           
  sc_dt::sc_fix c( curr, bit_size, i_bit_size );                                 
  sc_dt::sc_fix o( old, bit_size, i_bit_size );                                  
  sc_dt::sc_fix xor_res(c^o);  
  unsigned sum = 0;
  for(int i=0; i<bit_size; ++i)                                                  
  {                                                                              
   if( xor_res[i] )
   {  ++(bit_comm[i]);   ++sum;   }                                             
  }; 
  return sum;
 }; 


#define PK_COMPCOMM_FX(type)                                            \
template<> unsigned pk_compute_comm_fx_                                 \
         (const type &curr, const type &old, unsigned* bit_comm)        \
{                                                                       \
 const int bit_size = pk_bit_size< type >::bit_size(&curr);             \
 type xor_res(curr^old);                                                \
 unsigned sum = 0;                                                       \
 for(int i=0; i<bit_size; ++i)                                           \
 {                                                                       \
  if( xor_res[i] )                                                       \
  {  ++(bit_comm[i]);   ++sum;   }                                       \
 };                                                                      \
 return sum;   };



PK_COMPCOMM_FX(sc_fix) 
PK_COMPCOMM_FX(sc_ufix)


#undef PK_COMPCOMM_FX


unsigned pk_compute_comm_fx(const float& curr, const float& old, unsigned* bit_comm)
{  return pk_compute_comm_fx_( curr, old, bit_comm );  };

unsigned pk_compute_comm_fx(const double& curr, const double& old, unsigned* bit_comm)
{  return pk_compute_comm_fx_( curr, old, bit_comm );   };

unsigned pk_compute_comm_fx(const sc_fix& curr, const sc_fix& old, unsigned* bit_comm)
{  return pk_compute_comm_fx_( curr, old, bit_comm );   };


unsigned pk_compute_comm_fx(const sc_ufix& curr, const sc_ufix& old, unsigned* bit_comm)
{  return pk_compute_comm_fx_( curr, old, bit_comm );   };


}  //pk_core  
