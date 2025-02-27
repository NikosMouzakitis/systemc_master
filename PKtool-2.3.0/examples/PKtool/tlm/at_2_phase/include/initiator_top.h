/**********************************************************************
    The following code is derived, directly or indirectly, from the SystemC
    source code Copyright (c) 1996-2008 by all Contributors.
    All Rights reserved.
 
    The contents of this file are subject to the restrictions and limitations
    set forth in the SystemC Open Source License Version 3.0 (the "License");
    You may not use this file except in compliance with such restrictions and
    limitations. You may obtain instructions on how to receive a copy of the
    License at http://www.systemc.org/. Software distributed by Contributors
    under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
    ANY KIND, either express or implied. See the License for the specific
    language governing rights and limitations under the License.
 *********************************************************************/

//=====================================================================
/// @file initiator_top.h
//
/// @brief Initiator top module contains a traffic generator and an 
///        example initiator module unique for the example
//
//=====================================================================
//  Original Authors:
//    Bill Bunton, ESLX
//    Charles Wilson, ESLX
//    Jack Donovan, ESLX
//=====================================================================

/*****************************************************************************
 
  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.
      
	  Name, Affiliation, Date:  Giovanni B. Vece, UniversitÓ Politecnica
	                            delle Marche (Italy).

  Description of Modification:  - Inclusion of the header file "power_module_init.h"
							    - The m_initiator module has been converted 
								  into a power_module.
                                
    
 *****************************************************************************/

#ifndef __INITIATOR_TOP_H__
#define __INITIATOR_TOP_H__

#include "tlm.h"                                // TLM headers
#include "select_initiator.h"                   // AT initiator
#include "traffic_generator.h"                  // traffic generator


#include "power_module_init.h"       // power_module header


class initiator_top                          		       
  : public sc_core::sc_module                       
  , virtual public tlm::tlm_bw_transport_if<>  // backward non-blocking interface
{
//Member Methods  =====================================================  

  public:
	  
//=====================================================================
///  @fn initiator_top::initiator_top
//	    
///  @brief initiator_top constructor
//	    
///  @details
///    Initiator top module contains a traffic generator and an example 
///    unique initiator module
//
//===================================================================== 
  initiator_top 	                                   
  ( sc_core::sc_module_name name                ///< module name
  , const unsigned int  ID                      ///< initiator ID
  , sc_dt::uint64       base_address_1          ///< first base address
  , sc_dt::uint64       base_address_2          ///< second base address
  , unsigned int        active_txn_count        ///< Max number of active transactions  
  );
  
private: 

/// Not Implemented for this example but required by the initiator socket
  void												
  invalidate_direct_mem_ptr					
  ( sc_dt::uint64      start_range                        
  , sc_dt::uint64      end_range                 
  );
    
/// Not Implemented for this example but require by the initiator socket
  tlm::tlm_sync_enum	 
  nb_transport_bw								
  ( tlm::tlm_generic_payload  &payload
  , tlm::tlm_phase            &phase
  , sc_core::sc_time          &delta
  );

//Member Variables/Objects  ===========================================

  public:
  
  tlm::tlm_initiator_socket<> initiator_socket;	///< processor socket

  private:
  
  typedef tlm::tlm_generic_payload  *gp_ptr;   ///< Generic Payload pointer
  
  sc_core::sc_fifo <gp_ptr>  m_request_fifo;   ///< request SC FIFO
  sc_core::sc_fifo <gp_ptr>  m_response_fifo;  ///< response SC FIFO
  
  const unsigned int         m_ID;             ///< initiator ID
  bool                       m_enable_target_tracking; ///< track target timing
    
  POWER_MODULE(select_initiator)     m_initiator;      ///power_module conversion
                                                             
  traffic_generator          m_traffic_gen;    ///< traffic generator instance

};

#endif /* __INITIATOR_TOP_H__ */
