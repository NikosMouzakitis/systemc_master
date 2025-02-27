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

Overloaded operators for operator-based power models

Some operators are defined here, others in the file pk_model_operators_2.h

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

using pk_core::sc_in_aug;


#include "PKtool/power_models/pk_model_lib_header.h"
#include "PKtool/power_models/pk_default_lib.h" 

#include "PKtool/power_models/pk_model_operators_2.h"


// ADDition operators:


//  sc_in_aug<type> + sc_in_aug<type>

PK_OPMODEL_OP2a( +, '+', int, int)
PK_OPMODEL_OP2a( +, '+', unsigned, unsigned)  
PK_OPMODEL_OP2a( +, '+', short, short)
PK_OPMODEL_OP2a( +, '+', long, long)
PK_OPMODEL_OP2a( +, '+', float, float)  
PK_OPMODEL_OP2a( +, '+', double, double)
PK_OPMODEL_OP2a( +, '+', sc_signed, sc_signed) 
PK_OPMODEL_OP2a( +, '+', sc_unsigned, sc_unsigned)



//  sc_in_aug<int> + type;

PK_OPMODEL_OP2c( +, '+', int, int, int)
PK_OPMODEL_OP2c( +, '+', int, short, int)
PK_OPMODEL_OP2c( +, '+', int, long, long)
PK_OPMODEL_OP2c( +, '+', int, unsigned, int)
PK_OPMODEL_OP2c( +, '+', int, float, float)
PK_OPMODEL_OP2c( +, '+', int, double, double)
PK_OPMODEL_OP2c( +, '+', int, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( +, '+', int, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( +, '+', int, int, int)
PK_OPMODEL_OP2e( +, '+', int, short, int)
PK_OPMODEL_OP2e( +, '+', int, long, long)
PK_OPMODEL_OP2e( +, '+', int, unsigned, int)
PK_OPMODEL_OP2e( +, '+', int, float, float)
PK_OPMODEL_OP2e( +, '+', int, double, double)
PK_OPMODEL_OP2e( +, '+', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( +, '+', int, sc_signed, sc_signed)

PK_OPMODEL_OP2g( +, '+', int, short, int)
PK_OPMODEL_OP2g( +, '+', int, long, long)
PK_OPMODEL_OP2g( +, '+', int, unsigned, int)
PK_OPMODEL_OP2g( +, '+', int, float, float)
PK_OPMODEL_OP2g( +, '+', int, double, double)
PK_OPMODEL_OP2g( +, '+', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( +, '+', int, sc_signed, sc_signed)


//  sc_in_aug<short> + type;

PK_OPMODEL_OP2c( +, '+', short, int, int)
PK_OPMODEL_OP2c( +, '+', short, short, short)
PK_OPMODEL_OP2c( +, '+', short, long, long)
PK_OPMODEL_OP2c( +, '+', short, unsigned, int)
PK_OPMODEL_OP2c( +, '+', short, float, float)
PK_OPMODEL_OP2c( +, '+', short, double, double)
PK_OPMODEL_OP2c( +, '+', short, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( +, '+', short, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( +, '+', short, int, int)
PK_OPMODEL_OP2e( +, '+', short, short, short)
PK_OPMODEL_OP2e( +, '+', short, long, long)
PK_OPMODEL_OP2e( +, '+', short, unsigned, int)
PK_OPMODEL_OP2e( +, '+', short, float, float)
PK_OPMODEL_OP2e( +, '+', short, double, double)
PK_OPMODEL_OP2e( +, '+', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( +, '+', short, sc_signed, sc_signed)

PK_OPMODEL_OP2g( +, '+', short, long, long)
PK_OPMODEL_OP2g( +, '+', short, unsigned, int)
PK_OPMODEL_OP2g( +, '+', short, float, float)
PK_OPMODEL_OP2g( +, '+', short, double, double)
PK_OPMODEL_OP2g( +, '+', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( +, '+', short, sc_signed, sc_signed)


//  sc_in_aug<long> + type;

PK_OPMODEL_OP2c( +, '+', long, int, long)
PK_OPMODEL_OP2c( +, '+', long, short, long)
PK_OPMODEL_OP2c( +, '+', long, long, long)
PK_OPMODEL_OP2c( +, '+', long, unsigned, long)
PK_OPMODEL_OP2c( +, '+', long, float, float)
PK_OPMODEL_OP2c( +, '+', long, double, double)
PK_OPMODEL_OP2c( +, '+', long, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( +, '+', long, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( +, '+', long, int, long)
PK_OPMODEL_OP2e( +, '+', long, short, long)
PK_OPMODEL_OP2e( +, '+', long, long, long)
PK_OPMODEL_OP2e( +, '+', long, unsigned, long)
PK_OPMODEL_OP2e( +, '+', long, float, float)
PK_OPMODEL_OP2e( +, '+', long, double, double)
PK_OPMODEL_OP2e( +, '+', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( +, '+', long, sc_signed, sc_signed)

PK_OPMODEL_OP2g( +, '+', long, unsigned, long)
PK_OPMODEL_OP2g( +, '+', long, float, float)
PK_OPMODEL_OP2g( +, '+', long, double, double)
PK_OPMODEL_OP2g( +, '+', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( +, '+', long, sc_signed, sc_signed)


//  sc_in_aug<unsigned> + type;

PK_OPMODEL_OP2c( +, '+', unsigned, int, int)
PK_OPMODEL_OP2c( +, '+', unsigned, short, int)
PK_OPMODEL_OP2c( +, '+', unsigned, long, long)
PK_OPMODEL_OP2c( +, '+', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2c( +, '+', unsigned, float, float)
PK_OPMODEL_OP2c( +, '+', unsigned, double, double)
PK_OPMODEL_OP2c( +, '+', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( +, '+', unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP2e( +, '+', unsigned, int, int)
PK_OPMODEL_OP2e( +, '+', unsigned, short, int)
PK_OPMODEL_OP2e( +, '+', unsigned, long, long)
PK_OPMODEL_OP2e( +, '+', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2e( +, '+', unsigned, float, float)
PK_OPMODEL_OP2e( +, '+', unsigned, double, double)
PK_OPMODEL_OP2e( +, '+', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e( +, '+', unsigned, sc_signed, sc_signed)

PK_OPMODEL_OP2g( +, '+', unsigned, float, float)
PK_OPMODEL_OP2g( +, '+', unsigned, double, double)
PK_OPMODEL_OP2g( +, '+', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2g( +, '+', unsigned, sc_signed, sc_signed)


//  sc_in_aug<float> + type;

PK_OPMODEL_OP2c( +, '+', float, int, float)
PK_OPMODEL_OP2c( +, '+', float, short, float)
PK_OPMODEL_OP2c( +, '+', float, long, float)
PK_OPMODEL_OP2c( +, '+', float, unsigned, float)
PK_OPMODEL_OP2c( +, '+', float, float, float)
PK_OPMODEL_OP2c( +, '+', float, double, double)

PK_OPMODEL_OP2e( +, '+', float, int, float)
PK_OPMODEL_OP2e( +, '+', float, short, float)
PK_OPMODEL_OP2e( +, '+', float, long, float)
PK_OPMODEL_OP2e( +, '+', float, unsigned, float)
PK_OPMODEL_OP2e( +, '+', float, float, float)
PK_OPMODEL_OP2e( +, '+', float, double, double)

PK_OPMODEL_OP2g( +, '+', float, double, double)


//  sc_in_aug<double> + type;

PK_OPMODEL_OP2c( +, '+', double, int, double)
PK_OPMODEL_OP2c( +, '+', double, short, double)
PK_OPMODEL_OP2c( +, '+', double, long, double)
PK_OPMODEL_OP2c( +, '+', double, unsigned, double)
PK_OPMODEL_OP2c( +, '+', double, float, double)
PK_OPMODEL_OP2c( +, '+', double, double, double)

PK_OPMODEL_OP2e( +, '+', double, int, double)
PK_OPMODEL_OP2e( +, '+', double, short, double)
PK_OPMODEL_OP2e( +, '+', double, long, double)
PK_OPMODEL_OP2e( +, '+', double, unsigned, double)
PK_OPMODEL_OP2e( +, '+', double, float, double)
PK_OPMODEL_OP2e( +, '+', double, double, double)


//  sc_in_aug<sc_signed> + type;

PK_OPMODEL_OP2c( +, '+', sc_signed, int, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_signed, short, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_signed, long, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_signed, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( +, '+', sc_signed, int, sc_signed)
PK_OPMODEL_OP2e( +, '+', sc_signed, short, sc_signed)
PK_OPMODEL_OP2e( +, '+', sc_signed, long, sc_signed)
PK_OPMODEL_OP2e( +, '+', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2e( +, '+', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( +, '+', sc_signed, sc_signed, sc_signed)

PK_OPMODEL_OP2g( +, '+', sc_signed, sc_unsigned, sc_signed)


//  sc_in_aug<sc_unsigned> + type;

PK_OPMODEL_OP2c( +, '+', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2c( +, '+', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( +, '+', sc_unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP2e( +, '+', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2e( +, '+', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2e( +, '+', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2e( +, '+', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2e( +, '+', sc_unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e( +, '+', sc_unsigned, sc_signed, sc_signed)


// SUBtraction operators:


//  sc_in_aug<type> - sc_in_aug<type>

PK_OPMODEL_OP2a( -, '-', int, int)
PK_OPMODEL_OP2a( -, '-', unsigned, int)  
PK_OPMODEL_OP2a( -, '-', short, short)
PK_OPMODEL_OP2a( -, '-', long, long)
PK_OPMODEL_OP2a( -, '-', float, float)  
PK_OPMODEL_OP2a( -, '-', double, double)
PK_OPMODEL_OP2a( -, '-', sc_signed, sc_signed) 
PK_OPMODEL_OP2a( -, '-', sc_unsigned, sc_signed)



//  sc_in_aug<int> - type;

PK_OPMODEL_OP2c( -, '-', int, int, int)
PK_OPMODEL_OP2c( -, '-', int, short, int)
PK_OPMODEL_OP2c( -, '-', int, long, long)
PK_OPMODEL_OP2c( -, '-', int, unsigned, int)
PK_OPMODEL_OP2c( -, '-', int, float, float)
PK_OPMODEL_OP2c( -, '-', int, double, double)
PK_OPMODEL_OP2c( -, '-', int, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( -, '-', int, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( -, '-', int, int, int)
PK_OPMODEL_OP2e( -, '-', int, short, int)
PK_OPMODEL_OP2e( -, '-', int, long, long)
PK_OPMODEL_OP2e( -, '-', int, unsigned, int)
PK_OPMODEL_OP2e( -, '-', int, float, float)
PK_OPMODEL_OP2e( -, '-', int, double, double)
PK_OPMODEL_OP2e( -, '-', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( -, '-', int, sc_signed, sc_signed)

PK_OPMODEL_OP2g( -, '-', int, short, int)
PK_OPMODEL_OP2g( -, '-', int, long, long)
PK_OPMODEL_OP2g( -, '-', int, unsigned, int)
PK_OPMODEL_OP2g( -, '-', int, float, float)
PK_OPMODEL_OP2g( -, '-', int, double, double)
PK_OPMODEL_OP2g( -, '-', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( -, '-', int, sc_signed, sc_signed)


//  sc_in_aug<short> - type;

PK_OPMODEL_OP2c( -, '-', short, int, int)
PK_OPMODEL_OP2c( -, '-', short, short, short)
PK_OPMODEL_OP2c( -, '-', short, long, long)
PK_OPMODEL_OP2c( -, '-', short, unsigned, int)
PK_OPMODEL_OP2c( -, '-', short, float, float)
PK_OPMODEL_OP2c( -, '-', short, double, double)
PK_OPMODEL_OP2c( -, '-', short, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( -, '-', short, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( -, '-', short, int, int)
PK_OPMODEL_OP2e( -, '-', short, short, short)
PK_OPMODEL_OP2e( -, '-', short, long, long)
PK_OPMODEL_OP2e( -, '-', short, unsigned, int)
PK_OPMODEL_OP2e( -, '-', short, float, float)
PK_OPMODEL_OP2e( -, '-', short, double, double)
PK_OPMODEL_OP2e( -, '-', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( -, '-', short, sc_signed, sc_signed)

PK_OPMODEL_OP2g( -, '-', short, long, long)
PK_OPMODEL_OP2g( -, '-', short, unsigned, int)
PK_OPMODEL_OP2g( -, '-', short, float, float)
PK_OPMODEL_OP2g( -, '-', short, double, double)
PK_OPMODEL_OP2g( -, '-', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( -, '-', short, sc_signed, sc_signed)


//  sc_in_aug<long> - type;

PK_OPMODEL_OP2c( -, '-', long, int, long)
PK_OPMODEL_OP2c( -, '-', long, short, long)
PK_OPMODEL_OP2c( -, '-', long, long, long)
PK_OPMODEL_OP2c( -, '-', long, unsigned, long)
PK_OPMODEL_OP2c( -, '-', long, float, float)
PK_OPMODEL_OP2c( -, '-', long, double, double)
PK_OPMODEL_OP2c( -, '-', long, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( -, '-', long, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( -, '-', long, int, long)
PK_OPMODEL_OP2e( -, '-', long, short, long)
PK_OPMODEL_OP2e( -, '-', long, long, long)
PK_OPMODEL_OP2e( -, '-', long, unsigned, long)
PK_OPMODEL_OP2e( -, '-', long, float, float)
PK_OPMODEL_OP2e( -, '-', long, double, double)
PK_OPMODEL_OP2e( -, '-', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( -, '-', long, sc_signed, sc_signed)

PK_OPMODEL_OP2g( -, '-', long, unsigned, long)
PK_OPMODEL_OP2g( -, '-', long, float, float)
PK_OPMODEL_OP2g( -, '-', long, double, double)
PK_OPMODEL_OP2g( -, '-', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( -, '-', long, sc_signed, sc_signed)


//  sc_in_aug<unsigned> - type;

PK_OPMODEL_OP2c( -, '-', unsigned, int, int)
PK_OPMODEL_OP2c( -, '-', unsigned, short, int)
PK_OPMODEL_OP2c( -, '-', unsigned, long, long)
PK_OPMODEL_OP2c( -, '-', unsigned, unsigned, int)
PK_OPMODEL_OP2c( -, '-', unsigned, float, float)
PK_OPMODEL_OP2c( -, '-', unsigned, double, double)
PK_OPMODEL_OP2c( -, '-', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( -, '-', unsigned, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( -, '-', unsigned, int, int)
PK_OPMODEL_OP2e( -, '-', unsigned, short, int)
PK_OPMODEL_OP2e( -, '-', unsigned, long, long)
PK_OPMODEL_OP2e( -, '-', unsigned, unsigned, signed)
PK_OPMODEL_OP2e( -, '-', unsigned, float, float)
PK_OPMODEL_OP2e( -, '-', unsigned, double, double)
PK_OPMODEL_OP2e( -, '-', unsigned, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( -, '-', unsigned, sc_signed, sc_signed)

PK_OPMODEL_OP2g( -, '-', unsigned, float, float)
PK_OPMODEL_OP2g( -, '-', unsigned, double, double)
PK_OPMODEL_OP2g( -, '-', unsigned, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( -, '-', unsigned, sc_signed, sc_signed)


//  sc_in_aug<float> - type;

PK_OPMODEL_OP2c( -, '-', float, int, float)
PK_OPMODEL_OP2c( -, '-', float, short, float)
PK_OPMODEL_OP2c( -, '-', float, long, float)
PK_OPMODEL_OP2c( -, '-', float, unsigned, float)
PK_OPMODEL_OP2c( -, '-', float, float, float)
PK_OPMODEL_OP2c( -, '-', float, double, double)

PK_OPMODEL_OP2e( -, '-', float, int, float)
PK_OPMODEL_OP2e( -, '-', float, short, float)
PK_OPMODEL_OP2e( -, '-', float, long, float)
PK_OPMODEL_OP2e( -, '-', float, unsigned, float)
PK_OPMODEL_OP2e( -, '-', float, float, float)
PK_OPMODEL_OP2e( -, '-', float, double, double)

PK_OPMODEL_OP2g( -, '-', float, double, double)


//  sc_in_aug<double> - type;

PK_OPMODEL_OP2c( -, '-', double, int, double)
PK_OPMODEL_OP2c( -, '-', double, short, double)
PK_OPMODEL_OP2c( -, '-', double, long, double)
PK_OPMODEL_OP2c( -, '-', double, unsigned, double)
PK_OPMODEL_OP2c( -, '-', double, float, double)
PK_OPMODEL_OP2c( -, '-', double, double, double)

PK_OPMODEL_OP2e( -, '-', double, int, double)
PK_OPMODEL_OP2e( -, '-', double, short, double)
PK_OPMODEL_OP2e( -, '-', double, long, double)
PK_OPMODEL_OP2e( -, '-', double, unsigned, double)
PK_OPMODEL_OP2e( -, '-', double, float, double)
PK_OPMODEL_OP2e( -, '-', double, double, double)


//  sc_in_aug<sc_signed> - type;

PK_OPMODEL_OP2c( -, '-', sc_signed, int, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_signed, short, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_signed, long, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_signed, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( -, '-', sc_signed, int, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_signed, short, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_signed, long, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_signed, sc_signed, sc_signed)

PK_OPMODEL_OP2g( -, '-', sc_signed, sc_unsigned, sc_signed)


//  sc_in_aug<sc_unsigned> - type;

PK_OPMODEL_OP2c( -, '-', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_unsigned, unsigned, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( -, '-', sc_unsigned, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( -, '-', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_unsigned, unsigned, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_unsigned, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( -, '-', sc_unsigned, sc_signed, sc_signed)


// MULtiplication operators:


//  sc_in_aug<type> * sc_in_aug<type>

PK_OPMODEL_OP2a( *, '*', int, int)
PK_OPMODEL_OP2a( *, '*', unsigned, unsigned)  
PK_OPMODEL_OP2a( *, '*', short, short)
PK_OPMODEL_OP2a( *, '*', long, long)
PK_OPMODEL_OP2a( *, '*', float, float)  
PK_OPMODEL_OP2a( *, '*', double, double)
PK_OPMODEL_OP2a( *, '*', sc_signed, sc_signed) 
PK_OPMODEL_OP2a( *, '*', sc_unsigned, sc_unsigned)



//  sc_in_aug<int> * type;

PK_OPMODEL_OP2c( *, '*', int, int, int)
PK_OPMODEL_OP2c( *, '*', int, short, int)
PK_OPMODEL_OP2c( *, '*', int, long, long)
PK_OPMODEL_OP2c( *, '*', int, unsigned, int)
PK_OPMODEL_OP2c( *, '*', int, float, float)
PK_OPMODEL_OP2c( *, '*', int, double, double)
PK_OPMODEL_OP2c( *, '*', int, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( *, '*', int, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( *, '*', int, int, int)
PK_OPMODEL_OP2e( *, '*', int, short, int)
PK_OPMODEL_OP2e( *, '*', int, long, long)
PK_OPMODEL_OP2e( *, '*', int, unsigned, int)
PK_OPMODEL_OP2e( *, '*', int, float, float)
PK_OPMODEL_OP2e( *, '*', int, double, double)
PK_OPMODEL_OP2e( *, '*', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( *, '*', int, sc_signed, sc_signed)

PK_OPMODEL_OP2g( *, '*', int, short, int)
PK_OPMODEL_OP2g( *, '*', int, long, long)
PK_OPMODEL_OP2g( *, '*', int, unsigned, int)
PK_OPMODEL_OP2g( *, '*', int, float, float)
PK_OPMODEL_OP2g( *, '*', int, double, double)
PK_OPMODEL_OP2g( *, '*', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( *, '*', int, sc_signed, sc_signed)


//  sc_in_aug<short> * type;

PK_OPMODEL_OP2c( *, '*', short, int, int)
PK_OPMODEL_OP2c( *, '*', short, short, short)
PK_OPMODEL_OP2c( *, '*', short, long, long)
PK_OPMODEL_OP2c( *, '*', short, unsigned, int)
PK_OPMODEL_OP2c( *, '*', short, float, float)
PK_OPMODEL_OP2c( *, '*', short, double, double)
PK_OPMODEL_OP2c( *, '*', short, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( *, '*', short, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( *, '*', short, int, int)
PK_OPMODEL_OP2e( *, '*', short, short, short)
PK_OPMODEL_OP2e( *, '*', short, long, long)
PK_OPMODEL_OP2e( *, '*', short, unsigned, int)
PK_OPMODEL_OP2e( *, '*', short, float, float)
PK_OPMODEL_OP2e( *, '*', short, double, double)
PK_OPMODEL_OP2e( *, '*', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( *, '*', short, sc_signed, sc_signed)

PK_OPMODEL_OP2g( *, '*', short, long, long)
PK_OPMODEL_OP2g( *, '*', short, unsigned, int)
PK_OPMODEL_OP2g( *, '*', short, float, float)
PK_OPMODEL_OP2g( *, '*', short, double, double)
PK_OPMODEL_OP2g( *, '*', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( *, '*', short, sc_signed, sc_signed)


//  sc_in_aug<long> * type;

PK_OPMODEL_OP2c( *, '*', long, int, long)
PK_OPMODEL_OP2c( *, '*', long, short, long)
PK_OPMODEL_OP2c( *, '*', long, long, long)
PK_OPMODEL_OP2c( *, '*', long, unsigned, long)
PK_OPMODEL_OP2c( *, '*', long, float, float)
PK_OPMODEL_OP2c( *, '*', long, double, double)
PK_OPMODEL_OP2c( *, '*', long, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( *, '*', long, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( *, '*', long, int, long)
PK_OPMODEL_OP2e( *, '*', long, short, long)
PK_OPMODEL_OP2e( *, '*', long, long, long)
PK_OPMODEL_OP2e( *, '*', long, unsigned, long)
PK_OPMODEL_OP2e( *, '*', long, float, float)
PK_OPMODEL_OP2e( *, '*', long, double, double)
PK_OPMODEL_OP2e( *, '*', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( *, '*', long, sc_signed, sc_signed)

PK_OPMODEL_OP2g( *, '*', long, unsigned, long)
PK_OPMODEL_OP2g( *, '*', long, float, float)
PK_OPMODEL_OP2g( *, '*', long, double, double)
PK_OPMODEL_OP2g( *, '*', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( *, '*', long, sc_signed, sc_signed)


//  sc_in_aug<unsigned> * type;

PK_OPMODEL_OP2c( *, '*', unsigned, int, int)
PK_OPMODEL_OP2c( *, '*', unsigned, short, int)
PK_OPMODEL_OP2c( *, '*', unsigned, long, long)
PK_OPMODEL_OP2c( *, '*', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2c( *, '*', unsigned, float, float)
PK_OPMODEL_OP2c( *, '*', unsigned, double, double)
PK_OPMODEL_OP2c( *, '*', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( *, '*', unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP2e( *, '*', unsigned, int, int)
PK_OPMODEL_OP2e( *, '*', unsigned, short, int)
PK_OPMODEL_OP2e( *, '*', unsigned, long, long)
PK_OPMODEL_OP2e( *, '*', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2e( *, '*', unsigned, float, float)
PK_OPMODEL_OP2e( *, '*', unsigned, double, double)
PK_OPMODEL_OP2e( *, '*', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e( *, '*', unsigned, sc_signed, sc_signed)

PK_OPMODEL_OP2g( *, '*', unsigned, float, float)
PK_OPMODEL_OP2g( *, '*', unsigned, double, double)
PK_OPMODEL_OP2g( *, '*', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2g( *, '*', unsigned, sc_signed, sc_signed)


//  sc_in_aug<float> * type;

PK_OPMODEL_OP2c( *, '*', float, int, float)
PK_OPMODEL_OP2c( *, '*', float, short, float)
PK_OPMODEL_OP2c( *, '*', float, long, float)
PK_OPMODEL_OP2c( *, '*', float, unsigned, float)
PK_OPMODEL_OP2c( *, '*', float, float, float)
PK_OPMODEL_OP2c( *, '*', float, double, double)

PK_OPMODEL_OP2e( *, '*', float, int, float)
PK_OPMODEL_OP2e( *, '*', float, short, float)
PK_OPMODEL_OP2e( *, '*', float, long, float)
PK_OPMODEL_OP2e( *, '*', float, unsigned, float)
PK_OPMODEL_OP2e( *, '*', float, float, float)
PK_OPMODEL_OP2e( *, '*', float, double, double)

PK_OPMODEL_OP2g( *, '*', float, double, double)


//  sc_in_aug<double> * type;

PK_OPMODEL_OP2c( *, '*', double, int, double)
PK_OPMODEL_OP2c( *, '*', double, short, double)
PK_OPMODEL_OP2c( *, '*', double, long, double)
PK_OPMODEL_OP2c( *, '*', double, unsigned, double)
PK_OPMODEL_OP2c( *, '*', double, float, double)
PK_OPMODEL_OP2c( *, '*', double, double, double)

PK_OPMODEL_OP2e( *, '*', double, int, double)
PK_OPMODEL_OP2e( *, '*', double, short, double)
PK_OPMODEL_OP2e( *, '*', double, long, double)
PK_OPMODEL_OP2e( *, '*', double, unsigned, double)
PK_OPMODEL_OP2e( *, '*', double, float, double)
PK_OPMODEL_OP2e( *, '*', double, double, double)


//  sc_in_aug<sc_signed> * type;

PK_OPMODEL_OP2c( *, '*', sc_signed, int, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_signed, short, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_signed, long, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_signed, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( *, '*', sc_signed, int, sc_signed)
PK_OPMODEL_OP2e( *, '*', sc_signed, short, sc_signed)
PK_OPMODEL_OP2e( *, '*', sc_signed, long, sc_signed)
PK_OPMODEL_OP2e( *, '*', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2e( *, '*', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( *, '*', sc_signed, sc_signed, sc_signed)

PK_OPMODEL_OP2g( *, '*', sc_signed, sc_unsigned, sc_signed)


//  sc_in_aug<sc_unsigned> * type;

PK_OPMODEL_OP2c( *, '*', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2c( *, '*', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( *, '*', sc_unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP2e( *, '*', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2e( *, '*', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2e( *, '*', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2e( *, '*', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2e( *, '*', sc_unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e( *, '*', sc_unsigned, sc_signed, sc_signed)


// DIVision operators:


//  sc_in_aug<type> / sc_in_aug<type>

PK_OPMODEL_OP2a( /, '/', int, int)
PK_OPMODEL_OP2a( /, '/', unsigned, unsigned)  
PK_OPMODEL_OP2a( /, '/', short, short)
PK_OPMODEL_OP2a( /, '/', long, long)
PK_OPMODEL_OP2a( /, '/', float, float)  
PK_OPMODEL_OP2a( /, '/', double, double)
PK_OPMODEL_OP2a( /, '/', sc_signed, sc_signed) 
PK_OPMODEL_OP2a( /, '/', sc_unsigned, sc_unsigned)



//  sc_in_aug<int> / type;

PK_OPMODEL_OP2c( /, '/', int, int, int)
PK_OPMODEL_OP2c( /, '/', int, short, int)
PK_OPMODEL_OP2c( /, '/', int, long, long)
PK_OPMODEL_OP2c( /, '/', int, unsigned, int)
PK_OPMODEL_OP2c( /, '/', int, float, float)
PK_OPMODEL_OP2c( /, '/', int, double, double)
PK_OPMODEL_OP2c( /, '/', int, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( /, '/', int, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( /, '/', int, int, int)
PK_OPMODEL_OP2e( /, '/', int, short, int)
PK_OPMODEL_OP2e( /, '/', int, long, long)
PK_OPMODEL_OP2e( /, '/', int, unsigned, int)
PK_OPMODEL_OP2e( /, '/', int, float, float)
PK_OPMODEL_OP2e( /, '/', int, double, double)
PK_OPMODEL_OP2e( /, '/', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( /, '/', int, sc_signed, sc_signed)

PK_OPMODEL_OP2g( /, '/', int, short, int)
PK_OPMODEL_OP2g( /, '/', int, long, long)
PK_OPMODEL_OP2g( /, '/', int, unsigned, int)
PK_OPMODEL_OP2g( /, '/', int, float, float)
PK_OPMODEL_OP2g( /, '/', int, double, double)
PK_OPMODEL_OP2g( /, '/', int, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( /, '/', int, sc_signed, sc_signed)


//  sc_in_aug<short> / type;

PK_OPMODEL_OP2c( /, '/', short, int, int)
PK_OPMODEL_OP2c( /, '/', short, short, short)
PK_OPMODEL_OP2c( /, '/', short, long, long)
PK_OPMODEL_OP2c( /, '/', short, unsigned, int)
PK_OPMODEL_OP2c( /, '/', short, float, float)
PK_OPMODEL_OP2c( /, '/', short, double, double)
PK_OPMODEL_OP2c( /, '/', short, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( /, '/', short, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( /, '/', short, int, int)
PK_OPMODEL_OP2e( /, '/', short, short, short)
PK_OPMODEL_OP2e( /, '/', short, long, long)
PK_OPMODEL_OP2e( /, '/', short, unsigned, int)
PK_OPMODEL_OP2e( /, '/', short, float, float)
PK_OPMODEL_OP2e( /, '/', short, double, double)
PK_OPMODEL_OP2e( /, '/', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( /, '/', short, sc_signed, sc_signed)

PK_OPMODEL_OP2g( /, '/', short, long, long)
PK_OPMODEL_OP2g( /, '/', short, unsigned, int)
PK_OPMODEL_OP2g( /, '/', short, float, float)
PK_OPMODEL_OP2g( /, '/', short, double, double)
PK_OPMODEL_OP2g( /, '/', short, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( /, '/', short, sc_signed, sc_signed)


//  sc_in_aug<long> / type;

PK_OPMODEL_OP2c( /, '/', long, int, long)
PK_OPMODEL_OP2c( /, '/', long, short, long)
PK_OPMODEL_OP2c( /, '/', long, long, long)
PK_OPMODEL_OP2c( /, '/', long, unsigned, long)
PK_OPMODEL_OP2c( /, '/', long, float, float)
PK_OPMODEL_OP2c( /, '/', long, double, double)
PK_OPMODEL_OP2c( /, '/', long, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( /, '/', long, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( /, '/', long, int, long)
PK_OPMODEL_OP2e( /, '/', long, short, long)
PK_OPMODEL_OP2e( /, '/', long, long, long)
PK_OPMODEL_OP2e( /, '/', long, unsigned, long)
PK_OPMODEL_OP2e( /, '/', long, float, float)
PK_OPMODEL_OP2e( /, '/', long, double, double)
PK_OPMODEL_OP2e( /, '/', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( /, '/', long, sc_signed, sc_signed)

PK_OPMODEL_OP2g( /, '/', long, unsigned, long)
PK_OPMODEL_OP2g( /, '/', long, float, float)
PK_OPMODEL_OP2g( /, '/', long, double, double)
PK_OPMODEL_OP2g( /, '/', long, sc_unsigned, sc_signed)
PK_OPMODEL_OP2g( /, '/', long, sc_signed, sc_signed)


//  sc_in_aug<unsigned> / type;

PK_OPMODEL_OP2c( /, '/', unsigned, int, int)
PK_OPMODEL_OP2c( /, '/', unsigned, short, int)
PK_OPMODEL_OP2c( /, '/', unsigned, long, long)
PK_OPMODEL_OP2c( /, '/', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2c( /, '/', unsigned, float, float)
PK_OPMODEL_OP2c( /, '/', unsigned, double, double)
PK_OPMODEL_OP2c( /, '/', unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( /, '/', unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP2e( /, '/', unsigned, int, int)
PK_OPMODEL_OP2e( /, '/', unsigned, short, int)
PK_OPMODEL_OP2e( /, '/', unsigned, long, long)
PK_OPMODEL_OP2e( /, '/', unsigned, unsigned, unsigned)
PK_OPMODEL_OP2e( /, '/', unsigned, float, float)
PK_OPMODEL_OP2e( /, '/', unsigned, double, double)
PK_OPMODEL_OP2e( /, '/', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e( /, '/', unsigned, sc_signed, sc_signed)

PK_OPMODEL_OP2g( /, '/', unsigned, float, float)
PK_OPMODEL_OP2g( /, '/', unsigned, double, double)
PK_OPMODEL_OP2g( /, '/', unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2g( /, '/', unsigned, sc_signed, sc_signed)


//  sc_in_aug<float> / type;

PK_OPMODEL_OP2c( /, '/', float, int, float)
PK_OPMODEL_OP2c( /, '/', float, short, float)
PK_OPMODEL_OP2c( /, '/', float, long, float)
PK_OPMODEL_OP2c( /, '/', float, unsigned, float)
PK_OPMODEL_OP2c( /, '/', float, float, float)
PK_OPMODEL_OP2c( /, '/', float, double, double)

PK_OPMODEL_OP2e( /, '/', float, int, float)
PK_OPMODEL_OP2e( /, '/', float, short, float)
PK_OPMODEL_OP2e( /, '/', float, long, float)
PK_OPMODEL_OP2e( /, '/', float, unsigned, float)
PK_OPMODEL_OP2e( /, '/', float, float, float)
PK_OPMODEL_OP2e( /, '/', float, double, double)

PK_OPMODEL_OP2g( /, '/', float, double, double)


//  sc_in_aug<double> / type;

PK_OPMODEL_OP2c( /, '/', double, int, double)
PK_OPMODEL_OP2c( /, '/', double, short, double)
PK_OPMODEL_OP2c( /, '/', double, long, double)
PK_OPMODEL_OP2c( /, '/', double, unsigned, double)
PK_OPMODEL_OP2c( /, '/', double, float, double)
PK_OPMODEL_OP2c( /, '/', double, double, double)

PK_OPMODEL_OP2e( /, '/', double, int, double)
PK_OPMODEL_OP2e( /, '/', double, short, double)
PK_OPMODEL_OP2e( /, '/', double, long, double)
PK_OPMODEL_OP2e( /, '/', double, unsigned, double)
PK_OPMODEL_OP2e( /, '/', double, float, double)
PK_OPMODEL_OP2e( /, '/', double, double, double)


//  sc_in_aug<sc_signed> / type;

PK_OPMODEL_OP2c( /, '/', sc_signed, int, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_signed, short, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_signed, long, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_signed, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_signed, sc_unsigned&, sc_signed)

PK_OPMODEL_OP2e( /, '/', sc_signed, int, sc_signed)
PK_OPMODEL_OP2e( /, '/', sc_signed, short, sc_signed)
PK_OPMODEL_OP2e( /, '/', sc_signed, long, sc_signed)
PK_OPMODEL_OP2e( /, '/', sc_signed, unsigned, sc_signed)
PK_OPMODEL_OP2e( /, '/', sc_signed, sc_unsigned, sc_signed)
PK_OPMODEL_OP2e( /, '/', sc_signed, sc_signed, sc_signed)

PK_OPMODEL_OP2g( /, '/', sc_signed, sc_unsigned, sc_signed)


//  sc_in_aug<sc_unsigned> / type;

PK_OPMODEL_OP2c( /, '/', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2c( /, '/', sc_unsigned, sc_signed&, sc_signed)
PK_OPMODEL_OP2c( /, '/', sc_unsigned, sc_unsigned&, sc_unsigned)

PK_OPMODEL_OP2e( /, '/', sc_unsigned, int, sc_signed)
PK_OPMODEL_OP2e( /, '/', sc_unsigned, short, sc_signed)
PK_OPMODEL_OP2e( /, '/', sc_unsigned, long, sc_signed)
PK_OPMODEL_OP2e( /, '/', sc_unsigned, unsigned, sc_unsigned)
PK_OPMODEL_OP2e( /, '/', sc_unsigned, sc_unsigned, sc_unsigned)
PK_OPMODEL_OP2e( /, '/', sc_unsigned, sc_signed, sc_signed)


#endif

