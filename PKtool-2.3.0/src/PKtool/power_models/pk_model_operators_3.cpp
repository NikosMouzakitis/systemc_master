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

Some operators are defined here, others in the file pk_model_operators_3.h

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



#include "PKtool/types_aug/pk_int_types.h"

using pk_dt::sc_int_aug;
using pk_dt::sc_uint_aug;
using pk_dt::sc_signed_aug;
using pk_dt::sc_unsigned_aug;
using pk_dt::sc_bigint_aug;
using pk_dt::sc_biguint_aug;


#include "PKtool/power_models/pk_model_lib_header.h"
#include "PKtool/power_models/pk_default_lib.h" 


#include "PKtool/power_models/pk_model_operators_3.h"

int pk_lnk3 = 0; 


// ADDition operators:


//  sc_in_aug<type>.read() + sc_in_aug<type>.read()

PK_OPMODEL_OP3a(+, '+', int, int)
PK_OPMODEL_OP3a(+, '+', short, short)
PK_OPMODEL_OP3a(+, '+', long, long)
PK_OPMODEL_OP3a(+, '+', float, float)
PK_OPMODEL_OP3a(+, '+', double, double)
PK_OPMODEL_OP3a(+, '+', unsigned, int)
PK_OPMODEL_OP3a(+, '+', sc_signed, sc_signed)
PK_OPMODEL_OP3a(+, '+', sc_unsigned, sc_unsigned)


//  sc_in_aug<int>.read() + type

