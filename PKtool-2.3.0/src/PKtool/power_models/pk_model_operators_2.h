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
51 Franklin Street, Fifth Floor, Boston, MA 02110+1301 USA.

************************************************************************/

/***********************************************************************


 Original Author: Giovanni B. Vece

 Affiliation: Università Politecnica delle Marche (Italy)


************************************************************************/

/************************************************************************

Overloaded operators for operator+based power models (declarations and definitions)

Some operators are defined here, others in the file pk_model_operators_2.cpp

*************************************************************************/

#ifndef PK_MODEL_OPERATORS_2_H
#define PK_MODEL_OPERATORS_2_H

#include "PKtool/power_models/pk_opmodel_macros.h"


// ADDition operators:


//  sc_in_aug<type> + sc_in_aug<type>

PK_OPMODEL_OP2a_DECL( +, '+', int, int)
PK_OPMODEL_OP2a_DECL( +, '+', short, short)  
PK_OPMODEL_OP2a_DECL( +, '+', long, long)  
PK_OPMODEL_OP2a_DECL( +, '+', unsigned, unsigned)
PK_OPMODEL_OP2a_DECL( +, '+', float, float)  
PK_OPMODEL_OP2a_DECL( +, '+', double, double)
PK_OPMODEL_OP2a_DECL( +, '+', sc_signed, sc_signed) 
PK_OPMODEL_OP2a_DECL( +, '+', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2b( +, '+', sc_bigint, sc_signed)
PK_OPMODEL_OP2b( +, '+', sc_biguint, sc_unsigned)


//  sc_in_aug<int> + type;

PK_OPMODEL_OP2c_DECL( +, '+', int, int, int)
PK_OPMODEL_OP2c_DECL( +, '+', int, short, int)
PK_OPMODEL_OP2c_DECL( +, '+', int, long, long)
PK_OPMODEL_OP2c_DECL( +, '+', int, unsigned, int)
PK_OPMODEL_OP2c_DECL( +, '+', int, float, float)
PK_OPMODEL_OP2c_DECL( +, '+', int, double, double)
PK_OPMODEL_OP2c_DECL( +, '+', int, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', int, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(+, '+', int, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( +, '+', int, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( +, '+', int, int, int)
PK_OPMODEL_OP2e_DECL( +, '+', int, short, int)
PK_OPMODEL_OP2e_DECL( +, '+', int, long, long)
PK_OPMODEL_OP2e_DECL( +, '+', int, unsigned, int)
PK_OPMODEL_OP2e_DECL( +, '+', int, float, float)
PK_OPMODEL_OP2e_DECL( +, '+', int, double, double)
PK_OPMODEL_OP2e_DECL( +, '+', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', int, sc_signed, sc_signed)
PK_OPMODEL_OP2f(+, '+', int, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( +, '+', int, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( +, '+', int, short, int)
PK_OPMODEL_OP2g_DECL( +, '+', int, long, long)
PK_OPMODEL_OP2g_DECL( +, '+', int, unsigned, int)
PK_OPMODEL_OP2g_DECL( +, '+', int, float, float)
PK_OPMODEL_OP2g_DECL( +, '+', int, double, double)
PK_OPMODEL_OP2g_DECL( +, '+', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( +, '+', int, sc_signed, sc_signed)
PK_OPMODEL_OP2h( +, '+', int, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( +, '+', int, sc_biguint, sc_signed)


//  sc_in_aug<short> + type;

PK_OPMODEL_OP2c_DECL( +, '+', short, int, int)
PK_OPMODEL_OP2c_DECL( +, '+', short, short, short)
PK_OPMODEL_OP2c_DECL( +, '+', short, long, long)
PK_OPMODEL_OP2c_DECL( +, '+', short, unsigned, int)
PK_OPMODEL_OP2c_DECL( +, '+', short, float, float)
PK_OPMODEL_OP2c_DECL( +, '+', short, double, double)
PK_OPMODEL_OP2c_DECL( +, '+', short, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', short, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(+, '+', short, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( +, '+', short, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( +, '+', short, int, int)
PK_OPMODEL_OP2e_DECL( +, '+', short, short, short)
PK_OPMODEL_OP2e_DECL( +, '+', short, long, long)
PK_OPMODEL_OP2e_DECL( +, '+', short, unsigned, int)
PK_OPMODEL_OP2e_DECL( +, '+', short, float, float)
PK_OPMODEL_OP2e_DECL( +, '+', short, double, double)
PK_OPMODEL_OP2e_DECL( +, '+', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', short, sc_signed, sc_signed)
PK_OPMODEL_OP2f(+, '+', short, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( +, '+', short, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( +, '+', short, long, long)
PK_OPMODEL_OP2g_DECL( +, '+', short, unsigned, int)
PK_OPMODEL_OP2g_DECL( +, '+', short, float, float)
PK_OPMODEL_OP2g_DECL( +, '+', short, double, double)
PK_OPMODEL_OP2g_DECL( +, '+', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( +, '+', short, sc_signed, sc_signed)
PK_OPMODEL_OP2h( +, '+', short, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( +, '+', short, sc_biguint, sc_signed)


//  sc_in_aug<long> + type;

PK_OPMODEL_OP2c_DECL( +, '+', long, int, long)
PK_OPMODEL_OP2c_DECL( +, '+', long, short, long)
PK_OPMODEL_OP2c_DECL( +, '+', long, long, long)
PK_OPMODEL_OP2c_DECL( +, '+', long, unsigned, long)
PK_OPMODEL_OP2c_DECL( +, '+', long, float, float)
PK_OPMODEL_OP2c_DECL( +, '+', long, double, double)
PK_OPMODEL_OP2c_DECL( +, '+', long, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', long, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(+, '+', long, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( +, '+', long, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( +, '+', long, int, long)
PK_OPMODEL_OP2e_DECL( +, '+', long, short, long)
PK_OPMODEL_OP2e_DECL( +, '+', long, long, long)
PK_OPMODEL_OP2e_DECL( +, '+', long, unsigned, long)
PK_OPMODEL_OP2e_DECL( +, '+', long, float, float)
PK_OPMODEL_OP2e_DECL( +, '+', long, double, double)
PK_OPMODEL_OP2e_DECL( +, '+', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', long, sc_signed, sc_signed)
PK_OPMODEL_OP2f(+, '+', long, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( +, '+', long, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( +, '+', long, unsigned, long)
PK_OPMODEL_OP2g_DECL( +, '+', long, float, float)
PK_OPMODEL_OP2g_DECL( +, '+', long, double, double)
PK_OPMODEL_OP2g_DECL( +, '+', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( +, '+', long, sc_signed, sc_signed)
PK_OPMODEL_OP2h( +, '+', long, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( +, '+', long, sc_biguint, sc_signed)


//  sc_in_aug<unsigned> + type;

PK_OPMODEL_OP2c_DECL( +, '+', unsigned, int, int)
PK_OPMODEL_OP2c_DECL( +, '+', unsigned, short, int)
PK_OPMODEL_OP2c_DECL( +, '+', unsigned, long, long)
PK_OPMODEL_OP2c_DECL( +, '+', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2c_DECL( +, '+', unsigned, float, float)
PK_OPMODEL_OP2c_DECL( +, '+', unsigned, double, double)
PK_OPMODEL_OP2c_DECL( +, '+', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', unsigned, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2d(+, '+', unsigned, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( +, '+', unsigned, sc_uint, sc_dt::uint_type)

PK_OPMODEL_OP2e_DECL( +, '+', unsigned, int, int)
PK_OPMODEL_OP2e_DECL( +, '+', unsigned, short, int)
PK_OPMODEL_OP2e_DECL( +, '+', unsigned, long, long)
PK_OPMODEL_OP2e_DECL( +, '+', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2e_DECL( +, '+', unsigned, float, float)
PK_OPMODEL_OP2e_DECL( +, '+', unsigned, double, double)
PK_OPMODEL_OP2e_DECL( +, '+', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( +, '+', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2f(+, '+', unsigned, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( +, '+', unsigned, sc_uint, sc_dt::uint_type)

PK_OPMODEL_OP2g_DECL( +, '+', unsigned, float, float)
PK_OPMODEL_OP2g_DECL( +, '+', unsigned, double, double)
PK_OPMODEL_OP2g_DECL( +, '+', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2g_DECL( +, '+', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2h( +, '+', unsigned, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( +, '+', unsigned, sc_biguint, sc_unsigned)


//  sc_in_aug<float> + type;

PK_OPMODEL_OP2c_DECL( +, '+', float, int, float)
PK_OPMODEL_OP2c_DECL( +, '+', float, short, float)
PK_OPMODEL_OP2c_DECL( +, '+', float, long, float)
PK_OPMODEL_OP2c_DECL( +, '+', float, unsigned, float)
PK_OPMODEL_OP2c_DECL( +, '+', float, float, float)
PK_OPMODEL_OP2c_DECL( +, '+', float, double, double)
PK_OPMODEL_OP2d(+, '+', float, sc_int, float)
PK_OPMODEL_OP2d( +, '+', float, sc_uint, float)

PK_OPMODEL_OP2e_DECL( +, '+', float, int, float)
PK_OPMODEL_OP2e_DECL( +, '+', float, short, float)
PK_OPMODEL_OP2e_DECL( +, '+', float, long, float)
PK_OPMODEL_OP2e_DECL( +, '+', float, unsigned, float)
PK_OPMODEL_OP2e_DECL( +, '+', float, float, float)
PK_OPMODEL_OP2e_DECL( +, '+', float, double, double)
PK_OPMODEL_OP2f(+, '+', float, sc_int, float)
PK_OPMODEL_OP2f( +, '+', float, sc_uint, float)

PK_OPMODEL_OP2g_DECL( +, '+', float, double, double)


//  sc_in_aug<double> + type;

PK_OPMODEL_OP2c_DECL( +, '+', double, int, double)
PK_OPMODEL_OP2c_DECL( +, '+', double, short, double)
PK_OPMODEL_OP2c_DECL( +, '+', double, long, double)
PK_OPMODEL_OP2c_DECL( +, '+', double, unsigned, double)
PK_OPMODEL_OP2c_DECL( +, '+', double, float, double)
PK_OPMODEL_OP2c_DECL( +, '+', double, double, double)
PK_OPMODEL_OP2d(+, '+', double, sc_int, double)
PK_OPMODEL_OP2d( +, '+', double, sc_uint, double)

PK_OPMODEL_OP2e_DECL( +, '+', double, int, double)
PK_OPMODEL_OP2e_DECL( +, '+', double, short, double)
PK_OPMODEL_OP2e_DECL( +, '+', double, long, double)
PK_OPMODEL_OP2e_DECL( +, '+', double, unsigned, double)
PK_OPMODEL_OP2e_DECL( +, '+', double, float, double)
PK_OPMODEL_OP2e_DECL( +, '+', double, double, double)
PK_OPMODEL_OP2f(+, '+', double, sc_int, double)
PK_OPMODEL_OP2f( +, '+', double, sc_uint, double)


//  sc_in_aug<sc_signed> + type;

PK_OPMODEL_OP2c_DECL( +, '+', sc_signed, int, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_signed, short, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_signed, long, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_signed, unsigned,sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_signed, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(+, '+', sc_signed, sc_int, sc_signed)
PK_OPMODEL_OP2d( +, '+', sc_signed, sc_uint, sc_signed)

PK_OPMODEL_OP2e_DECL( +, '+', sc_signed, int, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', sc_signed, short, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', sc_signed, long, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', sc_signed, sc_signed, sc_signed)
PK_OPMODEL_OP2f(+, '+', sc_signed, sc_int, sc_signed)
PK_OPMODEL_OP2f( +, '+', sc_signed, sc_uint, sc_signed)

PK_OPMODEL_OP2g_DECL( +, '+', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2h( +, '+', sc_signed, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( +, '+', sc_signed, sc_biguint, sc_signed)


//  sc_in_aug<sc_unsigned> + type;

PK_OPMODEL_OP2c_DECL( +, '+', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2c_DECL( +, '+', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( +, '+', sc_unsigned, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2d(+, '+', sc_unsigned, sc_int, sc_signed)
PK_OPMODEL_OP2d( +, '+', sc_unsigned, sc_uint, sc_unsigned)

PK_OPMODEL_OP2e_DECL( +, '+', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2e_DECL( +, '+', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( +, '+', sc_unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( +, '+', sc_unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2f(+, '+', sc_unsigned, sc_int, sc_signed)
PK_OPMODEL_OP2f( +, '+', sc_unsigned, sc_uint, sc_unsigned)

PK_OPMODEL_OP2h( +, '+', sc_unsigned, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( +, '+', sc_unsigned, sc_biguint, sc_unsigned)


//  sc_in_aug<sc_bigint<n> > + type;

PK_OPMODEL_OP2cc( +, '+', sc_bigint, int, sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_bigint, short, sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_bigint, long, sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_bigint, unsigned,sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_bigint, sc_signed&, sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_bigint, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2dd(+, '+', sc_bigint, sc_int, sc_signed)
PK_OPMODEL_OP2dd( +, '+', sc_bigint, sc_uint, sc_signed)

PK_OPMODEL_OP2ee( +, '+', sc_bigint, int, sc_signed)
PK_OPMODEL_OP2ee( +, '+', sc_bigint, short, sc_signed)
PK_OPMODEL_OP2ee( +, '+', sc_bigint, long, sc_signed)
PK_OPMODEL_OP2ee( +, '+', sc_bigint, unsigned, sc_signed)
PK_OPMODEL_OP2ee( +, '+', sc_bigint, sc_unsigned, sc_signed)
PK_OPMODEL_OP2ee( +, '+', sc_bigint, sc_signed, sc_signed)
PK_OPMODEL_OP2ff(+, '+', sc_bigint, sc_int, sc_signed)
PK_OPMODEL_OP2ff( +, '+', sc_bigint, sc_uint, sc_signed)

PK_OPMODEL_OP2hh( +, '+', sc_bigint, sc_biguint, sc_signed)


//  sc_in_aug<sc_biguint<n> > + type;

PK_OPMODEL_OP2cc( +, '+', sc_biguint, int, sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_biguint, short, sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_biguint, long, sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_biguint, unsigned,sc_unsigned)
PK_OPMODEL_OP2cc( +, '+', sc_biguint, sc_signed&, sc_signed)
PK_OPMODEL_OP2cc( +, '+', sc_biguint, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2dd(+, '+', sc_biguint, sc_int, sc_signed)
PK_OPMODEL_OP2dd( +, '+', sc_biguint, sc_uint, sc_unsigned)

PK_OPMODEL_OP2ee( +, '+', sc_biguint, int, sc_signed)
PK_OPMODEL_OP2ee( +, '+', sc_biguint, short, sc_signed)
PK_OPMODEL_OP2ee( +, '+', sc_biguint, long, sc_signed)
PK_OPMODEL_OP2ee( +, '+', sc_biguint, unsigned, sc_unsigned)
PK_OPMODEL_OP2ee( +, '+', sc_biguint, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2ee( +, '+', sc_biguint, sc_signed, sc_signed)
PK_OPMODEL_OP2ff(+, '+', sc_biguint, sc_int, sc_signed)
PK_OPMODEL_OP2ff( +, '+', sc_biguint, sc_uint, sc_unsigned)


// SUBtraction operators:


//  sc_in_aug<type> - sc_in_aug<type>

PK_OPMODEL_OP2a_DECL( -, '-', int, int)
PK_OPMODEL_OP2a_DECL( -, '-', short, short)  
PK_OPMODEL_OP2a_DECL( -, '-', long, long)  
PK_OPMODEL_OP2a_DECL( -, '-', unsigned, int)
PK_OPMODEL_OP2a_DECL( -, '-', float, float)  
PK_OPMODEL_OP2a_DECL( -, '-', double, double)
PK_OPMODEL_OP2a_DECL( -, '-', sc_signed, sc_signed) 
PK_OPMODEL_OP2a_DECL( -, '-', sc_unsigned, sc_signed)
PK_OPMODEL_OP2b( -, '-', sc_bigint, sc_signed)
PK_OPMODEL_OP2b( -, '-', sc_biguint, sc_signed)



//  sc_in_aug<int> - type;


PK_OPMODEL_OP2c_DECL( -, '-', int, int, int)
PK_OPMODEL_OP2c_DECL( -, '-', int, short, int)
PK_OPMODEL_OP2c_DECL( -, '-', int, long, long)
PK_OPMODEL_OP2c_DECL( -, '-', int, unsigned, int)
PK_OPMODEL_OP2c_DECL( -, '-', int, float, float)
PK_OPMODEL_OP2c_DECL( -, '-', int, double, double)
PK_OPMODEL_OP2c_DECL( -, '-', int, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', int, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(-, '-', int, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( -, '-', int, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( -, '-', int, int, int)
PK_OPMODEL_OP2e_DECL( -, '-', int, short, int)
PK_OPMODEL_OP2e_DECL( -, '-', int, long, long)
PK_OPMODEL_OP2e_DECL( -, '-', int, unsigned, int)
PK_OPMODEL_OP2e_DECL( -, '-', int, float, float)
PK_OPMODEL_OP2e_DECL( -, '-', int, double, double)
PK_OPMODEL_OP2e_DECL( -, '-', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', int, sc_signed, sc_signed)
PK_OPMODEL_OP2f(-, '-', int, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( -, '-', int, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( -, '-', int, short, int)
PK_OPMODEL_OP2g_DECL( -, '-', int, long, long)
PK_OPMODEL_OP2g_DECL( -, '-', int, unsigned, int)
PK_OPMODEL_OP2g_DECL( -, '-', int, float, float)
PK_OPMODEL_OP2g_DECL( -, '-', int, double, double)
PK_OPMODEL_OP2g_DECL( -, '-', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( -, '-', int, sc_signed, sc_signed)
PK_OPMODEL_OP2h( -, '-', int, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( -, '-', int, sc_biguint, sc_signed)


//  sc_in_aug<short> - type;

PK_OPMODEL_OP2c_DECL( -, '-', short, int, int)
PK_OPMODEL_OP2c_DECL( -, '-', short, short, short)
PK_OPMODEL_OP2c_DECL( -, '-', short, long, long)
PK_OPMODEL_OP2c_DECL( -, '-', short, unsigned, int)
PK_OPMODEL_OP2c_DECL( -, '-', short, float, float)
PK_OPMODEL_OP2c_DECL( -, '-', short, double, double)
PK_OPMODEL_OP2c_DECL( -, '-', short, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', short, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(-, '-', short, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( -, '-', short, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( -, '-', short, int, int)
PK_OPMODEL_OP2e_DECL( -, '-', short, short, short)
PK_OPMODEL_OP2e_DECL( -, '-', short, long, long)
PK_OPMODEL_OP2e_DECL( -, '-', short, unsigned, int)
PK_OPMODEL_OP2e_DECL( -, '-', short, float, float)
PK_OPMODEL_OP2e_DECL( -, '-', short, double, double)
PK_OPMODEL_OP2e_DECL( -, '-', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', short, sc_signed, sc_signed)
PK_OPMODEL_OP2f(-, '-', short, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( -, '-', short, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( -, '-', short, long, long)
PK_OPMODEL_OP2g_DECL( -, '-', short, unsigned, int)
PK_OPMODEL_OP2g_DECL( -, '-', short, float, float)
PK_OPMODEL_OP2g_DECL( -, '-', short, double, double)
PK_OPMODEL_OP2g_DECL( -, '-', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( -, '-', short, sc_signed, sc_signed)
PK_OPMODEL_OP2h( -, '-', short, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( -, '-', short, sc_biguint, sc_signed)


//  sc_in_aug<long> - type;

PK_OPMODEL_OP2c_DECL( -, '-', long, int, long)
PK_OPMODEL_OP2c_DECL( -, '-', long, short, long)
PK_OPMODEL_OP2c_DECL( -, '-', long, long, long)
PK_OPMODEL_OP2c_DECL( -, '-', long, unsigned, long)
PK_OPMODEL_OP2c_DECL( -, '-', long, float, float)
PK_OPMODEL_OP2c_DECL( -, '-', long, double, double)
PK_OPMODEL_OP2c_DECL( -, '-', long, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', long, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(-, '-', long, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( -, '-', long, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( -, '-', long, int, long)
PK_OPMODEL_OP2e_DECL( -, '-', long, short, long)
PK_OPMODEL_OP2e_DECL( -, '-', long, long, long)
PK_OPMODEL_OP2e_DECL( -, '-', long, unsigned, long)
PK_OPMODEL_OP2e_DECL( -, '-', long, float, float)
PK_OPMODEL_OP2e_DECL( -, '-', long, double, double)
PK_OPMODEL_OP2e_DECL( -, '-', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', long, sc_signed, sc_signed)
PK_OPMODEL_OP2f(-, '-', long, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( -, '-', long, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( -, '-', long, unsigned, long)
PK_OPMODEL_OP2g_DECL( -, '-', long, float, float)
PK_OPMODEL_OP2g_DECL( -, '-', long, double, double)
PK_OPMODEL_OP2g_DECL( -, '-', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( -, '-', long, sc_signed, sc_signed)
PK_OPMODEL_OP2h( -, '-', long, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( -, '-', long, sc_biguint, sc_signed)


//  sc_in_aug<unsigned> - type;

PK_OPMODEL_OP2c_DECL( -, '-', unsigned, int, int)
PK_OPMODEL_OP2c_DECL( -, '-', unsigned, short, int)
PK_OPMODEL_OP2c_DECL( -, '-', unsigned, long, long)
PK_OPMODEL_OP2c_DECL( -, '-', unsigned, unsigned, int)
PK_OPMODEL_OP2c_DECL( -, '-', unsigned, float, float)
PK_OPMODEL_OP2c_DECL( -, '-', unsigned, double, double)
PK_OPMODEL_OP2c_DECL( -, '-', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', unsigned, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(-, '-', unsigned, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( -, '-', unsigned, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( -, '-', unsigned, int, int)
PK_OPMODEL_OP2e_DECL( -, '-', unsigned, short, int)
PK_OPMODEL_OP2e_DECL( -, '-', unsigned, long, long)
PK_OPMODEL_OP2e_DECL( -, '-', unsigned, unsigned, int)
PK_OPMODEL_OP2e_DECL( -, '-', unsigned, float, float)
PK_OPMODEL_OP2e_DECL( -, '-', unsigned, double, double)
PK_OPMODEL_OP2e_DECL( -, '-', unsigned, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2f(-, '-', unsigned, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( -, '-', unsigned, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( -, '-', unsigned, float, float)
PK_OPMODEL_OP2g_DECL( -, '-', unsigned, double, double)
PK_OPMODEL_OP2g_DECL( -, '-', unsigned, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( -, '-', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2h( -, '-', unsigned, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( -, '-', unsigned, sc_biguint, sc_signed)


//  sc_in_aug<float> - type;

PK_OPMODEL_OP2c_DECL( -, '-', float, int, float)
PK_OPMODEL_OP2c_DECL( -, '-', float, short, float)
PK_OPMODEL_OP2c_DECL( -, '-', float, long, float)
PK_OPMODEL_OP2c_DECL( -, '-', float, unsigned, float)
PK_OPMODEL_OP2c_DECL( -, '-', float, float, float)
PK_OPMODEL_OP2c_DECL( -, '-', float, double, double)
PK_OPMODEL_OP2d(-, '-', float, sc_int, float)
PK_OPMODEL_OP2d( -, '-', float, sc_uint, float)

PK_OPMODEL_OP2e_DECL( -, '-', float, int, float)
PK_OPMODEL_OP2e_DECL( -, '-', float, short, float)
PK_OPMODEL_OP2e_DECL( -, '-', float, long, float)
PK_OPMODEL_OP2e_DECL( -, '-', float, unsigned, float)
PK_OPMODEL_OP2e_DECL( -, '-', float, float, float)
PK_OPMODEL_OP2e_DECL( -, '-', float, double, double)
PK_OPMODEL_OP2f(-, '-', float, sc_int, float)
PK_OPMODEL_OP2f( -, '-', float, sc_uint, float)

PK_OPMODEL_OP2g_DECL( -, '-', float, double, double)


//  sc_in_aug<double> - type;

PK_OPMODEL_OP2c_DECL( -, '-', double, int, double)
PK_OPMODEL_OP2c_DECL( -, '-', double, short, double)
PK_OPMODEL_OP2c_DECL( -, '-', double, long, double)
PK_OPMODEL_OP2c_DECL( -, '-', double, unsigned, double)
PK_OPMODEL_OP2c_DECL( -, '-', double, float, double)
PK_OPMODEL_OP2c_DECL( -, '-', double, double, double)
PK_OPMODEL_OP2d(-, '-', double, sc_int, double)
PK_OPMODEL_OP2d( -, '-', double, sc_uint, double)

PK_OPMODEL_OP2e_DECL( -, '-', double, int, double)
PK_OPMODEL_OP2e_DECL( -, '-', double, short, double)
PK_OPMODEL_OP2e_DECL( -, '-', double, long, double)
PK_OPMODEL_OP2e_DECL( -, '-', double, unsigned, double)
PK_OPMODEL_OP2e_DECL( -, '-', double, float, double)
PK_OPMODEL_OP2e_DECL( -, '-', double, double, double)
PK_OPMODEL_OP2f(-, '-', double, sc_int, double)
PK_OPMODEL_OP2f( -, '-', double, sc_uint, double)


//  sc_in_aug<sc_signed> - type;

PK_OPMODEL_OP2c_DECL( -, '-', sc_signed, int, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_signed, short, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_signed, long, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_signed, unsigned,sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_signed, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(-, '-', sc_signed, sc_int, sc_signed)
PK_OPMODEL_OP2d( -, '-', sc_signed, sc_uint, sc_signed)

PK_OPMODEL_OP2e_DECL( -, '-', sc_signed, int, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_signed, short, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_signed, long, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_signed, sc_signed, sc_signed)
PK_OPMODEL_OP2f(-, '-', sc_signed, sc_int, sc_signed)
PK_OPMODEL_OP2f( -, '-', sc_signed, sc_uint, sc_signed)

PK_OPMODEL_OP2g_DECL( -, '-', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2h( -, '-', sc_signed, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( -, '-', sc_signed, sc_biguint, sc_signed)


//  sc_in_aug<sc_unsigned> - type;

PK_OPMODEL_OP2c_DECL( -, '-', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_unsigned, unsigned, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( -, '-', sc_unsigned, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(-, '-', sc_unsigned, sc_int, sc_signed)
PK_OPMODEL_OP2d( -, '-', sc_unsigned, sc_uint, sc_signed)

PK_OPMODEL_OP2e_DECL( -, '-', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_unsigned, unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_unsigned, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( -, '-', sc_unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2f(-, '-', sc_unsigned, sc_int, sc_signed)
PK_OPMODEL_OP2f( -, '-', sc_unsigned, sc_uint, sc_signed)

PK_OPMODEL_OP2h( -, '-', sc_unsigned, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( -, '-', sc_unsigned, sc_biguint, sc_signed)


//  sc_in_aug<sc_bigint<n> > - type;

PK_OPMODEL_OP2cc( -, '-', sc_bigint, int, sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_bigint, short, sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_bigint, long, sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_bigint, unsigned,sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_bigint, sc_signed&, sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_bigint, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2dd(-, '-', sc_bigint, sc_int, sc_signed)
PK_OPMODEL_OP2dd( -, '-', sc_bigint, sc_uint, sc_signed)

PK_OPMODEL_OP2ee( -, '-', sc_bigint, int, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_bigint, short, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_bigint, long, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_bigint, unsigned, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_bigint, sc_unsigned, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_bigint, sc_signed, sc_signed)
PK_OPMODEL_OP2ff(-, '-', sc_bigint, sc_int, sc_signed)
PK_OPMODEL_OP2ff( -, '-', sc_bigint, sc_uint, sc_signed)

PK_OPMODEL_OP2hh( -, '-', sc_bigint, sc_biguint, sc_signed)


//  sc_in_aug<sc_biguint<n> > - type;

PK_OPMODEL_OP2cc( -, '-', sc_biguint, int, sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_biguint, short, sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_biguint, long, sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_biguint, unsigned,sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_biguint, sc_signed&, sc_signed)
PK_OPMODEL_OP2cc( -, '-', sc_biguint, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2dd(-, '-', sc_biguint, sc_int, sc_signed)
PK_OPMODEL_OP2dd( -, '-', sc_biguint, sc_uint, sc_signed)

PK_OPMODEL_OP2ee( -, '-', sc_biguint, int, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_biguint, short, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_biguint, long, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_biguint, unsigned, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_biguint, sc_unsigned, sc_signed)
PK_OPMODEL_OP2ee( -, '-', sc_biguint, sc_signed, sc_signed)
PK_OPMODEL_OP2ff(-, '-', sc_biguint, sc_int, sc_signed)
PK_OPMODEL_OP2ff( -, '-', sc_biguint, sc_uint, sc_signed)



// MULtiplication operators:


//  sc_in_aug<type> * sc_in_aug<type>

PK_OPMODEL_OP2a_DECL( *, '*', int, int)
PK_OPMODEL_OP2a_DECL( *, '*', short, short)  
PK_OPMODEL_OP2a_DECL( *, '*', long, long)  
PK_OPMODEL_OP2a_DECL( *, '*', unsigned, unsigned)
PK_OPMODEL_OP2a_DECL( *, '*', float, float)  
PK_OPMODEL_OP2a_DECL( *, '*', double, double)
PK_OPMODEL_OP2a_DECL( *, '*', sc_signed, sc_signed) 
PK_OPMODEL_OP2a_DECL( *, '*', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2b( *, '*', sc_bigint, sc_signed)
PK_OPMODEL_OP2b( *, '*', sc_biguint, sc_unsigned)


//  sc_in_aug<int> * type;

PK_OPMODEL_OP2c_DECL( *, '*', int, int, int)
PK_OPMODEL_OP2c_DECL( *, '*', int, short, int)
PK_OPMODEL_OP2c_DECL( *, '*', int, long, long)
PK_OPMODEL_OP2c_DECL( *, '*', int, unsigned, int)
PK_OPMODEL_OP2c_DECL( *, '*', int, float, float)
PK_OPMODEL_OP2c_DECL( *, '*', int, double, double)
PK_OPMODEL_OP2c_DECL( *, '*', int, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', int, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(*, '*', int, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( *, '*', int, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( *, '*', int, int, int)
PK_OPMODEL_OP2e_DECL( *, '*', int, short, int)
PK_OPMODEL_OP2e_DECL( *, '*', int, long, long)
PK_OPMODEL_OP2e_DECL( *, '*', int, unsigned, int)
PK_OPMODEL_OP2e_DECL( *, '*', int, float, float)
PK_OPMODEL_OP2e_DECL( *, '*', int, double, double)
PK_OPMODEL_OP2e_DECL( *, '*', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', int, sc_signed, sc_signed)
PK_OPMODEL_OP2f(*, '*', int, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( *, '*', int, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( *, '*', int, short, int)
PK_OPMODEL_OP2g_DECL( *, '*', int, long, long)
PK_OPMODEL_OP2g_DECL( *, '*', int, unsigned, int)
PK_OPMODEL_OP2g_DECL( *, '*', int, float, float)
PK_OPMODEL_OP2g_DECL( *, '*', int, double, double)
PK_OPMODEL_OP2g_DECL( *, '*', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( *, '*', int, sc_signed, sc_signed)
PK_OPMODEL_OP2h( *, '*', int, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( *, '*', int, sc_biguint, sc_signed)


//  sc_in_aug<short> * type;

PK_OPMODEL_OP2c_DECL( *, '*', short, int, int)
PK_OPMODEL_OP2c_DECL( *, '*', short, short, short)
PK_OPMODEL_OP2c_DECL( *, '*', short, long, long)
PK_OPMODEL_OP2c_DECL( *, '*', short, unsigned, int)
PK_OPMODEL_OP2c_DECL( *, '*', short, float, float)
PK_OPMODEL_OP2c_DECL( *, '*', short, double, double)
PK_OPMODEL_OP2c_DECL( *, '*', short, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', short, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(*, '*', short, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( *, '*', short, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( *, '*', short, int, int)
PK_OPMODEL_OP2e_DECL( *, '*', short, short, short)
PK_OPMODEL_OP2e_DECL( *, '*', short, long, long)
PK_OPMODEL_OP2e_DECL( *, '*', short, unsigned, int)
PK_OPMODEL_OP2e_DECL( *, '*', short, float, float)
PK_OPMODEL_OP2e_DECL( *, '*', short, double, double)
PK_OPMODEL_OP2e_DECL( *, '*', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', short, sc_signed, sc_signed)
PK_OPMODEL_OP2f(*, '*', short, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( *, '*', short, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( *, '*', short, long, long)
PK_OPMODEL_OP2g_DECL( *, '*', short, unsigned, int)
PK_OPMODEL_OP2g_DECL( *, '*', short, float, float)
PK_OPMODEL_OP2g_DECL( *, '*', short, double, double)
PK_OPMODEL_OP2g_DECL( *, '*', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( *, '*', short, sc_signed, sc_signed)
PK_OPMODEL_OP2h( *, '*', short, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( *, '*', short, sc_biguint, sc_signed)


//  sc_in_aug<long> * type;

PK_OPMODEL_OP2c_DECL( *, '*', long, int, long)
PK_OPMODEL_OP2c_DECL( *, '*', long, short, long)
PK_OPMODEL_OP2c_DECL( *, '*', long, long, long)
PK_OPMODEL_OP2c_DECL( *, '*', long, unsigned, long)
PK_OPMODEL_OP2c_DECL( *, '*', long, float, float)
PK_OPMODEL_OP2c_DECL( *, '*', long, double, double)
PK_OPMODEL_OP2c_DECL( *, '*', long, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', long, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(*, '*', long, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( *, '*', long, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( *, '*', long, int, long)
PK_OPMODEL_OP2e_DECL( *, '*', long, short, long)
PK_OPMODEL_OP2e_DECL( *, '*', long, long, long)
PK_OPMODEL_OP2e_DECL( *, '*', long, unsigned, long)
PK_OPMODEL_OP2e_DECL( *, '*', long, float, float)
PK_OPMODEL_OP2e_DECL( *, '*', long, double, double)
PK_OPMODEL_OP2e_DECL( *, '*', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', long, sc_signed, sc_signed)
PK_OPMODEL_OP2f(*, '*', long, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( *, '*', long, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( *, '*', long, unsigned, long)
PK_OPMODEL_OP2g_DECL( *, '*', long, float, float)
PK_OPMODEL_OP2g_DECL( *, '*', long, double, double)
PK_OPMODEL_OP2g_DECL( *, '*', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( *, '*', long, sc_signed, sc_signed)
PK_OPMODEL_OP2h( *, '*', long, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( *, '*', long, sc_biguint, sc_signed)


//  sc_in_aug<unsigned> * type;

PK_OPMODEL_OP2c_DECL( *, '*', unsigned, int, int)
PK_OPMODEL_OP2c_DECL( *, '*', unsigned, short, int)
PK_OPMODEL_OP2c_DECL( *, '*', unsigned, long, long)
PK_OPMODEL_OP2c_DECL( *, '*', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2c_DECL( *, '*', unsigned, float, float)
PK_OPMODEL_OP2c_DECL( *, '*', unsigned, double, double)
PK_OPMODEL_OP2c_DECL( *, '*', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', unsigned, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2d(*, '*', unsigned, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( *, '*', unsigned, sc_uint, sc_dt::uint_type)

PK_OPMODEL_OP2e_DECL( *, '*', unsigned, int, int)
PK_OPMODEL_OP2e_DECL( *, '*', unsigned, short, int)
PK_OPMODEL_OP2e_DECL( *, '*', unsigned, long, long)
PK_OPMODEL_OP2e_DECL( *, '*', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2e_DECL( *, '*', unsigned, float, float)
PK_OPMODEL_OP2e_DECL( *, '*', unsigned, double, double)
PK_OPMODEL_OP2e_DECL( *, '*', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( *, '*', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2f(*, '*', unsigned, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( *, '*', unsigned, sc_uint, sc_dt::uint_type)

PK_OPMODEL_OP2g_DECL( *, '*', unsigned, float, float)
PK_OPMODEL_OP2g_DECL( *, '*', unsigned, double, double)
PK_OPMODEL_OP2g_DECL( *, '*', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2g_DECL( *, '*', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2h( *, '*', unsigned, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( *, '*', unsigned, sc_biguint, sc_unsigned)


//  sc_in_aug<float> * type;

PK_OPMODEL_OP2c_DECL( *, '*', float, int, float)
PK_OPMODEL_OP2c_DECL( *, '*', float, short, float)
PK_OPMODEL_OP2c_DECL( *, '*', float, long, float)
PK_OPMODEL_OP2c_DECL( *, '*', float, unsigned, float)
PK_OPMODEL_OP2c_DECL( *, '*', float, float, float)
PK_OPMODEL_OP2c_DECL( *, '*', float, double, double)
PK_OPMODEL_OP2d(*, '*', float, sc_int, float)
PK_OPMODEL_OP2d( *, '*', float, sc_uint, float)

PK_OPMODEL_OP2e_DECL( *, '*', float, int, float)
PK_OPMODEL_OP2e_DECL( *, '*', float, short, float)
PK_OPMODEL_OP2e_DECL( *, '*', float, long, float)
PK_OPMODEL_OP2e_DECL( *, '*', float, unsigned, float)
PK_OPMODEL_OP2e_DECL( *, '*', float, float, float)
PK_OPMODEL_OP2e_DECL( *, '*', float, double, double)
PK_OPMODEL_OP2f(*, '*', float, sc_int, float)
PK_OPMODEL_OP2f( *, '*', float, sc_uint, float)

PK_OPMODEL_OP2g_DECL( *, '*', float, double, double)


//  sc_in_aug<double> * type;

PK_OPMODEL_OP2c_DECL( *, '*', double, int, double)
PK_OPMODEL_OP2c_DECL( *, '*', double, short, double)
PK_OPMODEL_OP2c_DECL( *, '*', double, long, double)
PK_OPMODEL_OP2c_DECL( *, '*', double, unsigned, double)
PK_OPMODEL_OP2c_DECL( *, '*', double, float, double)
PK_OPMODEL_OP2c_DECL( *, '*', double, double, double)
PK_OPMODEL_OP2d(*, '*', double, sc_int, double)
PK_OPMODEL_OP2d( *, '*', double, sc_uint, double)

PK_OPMODEL_OP2e_DECL( *, '*', double, int, double)
PK_OPMODEL_OP2e_DECL( *, '*', double, short, double)
PK_OPMODEL_OP2e_DECL( *, '*', double, long, double)
PK_OPMODEL_OP2e_DECL( *, '*', double, unsigned, double)
PK_OPMODEL_OP2e_DECL( *, '*', double, float, double)
PK_OPMODEL_OP2e_DECL( *, '*', double, double, double)
PK_OPMODEL_OP2f(*, '*', double, sc_int, double)
PK_OPMODEL_OP2f( *, '*', double, sc_uint, double)


//  sc_in_aug<sc_signed> * type;

PK_OPMODEL_OP2c_DECL( *, '*', sc_signed, int, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_signed, short, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_signed, long, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_signed, unsigned,sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_signed, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(*, '*', sc_signed, sc_int, sc_signed)
PK_OPMODEL_OP2d( *, '*', sc_signed, sc_uint, sc_signed)

PK_OPMODEL_OP2e_DECL( *, '*', sc_signed, int, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', sc_signed, short, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', sc_signed, long, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', sc_signed, sc_signed, sc_signed)
PK_OPMODEL_OP2f(*, '*', sc_signed, sc_int, sc_signed)
PK_OPMODEL_OP2f( *, '*', sc_signed, sc_uint, sc_signed)

PK_OPMODEL_OP2g_DECL( *, '*', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2h( *, '*', sc_signed, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( *, '*', sc_signed, sc_biguint, sc_signed)


//  sc_in_aug<sc_unsigned> * type;

PK_OPMODEL_OP2c_DECL( *, '*', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2c_DECL( *, '*', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( *, '*', sc_unsigned, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2d(*, '*', sc_unsigned, sc_int, sc_signed)
PK_OPMODEL_OP2d( *, '*', sc_unsigned, sc_uint, sc_unsigned)

PK_OPMODEL_OP2e_DECL( *, '*', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2e_DECL( *, '*', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( *, '*', sc_unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( *, '*', sc_unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2f(*, '*', sc_unsigned, sc_int, sc_signed)
PK_OPMODEL_OP2f( *, '*', sc_unsigned, sc_uint, sc_unsigned)

PK_OPMODEL_OP2h( *, '*', sc_unsigned, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( *, '*', sc_unsigned, sc_biguint, sc_unsigned)


//  sc_in_aug<sc_bigint<n> > * type;

PK_OPMODEL_OP2cc( *, '*', sc_bigint, int, sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_bigint, short, sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_bigint, long, sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_bigint, unsigned,sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_bigint, sc_signed&, sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_bigint, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2dd(*, '*', sc_bigint, sc_int, sc_signed)
PK_OPMODEL_OP2dd( *, '*', sc_bigint, sc_uint, sc_signed)

PK_OPMODEL_OP2ee( *, '*', sc_bigint, int, sc_signed)
PK_OPMODEL_OP2ee( *, '*', sc_bigint, short, sc_signed)
PK_OPMODEL_OP2ee( *, '*', sc_bigint, long, sc_signed)
PK_OPMODEL_OP2ee( *, '*', sc_bigint, unsigned, sc_signed)
PK_OPMODEL_OP2ee( *, '*', sc_bigint, sc_unsigned, sc_signed)
PK_OPMODEL_OP2ee( *, '*', sc_bigint, sc_signed, sc_signed)
PK_OPMODEL_OP2ff(*, '*', sc_bigint, sc_int, sc_signed)
PK_OPMODEL_OP2ff( *, '*', sc_bigint, sc_uint, sc_signed)

PK_OPMODEL_OP2hh( *, '*', sc_bigint, sc_biguint, sc_signed)


//  sc_in_aug<sc_biguint<n> > * type;

PK_OPMODEL_OP2cc( *, '*', sc_biguint, int, sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_biguint, short, sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_biguint, long, sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_biguint, unsigned,sc_unsigned)
PK_OPMODEL_OP2cc( *, '*', sc_biguint, sc_signed&, sc_signed)
PK_OPMODEL_OP2cc( *, '*', sc_biguint, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2dd(*, '*', sc_biguint, sc_int, sc_signed)
PK_OPMODEL_OP2dd( *, '*', sc_biguint, sc_uint, sc_unsigned)

PK_OPMODEL_OP2ee( *, '*', sc_biguint, int, sc_signed)
PK_OPMODEL_OP2ee( *, '*', sc_biguint, short, sc_signed)
PK_OPMODEL_OP2ee( *, '*', sc_biguint, long, sc_signed)
PK_OPMODEL_OP2ee( *, '*', sc_biguint, unsigned, sc_unsigned)
PK_OPMODEL_OP2ee( *, '*', sc_biguint, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2ee( *, '*', sc_biguint, sc_signed, sc_signed)
PK_OPMODEL_OP2ff(*, '*', sc_biguint, sc_int, sc_signed)
PK_OPMODEL_OP2ff( *, '*', sc_biguint, sc_uint, sc_unsigned)



// DIVision operators:


//  sc_in_aug<type> / sc_in_aug<type>

PK_OPMODEL_OP2a_DECL( /, '/', int, int)
PK_OPMODEL_OP2a_DECL( /, '/', short, short)  
PK_OPMODEL_OP2a_DECL( /, '/', long, long)  
PK_OPMODEL_OP2a_DECL( /, '/', unsigned, unsigned)
PK_OPMODEL_OP2a_DECL( /, '/', float, float)  
PK_OPMODEL_OP2a_DECL( /, '/', double, double)
PK_OPMODEL_OP2a_DECL( /, '/', sc_signed, sc_signed) 
PK_OPMODEL_OP2a_DECL( /, '/', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2b( /, '/', sc_bigint, sc_signed)
PK_OPMODEL_OP2b( /, '/', sc_biguint, sc_unsigned)


//  sc_in_aug<int> / type;

PK_OPMODEL_OP2c_DECL( /, '/', int, int, int)
PK_OPMODEL_OP2c_DECL( /, '/', int, short, int)
PK_OPMODEL_OP2c_DECL( /, '/', int, long, long)
PK_OPMODEL_OP2c_DECL( /, '/', int, unsigned, int)
PK_OPMODEL_OP2c_DECL( /, '/', int, float, float)
PK_OPMODEL_OP2c_DECL( /, '/', int, double, double)
PK_OPMODEL_OP2c_DECL( /, '/', int, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', int, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(/, '/', int, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( /, '/', int, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( /, '/', int, int, int)
PK_OPMODEL_OP2e_DECL( /, '/', int, short, int)
PK_OPMODEL_OP2e_DECL( /, '/', int, long, long)
PK_OPMODEL_OP2e_DECL( /, '/', int, unsigned, int)
PK_OPMODEL_OP2e_DECL( /, '/', int, float, float)
PK_OPMODEL_OP2e_DECL( /, '/', int, double, double)
PK_OPMODEL_OP2e_DECL( /, '/', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', int, sc_signed, sc_signed)
PK_OPMODEL_OP2f(/, '/', int, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( /, '/', int, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( /, '/', int, short, int)
PK_OPMODEL_OP2g_DECL( /, '/', int, long, long)
PK_OPMODEL_OP2g_DECL( /, '/', int, unsigned, int)
PK_OPMODEL_OP2g_DECL( /, '/', int, float, float)
PK_OPMODEL_OP2g_DECL( /, '/', int, double, double)
PK_OPMODEL_OP2g_DECL( /, '/', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( /, '/', int, sc_signed, sc_signed)
PK_OPMODEL_OP2h( /, '/', int, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( /, '/', int, sc_biguint, sc_signed)


//  sc_in_aug<short> / type;

PK_OPMODEL_OP2c_DECL( /, '/', short, int, int)
PK_OPMODEL_OP2c_DECL( /, '/', short, short, short)
PK_OPMODEL_OP2c_DECL( /, '/', short, long, long)
PK_OPMODEL_OP2c_DECL( /, '/', short, unsigned, int)
PK_OPMODEL_OP2c_DECL( /, '/', short, float, float)
PK_OPMODEL_OP2c_DECL( /, '/', short, double, double)
PK_OPMODEL_OP2c_DECL( /, '/', short, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', short, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(/, '/', short, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( /, '/', short, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( /, '/', short, int, int)
PK_OPMODEL_OP2e_DECL( /, '/', short, short, short)
PK_OPMODEL_OP2e_DECL( /, '/', short, long, long)
PK_OPMODEL_OP2e_DECL( /, '/', short, unsigned, int)
PK_OPMODEL_OP2e_DECL( /, '/', short, float, float)
PK_OPMODEL_OP2e_DECL( /, '/', short, double, double)
PK_OPMODEL_OP2e_DECL( /, '/', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', short, sc_signed, sc_signed)
PK_OPMODEL_OP2f(/, '/', short, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( /, '/', short, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( /, '/', short, long, long)
PK_OPMODEL_OP2g_DECL( /, '/', short, unsigned, int)
PK_OPMODEL_OP2g_DECL( /, '/', short, float, float)
PK_OPMODEL_OP2g_DECL( /, '/', short, double, double)
PK_OPMODEL_OP2g_DECL( /, '/', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( /, '/', short, sc_signed, sc_signed)
PK_OPMODEL_OP2h( /, '/', short, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( /, '/', short, sc_biguint, sc_signed)


//  sc_in_aug<long> / type;

PK_OPMODEL_OP2c_DECL( /, '/', long, int, long)
PK_OPMODEL_OP2c_DECL( /, '/', long, short, long)
PK_OPMODEL_OP2c_DECL( /, '/', long, long, long)
PK_OPMODEL_OP2c_DECL( /, '/', long, unsigned, long)
PK_OPMODEL_OP2c_DECL( /, '/', long, float, float)
PK_OPMODEL_OP2c_DECL( /, '/', long, double, double)
PK_OPMODEL_OP2c_DECL( /, '/', long, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', long, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(/, '/', long, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( /, '/', long, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2e_DECL( /, '/', long, int, long)
PK_OPMODEL_OP2e_DECL( /, '/', long, short, long)
PK_OPMODEL_OP2e_DECL( /, '/', long, long, long)
PK_OPMODEL_OP2e_DECL( /, '/', long, unsigned, long)
PK_OPMODEL_OP2e_DECL( /, '/', long, float, float)
PK_OPMODEL_OP2e_DECL( /, '/', long, double, double)
PK_OPMODEL_OP2e_DECL( /, '/', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', long, sc_signed, sc_signed)
PK_OPMODEL_OP2f(/, '/', long, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( /, '/', long, sc_uint, sc_dt::int_type)

PK_OPMODEL_OP2g_DECL( /, '/', long, unsigned, long)
PK_OPMODEL_OP2g_DECL( /, '/', long, float, float)
PK_OPMODEL_OP2g_DECL( /, '/', long, double, double)
PK_OPMODEL_OP2g_DECL( /, '/', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g_DECL( /, '/', long, sc_signed, sc_signed)
PK_OPMODEL_OP2h( /, '/', long, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( /, '/', long, sc_biguint, sc_signed)


//  sc_in_aug<unsigned> / type;

PK_OPMODEL_OP2c_DECL( /, '/', unsigned, int, int)
PK_OPMODEL_OP2c_DECL( /, '/', unsigned, short, int)
PK_OPMODEL_OP2c_DECL( /, '/', unsigned, long, long)
PK_OPMODEL_OP2c_DECL( /, '/', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2c_DECL( /, '/', unsigned, float, float)
PK_OPMODEL_OP2c_DECL( /, '/', unsigned, double, double)
PK_OPMODEL_OP2c_DECL( /, '/', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', unsigned, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2d(/, '/', unsigned, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2d( /, '/', unsigned, sc_uint, sc_dt::uint_type)

PK_OPMODEL_OP2e_DECL( /, '/', unsigned, int, int)
PK_OPMODEL_OP2e_DECL( /, '/', unsigned, short, int)
PK_OPMODEL_OP2e_DECL( /, '/', unsigned, long, long)
PK_OPMODEL_OP2e_DECL( /, '/', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2e_DECL( /, '/', unsigned, float, float)
PK_OPMODEL_OP2e_DECL( /, '/', unsigned, double, double)
PK_OPMODEL_OP2e_DECL( /, '/', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( /, '/', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2f(/, '/', unsigned, sc_int, sc_dt::int_type)
PK_OPMODEL_OP2f( /, '/', unsigned, sc_uint, sc_dt::uint_type)

PK_OPMODEL_OP2g_DECL( /, '/', unsigned, float, float)
PK_OPMODEL_OP2g_DECL( /, '/', unsigned, double, double)
PK_OPMODEL_OP2g_DECL( /, '/', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2g_DECL( /, '/', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2h( /, '/', unsigned, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( /, '/', unsigned, sc_biguint, sc_unsigned)


//  sc_in_aug<float> / type;

PK_OPMODEL_OP2c_DECL( /, '/', float, int, float)
PK_OPMODEL_OP2c_DECL( /, '/', float, short, float)
PK_OPMODEL_OP2c_DECL( /, '/', float, long, float)
PK_OPMODEL_OP2c_DECL( /, '/', float, unsigned, float)
PK_OPMODEL_OP2c_DECL( /, '/', float, float, float)
PK_OPMODEL_OP2c_DECL( /, '/', float, double, double)
PK_OPMODEL_OP2d(/, '/', float, sc_int, float)
PK_OPMODEL_OP2d( /, '/', float, sc_uint, float)

PK_OPMODEL_OP2e_DECL( /, '/', float, int, float)
PK_OPMODEL_OP2e_DECL( /, '/', float, short, float)
PK_OPMODEL_OP2e_DECL( /, '/', float, long, float)
PK_OPMODEL_OP2e_DECL( /, '/', float, unsigned, float)
PK_OPMODEL_OP2e_DECL( /, '/', float, float, float)
PK_OPMODEL_OP2e_DECL( /, '/', float, double, double)
PK_OPMODEL_OP2f(/, '/', float, sc_int, float)
PK_OPMODEL_OP2f( /, '/', float, sc_uint, float)

PK_OPMODEL_OP2g_DECL( /, '/', float, double, double)


//  sc_in_aug<double> / type;

PK_OPMODEL_OP2c_DECL( /, '/', double, int, double)
PK_OPMODEL_OP2c_DECL( /, '/', double, short, double)
PK_OPMODEL_OP2c_DECL( /, '/', double, long, double)
PK_OPMODEL_OP2c_DECL( /, '/', double, unsigned, double)
PK_OPMODEL_OP2c_DECL( /, '/', double, float, double)
PK_OPMODEL_OP2c_DECL( /, '/', double, double, double)
PK_OPMODEL_OP2d(/, '/', double, sc_int, double)
PK_OPMODEL_OP2d( /, '/', double, sc_uint, double)

PK_OPMODEL_OP2e_DECL( /, '/', double, int, double)
PK_OPMODEL_OP2e_DECL( /, '/', double, short, double)
PK_OPMODEL_OP2e_DECL( /, '/', double, long, double)
PK_OPMODEL_OP2e_DECL( /, '/', double, unsigned, double)
PK_OPMODEL_OP2e_DECL( /, '/', double, float, double)
PK_OPMODEL_OP2e_DECL( /, '/', double, double, double)
PK_OPMODEL_OP2f(/, '/', double, sc_int, double)
PK_OPMODEL_OP2f( /, '/', double, sc_uint, double)


//  sc_in_aug<sc_signed> / type;

PK_OPMODEL_OP2c_DECL( /, '/', sc_signed, int, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_signed, short, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_signed, long, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_signed, unsigned,sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_signed, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2d(/, '/', sc_signed, sc_int, sc_signed)
PK_OPMODEL_OP2d( /, '/', sc_signed, sc_uint, sc_signed)

PK_OPMODEL_OP2e_DECL( /, '/', sc_signed, int, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', sc_signed, short, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', sc_signed, long, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', sc_signed, sc_signed, sc_signed)
PK_OPMODEL_OP2f(/, '/', sc_signed, sc_int, sc_signed)
PK_OPMODEL_OP2f( /, '/', sc_signed, sc_uint, sc_signed)

PK_OPMODEL_OP2g_DECL( /, '/', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2h( /, '/', sc_signed, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( /, '/', sc_signed, sc_biguint, sc_signed)


//  sc_in_aug<sc_unsigned> / type;

PK_OPMODEL_OP2c_DECL( /, '/', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2c_DECL( /, '/', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c_DECL( /, '/', sc_unsigned, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2d(/, '/', sc_unsigned, sc_int, sc_signed)
PK_OPMODEL_OP2d( /, '/', sc_unsigned, sc_uint, sc_unsigned)

PK_OPMODEL_OP2e_DECL( /, '/', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2e_DECL( /, '/', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( /, '/', sc_unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e_DECL( /, '/', sc_unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP2f(/, '/', sc_unsigned, sc_int, sc_signed)
PK_OPMODEL_OP2f( /, '/', sc_unsigned, sc_uint, sc_unsigned)

PK_OPMODEL_OP2h( /, '/', sc_unsigned, sc_bigint, sc_signed)
PK_OPMODEL_OP2h( /, '/', sc_unsigned, sc_biguint, sc_unsigned)


//  sc_in_aug<sc_bigint<n> > / type;

PK_OPMODEL_OP2cc( /, '/', sc_bigint, int, sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_bigint, short, sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_bigint, long, sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_bigint, unsigned,sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_bigint, sc_signed&, sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_bigint, sc_unsigned&, sc_signed)
PK_OPMODEL_OP2dd(/, '/', sc_bigint, sc_int, sc_signed)
PK_OPMODEL_OP2dd( /, '/', sc_bigint, sc_uint, sc_signed)

PK_OPMODEL_OP2ee( /, '/', sc_bigint, int, sc_signed)
PK_OPMODEL_OP2ee( /, '/', sc_bigint, short, sc_signed)
PK_OPMODEL_OP2ee( /, '/', sc_bigint, long, sc_signed)
PK_OPMODEL_OP2ee( /, '/', sc_bigint, unsigned, sc_signed)
PK_OPMODEL_OP2ee( /, '/', sc_bigint, sc_unsigned, sc_signed)
PK_OPMODEL_OP2ee( /, '/', sc_bigint, sc_signed, sc_signed)
PK_OPMODEL_OP2ff(/, '/', sc_bigint, sc_int, sc_signed)
PK_OPMODEL_OP2ff( /, '/', sc_bigint, sc_uint, sc_signed)

PK_OPMODEL_OP2hh( /, '/', sc_bigint, sc_biguint, sc_signed)


//  sc_in_aug<sc_biguint<n> > / type;

PK_OPMODEL_OP2cc( /, '/', sc_biguint, int, sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_biguint, short, sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_biguint, long, sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_biguint, unsigned,sc_unsigned)
PK_OPMODEL_OP2cc( /, '/', sc_biguint, sc_signed&, sc_signed)
PK_OPMODEL_OP2cc( /, '/', sc_biguint, sc_unsigned&, sc_unsigned)
PK_OPMODEL_OP2dd(/, '/', sc_biguint, sc_int, sc_signed)
PK_OPMODEL_OP2dd( /, '/', sc_biguint, sc_uint, sc_unsigned)

PK_OPMODEL_OP2ee( /, '/', sc_biguint, int, sc_signed)
PK_OPMODEL_OP2ee( /, '/', sc_biguint, short, sc_signed)
PK_OPMODEL_OP2ee( /, '/', sc_biguint, long, sc_signed)
PK_OPMODEL_OP2ee( /, '/', sc_biguint, unsigned, sc_unsigned)
PK_OPMODEL_OP2ee( /, '/', sc_biguint, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2ee( /, '/', sc_biguint, sc_signed, sc_signed)
PK_OPMODEL_OP2ff(/, '/', sc_biguint, sc_int, sc_signed)
PK_OPMODEL_OP2ff( /, '/', sc_biguint, sc_uint, sc_unsigned)



#endif

