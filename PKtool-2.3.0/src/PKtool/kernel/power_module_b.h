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

#ifndef POWER_MODULE_B_H
#define POWER_MODULE_B_H

#include "PKtool/power_models/power_model_b.h"  
#include "PKtool/kernel/power_kernel.h"
#include "PKtool/kernel/pk_kernel_impl.h"
#include "PKtool/kernel/pk_sensitive.h"
#include "PKtool/kernel/pk_kernel_syscrefs.h"  


#ifdef PK_ENABLE_TLM

#include "PKtool/tlm/pk_tlm_power_model_b.h"
#include "PKtool/tlm/pk_tlm_socket_base.h"

#endif



namespace pk_core  
{

//forward declarations

class power_module_b;



// ----------------------------------------------------------------------------
//  STRUCT : pk_sensitivity_handler 
// ----------------------------------------------------------------------------

struct pk_sensitivity_handler
{
 
 pk_sensitivity_handler(const power_kernel& pk_):
   inportsens_enabled(false), modelsens_enabled(false), 
   FSMsens_enabled(false), pk(pk_)
 {};
  

 inline bool make_inport_proc() const
 { return ( (!inportsens_enabled) && ( pk.k_impl->inport_aug.size() > 0 ) ); } 
   
 inline bool make_cyclemodel_proc() const
 { return ( (!modelsens_enabled) ); }   

 inline bool make_FSM_proc() const
 { return ( (!FSMsens_enabled) && ( pk.k_impl->state_nb > 1 ) );  }

 
 bool inportsens_enabled, modelsens_enabled, FSMsens_enabled;

 private:

 const power_kernel& pk;

};



// ----------------------------------------------------------------------------
//  CLASS : pk_final_action_helper 
//  This class is aimed to guarantee the execution of the final tasks, 
//   in case of power_module instanced dynamically and not deleted  explicitly.
//     
// ----------------------------------------------------------------------------


class pk_final_action_helper
{
 friend class power_module_b;

 static power_module_b* powmod_h[PK_MAX_POWER_MODULE_NB];

 public:
 
 pk_final_action_helper();

 ~pk_final_action_helper();

 static int counter;
 
};

extern pk_final_action_helper final_action_obj;



// ----------------------------------------------------------------------------
//  CLASS : power_module_b  
// ----------------------------------------------------------------------------


class power_module_b:  public sc_core::sc_module
{
 friend class pk_kernel_impl;
 friend class power_kernel;
 friend class pk_state_fc;
 friend class pk_dyndata_fc;
 friend class pk_set_estype_b;
 friend class pk_sensitive;  
 friend class pk_sensitive_pos;
 friend class pk_sensitive_neg;
 friend class pk_final_action_helper;
 friend class pk_read_cfg_data;  
 #ifdef PK_ENABLE_TLM  
  friend struct pk_tlm::pk_enable_tlmfc;    
 #endif

 protected:

 //constructor

 power_module_b(const char* nm);


 static power_module_b* curr_powmod( power_module_b* pmb = 0 );


 virtual void powmod_dtor()   // emulates the power module destructor, 
 {};                          // does nothing by default

 

 public:  


 inline void sensitivity_proc()   
 { 
  while(true)
  {
   for(int i=0; i<stabilization_deltas; ++i) { sc_core::wait(sc_core::SC_ZERO_TIME); };
   sensitivity_ev.notify();    
   sc_core::wait();
  }
 }  


 inline void modelcycle_proc()       
 { 
  while(true)
  {
   wait(sc_core::SC_ZERO_TIME);
   if( pk.curr_pm()->cycle_accurate() ) 
      pk.do_cycle_estimation();
   wait();
  };
 };



 void initialize_augs()   
 {  pk.initialize_augs();};




 inline void powerFSM_proc()
 {  pk.powerFSM_task(); };  

 void update_inport_proc()   
 { pk.update_inport_augs();	};

 
 protected:

 void initialize();    

 virtual void make_base_procs() = 0;
 
 inline void set_init_deltas( int value )
 { 
  if(0 < value)
	pk.initialization_deltas( value ); 
 };

 inline void set_stab_deltas(int value)
 {
  if(0 < value)   
        stabilization_deltas = value;   
 };


 
 void end_of_elaboration();


 #ifdef PK_ENABLE_TLM

