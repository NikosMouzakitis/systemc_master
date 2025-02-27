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

Overloaded operators for operator-based power models

Some operators are defined here, others in the file pk_model_operators_1.h

*************************************************************************/


#include "PKtool/kernel/pk_settings.h"


#ifdef PK_ENABLE_OPMODELS

#include "systemc.h"
#include "PKtool/utils/pk_report_ids.h"
#include "PKtool/utils/pk_report.h"
#include "PKtool/kernel/power_module_fcs.h"   
#include "PKtool/power_models/pk_model_creator.h"
#include "PKtool/utils/pk_user_macros.h"
#include "PKtool/types_aug/pk_aug_if.h"
#include "PKtool/types_aug/pk_cpptypes_aug.h"
#include "PKtool/types_aug/sc_signal_ports_aug.h"
#include "PKtool/kernel/power_kernel.h"

#undef PK_MODEL_END

#define PK_MODEL_END(name, index)


#ifdef PK_ENABLE_TLM

#undef PK_TLM_MODEL_END

#define PK_TLM_MODEL_END(name, index)

#endif



#include "PKtool/types_aug/pk_bit_types.h"

using pk_dt::sc_bit_aug;
using pk_dt::sc_logic_aug;
using pk_dt::sc_lv_aug;
using pk_dt::sc_bv_aug;




#include "PKtool/types_aug/pk_int_types.h"

using pk_dt::sc_int_aug;
using pk_dt::sc_uint_aug;
using pk_dt::sc_signed_aug;
using pk_dt::sc_unsigned_aug;
using pk_dt::sc_bigint_aug;
using pk_dt::sc_biguint_aug;




#include "PKtool/power_models/pk_model_lib_header.h"
#include "PKtool/power_models/pk_default_lib.h" 

#include "PKtool/power_models/pk_model_operators_1.h"



         

// ADDition operators:  

//  aug_type + aug_type = return type

