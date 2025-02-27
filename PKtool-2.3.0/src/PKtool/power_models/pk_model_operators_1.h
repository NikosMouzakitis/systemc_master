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

/************************************************************************

Overloaded operators for operator-based power models (declarations and definitions)

Some operators are defined here, others in the file pk_model_operators_1.cpp

*************************************************************************/



#ifndef PK_MODEL_OPERATORS_H
#define PK_MODEL_OPERATORS_H

#include "PKtool/power_models/pk_opmodel_macros.h"


// ADDition operators:

//  aug_type + aug_type = return type

PK_OPMODEL_OP1a_DECL(+, '+', sc_signed, sc_signed) 
PK_OPMODEL_OP1a_DECL(+, '+', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP1b(+, '+', sc_int, sc_dt::int_type)
PK_OPMODEL_OP1b(+, '+', sc_uint, sc_dt::uint_type)
PK_OPMODEL_OP1b(+, '+', sc_bigint, sc_signed)
PK_OPMODEL_OP1b(+, '+', sc_biguint, sc_unsigned)
PK_OPMODEL_OP1c_DECL( +, '+', int, int)               
PK_OPMODEL_OP1c_DECL( +, '+', short, short)           
PK_OPMODEL_OP1c_DECL( +, '+', long, long)				
PK_OPMODEL_OP1c_DECL( +, '+', unsigned, unsigned)     
PK_OPMODEL_OP1c_DECL( +, '+', float, float)           
PK_OPMODEL_OP1c_DECL( +, '+', double, double) 


//  int_aug + type = return type

PK_OPMODEL_OP1d_DECL(+, '+', int, int, int)
PK_OPMODEL_OP1d_DECL(+, '+', int, short, int)
PK_OPMODEL_OP1d_DECL(+, '+', int, long, long)
PK_OPMODEL_OP1d_DECL(+, '+', int, unsigned, int)
PK_OPMODEL_OP1d_DECL(+, '+', int, float, float)
PK_OPMODEL_OP1d_DECL(+, '+', int, double, double)
PK_OPMODEL_OP1d_DECL(+, '+', int, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(+, '+', int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(+, '+', int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(+, '+', int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(+, '+', int, short, int)
PK_OPMODEL_OP1e1_DECL(+, '+', int, long, long)
PK_OPMODEL_OP1e1_DECL(+, '+', int, unsigned, int)
PK_OPMODEL_OP1e1_DECL(+, '+', int, float, float)
PK_OPMODEL_OP1e1_DECL(+, '+', int, double, double)
PK_OPMODEL_OP1e2_DECL(+, '+', int, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(+, '+', int, sc_unsigned, sc_signed)


//  short_aug + type = return type

PK_OPMODEL_OP1d_DECL(+, '+', short, int, int)
PK_OPMODEL_OP1d_DECL(+, '+', short, short, short)
PK_OPMODEL_OP1d_DECL(+, '+', short, long, long)
PK_OPMODEL_OP1d_DECL(+, '+', short, unsigned, int)
PK_OPMODEL_OP1d_DECL(+, '+', short, float, float)
PK_OPMODEL_OP1d_DECL(+, '+', short, double, double)
PK_OPMODEL_OP1d_DECL(+, '+', short, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(+, '+', short, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(+, '+', short, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(+, '+', short, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(+, '+', short, long, long)
PK_OPMODEL_OP1e1_DECL(+, '+', short, unsigned, int)
PK_OPMODEL_OP1e1_DECL(+, '+', short, float, float)
PK_OPMODEL_OP1e1_DECL(+, '+', short, double, double)
PK_OPMODEL_OP1e2_DECL(+, '+', short, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(+, '+', short, sc_unsigned, sc_signed)


//  long_aug + type = return type

PK_OPMODEL_OP1d_DECL(+, '+', long, int, long)
PK_OPMODEL_OP1d_DECL(+, '+', long, short, long)
PK_OPMODEL_OP1d_DECL(+, '+', long, long, long)
PK_OPMODEL_OP1d_DECL(+, '+', long, unsigned, long)
PK_OPMODEL_OP1d_DECL(+, '+', long, float, float)
PK_OPMODEL_OP1d_DECL(+, '+', long, double, double)
PK_OPMODEL_OP1d_DECL(+, '+', long, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(+, '+', long, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(+, '+', long, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(+, '+', long, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(+, '+', long, unsigned, long)
PK_OPMODEL_OP1e1_DECL(+, '+', long, float, float)
PK_OPMODEL_OP1e1_DECL(+, '+', long, double, double)
PK_OPMODEL_OP1e2_DECL(+, '+', long, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(+, '+', long, sc_unsigned, sc_signed)


//  unsigned_aug + type = return type

PK_OPMODEL_OP1d_DECL(+, '+', unsigned, int, int)
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, short, int)
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, long, long)
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, unsigned, unsigned)
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, float, float)
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, double, double)
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(+, '+', unsigned, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e1_DECL(+, '+', unsigned, float, float)
PK_OPMODEL_OP1e1_DECL(+, '+', unsigned, double, double)
PK_OPMODEL_OP1e2_DECL(+, '+', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(+, '+', unsigned, sc_unsigned, sc_unsigned)


//  float_aug + type = return type

PK_OPMODEL_OP1d_DECL(+, '+', float, int, float)
PK_OPMODEL_OP1d_DECL(+, '+', float, short, float)
PK_OPMODEL_OP1d_DECL(+, '+', float, long, float)
PK_OPMODEL_OP1d_DECL(+, '+', float, unsigned, float)
PK_OPMODEL_OP1d_DECL(+, '+', float, float, float)
PK_OPMODEL_OP1d_DECL(+, '+', float, double, double)
PK_OPMODEL_OP1d_DECL(+, '+', float, sc_int_base&, float)
PK_OPMODEL_OP1d_DECL(+, '+', float, sc_uint_base&, float)

PK_OPMODEL_OP1e1_DECL(+, '+', float, double, double)


//  double_aug + type = return type

PK_OPMODEL_OP1d_DECL(+, '+', double, int, double)
PK_OPMODEL_OP1d_DECL(+, '+', double, short, double)
PK_OPMODEL_OP1d_DECL(+, '+', double, long, double)
PK_OPMODEL_OP1d_DECL(+, '+', double, unsigned, double)
PK_OPMODEL_OP1d_DECL(+, '+', double, float, double)
PK_OPMODEL_OP1d_DECL(+, '+', double, double, double)
PK_OPMODEL_OP1d_DECL(+, '+', double, sc_int_base&, double)
PK_OPMODEL_OP1d_DECL(+, '+', double, sc_uint_base&, double)


//  sc_signed_aug + type = return type

PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, int, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, long, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, unsigned , sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, int64, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_signed, uint64, sc_signed)


//  sc_unsigned_aug + type = return type

PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, unsigned , sc_unsigned)
PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, sc_uint_base&, sc_unsigned)
PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, int64, sc_signed)
PK_OPMODEL_OP1f_DECL(+, '+', sc_unsigned, uint64, sc_unsigned)


//  sc_int_aug<n> + type = return type

PK_OPMODEL_OP1g(+, '+', sc_int, int, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_int, short, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_int, long, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_int, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_int, float, float)
PK_OPMODEL_OP1g(+, '+', sc_int, double, double)
PK_OPMODEL_OP1g(+, '+', sc_int, sc_signed&, sc_signed)
PK_OPMODEL_OP1g(+, '+', sc_int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1g(+, '+', sc_int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e3(+, '+', sc_int, int, sc_dt::int_type)
PK_OPMODEL_OP1e3(+, '+', sc_int, short, sc_dt::int_type)
PK_OPMODEL_OP1e3(+, '+', sc_int, long, sc_dt::int_type)
PK_OPMODEL_OP1e3(+, '+', sc_int, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1e3(+, '+', sc_int, float, float)
PK_OPMODEL_OP1e3(+, '+', sc_int, double, double)
PK_OPMODEL_OP1e4(+, '+', sc_int, sc_uint, sc_dt::int_type)
PK_OPMODEL_OP1e4(+, '+', sc_int, sc_bigint, sc_signed)
PK_OPMODEL_OP1e4(+, '+', sc_int, sc_biguint, sc_signed)


//  sc_uint_aug<n> + type = return type

PK_OPMODEL_OP1g(+, '+', sc_uint, int, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_uint, short, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_uint, long, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_uint, unsigned, sc_dt::uint_type)
PK_OPMODEL_OP1g(+, '+', sc_uint, float, float)
PK_OPMODEL_OP1g(+, '+', sc_uint, double, double)
PK_OPMODEL_OP1g(+, '+', sc_uint, sc_signed&, sc_signed)
PK_OPMODEL_OP1g(+, '+', sc_uint, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1g(+, '+', sc_uint, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1g(+, '+', sc_uint, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e3(+, '+', sc_uint, int, sc_dt::int_type)
PK_OPMODEL_OP1e3(+, '+', sc_uint, short, sc_dt::int_type)
PK_OPMODEL_OP1e3(+, '+', sc_uint, long, sc_dt::int_type)
PK_OPMODEL_OP1e3(+, '+', sc_uint, unsigned, sc_dt::uint_type)
PK_OPMODEL_OP1e3(+, '+', sc_uint, float, float)
PK_OPMODEL_OP1e3(+, '+', sc_uint, double, double)
PK_OPMODEL_OP1e4(+, '+', sc_uint, sc_bigint, sc_signed)
PK_OPMODEL_OP1e4(+, '+', sc_uint, sc_biguint, sc_unsigned)


//  sc_bigint_aug<n> + type = return type

PK_OPMODEL_OP1e4(+, '+', sc_bigint, sc_biguint, sc_signed)




// SUBtraction operators:

//  aug_type - aug_type = return type

PK_OPMODEL_OP1a_DECL(-, '-', sc_signed, sc_signed) 
PK_OPMODEL_OP1a_DECL(-, '-', sc_unsigned, sc_signed)
PK_OPMODEL_OP1b(-, '-', sc_int, sc_dt::int_type)
PK_OPMODEL_OP1b(-, '-', sc_uint, sc_dt::int_type)
PK_OPMODEL_OP1b(-, '-', sc_bigint, sc_signed)
PK_OPMODEL_OP1b(-, '-', sc_biguint, sc_signed)
PK_OPMODEL_OP1c_DECL( -, '-', int, int)               
PK_OPMODEL_OP1c_DECL( -, '-', short, short)           
PK_OPMODEL_OP1c_DECL( -, '-', long, long)				
PK_OPMODEL_OP1c_DECL( -, '-', unsigned, int)     
PK_OPMODEL_OP1c_DECL( -, '-', float, float)           
PK_OPMODEL_OP1c_DECL( -, '-', double, double) 


//  int_aug - type = return type

PK_OPMODEL_OP1d_DECL(-, '-', int, int, int)
PK_OPMODEL_OP1d_DECL(-, '-', int, short, int)
PK_OPMODEL_OP1d_DECL(-, '-', int, long, long)
PK_OPMODEL_OP1d_DECL(-, '-', int, unsigned, int)
PK_OPMODEL_OP1d_DECL(-, '-', int, float, float)
PK_OPMODEL_OP1d_DECL(-, '-', int, double, double)
PK_OPMODEL_OP1d_DECL(-, '-', int, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(-, '-', int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(-, '-', int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(-, '-', int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(-, '-', int, short, int)
PK_OPMODEL_OP1e1_DECL(-, '-', int, long, long)
PK_OPMODEL_OP1e1_DECL(-, '-', int, unsigned, int)
PK_OPMODEL_OP1e1_DECL(-, '-', int, float, float)
PK_OPMODEL_OP1e1_DECL(-, '-', int, double, double)
PK_OPMODEL_OP1e2_DECL(-, '-', int, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(-, '-', int, sc_unsigned, sc_signed)


//  short_aug - type = return type

PK_OPMODEL_OP1d_DECL(-, '-', short, int, int)
PK_OPMODEL_OP1d_DECL(-, '-', short, short, short)
PK_OPMODEL_OP1d_DECL(-, '-', short, long, long)
PK_OPMODEL_OP1d_DECL(-, '-', short, unsigned, int)
PK_OPMODEL_OP1d_DECL(-, '-', short, float, float)
PK_OPMODEL_OP1d_DECL(-, '-', short, double, double)
PK_OPMODEL_OP1d_DECL(-, '-', short, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(-, '-', short, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(-, '-', short, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(-, '-', short, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(-, '-', short, long, long)
PK_OPMODEL_OP1e1_DECL(-, '-', short, unsigned, int)
PK_OPMODEL_OP1e1_DECL(-, '-', short, float, float)
PK_OPMODEL_OP1e1_DECL(-, '-', short, double, double)
PK_OPMODEL_OP1e2_DECL(-, '-', short, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(-, '-', short, sc_unsigned, sc_signed)


//  long_aug - type = return type

PK_OPMODEL_OP1d_DECL(-, '-', long, int, long)
PK_OPMODEL_OP1d_DECL(-, '-', long, short, long)
PK_OPMODEL_OP1d_DECL(-, '-', long, long, long)
PK_OPMODEL_OP1d_DECL(-, '-', long, unsigned, long)
PK_OPMODEL_OP1d_DECL(-, '-', long, float, float)
PK_OPMODEL_OP1d_DECL(-, '-', long, double, double)
PK_OPMODEL_OP1d_DECL(-, '-', long, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(-, '-', long, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(-, '-', long, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(-, '-', long, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(-, '-', long, unsigned, long)
PK_OPMODEL_OP1e1_DECL(-, '-', long, float, float)
PK_OPMODEL_OP1e1_DECL(-, '-', long, double, double)
PK_OPMODEL_OP1e2_DECL(-, '-', long, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(-, '-', long, sc_unsigned, sc_signed)


//  unsigned_aug - type = return type

PK_OPMODEL_OP1d_DECL(-, '-', unsigned, int, int)
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, short, int)
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, long, long)
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, unsigned, int)
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, float, float)
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, double, double)
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(-, '-', unsigned, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(-, '-', unsigned, float, float)
PK_OPMODEL_OP1e1_DECL(-, '-', unsigned, double, double)
PK_OPMODEL_OP1e2_DECL(-, '-', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(-, '-', unsigned, sc_unsigned, sc_signed)


//  float_aug - type = return type

PK_OPMODEL_OP1d_DECL(-, '-', float, int, float)
PK_OPMODEL_OP1d_DECL(-, '-', float, short, float)
PK_OPMODEL_OP1d_DECL(-, '-', float, long, float)
PK_OPMODEL_OP1d_DECL(-, '-', float, unsigned, float)
PK_OPMODEL_OP1d_DECL(-, '-', float, float, float)
PK_OPMODEL_OP1d_DECL(-, '-', float, double, double)
PK_OPMODEL_OP1d_DECL(-, '-', float, sc_int_base&, float)
PK_OPMODEL_OP1d_DECL(-, '-', float, sc_uint_base&, float)

PK_OPMODEL_OP1e1_DECL(-, '-', float, double, double)


//  double_aug - type = return type

PK_OPMODEL_OP1d_DECL(-, '-', double, int, double)
PK_OPMODEL_OP1d_DECL(-, '-', double, short, double)
PK_OPMODEL_OP1d_DECL(-, '-', double, long, double)
PK_OPMODEL_OP1d_DECL(-, '-', double, unsigned, double)
PK_OPMODEL_OP1d_DECL(-, '-', double, float, double)
PK_OPMODEL_OP1d_DECL(-, '-', double, double, double)
PK_OPMODEL_OP1d_DECL(-, '-', double, sc_int_base&, double)
PK_OPMODEL_OP1d_DECL(-, '-', double, sc_uint_base&, double)


//  sc_signed_aug - type = return type

PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, int, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, long, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, unsigned , sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, int64, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_signed, uint64, sc_signed)


//  sc_unsigned_aug - type = return type

PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, unsigned , sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, int64, sc_signed)
PK_OPMODEL_OP1f_DECL(-, '-', sc_unsigned, uint64, sc_unsigned)


//  sc_int_aug<n> - type = return type

PK_OPMODEL_OP1g(-, '-', sc_int, int, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_int, short, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_int, long, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_int, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_int, float, float)
PK_OPMODEL_OP1g(-, '-', sc_int, double, double)
PK_OPMODEL_OP1g(-, '-', sc_int, sc_signed&, sc_signed)
PK_OPMODEL_OP1g(-, '-', sc_int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1g(-, '-', sc_int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e3(-, '-', sc_int, int, sc_dt::int_type)
PK_OPMODEL_OP1e3(-, '-', sc_int, short, sc_dt::int_type)
PK_OPMODEL_OP1e3(-, '-', sc_int, long, sc_dt::int_type)
PK_OPMODEL_OP1e3(-, '-', sc_int, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1e3(-, '-', sc_int, float, float)
PK_OPMODEL_OP1e3(-, '-', sc_int, double, double)
PK_OPMODEL_OP1e4(-, '-', sc_int, sc_uint, sc_dt::int_type)
PK_OPMODEL_OP1e4(-, '-', sc_int, sc_bigint, sc_signed)
PK_OPMODEL_OP1e4(-, '-', sc_int, sc_biguint, sc_signed)


//  sc_uint_aug<n> - type = return type

PK_OPMODEL_OP1g(-, '-', sc_uint, int, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_uint, short, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_uint, long, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_uint, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_uint, float, float)
PK_OPMODEL_OP1g(-, '-', sc_uint, double, double)
PK_OPMODEL_OP1g(-, '-', sc_uint, sc_signed&, sc_signed)
PK_OPMODEL_OP1g(-, '-', sc_uint, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1g(-, '-', sc_uint, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1g(-, '-', sc_uint, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e3(-, '-', sc_uint, int, sc_dt::int_type)
PK_OPMODEL_OP1e3(-, '-', sc_uint, short, sc_dt::int_type)
PK_OPMODEL_OP1e3(-, '-', sc_uint, long, sc_dt::int_type)
PK_OPMODEL_OP1e3(-, '-', sc_uint, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1e3(-, '-', sc_uint, float, float)
PK_OPMODEL_OP1e3(-, '-', sc_uint, double, double)
PK_OPMODEL_OP1e4(-, '-', sc_uint, sc_bigint, sc_signed)
PK_OPMODEL_OP1e4(-, '-', sc_uint, sc_biguint, sc_signed)


//  sc_bigint_aug<n> - type = return type

PK_OPMODEL_OP1e4(-, '-', sc_bigint, sc_biguint, sc_signed)



// MULtiplication operators:


//  aug_type * aug_type = return type

PK_OPMODEL_OP1a_DECL(*, '*', sc_signed, sc_signed) 
PK_OPMODEL_OP1a_DECL(*, '*', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP1b(*, '*', sc_int, sc_dt::int_type)
PK_OPMODEL_OP1b(*, '*', sc_uint, sc_dt::uint_type)
PK_OPMODEL_OP1b(*, '*', sc_bigint, sc_signed)
PK_OPMODEL_OP1b(*, '*', sc_biguint, sc_unsigned)
PK_OPMODEL_OP1c_DECL( *, '*', int, int)               
PK_OPMODEL_OP1c_DECL( *, '*', short, short)           
PK_OPMODEL_OP1c_DECL( *, '*', long, long)				
PK_OPMODEL_OP1c_DECL( *, '*', unsigned, unsigned)     
PK_OPMODEL_OP1c_DECL( *, '*', float, float)           
PK_OPMODEL_OP1c_DECL( *, '*', double, double) 


//  int_aug * type = return type

PK_OPMODEL_OP1d_DECL(*, '*', int, int, int)
PK_OPMODEL_OP1d_DECL(*, '*', int, short, int)
PK_OPMODEL_OP1d_DECL(*, '*', int, long, long)
PK_OPMODEL_OP1d_DECL(*, '*', int, unsigned, int)
PK_OPMODEL_OP1d_DECL(*, '*', int, float, float)
PK_OPMODEL_OP1d_DECL(*, '*', int, double, double)
PK_OPMODEL_OP1d_DECL(*, '*', int, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(*, '*', int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(*, '*', int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(*, '*', int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(*, '*', int, short, int)
PK_OPMODEL_OP1e1_DECL(*, '*', int, long, long)
PK_OPMODEL_OP1e1_DECL(*, '*', int, unsigned, int)
PK_OPMODEL_OP1e1_DECL(*, '*', int, float, float)
PK_OPMODEL_OP1e1_DECL(*, '*', int, double, double)
PK_OPMODEL_OP1e2_DECL(*, '*', int, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(*, '*', int, sc_unsigned, sc_signed)


//  short_aug * type = return type

PK_OPMODEL_OP1d_DECL(*, '*', short, int, int)
PK_OPMODEL_OP1d_DECL(*, '*', short, short, short)
PK_OPMODEL_OP1d_DECL(*, '*', short, long, long)
PK_OPMODEL_OP1d_DECL(*, '*', short, unsigned, int)
PK_OPMODEL_OP1d_DECL(*, '*', short, float, float)
PK_OPMODEL_OP1d_DECL(*, '*', short, double, double)
PK_OPMODEL_OP1d_DECL(*, '*', short, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(*, '*', short, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(*, '*', short, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(*, '*', short, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(*, '*', short, long, long)
PK_OPMODEL_OP1e1_DECL(*, '*', short, unsigned, int)
PK_OPMODEL_OP1e1_DECL(*, '*', short, float, float)
PK_OPMODEL_OP1e1_DECL(*, '*', short, double, double)
PK_OPMODEL_OP1e2_DECL(*, '*', short, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(*, '*', short, sc_unsigned, sc_signed)


//  long_aug * type = return type

PK_OPMODEL_OP1d_DECL(*, '*', long, int, long)
PK_OPMODEL_OP1d_DECL(*, '*', long, short, long)
PK_OPMODEL_OP1d_DECL(*, '*', long, long, long)
PK_OPMODEL_OP1d_DECL(*, '*', long, unsigned, long)
PK_OPMODEL_OP1d_DECL(*, '*', long, float, float)
PK_OPMODEL_OP1d_DECL(*, '*', long, double, double)
PK_OPMODEL_OP1d_DECL(*, '*', long, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(*, '*', long, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(*, '*', long, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(*, '*', long, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(*, '*', long, unsigned, long)
PK_OPMODEL_OP1e1_DECL(*, '*', long, float, float)
PK_OPMODEL_OP1e1_DECL(*, '*', long, double, double)
PK_OPMODEL_OP1e2_DECL(*, '*', long, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(*, '*', long, sc_unsigned, sc_signed)


//  unsigned_aug * type = return type

PK_OPMODEL_OP1d_DECL(*, '*', unsigned, int, int)
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, short, int)
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, long, long)
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, unsigned, unsigned)
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, float, float)
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, double, double)
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(*, '*', unsigned, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e1_DECL(*, '*', unsigned, float, float)
PK_OPMODEL_OP1e1_DECL(*, '*', unsigned, double, double)
PK_OPMODEL_OP1e2_DECL(*, '*', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(*, '*', unsigned, sc_unsigned, sc_unsigned)


//  float_aug * type = return type

PK_OPMODEL_OP1d_DECL(*, '*', float, int, float)
PK_OPMODEL_OP1d_DECL(*, '*', float, short, float)
PK_OPMODEL_OP1d_DECL(*, '*', float, long, float)
PK_OPMODEL_OP1d_DECL(*, '*', float, unsigned, float)
PK_OPMODEL_OP1d_DECL(*, '*', float, float, float)
PK_OPMODEL_OP1d_DECL(*, '*', float, double, double)
PK_OPMODEL_OP1d_DECL(*, '*', float, sc_int_base&, float)
PK_OPMODEL_OP1d_DECL(*, '*', float, sc_uint_base&, float)

PK_OPMODEL_OP1e1_DECL(*, '*', float, double, double)


//  double_aug * type = return type

PK_OPMODEL_OP1d_DECL(*, '*', double, int, double)
PK_OPMODEL_OP1d_DECL(*, '*', double, short, double)
PK_OPMODEL_OP1d_DECL(*, '*', double, long, double)
PK_OPMODEL_OP1d_DECL(*, '*', double, unsigned, double)
PK_OPMODEL_OP1d_DECL(*, '*', double, float, double)
PK_OPMODEL_OP1d_DECL(*, '*', double, double, double)
PK_OPMODEL_OP1d_DECL(*, '*', double, sc_int_base&, double)
PK_OPMODEL_OP1d_DECL(*, '*', double, sc_uint_base&, double)


//  sc_signed_aug * type = return type

PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, int, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, long, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, unsigned , sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, int64, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_signed, uint64, sc_signed)


//  sc_unsigned_aug * type = return type

PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, unsigned , sc_unsigned)
PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, sc_uint_base&, sc_unsigned)
PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, int64, sc_signed)
PK_OPMODEL_OP1f_DECL(*, '*', sc_unsigned, uint64, sc_unsigned)


//  sc_int_aug<n> * type = return type

PK_OPMODEL_OP1g(*, '*', sc_int, int, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_int, short, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_int, long, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_int, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_int, float, float)
PK_OPMODEL_OP1g(*, '*', sc_int, double, double)
PK_OPMODEL_OP1g(*, '*', sc_int, sc_signed&, sc_signed)
PK_OPMODEL_OP1g(*, '*', sc_int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1g(*, '*', sc_int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e3(*, '*', sc_int, int, sc_dt::int_type)
PK_OPMODEL_OP1e3(*, '*', sc_int, short, sc_dt::int_type)
PK_OPMODEL_OP1e3(*, '*', sc_int, long, sc_dt::int_type)
PK_OPMODEL_OP1e3(*, '*', sc_int, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1e3(*, '*', sc_int, float, float)
PK_OPMODEL_OP1e3(*, '*', sc_int, double, double)
PK_OPMODEL_OP1e4(*, '*', sc_int, sc_uint, sc_dt::int_type)
PK_OPMODEL_OP1e4(*, '*', sc_int, sc_bigint, sc_signed)
PK_OPMODEL_OP1e4(*, '*', sc_int, sc_biguint, sc_signed)


//  sc_uint_aug<n> * type = return type

PK_OPMODEL_OP1g(*, '*', sc_uint, int, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_uint, short, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_uint, long, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_uint, unsigned, sc_dt::uint_type)
PK_OPMODEL_OP1g(*, '*', sc_uint, float, float)
PK_OPMODEL_OP1g(*, '*', sc_uint, double, double)
PK_OPMODEL_OP1g(*, '*', sc_uint, sc_signed&, sc_signed)
PK_OPMODEL_OP1g(*, '*', sc_uint, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1g(*, '*', sc_uint, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1g(*, '*', sc_uint, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e3(*, '*', sc_uint, int, sc_dt::int_type)
PK_OPMODEL_OP1e3(*, '*', sc_uint, short, sc_dt::int_type)
PK_OPMODEL_OP1e3(*, '*', sc_uint, long, sc_dt::int_type)
PK_OPMODEL_OP1e3(*, '*', sc_uint, unsigned, sc_dt::uint_type)
PK_OPMODEL_OP1e3(*, '*', sc_uint, float, float)
PK_OPMODEL_OP1e3(*, '*', sc_uint, double, double)
PK_OPMODEL_OP1e4(*, '*', sc_uint, sc_bigint, sc_signed)
PK_OPMODEL_OP1e4(*, '*', sc_uint, sc_biguint, sc_unsigned)


//  sc_bigint_aug<n> * type = return type

PK_OPMODEL_OP1e4(*, '*', sc_bigint, sc_biguint, sc_signed)



// DIVision operators:

//  aug_type / aug_type = return type

PK_OPMODEL_OP1a_DECL(/, '/', sc_signed, sc_signed) 
PK_OPMODEL_OP1a_DECL(/, '/', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP1b(/, '/', sc_int, sc_dt::int_type)
PK_OPMODEL_OP1b(/, '/', sc_uint, sc_dt::uint_type)
PK_OPMODEL_OP1b(/, '/', sc_bigint, sc_signed)
PK_OPMODEL_OP1b(/, '/', sc_biguint, sc_unsigned)
PK_OPMODEL_OP1c_DECL( /, '/', int, int)               
PK_OPMODEL_OP1c_DECL( /, '/', short, short)           
PK_OPMODEL_OP1c_DECL( /, '/', long, long)				
PK_OPMODEL_OP1c_DECL( /, '/', unsigned, unsigned)     
PK_OPMODEL_OP1c_DECL( /, '/', float, float)           
PK_OPMODEL_OP1c_DECL( /, '/', double, double) 


//  int_aug / type = return type

PK_OPMODEL_OP1d_DECL(/, '/', int, int, int)
PK_OPMODEL_OP1d_DECL(/, '/', int, short, int)
PK_OPMODEL_OP1d_DECL(/, '/', int, long, long)
PK_OPMODEL_OP1d_DECL(/, '/', int, unsigned, int)
PK_OPMODEL_OP1d_DECL(/, '/', int, float, float)
PK_OPMODEL_OP1d_DECL(/, '/', int, double, double)
PK_OPMODEL_OP1d_DECL(/, '/', int, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(/, '/', int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(/, '/', int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(/, '/', int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(/, '/', int, short, int)
PK_OPMODEL_OP1e1_DECL(/, '/', int, long, long)
PK_OPMODEL_OP1e1_DECL(/, '/', int, unsigned, int)
PK_OPMODEL_OP1e1_DECL(/, '/', int, float, float)
PK_OPMODEL_OP1e1_DECL(/, '/', int, double, double)
PK_OPMODEL_OP1e2_DECL(/, '/', int, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(/, '/', int, sc_unsigned, sc_signed)


//  short_aug / type = return type

PK_OPMODEL_OP1d_DECL(/, '/', short, int, int)
PK_OPMODEL_OP1d_DECL(/, '/', short, short, short)
PK_OPMODEL_OP1d_DECL(/, '/', short, long, long)
PK_OPMODEL_OP1d_DECL(/, '/', short, unsigned, int)
PK_OPMODEL_OP1d_DECL(/, '/', short, float, float)
PK_OPMODEL_OP1d_DECL(/, '/', short, double, double)
PK_OPMODEL_OP1d_DECL(/, '/', short, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(/, '/', short, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(/, '/', short, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(/, '/', short, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(/, '/', short, long, long)
PK_OPMODEL_OP1e1_DECL(/, '/', short, unsigned, int)
PK_OPMODEL_OP1e1_DECL(/, '/', short, float, float)
PK_OPMODEL_OP1e1_DECL(/, '/', short, double, double)
PK_OPMODEL_OP1e2_DECL(/, '/', short, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(/, '/', short, sc_unsigned, sc_signed)


//  long_aug / type = return type

PK_OPMODEL_OP1d_DECL(/, '/', long, int, long)
PK_OPMODEL_OP1d_DECL(/, '/', long, short, long)
PK_OPMODEL_OP1d_DECL(/, '/', long, long, long)
PK_OPMODEL_OP1d_DECL(/, '/', long, unsigned, long)
PK_OPMODEL_OP1d_DECL(/, '/', long, float, float)
PK_OPMODEL_OP1d_DECL(/, '/', long, double, double)
PK_OPMODEL_OP1d_DECL(/, '/', long, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(/, '/', long, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d_DECL(/, '/', long, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(/, '/', long, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1_DECL(/, '/', long, unsigned, long)
PK_OPMODEL_OP1e1_DECL(/, '/', long, float, float)
PK_OPMODEL_OP1e1_DECL(/, '/', long, double, double)
PK_OPMODEL_OP1e2_DECL(/, '/', long, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(/, '/', long, sc_unsigned, sc_signed)


//  unsigned_aug / type = return type

PK_OPMODEL_OP1d_DECL(/, '/', unsigned, int, int)
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, short, int)
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, long, long)
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, unsigned, unsigned)
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, float, float)
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, double, double)
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d_DECL(/, '/', unsigned, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e1_DECL(/, '/', unsigned, float, float)
PK_OPMODEL_OP1e1_DECL(/, '/', unsigned, double, double)
PK_OPMODEL_OP1e2_DECL(/, '/', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP1e2_DECL(/, '/', unsigned, sc_unsigned, sc_unsigned)


//  float_aug / type = return type

PK_OPMODEL_OP1d_DECL(/, '/', float, int, float)
PK_OPMODEL_OP1d_DECL(/, '/', float, short, float)
PK_OPMODEL_OP1d_DECL(/, '/', float, long, float)
PK_OPMODEL_OP1d_DECL(/, '/', float, unsigned, float)
PK_OPMODEL_OP1d_DECL(/, '/', float, float, float)
PK_OPMODEL_OP1d_DECL(/, '/', float, double, double)
PK_OPMODEL_OP1d_DECL(/, '/', float, sc_int_base&, float)
PK_OPMODEL_OP1d_DECL(/, '/', float, sc_uint_base&, float)

PK_OPMODEL_OP1e1_DECL(/, '/', float, double, double)


//  double_aug / type = return type

PK_OPMODEL_OP1d_DECL(/, '/', double, int, double)
PK_OPMODEL_OP1d_DECL(/, '/', double, short, double)
PK_OPMODEL_OP1d_DECL(/, '/', double, long, double)
PK_OPMODEL_OP1d_DECL(/, '/', double, unsigned, double)
PK_OPMODEL_OP1d_DECL(/, '/', double, float, double)
PK_OPMODEL_OP1d_DECL(/, '/', double, double, double)
PK_OPMODEL_OP1d_DECL(/, '/', double, sc_int_base&, double)
PK_OPMODEL_OP1d_DECL(/, '/', double, sc_uint_base&, double)


//  sc_signed_aug / type = return type

PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, int, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, long, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, unsigned , sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, int64, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_signed, uint64, sc_signed)


//  sc_unsigned_aug / type = return type

PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, unsigned , sc_unsigned)
PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, sc_uint_base&, sc_unsigned)
PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, int64, sc_signed)
PK_OPMODEL_OP1f_DECL(/, '/', sc_unsigned, uint64, sc_unsigned)


//  sc_int_aug<n> / type = return type

PK_OPMODEL_OP1g(/, '/', sc_int, int, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_int, short, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_int, long, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_int, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_int, float, float)
PK_OPMODEL_OP1g(/, '/', sc_int, double, double)
PK_OPMODEL_OP1g(/, '/', sc_int, sc_signed&, sc_signed)
PK_OPMODEL_OP1g(/, '/', sc_int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1g(/, '/', sc_int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e3(/, '/', sc_int, int, sc_dt::int_type)
PK_OPMODEL_OP1e3(/, '/', sc_int, short, sc_dt::int_type)
PK_OPMODEL_OP1e3(/, '/', sc_int, long, sc_dt::int_type)
PK_OPMODEL_OP1e3(/, '/', sc_int, unsigned, sc_dt::int_type)
PK_OPMODEL_OP1e3(/, '/', sc_int, float, float)
PK_OPMODEL_OP1e3(/, '/', sc_int, double, double)
PK_OPMODEL_OP1e4(/, '/', sc_int, sc_uint, sc_dt::int_type)
PK_OPMODEL_OP1e4(/, '/', sc_int, sc_bigint, sc_signed)
PK_OPMODEL_OP1e4(/, '/', sc_int, sc_biguint, sc_signed)


//  sc_uint_aug<n> / type = return type

PK_OPMODEL_OP1g(/, '/', sc_uint, int, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_uint, short, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_uint, long, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_uint, unsigned, sc_dt::uint_type)
PK_OPMODEL_OP1g(/, '/', sc_uint, float, float)
PK_OPMODEL_OP1g(/, '/', sc_uint, double, double)
PK_OPMODEL_OP1g(/, '/', sc_uint, sc_signed&, sc_signed)
PK_OPMODEL_OP1g(/, '/', sc_uint, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1g(/, '/', sc_uint, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1g(/, '/', sc_uint, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e3(/, '/', sc_uint, int, sc_dt::int_type)
PK_OPMODEL_OP1e3(/, '/', sc_uint, short, sc_dt::int_type)
PK_OPMODEL_OP1e3(/, '/', sc_uint, long, sc_dt::int_type)
PK_OPMODEL_OP1e3(/, '/', sc_uint, unsigned, sc_dt::uint_type)
PK_OPMODEL_OP1e3(/, '/', sc_uint, float, float)
PK_OPMODEL_OP1e3(/, '/', sc_uint, double, double)
PK_OPMODEL_OP1e4(/, '/', sc_uint, sc_bigint, sc_signed)
PK_OPMODEL_OP1e4(/, '/', sc_uint, sc_biguint, sc_unsigned)


//  sc_bigint_aug<n> / type = return type

PK_OPMODEL_OP1e4(/, '/', sc_bigint, sc_biguint, sc_signed)




#endif