 inline void do_TLM_estimation( int TLM_fc)
 {  pk.k_impl->do_TLM_estimation(TLM_fc);  }

  void b_trans_estim(const tlm::tlm_generic_payload& gp, const sc_core::sc_time& t)
  {
   ++TLMfc_pmodels.TLMfc_calls[pk_tlm::PK_B_TRANS];
   TLMfc_pmodels.TLMfc_est[pk_tlm::PK_B_TRANS] += TLMfc_pmodels.TLMfc_pm[pk_tlm::PK_B_TRANS]->b_trans_estim(gp, t);
  };

  void nb_transfw_estim(const tlm::tlm_generic_payload& gp, 
	                    const tlm::tlm_phase& ph,
 	                    const sc_core::sc_time& t,
						const tlm::tlm_sync_enum st)
  { 
   ++TLMfc_pmodels.TLMfc_calls[pk_tlm::PK_NB_FW_TRANS];
   TLMfc_pmodels.TLMfc_est[pk_tlm::PK_NB_FW_TRANS] += TLMfc_pmodels.TLMfc_pm[pk_tlm::PK_NB_FW_TRANS]->nb_transfw_estim(gp, ph, t, st);
  };

  void nb_transbw_estim(const tlm::tlm_generic_payload& gp,
	                    const tlm::tlm_phase& ph,
	                    const sc_core::sc_time& t,
						const tlm::tlm_sync_enum st)
  {
   ++TLMfc_pmodels.TLMfc_calls[pk_tlm::PK_NB_BW_TRANS];
   TLMfc_pmodels.TLMfc_est[pk_tlm::PK_NB_BW_TRANS] += TLMfc_pmodels.TLMfc_pm[pk_tlm::PK_NB_BW_TRANS]->nb_transbw_estim(gp, ph, t, st);
  };

  void get_dirmem_estim(const tlm::tlm_generic_payload& gp, const tlm::tlm_dmi& d )
  {
   ++TLMfc_pmodels.TLMfc_calls[pk_tlm::PK_FW_DIR_MEM_IF];
   TLMfc_pmodels.TLMfc_est[pk_tlm::PK_FW_DIR_MEM_IF] += TLMfc_pmodels.TLMfc_pm[pk_tlm::PK_FW_DIR_MEM_IF]->get_dirmem_estim(gp, d);
  };
  
 
  void inv_dirmem_estim(const sc_dt::uint64& start, const sc_dt::uint64& end )  
  {
   ++TLMfc_pmodels.TLMfc_calls[pk_tlm::PK_BW_DIR_MEM_IF];
   TLMfc_pmodels.TLMfc_est[pk_tlm::PK_BW_DIR_MEM_IF] += TLMfc_pmodels.TLMfc_pm[pk_tlm::PK_BW_DIR_MEM_IF]->inv_dirmem_estim(start, end);
  };

 inline void enable_TLM_idle_estim()
 { pk.k_impl->idle_power_on = true; }

 inline void set_socket(pk_tlm::pk_socket_base* s, int TLM_fc )
 { pk.k_impl->set_socket(s, TLM_fc); }
  

 #endif


 inline void final_action()
 { 
  if( monitored && (!final_action_done) )     
  {
   final_action_done = true;
   for(int i=0; i<PK_MAX_POWER_MODULE_NB; ++i) 
   {
	if(pk_final_action_helper::powmod_h[i] == this) 
	      { pk_final_action_helper::powmod_h[i] = 0; break; }
   };
   pk.final_action();
  } 
 }

 virtual ~power_module_b()
 {};

 private:

 static sc_core::sc_module_name  compose_pmb_nm( const char* );

 void start_of_simulation();  


 class set_curr_powmod
 {
  friend class power_module_b;

  //constructor
  explicit set_curr_powmod(power_module_b* pmb)
  {power_module_b::curr_powmod(pmb);}

 };

 set_curr_powmod scp;

 protected:

 bool monitored, initialized;

 sc_core::sc_event updcomm_ev; 
 sc_core::sc_event sensitivity_ev; 
 pk_sensitivity_handler* psh;


 private:

 power_kernel pk;
 static const char* curr_modname;
 bool& one_state;
 bool final_action_done;  
 int stabilization_deltas;  

 #ifdef PK_ENABLE_TLM
    pk_tlm::pk_TLMfc_data& TLMfc_pmodels;
 #endif

};



}   // pk_core   



#endif



