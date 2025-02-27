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



#ifndef POWER_MODULE_TRG_H
#define POWER_MODULE_TRG_H


POWER_MODULE_CLASS(at_target_2_phase)
{

 PK_USES_ENERGY_MODELS

 PK_HAS_PROCESS(at_target_2_phase);

 POWER_MODULE(at_target_2_phase)
	 ( sc_core::sc_module_name   module_name           ///< SC module name
  , const unsigned int        ID                    ///< target ID
  , const char                *memory_socket        ///< socket name
  , sc_dt::uint64             memory_size           ///< memory size (bytes)
  , unsigned int              memory_width          ///< memory width (bytes)
  , const sc_core::sc_time    accept_delay          ///< accept delay (SC_TIME, SC_NS)
  , const sc_core::sc_time    read_response_delay   ///< read response delay (SC_TIME, SC_NS)
  , const sc_core::sc_time    write_response_delay  ///< write response delay (SC_TIME, SC_NS)
  ):
     at_target_2_phase(module_name,ID,memory_socket,memory_size,memory_width,
		               accept_delay,read_response_delay,write_response_delay),
	
	 PK_PMB_CTOR
     { }

    
	 PK_NB_TRANSPORT_FW_2 
	 PK_GET_DIRECT_MEM_PTR_2  
  
};


#endif