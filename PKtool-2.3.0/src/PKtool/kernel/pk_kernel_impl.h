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

#ifndef PK_KERNEL_IMPL_H
#define PK_KERNEL_IMPL_H




#include <fstream>
#include <vector>
#include <map>
#include "PKtool/power_models/pk_estimation.h"
#include "PKtool/power_models/pk_model_creator.h"
#include "PKtool/kernel/pk_settings.h"
#include "PKtool/types_aug/pk_aug_local.h"

#ifdef PK_ENABLE_TLM   

#include "PKtool/tlm/pk_tlm_socket_base.h"


#endif


using std::string;
using std::vector;


namespace pk_core
{


 class pk_read_cfg_data;
 void create_model( pk_kernel_impl* , unsigned );
 void set_init_pmodel(pk_kernel_impl* k_impl);          
 
 #ifdef PK_ENABLE_TLM

  void create_TLM_model( pk_kernel_impl* , power_model_b*&, unsigned );  

  using pk_tlm::pk_tlmfc_nb;

 #endif

 struct pk_sensitivity_handler;
 class power_module_b;
 class pk_aug_if;
 class pk_state_fc;
 class pk_dyndata_fc;
 class pk_model_lib_handler; 

 extern void pk_set_simtime(const sc_core::sc_time&);


// ----------------------------------------------------------------------------
//  STRUCT : pk_code_cfg
// ----------------------------------------------------------------------------


struct pk_code_cfg
{
 pk_state_fc* state_fc_pnts[PK_MAX_STATE_NB];  
 pk_dyndata_fc* dyndata_fc_pnts[PK_MAX_STATE_NB]; 
 std::map<sc_core::sc_module*, vector<pk_aug_if*> > aug_pnts;  
 unsigned state_nb;

 pk_code_cfg();

};


 extern std::map<const char*, pk_aug_local*> locdata_mod;  
 

// ----------------------------------------------------------------------------
//  CLASS : pk_kernel_impl
//
//   class with the Power Kernel implementation details  
// ----------------------------------------------------------------------------


class pk_kernel_impl
 {
  friend class power_model_b;
  friend class power_model_creator;
  friend class pk_creator_register;
  friend struct pk_sensitivity_handler;
  friend class power_module_b;  
  friend class pk_core::pk_read_cfg_data;
  friend class power_kernel;
  friend class pk_state_fc;
  friend class pk_dyndata_fc;
  friend class pk_set_estype_b;
  friend struct pk_initializer;
  friend void pk_core::pk_set_simtime(const sc_core::sc_time&); 
 
  #ifdef PK_ENABLE_TLM  
  friend void pk_core::create_TLM_model(pk_kernel_impl*, power_model_b*&, unsigned);
  friend struct pk_tlm::pk_enable_tlmfc;
  #endif

  friend void pk_core::create_model(pk_kernel_impl*, unsigned); 
  friend void pk_core::set_init_pmodel(pk_kernel_impl*);            
  

  
  template<class C> void clear_vec(vector<C>& v)
  {
   for(unsigned i=0; i<v.size(); i++) v[i] = 0;
   v.clear();
   return;
  }
  

  void initialize();

  void check_state();      

  void read_initial_data();
  
  bool power_state_change();

  void update_power_model();

  void update_power_state();


  void set_dynamic_data(int state);
  
  void init_aug_signals(); 

  void reset_augs();    

  void reset_aug_category( vector<pk_aug_if*>& );
  void reset_aug_category( pk_aug_local& );

  void do_cycle_estimation();
 
  void do_estimation();

  #ifdef PK_ENABLE_TLM

  void do_TLM_estimation( int TLM_fc);

  void print_TLM_est(); 

  void set_socket(pk_tlm::pk_socket_base*, int TLM_fc );

  void set_idle_power_data(const pk_read_cfg_data&);

  #endif

  void print_partial_est(); 

  void print_total_est();
 


 // constructor 

 pk_kernel_impl();

 // destructor

 ~pk_kernel_impl();

  vector<pk_aug_if*> intsignal_aug;
  vector<pk_aug_if*> inport_aug;
  vector<pk_aug_if*> outport_aug;
  vector<pk_aug_if*> inoutport_aug;

  pk_aug_local local_aug;  

  power_module_b* powmod_h;   
  bool& monitored;

  static bool set_simtime;
  static sc_core::sc_time sim_time;

  int initialization_deltas;

  const char* mod_name;
  int curr_st, past_st;   // current and past power state  
  sc_core::sc_time startime, endtime; // starting and final time of current power state 
  bool one_state;
  pk_est_type est_type;  
  pk_model_lib_handler* modlib_h;  
  unsigned st_changes;
  int state_nb, init_st;
  int pm_indexs[PK_MAX_STATE_NB];    
  power_model_b* power_models[PK_MAX_STATE_NB];
  power_model_b* pm; 
  pk_state_fc* state_fc_pnts[PK_MAX_STATE_NB];  
  pk_dyndata_fc* dyndata_fc_pnts[PK_MAX_STATE_NB]; 
  pk_estimation partial_est, total_est; 

  static pk_code_cfg pk_code_cfg_reg[PK_MAX_POWER_MODULE_NB];

  bool state_changed;  

  std::ofstream result_file;
  std::ifstream* file_in;
  std::string filename;

  #ifdef PK_ENABLE_TLM
  bool TLM_on, target_on, init_on;    
  bool TLMfc_on[pk_tlmfc_nb];
  bool idle_power_on;
  double  TLM_static_power;
  pk_estimation TLM_total_est;

  pk_tlm::tlm_power_model_b* implfc_pm;
  pk_tlm::pk_TLMfc_data  target_fc_data;
  pk_tlm::pk_socket_base*  socket_aug[PK_MAX_SOCKET_AUG_PER_MODULE];
  int socket_nb;
  #endif

  private:
 
 // disabled

 pk_kernel_impl(const pk_kernel_impl&);
 pk_kernel_impl& operator = (const pk_kernel_impl&);

};


}    //pk_core  



#endif
