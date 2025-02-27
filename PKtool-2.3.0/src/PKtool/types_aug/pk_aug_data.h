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

#ifndef PK_AUG_DATA_H
#define PK_AUG_DATA_H

#include "PKtool/types_aug/pk_augdata_base.h"  
#include "PKtool/types_aug/pk_bit_size.h"  
#include "PKtool/types_aug/pk_compute_comm_fcs.h"

namespace pk_core    
{


// ----------------------------------------------------------------------------
//  FUNCTION : pk_bitarray_conv   
// ----------------------------------------------------------------------------



template<class T> inline void pk_bitarray_conv(const T& value, bool* bit_rep, const int size)
{
 for(int i=0; i<size; ++i)
	 bit_rep[i] = ( value[i] ? true : false); 
}


template<> 
   inline void pk_bitarray_conv(const sc_dt::sc_logic& val, bool* bit_rep, const int size)
{  bit_rep[0] = ( (val.value() == sc_dt::Log_1 ) ? true : false ); }


template<> 
   inline void pk_bitarray_conv(const sc_dt::sc_bv_base& value, bool* bit_rep, const int size)
{ 
 for(int i=0; i<size; ++i)
	 bit_rep[i] = ( value[i].to_bool() ? true : false );  
}

template<> 
   inline void pk_bitarray_conv(const sc_dt::sc_lv_base& value, bool* bit_rep, const int size)
{ 
 for(int i=0; i<size; ++i)
	 bit_rep[i] = ( value[i].to_bool() ? true : false );
}

template<int n> 
   inline void pk_bitarray_conv(const sc_dt::sc_lv<n>& val, bool* bit_rep, const int size)
{ 
 for(int i=0; i<size; ++i)
	 bit_rep[i] = ( (val[i].value() == sc_dt::Log_1 ) ? true : false );
}    

template<int n> 
   inline void pk_bitarray_conv(const sc_dt::sc_bv<n>& value, bool* bit_rep, const int size)
{ 
 for(int i=0; i<size; ++i)
	 bit_rep[i] = ( value[i].to_bool() ? true : false );
}





#define PK_BIT_CONVERT_FC(type)                                             \
template<>                                                                  \
   inline void pk_bitarray_conv(const type &value, bool* bit_rep, const int size)    \
{                                                                           \
 sc_dt::sc_lv_base tmp( size );                                             \
 tmp = value;                                                               \
 for(int i=0; i < size; ++i)                                                \
 bit_rep[i] = ( tmp[i].value() == sc_dt::Log_1 ) ?  true : false ;          \
}

PK_BIT_CONVERT_FC( sc_dt::sc_bit )
PK_BIT_CONVERT_FC( sc_dt::int64 )
PK_BIT_CONVERT_FC( sc_dt::uint64 )
PK_BIT_CONVERT_FC( int )
PK_BIT_CONVERT_FC( unsigned )
PK_BIT_CONVERT_FC( short int )
PK_BIT_CONVERT_FC( long int )


template<> inline void pk_bitarray_conv(const bool& value, bool* bit_rep, const int size)
{ bit_rep[0] = ( value ? true : false ); }


void pk_bitarray_conv_fc(const float& value, bool* bit_rep, const int size);

void pk_bitarray_conv_fc(const double& value, bool* bit_rep, const int size);



template<> inline void pk_bitarray_conv(const float& value, bool* bit_rep, const int size)
{   pk_bitarray_conv_fc(value, bit_rep, size);  }


template<> inline void pk_bitarray_conv(const double& value, bool* bit_rep, const int size)
{  pk_bitarray_conv_fc(value, bit_rep, size); }




// ----------------------------------------------------------------------------
//  CLASS : pk_augdata_T    
// ----------------------------------------------------------------------------


template<class T> class pk_augdata_T : public pk_augdata_base
{

 public:
 
 explicit pk_augdata_T(const T* sgnval_h, int sz = -1 ) : 
   pk_augdata_base(sz), base( static_cast<pk_augdata_base&>(*this) ),
	   sgn_value( const_cast<T&>(*sgnval_h) ), old_sgnval(sgn_value), initialized(false)
 { }; 

 explicit pk_augdata_T(const T* sgnval_h, bool copy_ctor_avail, int sz = -1 ) : 
   pk_augdata_base(sz), base( static_cast<pk_augdata_base&>(*this) ),
   sgn_value( const_cast<T&>(*sgnval_h) ), old_sgnval(sgn_value), initialized( false )
 { }; 



 inline void init_value( const T& value )
 {  
  old_sgnval = sgn_value = value; 
  const int size = base.bit_size;  
  pk_bitarray_conv( value, base.bit_values, size );  
 };


 inline void update_value( const T& value )
 {  
  old_sgnval = sgn_value;
  sgn_value = value; 
 };

 void compute_data( )  
 {
  if(totcomm_on || bitcomm_on)
  {
   total_comm_ += pk_compute_comm<T>::fc( sgn_value, old_sgnval, base.bit_comms); 
  };

  if(bitvals_on) 
  { 
   const int size = base.bit_size;
   pk_bitarray_conv( sgn_value, base.bit_values, size ); 
  }; 

  if(onetms_on) comp_ontimes();  
  old_sgnval = sgn_value;   
 };
 


 double bit_onetime(unsigned pos)  
 { 
  if( (pos < 0) || (pos >= base.bit_size) )
  {
   cout<<"ERROR"<<endl;    // to be completed
   exit(1);
  }
  else comp_ontimes();

  return bit_onetimes[pos]; 
 }

 private:

 

 void comp_ontimes() 
 {
  //temporary implementation
  const int size = base.bit_size;
  if(!initialized)
  {
   curr_time = 0;
   old_bitvals = new bool[size];
   one_startimes = new double[size];
   initialized = true;
  }

  pk_bitarray_conv( sgn_value, base.bit_values, size );
  curr_time = (sc_core::sc_time_stamp()).to_seconds();

  for( int i=0; i<size; ++i )
  {
   if( bit_values[i] ^ old_bitvals[i] )
   {
    if( old_bitvals[i] )bit_onetimes[i] += (curr_time - one_startimes[i]);
	else one_startimes[i] = curr_time;
	old_bitvals[i] = bit_values[i];  
   } 
  };
 };

 void reset_ontimes() //temporary implementation
 { 
  const int size = base.bit_size;

  if(!initialized)
  {
   curr_time = 0;
   old_bitvals = new bool[size];
   one_startimes = new double[size];
   initialized = true;
  }

  for( int i=0; i < size; ++i )
  {
    bit_onetimes[i] = 0;
	old_bitvals[i] = base.bit_values[i];
    if( bit_values[i] ) one_startimes[i] = curr_time;
  } 
 };

 
 pk_augdata_base& base;
 T& sgn_value;
 T old_sgnval;  
 
 double curr_time;
 bool* old_bitvals;
 double* one_startimes;

 bool initialized;
};




// ----------------------------------------------------------------------------
//  CLASS : pk_aug_data  
// ----------------------------------------------------------------------------


template<class T> class pk_aug_data : public pk_augdata_T<T>
{

 enum {size = pk_bit_size<T>::bit_size};   

 public:

 
 explicit pk_aug_data(const T* sgnval_h ) : pk_augdata_T<T>( sgnval_h )
 {
  pk_augdata_base& base = static_cast<pk_augdata_base&>(*this);

  base.bit_size = size;

  base.bit_values = bit_values_;
  base.bit_comms = bit_comms_;
  base.bit_onetimes = bit_onetimes_; 
  
  base.initialize();
 }; 

 
 private:
 
 bool bit_values_[size];
 unsigned bit_comms_[size];
 double bit_onetimes_[size];

};

#undef PK_AUG_DATA_SPEC
#define PK_AUG_DATA_SPEC( type )                                             \
                                                                             \
template<> class pk_aug_data< type > : public pk_augdata_T< type >           \
{                                                                            \
 public:                                                                     \
                                                                             \
 explicit pk_aug_data(const type *sgn_h ):                                   \
      pk_augdata_T< type >( sgn_h, pk_bit_size< type >::bit_size(sgn_h) )    \
 { };                                                                        \
                                                                             \
};
        
PK_AUG_DATA_SPEC( sc_dt::sc_bv_base )
PK_AUG_DATA_SPEC( sc_dt::sc_lv_base )
PK_AUG_DATA_SPEC( sc_dt::sc_int_base )
PK_AUG_DATA_SPEC( sc_dt::sc_uint_base )
PK_AUG_DATA_SPEC( sc_dt::sc_signed )
PK_AUG_DATA_SPEC( sc_dt::sc_unsigned )


#ifdef SC_INCLUDE_FX

#undef PK_AUG_DATA_SPEC
#define PK_AUG_DATA_SPEC( type )                                             \
                                                                             \
template<> class pk_aug_data< type > : public pk_augdata_T< type >           \
{                                                                            \
 public:                                                                     \
                                                                             \
 explicit pk_aug_data(const type *sgn_h ):                                   \
   pk_augdata_T< type >( sgn_h, true, pk_bit_size< type >::bit_size(sgn_h) ) \
 { };                                                                        \
                                                                             \
};


#undef PK_AUG_DATA_SPEC_2
#define PK_AUG_DATA_SPEC_2( type )                                           \
                                                                             \
template<int W, int I, int Q, int O, int N>                                  \
      class pk_aug_data< type <W,I,Q,O,N> > : public pk_augdata_T< type <W,I,Q,O,N> >    \
{                                                                            \
 public:                                                                     \
                                                                             \
 explicit pk_aug_data(const type <W,I,Q,O,N> *sgn_h ):                       \
      pk_augdata_T< type <W,I,Q,O,N> >( sgn_h, true, pk_bit_size< type <W,I,Q,O,N> >::bit_size(sgn_h) )  \
 { };                                                                        \
                                                                             \
};


PK_AUG_DATA_SPEC( sc_dt::sc_fix )
PK_AUG_DATA_SPEC( sc_dt::sc_ufix )
PK_AUG_DATA_SPEC( sc_dt::sc_fix_fast )
PK_AUG_DATA_SPEC( sc_dt::sc_ufix_fast )

PK_AUG_DATA_SPEC_2( sc_dt::sc_fixed )
PK_AUG_DATA_SPEC_2( sc_dt::sc_ufixed )
PK_AUG_DATA_SPEC_2( sc_dt::sc_fixed_fast )
PK_AUG_DATA_SPEC_2( sc_dt::sc_ufixed_fast )

#undef PK_AUG_DATA_SPEC
#undef PK_AUG_DATA_SPEC_2


#endif


}  //pk_core  

#endif
