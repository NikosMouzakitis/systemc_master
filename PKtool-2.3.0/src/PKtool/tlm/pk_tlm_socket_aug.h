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

#ifndef TLM_SOCKETS_AUG_H
#define TLM_SOCKETS_AUG_H


namespace pk_tlm
{


 // ----------------------------------------------------------------------------
 //  CLASS : tlm_initiator_socket_aug  
 // ----------------------------------------------------------------------------

 template <unsigned int BUSWIDTH = 32,
	       typename TYPES = tlm::tlm_base_protocol_types,
           int N = 1
  #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
          ,sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
  #endif
          >
 class tlm_initiator_socket_aug: 
	     public tlm::tlm_initiator_socket<BUSWIDTH, TYPES, N
                       #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                         ,POL
                       #endif
                                         >, public pk_socket_base
 {
  friend class pk_core::power_module_b;

  typedef   tlm::tlm_initiator_socket<BUSWIDTH, TYPES, N
                       #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                         ,POL
                       #endif
                                         >    base_type;

  typedef tlm::tlm_fw_transport_if<TYPES>   FW_IF_;


  typedef sc_core::sc_port<FW_IF_, N 
	        #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                ,POL
            #endif
							> port_type;

  typedef pk_tlm_fwport_wrap<BUSWIDTH, TYPES, N 
	  #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                   ,POL 
      #endif
                          >   port_wrap_type;


  public:

  tlm_initiator_socket_aug() :pk_socket_base(this->name()), 
	                          port_wrap(static_cast<port_type&>(*this), fc_data)
  {}


  tlm_initiator_socket_aug(const char* name) : 
		               tlm::tlm_initiator_socket<BUSWIDTH, TYPES, N
                       #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                    ,POL
                       #endif
					   > (name), 
					   pk_socket_base(name),
					   port_wrap(static_cast<port_type&>(*this), fc_data)
  {}
 
 
  inline port_wrap_type* operator -> ()
  { return &port_wrap; };
 
  
  inline const port_wrap_type* operator -> () const
  { return &port_wrap; };
  

  private:
  
  port_wrap_type   port_wrap;

 };


 // ----------------------------------------------------------------------------
 //  CLASS : tlm_target_socket_aug  
 // ----------------------------------------------------------------------------


  template <unsigned int BUSWIDTH = 32,
	        typename TYPES = tlm::tlm_base_protocol_types,
            int N = 1
  #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
            ,sc_core::sc_port_policy POL = sc_core::SC_ONE_OR_MORE_BOUND
  #endif
          >
 class tlm_target_socket_aug: 
	     public tlm::tlm_target_socket<BUSWIDTH, TYPES, N
                       #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                         ,POL
                       #endif
                                         >, 
		 public pk_socket_base
 {
  friend class pk_core::power_module_b;

  typedef   tlm::tlm_target_socket<BUSWIDTH, TYPES, N
                       #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                         ,POL
                       #endif
                                         >    base_type;

  typedef tlm::tlm_bw_transport_if<TYPES>   BW_IF_;


  typedef sc_core::sc_port<BW_IF_, N 
	        #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                ,POL
            #endif
							> port_type;

  typedef pk_tlm_bwport_wrap<BUSWIDTH, TYPES, N 
	  #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                   ,POL 
      #endif
                          >   port_wrap_type;


  public:

  tlm_target_socket_aug() :pk_socket_base(this->name()), 
	  port_wrap(static_cast<port_type&>(*this), fc_data)
  {}


  tlm_target_socket_aug(const char* name) : 
		               tlm::tlm_initiator_socket<BUSWIDTH, TYPES, N
                       #if !(defined SYSTEMC_VERSION & SYSTEMC_VERSION <= 20050714)
                                    ,POL
                       #endif
					   > (name), 
					   pk_socket_base(name),
					   port_wrap(static_cast<port_type&>(*this), fc_data)
  {}
 
 
  inline port_wrap_type* operator -> ()
  { return &port_wrap; };
 
  
  inline const port_wrap_type* operator -> () const
  { return &port_wrap; };
  

  private:
  
  port_wrap_type   port_wrap;

 };

}   //pk_tlm






#endif