PK_OPMODEL_OP1a(+, '+', sc_signed, sc_signed) 
PK_OPMODEL_OP1a(+, '+', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP1c( +, '+', int, int)               
PK_OPMODEL_OP1c( +, '+', short, short)           
PK_OPMODEL_OP1c( +, '+', long, long)				
PK_OPMODEL_OP1c( +, '+', unsigned, unsigned)     
PK_OPMODEL_OP1c( +, '+', float, float)           
PK_OPMODEL_OP1c( +, '+', double, double) 


//  int_aug + type = return type

PK_OPMODEL_OP1d(+, '+', int, int, int)
PK_OPMODEL_OP1d(+, '+', int, short, int)
PK_OPMODEL_OP1d(+, '+', int, long, long)
PK_OPMODEL_OP1d(+, '+', int, unsigned, int)
PK_OPMODEL_OP1d(+, '+', int, float, float)
PK_OPMODEL_OP1d(+, '+', int, double, double)
PK_OPMODEL_OP1d(+, '+', int, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(+, '+', int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(+, '+', int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(+, '+', int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(+, '+', int, short, int)
PK_OPMODEL_OP1e1(+, '+', int, long, long)
PK_OPMODEL_OP1e1(+, '+', int, unsigned, int)
PK_OPMODEL_OP1e1(+, '+', int, float, float)
PK_OPMODEL_OP1e1(+, '+', int, double, double)
PK_OPMODEL_OP1e2(+, '+', int, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(+, '+', int, sc_unsigned, sc_signed)


//  short_aug + type = return type

PK_OPMODEL_OP1d(+, '+', short, int, int)
PK_OPMODEL_OP1d(+, '+', short, short, short)
PK_OPMODEL_OP1d(+, '+', short, long, long)
PK_OPMODEL_OP1d(+, '+', short, unsigned, int)
PK_OPMODEL_OP1d(+, '+', short, float, float)
PK_OPMODEL_OP1d(+, '+', short, double, double)
PK_OPMODEL_OP1d(+, '+', short, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(+, '+', short, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(+, '+', short, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(+, '+', short, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(+, '+', short, long, long)
PK_OPMODEL_OP1e1(+, '+', short, unsigned, int)
PK_OPMODEL_OP1e1(+, '+', short, float, float)
PK_OPMODEL_OP1e1(+, '+', short, double, double)
PK_OPMODEL_OP1e2(+, '+', short, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(+, '+', short, sc_unsigned, sc_signed)


//  long_aug + type = return type

PK_OPMODEL_OP1d(+, '+', long, int, long)
PK_OPMODEL_OP1d(+, '+', long, short, long)
PK_OPMODEL_OP1d(+, '+', long, long, long)
PK_OPMODEL_OP1d(+, '+', long, unsigned, long)
PK_OPMODEL_OP1d(+, '+', long, float, float)
PK_OPMODEL_OP1d(+, '+', long, double, double)
PK_OPMODEL_OP1d(+, '+', long, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(+, '+', long, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(+, '+', long, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(+, '+', long, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(+, '+', long, unsigned, long)
PK_OPMODEL_OP1e1(+, '+', long, float, float)
PK_OPMODEL_OP1e1(+, '+', long, double, double)
PK_OPMODEL_OP1e2(+, '+', long, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(+, '+', long, sc_unsigned, sc_signed)


//  unsigned_aug + type = return type

PK_OPMODEL_OP1d(+, '+', unsigned, int, int)
PK_OPMODEL_OP1d(+, '+', unsigned, short, int)
PK_OPMODEL_OP1d(+, '+', unsigned, long, long)
PK_OPMODEL_OP1d(+, '+', unsigned, unsigned, unsigned)
PK_OPMODEL_OP1d(+, '+', unsigned, float, float)
PK_OPMODEL_OP1d(+, '+', unsigned, double, double)
PK_OPMODEL_OP1d(+, '+', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(+, '+', unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1d(+, '+', unsigned, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(+, '+', unsigned, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e1(+, '+', unsigned, float, float)
PK_OPMODEL_OP1e1(+, '+', unsigned, double, double)
PK_OPMODEL_OP1e2(+, '+', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(+, '+', unsigned, sc_unsigned, sc_unsigned)


//  float_aug + type = return type

PK_OPMODEL_OP1d(+, '+', float, int, float)
PK_OPMODEL_OP1d(+, '+', float, short, float)
PK_OPMODEL_OP1d(+, '+', float, long, float)
PK_OPMODEL_OP1d(+, '+', float, unsigned, float)
PK_OPMODEL_OP1d(+, '+', float, float, float)
PK_OPMODEL_OP1d(+, '+', float, double, double)
PK_OPMODEL_OP1d(+, '+', float, sc_int_base&, float)
PK_OPMODEL_OP1d(+, '+', float, sc_uint_base&, float)

PK_OPMODEL_OP1e1(+, '+', float, double, double)


//  double_aug + type = return type

PK_OPMODEL_OP1d(+, '+', double, int, double)
PK_OPMODEL_OP1d(+, '+', double, short, double)
PK_OPMODEL_OP1d(+, '+', double, long, double)
PK_OPMODEL_OP1d(+, '+', double, unsigned, double)
PK_OPMODEL_OP1d(+, '+', double, float, double)
PK_OPMODEL_OP1d(+, '+', double, double, double)
PK_OPMODEL_OP1d(+, '+', double, sc_int_base&, double)
PK_OPMODEL_OP1d(+, '+', double, sc_uint_base&, double)


//  sc_signed_aug + type = return type


PK_OPMODEL_OP1f(+, '+', sc_signed, int, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_signed, long, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_signed, unsigned , sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_signed, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f(+, '+', sc_signed, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_signed, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_signed, int64, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_signed, uint64, sc_signed)


//  sc_unsigned_aug + type = return type

PK_OPMODEL_OP1f(+, '+', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_unsigned, unsigned , sc_unsigned)
PK_OPMODEL_OP1f(+, '+', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1f(+, '+', sc_unsigned, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_unsigned, sc_uint_base&, sc_unsigned)
PK_OPMODEL_OP1f(+, '+', sc_unsigned, int64, sc_signed)
PK_OPMODEL_OP1f(+, '+', sc_unsigned, uint64, sc_unsigned)



// SUBtraction operators:


//  aug_type - aug_type = return type

PK_OPMODEL_OP1a(-, '-', sc_signed, sc_signed) 
PK_OPMODEL_OP1a(-, '-', sc_unsigned, sc_signed)
PK_OPMODEL_OP1c( -, '-', int, int)               
PK_OPMODEL_OP1c( -, '-', short, short)           
PK_OPMODEL_OP1c( -, '-', long, long)				
PK_OPMODEL_OP1c( -, '-', unsigned, signed)     
PK_OPMODEL_OP1c( -, '-', float, float)           
PK_OPMODEL_OP1c( -, '-', double, double) 


//  int_aug - type = return type

PK_OPMODEL_OP1d(-, '-', int, int, int)
PK_OPMODEL_OP1d(-, '-', int, short, int)
PK_OPMODEL_OP1d(-, '-', int, long, long)
PK_OPMODEL_OP1d(-, '-', int, unsigned, int)
PK_OPMODEL_OP1d(-, '-', int, float, float)
PK_OPMODEL_OP1d(-, '-', int, double, double)
PK_OPMODEL_OP1d(-, '-', int, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(-, '-', int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(-, '-', int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(-, '-', int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(-, '-', int, short, int)
PK_OPMODEL_OP1e1(-, '-', int, long, long)
PK_OPMODEL_OP1e1(-, '-', int, unsigned, int)
PK_OPMODEL_OP1e1(-, '-', int, float, float)
PK_OPMODEL_OP1e1(-, '-', int, double, double)
PK_OPMODEL_OP1e2(-, '-', int, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(-, '-', int, sc_unsigned, sc_signed)


//  short_aug - type = return type

PK_OPMODEL_OP1d(-, '-', short, int, int)
PK_OPMODEL_OP1d(-, '-', short, short, short)
PK_OPMODEL_OP1d(-, '-', short, long, long)
PK_OPMODEL_OP1d(-, '-', short, unsigned, int)
PK_OPMODEL_OP1d(-, '-', short, float, float)
PK_OPMODEL_OP1d(-, '-', short, double, double)
PK_OPMODEL_OP1d(-, '-', short, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(-, '-', short, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(-, '-', short, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(-, '-', short, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(-, '-', short, long, long)
PK_OPMODEL_OP1e1(-, '-', short, unsigned, int)
PK_OPMODEL_OP1e1(-, '-', short, float, float)
PK_OPMODEL_OP1e1(-, '-', short, double, double)
PK_OPMODEL_OP1e2(-, '-', short, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(-, '-', short, sc_unsigned, sc_signed)


//  long_aug - type = return type

PK_OPMODEL_OP1d(-, '-', long, int, long)
PK_OPMODEL_OP1d(-, '-', long, short, long)
PK_OPMODEL_OP1d(-, '-', long, long, long)
PK_OPMODEL_OP1d(-, '-', long, unsigned, long)
PK_OPMODEL_OP1d(-, '-', long, float, float)
PK_OPMODEL_OP1d(-, '-', long, double, double)
PK_OPMODEL_OP1d(-, '-', long, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(-, '-', long, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(-, '-', long, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(-, '-', long, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(-, '-', long, unsigned, long)
PK_OPMODEL_OP1e1(-, '-', long, float, float)
PK_OPMODEL_OP1e1(-, '-', long, double, double)
PK_OPMODEL_OP1e2(-, '-', long, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(-, '-', long, sc_unsigned, sc_signed)


//  unsigned_aug - type = return type

PK_OPMODEL_OP1d(-, '-', unsigned, int, int)
PK_OPMODEL_OP1d(-, '-', unsigned, short, int)
PK_OPMODEL_OP1d(-, '-', unsigned, long, long)
PK_OPMODEL_OP1d(-, '-', unsigned, unsigned, signed)
PK_OPMODEL_OP1d(-, '-', unsigned, float, float)
PK_OPMODEL_OP1d(-, '-', unsigned, double, double)
PK_OPMODEL_OP1d(-, '-', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(-, '-', unsigned, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(-, '-', unsigned, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(-, '-', unsigned, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(-, '-', unsigned, float, float)
PK_OPMODEL_OP1e1(-, '-', unsigned, double, double)
PK_OPMODEL_OP1e2(-, '-', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(-, '-', unsigned, sc_unsigned, sc_signed)


//  float_aug - type = return type

PK_OPMODEL_OP1d(-, '-', float, int, float)
PK_OPMODEL_OP1d(-, '-', float, short, float)
PK_OPMODEL_OP1d(-, '-', float, long, float)
PK_OPMODEL_OP1d(-, '-', float, unsigned, float)
PK_OPMODEL_OP1d(-, '-', float, float, float)
PK_OPMODEL_OP1d(-, '-', float, double, double)
PK_OPMODEL_OP1d(-, '-', float, sc_int_base&, float)
PK_OPMODEL_OP1d(-, '-', float, sc_uint_base&, float)

PK_OPMODEL_OP1e1(-, '-', float, double, double)


//  double_aug - type = return type

PK_OPMODEL_OP1d(-, '-', double, int, double)
PK_OPMODEL_OP1d(-, '-', double, short, double)
PK_OPMODEL_OP1d(-, '-', double, long, double)
PK_OPMODEL_OP1d(-, '-', double, unsigned, double)
PK_OPMODEL_OP1d(-, '-', double, float, double)
PK_OPMODEL_OP1d(-, '-', double, double, double)
PK_OPMODEL_OP1d(-, '-', double, sc_int_base&, double)
PK_OPMODEL_OP1d(-, '-', double, sc_uint_base&, double)


//  sc_signed_aug - type = return type

PK_OPMODEL_OP1f(-, '-', sc_signed, int, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_signed, long, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_signed, unsigned , sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_signed, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f(-, '-', sc_signed, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_signed, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_signed, int64, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_signed, uint64, sc_signed)


//  sc_unsigned_aug - type = return type

PK_OPMODEL_OP1f(-, '-', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_unsigned, unsigned , sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_unsigned, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f(-, '-', sc_unsigned, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_unsigned, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_unsigned, int64, sc_signed)
PK_OPMODEL_OP1f(-, '-', sc_unsigned, uint64, sc_unsigned)




// MULtiplication operators:

//  aug_type * aug_type = return type

PK_OPMODEL_OP1a(*, '*', sc_signed, sc_signed) 
PK_OPMODEL_OP1a(*, '*', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP1c( *, '*', int, int)               
PK_OPMODEL_OP1c( *, '*', short, short)           
PK_OPMODEL_OP1c( *, '*', long, long)				
PK_OPMODEL_OP1c( *, '*', unsigned, unsigned)     
PK_OPMODEL_OP1c( *, '*', float, float)           
PK_OPMODEL_OP1c( *, '*', double, double) 


//  int_aug * type = return type

PK_OPMODEL_OP1d(*, '*', int, int, int)
PK_OPMODEL_OP1d(*, '*', int, short, int)
PK_OPMODEL_OP1d(*, '*', int, long, long)
PK_OPMODEL_OP1d(*, '*', int, unsigned, int)
PK_OPMODEL_OP1d(*, '*', int, float, float)
PK_OPMODEL_OP1d(*, '*', int, double, double)
PK_OPMODEL_OP1d(*, '*', int, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(*, '*', int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(*, '*', int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(*, '*', int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(*, '*', int, short, int)
PK_OPMODEL_OP1e1(*, '*', int, long, long)
PK_OPMODEL_OP1e1(*, '*', int, unsigned, int)
PK_OPMODEL_OP1e1(*, '*', int, float, float)
PK_OPMODEL_OP1e1(*, '*', int, double, double)
PK_OPMODEL_OP1e2(*, '*', int, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(*, '*', int, sc_unsigned, sc_signed)


//  short_aug * type = return type

PK_OPMODEL_OP1d(*, '*', short, int, int)
PK_OPMODEL_OP1d(*, '*', short, short, short)
PK_OPMODEL_OP1d(*, '*', short, long, long)
PK_OPMODEL_OP1d(*, '*', short, unsigned, int)
PK_OPMODEL_OP1d(*, '*', short, float, float)
PK_OPMODEL_OP1d(*, '*', short, double, double)
PK_OPMODEL_OP1d(*, '*', short, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(*, '*', short, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(*, '*', short, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(*, '*', short, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(*, '*', short, long, long)
PK_OPMODEL_OP1e1(*, '*', short, unsigned, int)
PK_OPMODEL_OP1e1(*, '*', short, float, float)
PK_OPMODEL_OP1e1(*, '*', short, double, double)
PK_OPMODEL_OP1e2(*, '*', short, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(*, '*', short, sc_unsigned, sc_signed)


//  long_aug * type = return type

PK_OPMODEL_OP1d(*, '*', long, int, long)
PK_OPMODEL_OP1d(*, '*', long, short, long)
PK_OPMODEL_OP1d(*, '*', long, long, long)
PK_OPMODEL_OP1d(*, '*', long, unsigned, long)
PK_OPMODEL_OP1d(*, '*', long, float, float)
PK_OPMODEL_OP1d(*, '*', long, double, double)
PK_OPMODEL_OP1d(*, '*', long, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(*, '*', long, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(*, '*', long, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(*, '*', long, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(*, '*', long, unsigned, long)
PK_OPMODEL_OP1e1(*, '*', long, float, float)
PK_OPMODEL_OP1e1(*, '*', long, double, double)
PK_OPMODEL_OP1e2(*, '*', long, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(*, '*', long, sc_unsigned, sc_signed)


//  unsigned_aug * type = return type

PK_OPMODEL_OP1d(*, '*', unsigned, int, int)
PK_OPMODEL_OP1d(*, '*', unsigned, short, int)
PK_OPMODEL_OP1d(*, '*', unsigned, long, long)
PK_OPMODEL_OP1d(*, '*', unsigned, unsigned, unsigned)
PK_OPMODEL_OP1d(*, '*', unsigned, float, float)
PK_OPMODEL_OP1d(*, '*', unsigned, double, double)
PK_OPMODEL_OP1d(*, '*', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(*, '*', unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1d(*, '*', unsigned, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(*, '*', unsigned, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e1(*, '*', unsigned, float, float)
PK_OPMODEL_OP1e1(*, '*', unsigned, double, double)
PK_OPMODEL_OP1e2(*, '*', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(*, '*', unsigned, sc_unsigned, sc_unsigned)


//  float_aug * type = return type

PK_OPMODEL_OP1d(*, '*', float, int, float)
PK_OPMODEL_OP1d(*, '*', float, short, float)
PK_OPMODEL_OP1d(*, '*', float, long, float)
PK_OPMODEL_OP1d(*, '*', float, unsigned, float)
PK_OPMODEL_OP1d(*, '*', float, float, float)
PK_OPMODEL_OP1d(*, '*', float, double, double)
PK_OPMODEL_OP1d(*, '*', float, sc_int_base&, float)
PK_OPMODEL_OP1d(*, '*', float, sc_uint_base&, float)

PK_OPMODEL_OP1e1(*, '*', float, double, double)


//  double_aug * type = return type

PK_OPMODEL_OP1d(*, '*', double, int, double)
PK_OPMODEL_OP1d(*, '*', double, short, double)
PK_OPMODEL_OP1d(*, '*', double, long, double)
PK_OPMODEL_OP1d(*, '*', double, unsigned, double)
PK_OPMODEL_OP1d(*, '*', double, float, double)
PK_OPMODEL_OP1d(*, '*', double, double, double)
PK_OPMODEL_OP1d(*, '*', double, sc_int_base&, double)
PK_OPMODEL_OP1d(*, '*', double, sc_uint_base&, double)


//  sc_signed_aug * type = return type

PK_OPMODEL_OP1f(*, '*', sc_signed, int, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_signed, long, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_signed, unsigned , sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_signed, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f(*, '*', sc_signed, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_signed, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_signed, int64, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_signed, uint64, sc_signed)


//  sc_unsigned_aug * type = return type

PK_OPMODEL_OP1f(*, '*', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_unsigned, unsigned , sc_unsigned)
PK_OPMODEL_OP1f(*, '*', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1f(*, '*', sc_unsigned, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_unsigned, sc_uint_base&, sc_unsigned)
PK_OPMODEL_OP1f(*, '*', sc_unsigned, int64, sc_signed)
PK_OPMODEL_OP1f(*, '*', sc_unsigned, uint64, sc_unsigned)



// DIVision operators:

//  aug_type / aug_type = return type

PK_OPMODEL_OP1a(/, '/', sc_signed, sc_signed) 
PK_OPMODEL_OP1a(/, '/', sc_unsigned, sc_unsigned)
PK_OPMODEL_OP1c( /, '/', int, int)               
PK_OPMODEL_OP1c( /, '/', short, short)           
PK_OPMODEL_OP1c( /, '/', long, long)				
PK_OPMODEL_OP1c( /, '/', unsigned, unsigned)     
PK_OPMODEL_OP1c( /, '/', float, float)           
PK_OPMODEL_OP1c( /, '/', double, double) 


//  int_aug / type = return type

PK_OPMODEL_OP1d(/, '/', int, int, int)
PK_OPMODEL_OP1d(/, '/', int, short, int)
PK_OPMODEL_OP1d(/, '/', int, long, long)
PK_OPMODEL_OP1d(/, '/', int, unsigned, int)
PK_OPMODEL_OP1d(/, '/', int, float, float)
PK_OPMODEL_OP1d(/, '/', int, double, double)
PK_OPMODEL_OP1d(/, '/', int, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(/, '/', int, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(/, '/', int, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(/, '/', int, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(/, '/', int, short, int)
PK_OPMODEL_OP1e1(/, '/', int, long, long)
PK_OPMODEL_OP1e1(/, '/', int, unsigned, int)
PK_OPMODEL_OP1e1(/, '/', int, float, float)
PK_OPMODEL_OP1e1(/, '/', int, double, double)
PK_OPMODEL_OP1e2(/, '/', int, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(/, '/', int, sc_unsigned, sc_signed)


//  short_aug / type = return type

PK_OPMODEL_OP1d(/, '/', short, int, int)
PK_OPMODEL_OP1d(/, '/', short, short, short)
PK_OPMODEL_OP1d(/, '/', short, long, long)
PK_OPMODEL_OP1d(/, '/', short, unsigned, int)
PK_OPMODEL_OP1d(/, '/', short, float, float)
PK_OPMODEL_OP1d(/, '/', short, double, double)
PK_OPMODEL_OP1d(/, '/', short, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(/, '/', short, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(/, '/', short, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(/, '/', short, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(/, '/', short, long, long)
PK_OPMODEL_OP1e1(/, '/', short, unsigned, int)
PK_OPMODEL_OP1e1(/, '/', short, float, float)
PK_OPMODEL_OP1e1(/, '/', short, double, double)
PK_OPMODEL_OP1e2(/, '/', short, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(/, '/', short, sc_unsigned, sc_signed)


//  long_aug / type = return type

PK_OPMODEL_OP1d(/, '/', long, int, long)
PK_OPMODEL_OP1d(/, '/', long, short, long)
PK_OPMODEL_OP1d(/, '/', long, long, long)
PK_OPMODEL_OP1d(/, '/', long, unsigned, long)
PK_OPMODEL_OP1d(/, '/', long, float, float)
PK_OPMODEL_OP1d(/, '/', long, double, double)
PK_OPMODEL_OP1d(/, '/', long, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(/, '/', long, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1d(/, '/', long, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(/, '/', long, sc_uint_base&, sc_dt::int_type)

PK_OPMODEL_OP1e1(/, '/', long, unsigned, long)
PK_OPMODEL_OP1e1(/, '/', long, float, float)
PK_OPMODEL_OP1e1(/, '/', long, double, double)
PK_OPMODEL_OP1e2(/, '/', long, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(/, '/', long, sc_unsigned, sc_signed)


//  unsigned_aug / type = return type

PK_OPMODEL_OP1d(/, '/', unsigned, int, int)
PK_OPMODEL_OP1d(/, '/', unsigned, short, int)
PK_OPMODEL_OP1d(/, '/', unsigned, long, long)
PK_OPMODEL_OP1d(/, '/', unsigned, unsigned, unsigned)
PK_OPMODEL_OP1d(/, '/', unsigned, float, float)
PK_OPMODEL_OP1d(/, '/', unsigned, double, double)
PK_OPMODEL_OP1d(/, '/', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1d(/, '/', unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1d(/, '/', unsigned, sc_int_base&, sc_dt::int_type)
PK_OPMODEL_OP1d(/, '/', unsigned, sc_uint_base&, sc_dt::uint_type)

PK_OPMODEL_OP1e1(/, '/', unsigned, float, float)
PK_OPMODEL_OP1e1(/, '/', unsigned, double, double)
PK_OPMODEL_OP1e2(/, '/', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP1e2(/, '/', unsigned, sc_unsigned, sc_unsigned)


//  float_aug / type = return type

PK_OPMODEL_OP1d(/, '/', float, int, float)
PK_OPMODEL_OP1d(/, '/', float, short, float)
PK_OPMODEL_OP1d(/, '/', float, long, float)
PK_OPMODEL_OP1d(/, '/', float, unsigned, float)
PK_OPMODEL_OP1d(/, '/', float, float, float)
PK_OPMODEL_OP1d(/, '/', float, double, double)
PK_OPMODEL_OP1d(/, '/', float, sc_int_base&, float)
PK_OPMODEL_OP1d(/, '/', float, sc_uint_base&, float)

PK_OPMODEL_OP1e1(/, '/', float, double, double)


//  double_aug / type = return type

PK_OPMODEL_OP1d(/, '/', double, int, double)
PK_OPMODEL_OP1d(/, '/', double, short, double)
PK_OPMODEL_OP1d(/, '/', double, long, double)
PK_OPMODEL_OP1d(/, '/', double, unsigned, double)
PK_OPMODEL_OP1d(/, '/', double, float, double)
PK_OPMODEL_OP1d(/, '/', double, double, double)
PK_OPMODEL_OP1d(/, '/', double, sc_int_base&, double)
PK_OPMODEL_OP1d(/, '/', double, sc_uint_base&, double)


//  sc_signed_aug / type = return type


PK_OPMODEL_OP1f(/, '/', sc_signed, int, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_signed, long, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_signed, unsigned , sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_signed, sc_unsigned&, sc_signed) 
PK_OPMODEL_OP1f(/, '/', sc_signed, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_signed, sc_uint_base&, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_signed, int64, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_signed, uint64, sc_signed)


//  sc_unsigned_aug / type = return type

PK_OPMODEL_OP1f(/, '/', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_unsigned, unsigned , sc_unsigned)
PK_OPMODEL_OP1f(/, '/', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_unsigned, sc_unsigned&, sc_unsigned) 
PK_OPMODEL_OP1f(/, '/', sc_unsigned, sc_int_base&, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_unsigned, sc_uint_base&, sc_unsigned)
PK_OPMODEL_OP1f(/, '/', sc_unsigned, int64, sc_signed)
PK_OPMODEL_OP1f(/, '/', sc_unsigned, uint64, sc_unsigned)




#endif