PK_OPMODEL_OP3c(+, '+', int, int, int) 
PK_OPMODEL_OP3c(+, '+', int, short, int)
PK_OPMODEL_OP3c(+, '+', int, long, long)
PK_OPMODEL_OP3c(+, '+', int, unsigned, int)
PK_OPMODEL_OP3c(+, '+', int, float, float)
PK_OPMODEL_OP3c(+, '+', int, double, double)
PK_OPMODEL_OP3c(+, '+', int, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(+, '+', int, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(+, '+', int, int, int)
PK_OPMODEL_OP3e(+, '+', int, short, int)
PK_OPMODEL_OP3e(+, '+', int, long, long)
PK_OPMODEL_OP3e(+, '+', int, unsigned, int)
PK_OPMODEL_OP3e(+, '+', int, float, float)
PK_OPMODEL_OP3e(+, '+', int, double, double)
PK_OPMODEL_OP3f(+, '+', int, sc_signed, sc_signed)
PK_OPMODEL_OP3f(+, '+', int, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(+, '+', int, short, int)
PK_OPMODEL_OP3h(+, '+', int, long, long)
PK_OPMODEL_OP3h(+, '+', int, unsigned, int)
PK_OPMODEL_OP3h(+, '+', int, float, float)
PK_OPMODEL_OP3h(+, '+', int, double, double)
PK_OPMODEL_OP3h(+, '+', int, sc_signed, sc_signed)
PK_OPMODEL_OP3h(+, '+', int, sc_unsigned, sc_signed)


//  sc_in_aug<short>.read() + type

PK_OPMODEL_OP3c(+, '+', short, int, int) 
PK_OPMODEL_OP3c(+, '+', short, short, short)
PK_OPMODEL_OP3c(+, '+', short, long, long)
PK_OPMODEL_OP3c(+, '+', short, unsigned, int)
PK_OPMODEL_OP3c(+, '+', short, float, float)
PK_OPMODEL_OP3c(+, '+', short, double, double)
PK_OPMODEL_OP3c(+, '+', short, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(+, '+', short, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(+, '+', short, int, int)
PK_OPMODEL_OP3e(+, '+', short, short, short)
PK_OPMODEL_OP3e(+, '+', short, long, long)
PK_OPMODEL_OP3e(+, '+', short, unsigned, int)
PK_OPMODEL_OP3e(+, '+', short, float, float)
PK_OPMODEL_OP3e(+, '+', short, double, double)
PK_OPMODEL_OP3f(+, '+', short, sc_signed, sc_signed)
PK_OPMODEL_OP3f(+, '+', short, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(+, '+', short, long, long)
PK_OPMODEL_OP3h(+, '+', short, unsigned, int)
PK_OPMODEL_OP3h(+, '+', short, float, float)
PK_OPMODEL_OP3h(+, '+', short, double, double)
PK_OPMODEL_OP3h(+, '+', short, sc_signed, sc_signed)
PK_OPMODEL_OP3h(+, '+', short, sc_unsigned, sc_unsigned)


//  sc_in_aug<long>.read() + type

PK_OPMODEL_OP3c(+, '+', long, int, long) 
PK_OPMODEL_OP3c(+, '+', long, short, long)
PK_OPMODEL_OP3c(+, '+', long, long, long)
PK_OPMODEL_OP3c(+, '+', long, unsigned, long)
PK_OPMODEL_OP3c(+, '+', long, float, float)
PK_OPMODEL_OP3c(+, '+', long, double, double)
PK_OPMODEL_OP3c(+, '+', long, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(+, '+', long, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(+, '+', long, int, long)
PK_OPMODEL_OP3e(+, '+', long, short, long)
PK_OPMODEL_OP3e(+, '+', long, long, long)
PK_OPMODEL_OP3e(+, '+', long, unsigned, long)
PK_OPMODEL_OP3e(+, '+', long, float, float)
PK_OPMODEL_OP3e(+, '+', long, double, double)
PK_OPMODEL_OP3f(+, '+', long, sc_signed, sc_signed)
PK_OPMODEL_OP3f(+, '+', long, sc_unsigned, sc_signed)


PK_OPMODEL_OP3h(+, '+', long, unsigned, long)
PK_OPMODEL_OP3h(+, '+', long, float, float)
PK_OPMODEL_OP3h(+, '+', long, double, double)
PK_OPMODEL_OP3h(+, '+', long, sc_signed, sc_signed)
PK_OPMODEL_OP3h(+, '+', long, sc_unsigned, sc_signed)


//  sc_in_aug<unsigned>.read() + type

PK_OPMODEL_OP3c(+, '+', unsigned, int, int) 
PK_OPMODEL_OP3c(+, '+', unsigned, short, int)
PK_OPMODEL_OP3c(+, '+', unsigned, long, long)
PK_OPMODEL_OP3c(+, '+', unsigned, unsigned, unsigned)
PK_OPMODEL_OP3c(+, '+', unsigned, float, float)
PK_OPMODEL_OP3c(+, '+', unsigned, double, double)
PK_OPMODEL_OP3c(+, '+', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(+, '+', unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP3e(+, '+', unsigned, int, int)
PK_OPMODEL_OP3e(+, '+', unsigned, short, int)
PK_OPMODEL_OP3e(+, '+', unsigned, long, long)
PK_OPMODEL_OP3e(+, '+', unsigned, unsigned, unsigned)
PK_OPMODEL_OP3e(+, '+', unsigned, float, float)
PK_OPMODEL_OP3e(+, '+', unsigned, double, double)
PK_OPMODEL_OP3f(+, '+', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3f(+, '+', unsigned, sc_unsigned, sc_unsigned)



PK_OPMODEL_OP3h(+, '+', unsigned, float, float)
PK_OPMODEL_OP3h(+, '+', unsigned, double, double)
PK_OPMODEL_OP3h(+, '+', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3h(+, '+', unsigned, sc_unsigned, sc_unsigned)


//  sc_in_aug<float>.read() + type

PK_OPMODEL_OP3c(+, '+', float, int, float) 
PK_OPMODEL_OP3c(+, '+', float, short, float)
PK_OPMODEL_OP3c(+, '+', float, long, float)
PK_OPMODEL_OP3c(+, '+', float, unsigned, float)
PK_OPMODEL_OP3c(+, '+', float, float, float)
PK_OPMODEL_OP3c(+, '+', float, double, double)

PK_OPMODEL_OP3e(+, '+', float, int, float)
PK_OPMODEL_OP3e(+, '+', float, short, float)
PK_OPMODEL_OP3e(+, '+', float, long, float)
PK_OPMODEL_OP3e(+, '+', float, unsigned, float)
PK_OPMODEL_OP3e(+, '+', float, float, float)
PK_OPMODEL_OP3e(+, '+', float, double, double)

PK_OPMODEL_OP3h(+, '+', float, double, double)


//  sc_in_aug<double>.read() + type

PK_OPMODEL_OP3c(+, '+', double, int, double) 
PK_OPMODEL_OP3c(+, '+', double, short, double)
PK_OPMODEL_OP3c(+, '+', double, long, double)
PK_OPMODEL_OP3c(+, '+', double, unsigned, double)
PK_OPMODEL_OP3c(+, '+', double, float, double)
PK_OPMODEL_OP3c(+, '+', double, double, double)

PK_OPMODEL_OP3e(+, '+', double, int, double)
PK_OPMODEL_OP3e(+, '+', double, short, double)
PK_OPMODEL_OP3e(+, '+', double, long, double)
PK_OPMODEL_OP3e(+, '+', double, unsigned, double)
PK_OPMODEL_OP3e(+, '+', double, float, double)
PK_OPMODEL_OP3e(+, '+', double, double, double)


//  sc_in_aug<sc_signed>.read() + type

PK_OPMODEL_OP3c(+, '+', sc_signed, int, sc_signed) 
PK_OPMODEL_OP3c(+, '+', sc_signed, short, sc_signed)
PK_OPMODEL_OP3c(+, '+', sc_signed, long, sc_signed)
PK_OPMODEL_OP3c(+, '+', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP3c(+, '+', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(+, '+', sc_signed, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(+, '+', sc_signed, int, sc_signed)
PK_OPMODEL_OP3e(+, '+', sc_signed, short, sc_signed)
PK_OPMODEL_OP3e(+, '+', sc_signed, long, sc_signed)
PK_OPMODEL_OP3e(+, '+', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP3f(+, '+', sc_signed, sc_signed, sc_signed)
PK_OPMODEL_OP3f(+, '+', sc_signed, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(+, '+', sc_signed, sc_unsigned, sc_signed)


//  sc_in_aug<sc_unsigned>.read() + type

PK_OPMODEL_OP3c(+, '+', sc_unsigned, int, sc_signed) 
PK_OPMODEL_OP3c(+, '+', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP3c(+, '+', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP3c(+, '+', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP3c(+, '+', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(+, '+', sc_unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP3e(+, '+', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP3e(+, '+', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP3e(+, '+', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP3e(+, '+', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP3f(+, '+', sc_unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3f(+, '+', sc_unsigned, sc_unsigned, sc_unsigned)



// SUBtraction operators:


//  sc_in_aug<type>.read() - sc_in_aug<type>.read()

PK_OPMODEL_OP3a(-, '-', int, int)
PK_OPMODEL_OP3a(-, '-', short, short)
PK_OPMODEL_OP3a(-, '-', long, long)
PK_OPMODEL_OP3a(-, '-', float, float)
PK_OPMODEL_OP3a(-, '-', double, double)
PK_OPMODEL_OP3a(-, '-', unsigned, int)
PK_OPMODEL_OP3a(-, '-', sc_signed, sc_signed)
PK_OPMODEL_OP3a(-, '-', sc_unsigned, sc_signed)


//  sc_in_aug<int>.read() - type

PK_OPMODEL_OP3c(-, '-', int, int, int) 
PK_OPMODEL_OP3c(-, '-', int, short, int)
PK_OPMODEL_OP3c(-, '-', int, long, long)
PK_OPMODEL_OP3c(-, '-', int, unsigned, int)
PK_OPMODEL_OP3c(-, '-', int, float, float)
PK_OPMODEL_OP3c(-, '-', int, double, double)
PK_OPMODEL_OP3c(-, '-', int, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(-, '-', int, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(-, '-', int, int, int)
PK_OPMODEL_OP3e(-, '-', int, short, int)
PK_OPMODEL_OP3e(-, '-', int, long, long)
PK_OPMODEL_OP3e(-, '-', int, unsigned, int)
PK_OPMODEL_OP3e(-, '-', int, float, float)
PK_OPMODEL_OP3e(-, '-', int, double, double)
PK_OPMODEL_OP3f(-, '-', int, sc_signed, sc_signed)
PK_OPMODEL_OP3f(-, '-', int, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(-, '-', int, short, int)
PK_OPMODEL_OP3h(-, '-', int, long, long)
PK_OPMODEL_OP3h(-, '-', int, unsigned, int)
PK_OPMODEL_OP3h(-, '-', int, float, float)
PK_OPMODEL_OP3h(-, '-', int, double, double)
PK_OPMODEL_OP3h(-, '-', int, sc_signed, sc_signed)
PK_OPMODEL_OP3h(-, '-', int, sc_unsigned, sc_signed)


//  sc_in_aug<short>.read() - type

PK_OPMODEL_OP3c(-, '-', short, int, int) 
PK_OPMODEL_OP3c(-, '-', short, short, short)
PK_OPMODEL_OP3c(-, '-', short, long, long)
PK_OPMODEL_OP3c(-, '-', short, unsigned, int)
PK_OPMODEL_OP3c(-, '-', short, float, float)
PK_OPMODEL_OP3c(-, '-', short, double, double)
PK_OPMODEL_OP3c(-, '-', short, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(-, '-', short, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(-, '-', short, int, int)
PK_OPMODEL_OP3e(-, '-', short, short, short)
PK_OPMODEL_OP3e(-, '-', short, long, long)
PK_OPMODEL_OP3e(-, '-', short, unsigned, int)
PK_OPMODEL_OP3e(-, '-', short, float, float)
PK_OPMODEL_OP3e(-, '-', short, double, double)
PK_OPMODEL_OP3f(-, '-', short, sc_signed, sc_signed)
PK_OPMODEL_OP3f(-, '-', short, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(-, '-', short, long, long)
PK_OPMODEL_OP3h(-, '-', short, unsigned, int)
PK_OPMODEL_OP3h(-, '-', short, float, float)
PK_OPMODEL_OP3h(-, '-', short, double, double)
PK_OPMODEL_OP3h(-, '-', short, sc_signed, sc_signed)
PK_OPMODEL_OP3h(-, '-', short, sc_unsigned, sc_unsigned)


//  sc_in_aug<long>.read() - type

PK_OPMODEL_OP3c(-, '-', long, int, long) 
PK_OPMODEL_OP3c(-, '-', long, short, long)
PK_OPMODEL_OP3c(-, '-', long, long, long)
PK_OPMODEL_OP3c(-, '-', long, unsigned, long)
PK_OPMODEL_OP3c(-, '-', long, float, float)
PK_OPMODEL_OP3c(-, '-', long, double, double)
PK_OPMODEL_OP3c(-, '-', long, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(-, '-', long, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(-, '-', long, int, long)
PK_OPMODEL_OP3e(-, '-', long, short, long)
PK_OPMODEL_OP3e(-, '-', long, long, long)
PK_OPMODEL_OP3e(-, '-', long, unsigned, long)
PK_OPMODEL_OP3e(-, '-', long, float, float)
PK_OPMODEL_OP3e(-, '-', long, double, double)
PK_OPMODEL_OP3f(-, '-', long, sc_signed, sc_signed)
PK_OPMODEL_OP3f(-, '-', long, sc_unsigned, sc_signed)


PK_OPMODEL_OP3h(-, '-', long, unsigned, long)
PK_OPMODEL_OP3h(-, '-', long, float, float)
PK_OPMODEL_OP3h(-, '-', long, double, double)
PK_OPMODEL_OP3h(-, '-', long, sc_signed, sc_signed)
PK_OPMODEL_OP3h(-, '-', long, sc_unsigned, sc_signed)


//  sc_in_aug<unsigned>.read() - type

PK_OPMODEL_OP3c(-, '-', unsigned, int, int) 
PK_OPMODEL_OP3c(-, '-', unsigned, short, int)
PK_OPMODEL_OP3c(-, '-', unsigned, long, long)
PK_OPMODEL_OP3c(-, '-', unsigned, unsigned, int)
PK_OPMODEL_OP3c(-, '-', unsigned, float, float)
PK_OPMODEL_OP3c(-, '-', unsigned, double, double)
PK_OPMODEL_OP3c(-, '-', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(-, '-', unsigned, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(-, '-', unsigned, int, int)
PK_OPMODEL_OP3e(-, '-', unsigned, short, int)
PK_OPMODEL_OP3e(-, '-', unsigned, long, long)
PK_OPMODEL_OP3e(-, '-', unsigned, unsigned, int)
PK_OPMODEL_OP3e(-, '-', unsigned, float, float)
PK_OPMODEL_OP3e(-, '-', unsigned, double, double)
PK_OPMODEL_OP3f(-, '-', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3f(-, '-', unsigned, sc_unsigned, sc_signed)



PK_OPMODEL_OP3h(-, '-', unsigned, float, float)
PK_OPMODEL_OP3h(-, '-', unsigned, double, double)
PK_OPMODEL_OP3h(-, '-', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3h(-, '-', unsigned, sc_unsigned, sc_signed)


//  sc_in_aug<float>.read() - type

PK_OPMODEL_OP3c(-, '-', float, int, float) 
PK_OPMODEL_OP3c(-, '-', float, short, float)
PK_OPMODEL_OP3c(-, '-', float, long, float)
PK_OPMODEL_OP3c(-, '-', float, unsigned, float)
PK_OPMODEL_OP3c(-, '-', float, float, float)
PK_OPMODEL_OP3c(-, '-', float, double, double)

PK_OPMODEL_OP3e(-, '-', float, int, float)
PK_OPMODEL_OP3e(-, '-', float, short, float)
PK_OPMODEL_OP3e(-, '-', float, long, float)
PK_OPMODEL_OP3e(-, '-', float, unsigned, float)
PK_OPMODEL_OP3e(-, '-', float, float, float)
PK_OPMODEL_OP3e(-, '-', float, double, double)

PK_OPMODEL_OP3h(-, '-', float, double, double)


//  sc_in_aug<double>.read() - type

PK_OPMODEL_OP3c(-, '-', double, int, double) 
PK_OPMODEL_OP3c(-, '-', double, short, double)
PK_OPMODEL_OP3c(-, '-', double, long, double)
PK_OPMODEL_OP3c(-, '-', double, unsigned, double)
PK_OPMODEL_OP3c(-, '-', double, float, double)
PK_OPMODEL_OP3c(-, '-', double, double, double)

PK_OPMODEL_OP3e(-, '-', double, int, double)
PK_OPMODEL_OP3e(-, '-', double, short, double)
PK_OPMODEL_OP3e(-, '-', double, long, double)
PK_OPMODEL_OP3e(-, '-', double, unsigned, double)
PK_OPMODEL_OP3e(-, '-', double, float, double)
PK_OPMODEL_OP3e(-, '-', double, double, double)


//  sc_in_aug<sc_signed>.read() - type

PK_OPMODEL_OP3c(-, '-', sc_signed, int, sc_signed) 
PK_OPMODEL_OP3c(-, '-', sc_signed, short, sc_signed)
PK_OPMODEL_OP3c(-, '-', sc_signed, long, sc_signed)
PK_OPMODEL_OP3c(-, '-', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP3c(-, '-', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(-, '-', sc_signed, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(-, '-', sc_signed, int, sc_signed)
PK_OPMODEL_OP3e(-, '-', sc_signed, short, sc_signed)
PK_OPMODEL_OP3e(-, '-', sc_signed, long, sc_signed)
PK_OPMODEL_OP3e(-, '-', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP3f(-, '-', sc_signed, sc_signed, sc_signed)
PK_OPMODEL_OP3f(-, '-', sc_signed, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(-, '-', sc_signed, sc_unsigned, sc_signed)


//  sc_in_aug<sc_unsigned>.read() - type

PK_OPMODEL_OP3c(-, '-', sc_unsigned, int, sc_signed) 
PK_OPMODEL_OP3c(-, '-', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP3c(-, '-', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP3c(-, '-', sc_unsigned, unsigned, sc_signed)
PK_OPMODEL_OP3c(-, '-', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(-, '-', sc_unsigned, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(-, '-', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP3e(-, '-', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP3e(-, '-', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP3e(-, '-', sc_unsigned, unsigned, sc_signed)
PK_OPMODEL_OP3f(-, '-', sc_unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3f(-, '-', sc_unsigned, sc_unsigned, sc_signed)



// MULtiplication operators:


//  sc_in_aug<type>.read() * sc_in_aug<type>.read()

PK_OPMODEL_OP3a(*, '*', int, int)
PK_OPMODEL_OP3a(*, '*', short, short)
PK_OPMODEL_OP3a(*, '*', long, long)
PK_OPMODEL_OP3a(*, '*', float, float)
PK_OPMODEL_OP3a(*, '*', double, double)
PK_OPMODEL_OP3a(*, '*', unsigned, int)
PK_OPMODEL_OP3a(*, '*', sc_signed, sc_signed)
PK_OPMODEL_OP3a(*, '*', sc_unsigned, sc_unsigned)


//  sc_in_aug<int>.read() * type

PK_OPMODEL_OP3c(*, '*', int, int, int) 
PK_OPMODEL_OP3c(*, '*', int, short, int)
PK_OPMODEL_OP3c(*, '*', int, long, long)
PK_OPMODEL_OP3c(*, '*', int, unsigned, int)
PK_OPMODEL_OP3c(*, '*', int, float, float)
PK_OPMODEL_OP3c(*, '*', int, double, double)
PK_OPMODEL_OP3c(*, '*', int, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(*, '*', int, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(*, '*', int, int, int)
PK_OPMODEL_OP3e(*, '*', int, short, int)
PK_OPMODEL_OP3e(*, '*', int, long, long)
PK_OPMODEL_OP3e(*, '*', int, unsigned, int)
PK_OPMODEL_OP3e(*, '*', int, float, float)
PK_OPMODEL_OP3e(*, '*', int, double, double)
PK_OPMODEL_OP3f(*, '*', int, sc_signed, sc_signed)
PK_OPMODEL_OP3f(*, '*', int, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(*, '*', int, short, int)
PK_OPMODEL_OP3h(*, '*', int, long, long)
PK_OPMODEL_OP3h(*, '*', int, unsigned, int)
PK_OPMODEL_OP3h(*, '*', int, float, float)
PK_OPMODEL_OP3h(*, '*', int, double, double)
PK_OPMODEL_OP3h(*, '*', int, sc_signed, sc_signed)
PK_OPMODEL_OP3h(*, '*', int, sc_unsigned, sc_signed)


//  sc_in_aug<short>.read() * type

PK_OPMODEL_OP3c(*, '*', short, int, int) 
PK_OPMODEL_OP3c(*, '*', short, short, short)
PK_OPMODEL_OP3c(*, '*', short, long, long)
PK_OPMODEL_OP3c(*, '*', short, unsigned, int)
PK_OPMODEL_OP3c(*, '*', short, float, float)
PK_OPMODEL_OP3c(*, '*', short, double, double)
PK_OPMODEL_OP3c(*, '*', short, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(*, '*', short, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(*, '*', short, int, int)
PK_OPMODEL_OP3e(*, '*', short, short, short)
PK_OPMODEL_OP3e(*, '*', short, long, long)
PK_OPMODEL_OP3e(*, '*', short, unsigned, int)
PK_OPMODEL_OP3e(*, '*', short, float, float)
PK_OPMODEL_OP3e(*, '*', short, double, double)
PK_OPMODEL_OP3f(*, '*', short, sc_signed, sc_signed)
PK_OPMODEL_OP3f(*, '*', short, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(*, '*', short, long, long)
PK_OPMODEL_OP3h(*, '*', short, unsigned, int)
PK_OPMODEL_OP3h(*, '*', short, float, float)
PK_OPMODEL_OP3h(*, '*', short, double, double)
PK_OPMODEL_OP3h(*, '*', short, sc_signed, sc_signed)
PK_OPMODEL_OP3h(*, '*', short, sc_unsigned, sc_unsigned)


//  sc_in_aug<long>.read() * type

PK_OPMODEL_OP3c(*, '*', long, int, long) 
PK_OPMODEL_OP3c(*, '*', long, short, long)
PK_OPMODEL_OP3c(*, '*', long, long, long)
PK_OPMODEL_OP3c(*, '*', long, unsigned, long)
PK_OPMODEL_OP3c(*, '*', long, float, float)
PK_OPMODEL_OP3c(*, '*', long, double, double)
PK_OPMODEL_OP3c(*, '*', long, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(*, '*', long, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(*, '*', long, int, long)
PK_OPMODEL_OP3e(*, '*', long, short, long)
PK_OPMODEL_OP3e(*, '*', long, long, long)
PK_OPMODEL_OP3e(*, '*', long, unsigned, long)
PK_OPMODEL_OP3e(*, '*', long, float, float)
PK_OPMODEL_OP3e(*, '*', long, double, double)
PK_OPMODEL_OP3f(*, '*', long, sc_signed, sc_signed)
PK_OPMODEL_OP3f(*, '*', long, sc_unsigned, sc_signed)


PK_OPMODEL_OP3h(*, '*', long, unsigned, long)
PK_OPMODEL_OP3h(*, '*', long, float, float)
PK_OPMODEL_OP3h(*, '*', long, double, double)
PK_OPMODEL_OP3h(*, '*', long, sc_signed, sc_signed)
PK_OPMODEL_OP3h(*, '*', long, sc_unsigned, sc_signed)


//  sc_in_aug<unsigned>.read() * type

PK_OPMODEL_OP3c(*, '*', unsigned, int, int) 
PK_OPMODEL_OP3c(*, '*', unsigned, short, int)
PK_OPMODEL_OP3c(*, '*', unsigned, long, long)
PK_OPMODEL_OP3c(*, '*', unsigned, unsigned, unsigned)
PK_OPMODEL_OP3c(*, '*', unsigned, float, float)
PK_OPMODEL_OP3c(*, '*', unsigned, double, double)
PK_OPMODEL_OP3c(*, '*', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(*, '*', unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP3e(*, '*', unsigned, int, int)
PK_OPMODEL_OP3e(*, '*', unsigned, short, int)
PK_OPMODEL_OP3e(*, '*', unsigned, long, long)
PK_OPMODEL_OP3e(*, '*', unsigned, unsigned, unsigned)
PK_OPMODEL_OP3e(*, '*', unsigned, float, float)
PK_OPMODEL_OP3e(*, '*', unsigned, double, double)
PK_OPMODEL_OP3f(*, '*', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3f(*, '*', unsigned, sc_unsigned, sc_unsigned)



PK_OPMODEL_OP3h(*, '*', unsigned, float, float)
PK_OPMODEL_OP3h(*, '*', unsigned, double, double)
PK_OPMODEL_OP3h(*, '*', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3h(*, '*', unsigned, sc_unsigned, sc_unsigned)


//  sc_in_aug<float>.read() * type

PK_OPMODEL_OP3c(*, '*', float, int, float) 
PK_OPMODEL_OP3c(*, '*', float, short, float)
PK_OPMODEL_OP3c(*, '*', float, long, float)
PK_OPMODEL_OP3c(*, '*', float, unsigned, float)
PK_OPMODEL_OP3c(*, '*', float, float, float)
PK_OPMODEL_OP3c(*, '*', float, double, double)

PK_OPMODEL_OP3e(*, '*', float, int, float)
PK_OPMODEL_OP3e(*, '*', float, short, float)
PK_OPMODEL_OP3e(*, '*', float, long, float)
PK_OPMODEL_OP3e(*, '*', float, unsigned, float)
PK_OPMODEL_OP3e(*, '*', float, float, float)
PK_OPMODEL_OP3e(*, '*', float, double, double)

PK_OPMODEL_OP3h(*, '*', float, double, double)


//  sc_in_aug<double>.read() * type

PK_OPMODEL_OP3c(*, '*', double, int, double) 
PK_OPMODEL_OP3c(*, '*', double, short, double)
PK_OPMODEL_OP3c(*, '*', double, long, double)
PK_OPMODEL_OP3c(*, '*', double, unsigned, double)
PK_OPMODEL_OP3c(*, '*', double, float, double)
PK_OPMODEL_OP3c(*, '*', double, double, double)

PK_OPMODEL_OP3e(*, '*', double, int, double)
PK_OPMODEL_OP3e(*, '*', double, short, double)
PK_OPMODEL_OP3e(*, '*', double, long, double)
PK_OPMODEL_OP3e(*, '*', double, unsigned, double)
PK_OPMODEL_OP3e(*, '*', double, float, double)
PK_OPMODEL_OP3e(*, '*', double, double, double)


//  sc_in_aug<sc_signed>.read() * type

PK_OPMODEL_OP3c(*, '*', sc_signed, int, sc_signed) 
PK_OPMODEL_OP3c(*, '*', sc_signed, short, sc_signed)
PK_OPMODEL_OP3c(*, '*', sc_signed, long, sc_signed)
PK_OPMODEL_OP3c(*, '*', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP3c(*, '*', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(*, '*', sc_signed, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(*, '*', sc_signed, int, sc_signed)
PK_OPMODEL_OP3e(*, '*', sc_signed, short, sc_signed)
PK_OPMODEL_OP3e(*, '*', sc_signed, long, sc_signed)
PK_OPMODEL_OP3e(*, '*', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP3f(*, '*', sc_signed, sc_signed, sc_signed)
PK_OPMODEL_OP3f(*, '*', sc_signed, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(*, '*', sc_signed, sc_unsigned, sc_signed)


//  sc_in_aug<sc_unsigned>.read() * type

PK_OPMODEL_OP3c(*, '*', sc_unsigned, int, sc_signed) 
PK_OPMODEL_OP3c(*, '*', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP3c(*, '*', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP3c(*, '*', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP3c(*, '*', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(*, '*', sc_unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP3e(*, '*', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP3e(*, '*', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP3e(*, '*', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP3e(*, '*', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP3f(*, '*', sc_unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3f(*, '*', sc_unsigned, sc_unsigned, sc_unsigned)



// DIVision operators:


//  sc_in_aug<type>.read() / sc_in_aug<type>.read()

PK_OPMODEL_OP3a(/, '/', int, int)
PK_OPMODEL_OP3a(/, '/', short, short)
PK_OPMODEL_OP3a(/, '/', long, long)
PK_OPMODEL_OP3a(/, '/', float, float)
PK_OPMODEL_OP3a(/, '/', double, double)
PK_OPMODEL_OP3a(/, '/', unsigned, int)
PK_OPMODEL_OP3a(/, '/', sc_signed, sc_signed)
PK_OPMODEL_OP3a(/, '/', sc_unsigned, sc_unsigned)


//  sc_in_aug<int>.read() / type

PK_OPMODEL_OP3c(/, '/', int, int, int) 
PK_OPMODEL_OP3c(/, '/', int, short, int)
PK_OPMODEL_OP3c(/, '/', int, long, long)
PK_OPMODEL_OP3c(/, '/', int, unsigned, int)
PK_OPMODEL_OP3c(/, '/', int, float, float)
PK_OPMODEL_OP3c(/, '/', int, double, double)
PK_OPMODEL_OP3c(/, '/', int, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(/, '/', int, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(/, '/', int, int, int)
PK_OPMODEL_OP3e(/, '/', int, short, int)
PK_OPMODEL_OP3e(/, '/', int, long, long)
PK_OPMODEL_OP3e(/, '/', int, unsigned, int)
PK_OPMODEL_OP3e(/, '/', int, float, float)
PK_OPMODEL_OP3e(/, '/', int, double, double)
PK_OPMODEL_OP3f(/, '/', int, sc_signed, sc_signed)
PK_OPMODEL_OP3f(/, '/', int, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(/, '/', int, short, int)
PK_OPMODEL_OP3h(/, '/', int, long, long)
PK_OPMODEL_OP3h(/, '/', int, unsigned, int)
PK_OPMODEL_OP3h(/, '/', int, float, float)
PK_OPMODEL_OP3h(/, '/', int, double, double)
PK_OPMODEL_OP3h(/, '/', int, sc_signed, sc_signed)
PK_OPMODEL_OP3h(/, '/', int, sc_unsigned, sc_signed)


//  sc_in_aug<short>.read() / type

PK_OPMODEL_OP3c(/, '/', short, int, int) 
PK_OPMODEL_OP3c(/, '/', short, short, short)
PK_OPMODEL_OP3c(/, '/', short, long, long)
PK_OPMODEL_OP3c(/, '/', short, unsigned, int)
PK_OPMODEL_OP3c(/, '/', short, float, float)
PK_OPMODEL_OP3c(/, '/', short, double, double)
PK_OPMODEL_OP3c(/, '/', short, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(/, '/', short, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(/, '/', short, int, int)
PK_OPMODEL_OP3e(/, '/', short, short, short)
PK_OPMODEL_OP3e(/, '/', short, long, long)
PK_OPMODEL_OP3e(/, '/', short, unsigned, int)
PK_OPMODEL_OP3e(/, '/', short, float, float)
PK_OPMODEL_OP3e(/, '/', short, double, double)
PK_OPMODEL_OP3f(/, '/', short, sc_signed, sc_signed)
PK_OPMODEL_OP3f(/, '/', short, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(/, '/', short, long, long)
PK_OPMODEL_OP3h(/, '/', short, unsigned, int)
PK_OPMODEL_OP3h(/, '/', short, float, float)
PK_OPMODEL_OP3h(/, '/', short, double, double)
PK_OPMODEL_OP3h(/, '/', short, sc_signed, sc_signed)
PK_OPMODEL_OP3h(/, '/', short, sc_unsigned, sc_unsigned)


//  sc_in_aug<long>.read() / type

PK_OPMODEL_OP3c(/, '/', long, int, long) 
PK_OPMODEL_OP3c(/, '/', long, short, long)
PK_OPMODEL_OP3c(/, '/', long, long, long)
PK_OPMODEL_OP3c(/, '/', long, unsigned, long)
PK_OPMODEL_OP3c(/, '/', long, float, float)
PK_OPMODEL_OP3c(/, '/', long, double, double)
PK_OPMODEL_OP3c(/, '/', long, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(/, '/', long, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(/, '/', long, int, long)
PK_OPMODEL_OP3e(/, '/', long, short, long)
PK_OPMODEL_OP3e(/, '/', long, long, long)
PK_OPMODEL_OP3e(/, '/', long, unsigned, long)
PK_OPMODEL_OP3e(/, '/', long, float, float)
PK_OPMODEL_OP3e(/, '/', long, double, double)
PK_OPMODEL_OP3f(/, '/', long, sc_signed, sc_signed)
PK_OPMODEL_OP3f(/, '/', long, sc_unsigned, sc_signed)


PK_OPMODEL_OP3h(/, '/', long, unsigned, long)
PK_OPMODEL_OP3h(/, '/', long, float, float)
PK_OPMODEL_OP3h(/, '/', long, double, double)
PK_OPMODEL_OP3h(/, '/', long, sc_signed, sc_signed)
PK_OPMODEL_OP3h(/, '/', long, sc_unsigned, sc_signed)


//  sc_in_aug<unsigned>.read() / type

PK_OPMODEL_OP3c(/, '/', unsigned, int, int) 
PK_OPMODEL_OP3c(/, '/', unsigned, short, int)
PK_OPMODEL_OP3c(/, '/', unsigned, long, long)
PK_OPMODEL_OP3c(/, '/', unsigned, unsigned, unsigned)
PK_OPMODEL_OP3c(/, '/', unsigned, float, float)
PK_OPMODEL_OP3c(/, '/', unsigned, double, double)
PK_OPMODEL_OP3c(/, '/', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(/, '/', unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP3e(/, '/', unsigned, int, int)
PK_OPMODEL_OP3e(/, '/', unsigned, short, int)
PK_OPMODEL_OP3e(/, '/', unsigned, long, long)
PK_OPMODEL_OP3e(/, '/', unsigned, unsigned, unsigned)
PK_OPMODEL_OP3e(/, '/', unsigned, float, float)
PK_OPMODEL_OP3e(/, '/', unsigned, double, double)
PK_OPMODEL_OP3f(/, '/', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3f(/, '/', unsigned, sc_unsigned, sc_unsigned)



PK_OPMODEL_OP3h(/, '/', unsigned, float, float)
PK_OPMODEL_OP3h(/, '/', unsigned, double, double)
PK_OPMODEL_OP3h(/, '/', unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3h(/, '/', unsigned, sc_unsigned, sc_unsigned)


//  sc_in_aug<float>.read() / type

PK_OPMODEL_OP3c(/, '/', float, int, float) 
PK_OPMODEL_OP3c(/, '/', float, short, float)
PK_OPMODEL_OP3c(/, '/', float, long, float)
PK_OPMODEL_OP3c(/, '/', float, unsigned, float)
PK_OPMODEL_OP3c(/, '/', float, float, float)
PK_OPMODEL_OP3c(/, '/', float, double, double)

PK_OPMODEL_OP3e(/, '/', float, int, float)
PK_OPMODEL_OP3e(/, '/', float, short, float)
PK_OPMODEL_OP3e(/, '/', float, long, float)
PK_OPMODEL_OP3e(/, '/', float, unsigned, float)
PK_OPMODEL_OP3e(/, '/', float, float, float)
PK_OPMODEL_OP3e(/, '/', float, double, double)

PK_OPMODEL_OP3h(/, '/', float, double, double)


//  sc_in_aug<double>.read() / type

PK_OPMODEL_OP3c(/, '/', double, int, double) 
PK_OPMODEL_OP3c(/, '/', double, short, double)
PK_OPMODEL_OP3c(/, '/', double, long, double)
PK_OPMODEL_OP3c(/, '/', double, unsigned, double)
PK_OPMODEL_OP3c(/, '/', double, float, double)
PK_OPMODEL_OP3c(/, '/', double, double, double)

PK_OPMODEL_OP3e(/, '/', double, int, double)
PK_OPMODEL_OP3e(/, '/', double, short, double)
PK_OPMODEL_OP3e(/, '/', double, long, double)
PK_OPMODEL_OP3e(/, '/', double, unsigned, double)
PK_OPMODEL_OP3e(/, '/', double, float, double)
PK_OPMODEL_OP3e(/, '/', double, double, double)


//  sc_in_aug<sc_signed>.read() / type

PK_OPMODEL_OP3c(/, '/', sc_signed, int, sc_signed) 
PK_OPMODEL_OP3c(/, '/', sc_signed, short, sc_signed)
PK_OPMODEL_OP3c(/, '/', sc_signed, long, sc_signed)
PK_OPMODEL_OP3c(/, '/', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP3c(/, '/', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(/, '/', sc_signed, sc_unsigned&, sc_signed)

PK_OPMODEL_OP3e(/, '/', sc_signed, int, sc_signed)
PK_OPMODEL_OP3e(/, '/', sc_signed, short, sc_signed)
PK_OPMODEL_OP3e(/, '/', sc_signed, long, sc_signed)
PK_OPMODEL_OP3e(/, '/', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP3f(/, '/', sc_signed, sc_signed, sc_signed)
PK_OPMODEL_OP3f(/, '/', sc_signed, sc_unsigned, sc_signed)

PK_OPMODEL_OP3h(/, '/', sc_signed, sc_unsigned, sc_signed)


//  sc_in_aug<sc_unsigned>.read() / type

PK_OPMODEL_OP3c(/, '/', sc_unsigned, int, sc_signed) 
PK_OPMODEL_OP3c(/, '/', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP3c(/, '/', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP3c(/, '/', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP3c(/, '/', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP3c(/, '/', sc_unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP3e(/, '/', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP3e(/, '/', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP3e(/, '/', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP3e(/, '/', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP3f(/, '/', sc_unsigned, sc_signed, sc_signed)
PK_OPMODEL_OP3f(/, '/', sc_unsigned, sc_unsigned, sc_unsigned)



#endif

