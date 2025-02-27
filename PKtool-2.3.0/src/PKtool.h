/***********************************************************************

Copyright (C) 2004 - 2011 by Giovanni B. Vece

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

#ifndef PKTOOL_H
#define PKTOOL_H

#include "PKtool/kernel/pk_settings.h"

#ifdef PK_ENABLE_TLM    //? new
#include "tlm.h"
#endif


#include "PKtool/utils/pk_report_ids.h"
#include "PKtool/utils/pk_report.h"
#include "PKtool/kernel/power_module_fcs.h"   
#include "PKtool/power_models/pk_model_creator.h"
#include "PKtool/utils/pk_user_macros.h"

#include "PKtool/types_aug/pk_aug_if.h"
#include "PKtool/types_aug/pk_cpptypes_aug.h"
#include "PKtool/types_aug/sc_signal_ports_aug.h" 
#include "PKtool/types_aug/sc_signal_rv_ports_aug.h"

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

//#endif                //?new


#include "PKtool/types_aug/pk_int_types.h"

using pk_dt::sc_int_aug;
using pk_dt::sc_uint_aug;
using pk_dt::sc_signed_aug;
using pk_dt::sc_unsigned_aug;
using pk_dt::sc_bigint_aug;
using pk_dt::sc_biguint_aug;

#ifdef SC_INCLUDE_FX

#include "PKtool/types_aug/pk_fix_types.h"

using pk_dt::sc_fix_aug;
using pk_dt::sc_fix_fast_aug;
using pk_dt::sc_fixed_aug;
using pk_dt::sc_ufix_aug;
using pk_dt::sc_ufix_fast_aug;
using pk_dt::sc_ufixed_aug;

#endif


using pk_core::sc_in_aug;
using pk_core::sc_out_aug;
using pk_core::sc_inout_aug;
using pk_core::sc_in_resolved_aug;
using pk_core::sc_inout_resolved_aug;
using pk_core::sc_out_resolved_aug;



#include "PKtool/power_models/pk_model_lib_header.h"
#include "PKtool/power_models/pk_default_lib.h"  


#ifdef PK_ENABLE_OPMODELS

using sc_dt::int64;
using sc_dt::sc_bigint;
using sc_dt::sc_biguint;
using sc_dt::sc_bit;
using sc_dt::sc_bv;
using sc_dt::sc_bv_base;
using sc_dt::sc_digit;
using sc_dt::sc_int;
using sc_dt::sc_int_base;
using sc_dt::sc_logic;
using sc_dt::sc_lv;
using sc_dt::sc_lv_base;
using sc_dt::sc_signed;
using sc_dt::sc_uint;
using sc_dt::sc_uint_base;
using sc_dt::sc_unsigned;
using sc_dt::uint64;

#include "PKtool/power_models/pk_model_operators_1.h"
#include "PKtool/power_models/pk_model_operators_2.h"
#include "PKtool/power_models/pk_model_operators_3.h"

#endif  


#include "PKtool/kernel/power_module_b.h"

using pk_core::pk_set_simtime;

extern pk_core::pk_istream pk_cin;
extern pk_core::pk_ostream pk_cout;


#ifdef PK_ENABLE_TLM    //? new

#include "PKtool/tlm/pk_tlm_socket_base.h"
#include "PKtool/tlm/pk_tlm_ifs.h"
#include "PKtool/tlm/pk_tlm_socket_aug.h"
#include "PKtool/tlm/pk_tlm_power_models.h"

#endif




#endif

