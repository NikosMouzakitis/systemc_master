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



#ifndef POWER_MODULE_INIT_H
#define POWER_MODULE_INIT_H


POWER_MODULE_CLASS(select_initiator)
{

 PK_USES_ENERGY_MODELS

 PK_HAS_PROCESS(select_initiator);

 POWER_MODULE(select_initiator)
	 ( sc_core::sc_module_name name                
       , const unsigned int  ID                      
       , sc_core::sc_time end_rsp_delay        
	 ): 
     select_initiator(name,ID,end_rsp_delay), PK_PMB_CTOR
     {
	  PK_B_TRANSPORT_1(initiator_socket)
	  PK_NB_TRANSPORT_FW_1(initiator_socket)

	  PK_TLM_ENABLE_STATIC_POWER
	 }

	 PK_NB_TRANSPORT_BW_2

};


#endif