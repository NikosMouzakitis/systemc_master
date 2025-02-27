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

#ifndef CPPTYPES_AUG_H
#define CPPTYPES_AUG_H

#include "PKtool/types_aug/pk_aug_signals.h"

#ifdef PK_ENABLE_OPMODELS 

#include "PKtool/power_models/pk_opmodel_macros.h"

#endif






namespace pk_dt
{

// ----------------------------------------------------------------------------
//  CLASS : pk_wrapper_T<T>
//
//  template class wrapping a variable of type T, assumes the existence of a
//  default constructor or a one-argument costructor;
// ----------------------------------------------------------------------------

template<class T> class pk_wrapper_T
{
 protected:

 T value_;

 pk_wrapper_T(): value_()
 {};

 template<class C> pk_wrapper_T(const C& val): value_(val)
 {}
};


// ----------------------------------------------------------------------------
//  CLASS : cpptype_aug<T>
//
//  template class for the internal augmented signals related to the C++ native types
// ----------------------------------------------------------------------------



template <typename T> class cpptype_aug
          : private pk_wrapper_T<T>, public pk_core::pk_internal_sgn<T>
{
 
 
 public:
 
 typedef cpptype_aug<T>& this_type_r;
 typedef pk_wrapper_T<T> cpp_type;
 typedef pk_core::pk_internal_sgn<T> pk_base;

 
 // constructors

 explicit cpptype_aug(): pk_base(&this->value_)   
 {};  

 
 template<typename C> explicit cpptype_aug(const C& init_val)
         : pk_wrapper_T<T>(init_val), pk_base(&this->value_)  
 {}  

 
 explicit cpptype_aug(const cpptype_aug<T>& init_val)
 : pk_wrapper_T<T>( static_cast< const pk_wrapper_T<T>& >(init_val) ), 
   pk_base(&pk_wrapper_T<T>::value_)
 {};   



#define PK_CPPTYPE_OP(op, type)                                            \
    cpptype_aug<T>& operator op (const type & val)                          \
	{                                                                       \
	 cpp_type::value_ op val;                                               \
	 pk_base::compute_data();                                               \
	 return *this;                                                          \
	}; 

#define PK_CPPTYPE_OPS(op)                                                  \
	  PK_CPPTYPE_OP (op, bool)                                              \
           PK_CPPTYPE_OP (op, char)                                       \
	  PK_CPPTYPE_OP (op, int)                                               \
      PK_CPPTYPE_OP (op, float)	                                         \
	  PK_CPPTYPE_OP (op, double)                                            \
	  PK_CPPTYPE_OP (op, unsigned)                                          \
      PK_CPPTYPE_OP (op, short)                                             \
      PK_CPPTYPE_OP (op,long)                                               \
      PK_CPPTYPE_OP (op,unsigned short)                                     \
      PK_CPPTYPE_OP (op,unsigned long)
  
 


 #ifdef PK_ENABLE_OPMODELS

 #define PK_CPPTYPE_OPMODEL_OP(op, op_sym, tp)                          \
    cpptype_aug<T>& operator op ( tp val )                              \
    {                                                                   \
	 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task( op_sym );  \
     cpp_type::value_ op val;                                           \
     pk_base::compute_data();                                           \
     return *this;                                                      \
    }                                                                   \
	PK_OPMODEL_OP7a(op, op_sym, tp)



   
 #define PK_CPPTYPE_OPMODEL_OPS(op, op_sym)                       \
	  PK_CPPTYPE_OPMODEL_OP (op, op_sym, bool)                    \
                                                                 \
	  PK_CPPTYPE_OPMODEL_OP (op, op_sym, int)                     \
      PK_CPPTYPE_OPMODEL_OP (op, op_sym, float)	                  \
	  PK_CPPTYPE_OPMODEL_OP (op, op_sym, double)                  \
	  PK_CPPTYPE_OPMODEL_OP (op, op_sym, unsigned)                \
      PK_CPPTYPE_OPMODEL_OP (op, op_sym, short)                   \
      PK_CPPTYPE_OPMODEL_OP (op, op_sym, long)                    \
      PK_CPPTYPE_OPMODEL_OP (op, op_sym, unsigned short)          \
      PK_CPPTYPE_OPMODEL_OP (op, op_sym, unsigned long)

 #endif
 
 
 // assignment operators

 cpptype_aug<T>& operator =(const cpptype_aug<T>& val)
 {
  cpp_type::value_ = val.value_; 
  pk_base::compute_data();
  return *this;
 };

 template<class C> cpptype_aug<T>& operator =(const C& val)  
 {
  cpp_type::value_= val;   
  pk_base::compute_data();
  return *this;
 }



 #ifdef PK_ENABLE_OPMODELS



  PK_CPPTYPE_OPMODEL_OPS( +=, '+' )
  PK_CPPTYPE_OPMODEL_OPS( -=, '-' )
  PK_CPPTYPE_OPMODEL_OPS( *=, '*' )
  PK_CPPTYPE_OPMODEL_OPS( /=, '/' )

 #else

  PK_CPPTYPE_OPS(+=)
  PK_CPPTYPE_OPS(-=)
  PK_CPPTYPE_OPS(*=)
  PK_CPPTYPE_OPS(/=)

#endif

  PK_CPPTYPE_OPS(%=)
  PK_CPPTYPE_OPS(^=)
  PK_CPPTYPE_OPS(&=)
  PK_CPPTYPE_OPS(|=)
  PK_CPPTYPE_OPS(<<=)
  PK_CPPTYPE_OPS(>>=)

 
 #ifdef PK_ENABLE_OPMODELS

  PK_OPMODEL_OP6a

 #else

 cpptype_aug<T>& operator++()
 {
  ++cpp_type::value_;
  pk_base::compute_data();
  return *this; 
 };

 const T operator++(int)
 {
  T tmp = cpp_type::value_;
  this->operator ++();
  return tmp; 
 };

 cpptype_aug<T>& operator--()
 {
  --cpp_type::value_;
  pk_base::compute_data();
  return *this; 
 };

 const T operator--(int)
 {
  T tmp = cpp_type::value_;
  this->operator --();
  return tmp; 
 };

#endif
 
 
 // implicit conversion to T

 operator T&() 
 {    
  return cpp_type::value_;
 };

 

 operator const T&() const   
 {   
  return cpp_type::value_;
 };


};

}  //pk_dt



using pk_dt::cpptype_aug;

// typedefs for the specializations related to the C++ native types

typedef cpptype_aug<bool> bool_aug;
//typedef cpptype_aug<char> char_aug;
typedef cpptype_aug<int> int_aug;
typedef cpptype_aug<float> float_aug;
typedef cpptype_aug<double> double_aug;
typedef cpptype_aug<signed> signed_aug;
typedef cpptype_aug<unsigned> unsigned_aug;
typedef cpptype_aug<long> long_aug;
typedef cpptype_aug<short> short_aug;






#endif
