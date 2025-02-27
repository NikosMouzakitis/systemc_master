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


#include "PKtool/kernel/pk_kernel_syscrefs.h"
#include "PKtool/types_aug/pk_augdata_base.h"
#include "PKtool/utils/pk_report_ids.h"
#include "PKtool/kernel/pk_kernel_impl.h"
#include "PKtool/kernel/power_module_fcs.h"  
#include "PKtool/kernel/power_kernel.h" 
#include "PKtool/types_aug/pk_aug_if.h"
#include "PKtool/kernel/pk_read_cfg_data.h"   
#include "PKtool/kernel/power_module_b.h"  
#include "PKtool/power_models/power_model_b.h"
#include "PKtool/utils/pk_report.h"
#include "PKtool/kernel/power_module_fcs.h"

#ifdef PK_ENABLE_TLM

#include "PKtool/tlm/pk_tlm_power_model_b.h"

#endif





namespace
{
 std::string message;


 const char* error_msg1(int state)
 { 
  char st_ch[4];
  std::string msg;
  message += "The state function for the state ";
  ::sprintf(st_ch,"%d",state);
  message += st_ch;
  message += " is not defined, or the power state enumeration has been wrongly defined";
  message +="\n";                   
  return message.c_str();           
 };


};

namespace           
{
 bool old_enum_rule = false;

};


namespace pk_core    
{

 void pk_set_simtime(const sc_core::sc_time& sim_time_)
 {
  pk_kernel_impl::set_simtime = true;
  pk_kernel_impl::sim_time = sim_time_;
 };
 

// ----------------------------------------------------------------------------
//  STRUCT : pk_code_cfg
// ----------------------------------------------------------------------------


pk_code_cfg:: pk_code_cfg(): state_nb(0) 
{

  for(int i=0; i<PK_MAX_STATE_NB; ++i)
  {
   state_fc_pnts[i] = 0;
   dyndata_fc_pnts[i] = 0;
  };



 };

// ----------------------------------------------------------------------------
//  CLASS : pk_kernel_impl
// ----------------------------------------------------------------------------



pk_code_cfg pk_kernel_impl::pk_code_cfg_reg[PK_MAX_POWER_MODULE_NB];

bool pk_kernel_impl::set_simtime(false);
sc_core::sc_time pk_kernel_impl::sim_time;

  
pk_kernel_impl::pk_kernel_impl():
      powmod_h( power_module_b::curr_powmod() ), 
     monitored(powmod_h->monitored), 
	 initialization_deltas( PK_DELTA_INITMAX_DEFAULT ), 
	 mod_name(power_module_b::curr_modname), one_state(false), 
	 est_type(pk_energy), modlib_h(0), st_changes(0),state_nb(0) 
	  
 {  initialize();  };


 pk_kernel_impl::~pk_kernel_impl()
 { };

 void pk_kernel_impl::check_state()       
 {
  if(!one_state)
  {
   bool& old_rule = old_enum_rule;
   if(!state_fc_pnts[0]) 
   {
    old_rule = true;
    for(int i=0; i<state_nb; ++i)
    {
	 state_fc_pnts[i] = state_fc_pnts[i+1];
	 dyndata_fc_pnts[i] = dyndata_fc_pnts[i+1];
    }
   }
   for(int i=0; i<state_nb; ++i)
   { 
    if( (!old_rule && !state_fc_pnts[i]) || (old_rule && !state_fc_pnts[i+1]) )
    {
	 int state_nb = old_rule ? i : i+1 ;
	 PK_REPORT_ERROR(PK_UNDEFINED_STATE_FC_, error_msg1( state_nb ));
    }
   };
  };
 };
 

 bool pk_kernel_impl::power_state_change()
 {
  if(init_st != -1)   //new2   if(init_st!=0)
  {
   update_power_state();                                    
   if(curr_st != past_st)
   {
	if(dyndata_fc_pnts[past_st - 1]) 
	  { set_dynamic_data(past_st - 1); }; 
	 endtime = sc_core::sc_time_stamp();   
	 state_changed = true;
	 return true;         
    };
   };
   return false;
  }; 

 void pk_kernel_impl::update_power_model()
 {
  if(init_st == -1) pm = power_models[0];  
  else pm = power_models[curr_st - 1];  
  if(!pm)
  {
   cout<<"ERROR: No power model assigned to the power state number "<<(curr_st -1)<<endl;
   cout<<"Probably you haven't defined the state function for this power state"<<endl;
   exit(1);
  };
  reset_augs( );   
  pm->set_signals(*this); 
  return;
 };


 void pk_kernel_impl::update_power_state()
 {
  if(state_fc_pnts[curr_st-1] == 0)  
  {
   PK_REPORT_ERROR(PK_UNDEFINED_STATE_FC_, error_msg1( curr_st ));
  }
  else
  curr_st = (state_fc_pnts[curr_st-1]->state_fc() + 1);    
  if(old_enum_rule) --curr_st;                             
 };

 void pk_kernel_impl::set_dynamic_data(int state)
 {
  if(dyndata_fc_pnts[state]) dyndata_fc_pnts[state]->pk_mod_fnc(); 
 };



void pk_kernel_impl::initialize()
{
  for(int i=0; i<PK_MAX_STATE_NB; ++i)
  {
   pm_indexs[i] = -1;
   power_models[i] = 0;
   dyndata_fc_pnts[i] = 0;
   state_fc_pnts[i] = 0;
  };

  #ifdef PK_ENABLE_TLM

  TLM_on = target_on = init_on = false;
  for(int i=0; i<pk_tlmfc_nb; ++i) TLMfc_on[i] = false;
  
  idle_power_on = false;
  TLM_static_power = 0;
  socket_nb = 0;
  for(int i=0;  i<PK_MAX_SOCKET_AUG_PER_MODULE;  ++i)
		   socket_aug[i] = 0;

  #endif

  init_aug_signals();
};

void pk_kernel_impl::read_initial_data()
{ 
  pk_read_cfg_data rid_ob(this);  
  rid_ob.read_options();                                
  rid_ob.read_cfg_data_();                              

};



 void pk_kernel_impl::init_aug_signals()                                                                 
 {                                                                                                                                                                            
  intsignal_aug = pk_aug_if::intsignal_aug;                                                           
  inport_aug = pk_aug_if::inport_aug;                                                     
  outport_aug = pk_aug_if::outport_aug;                                                   
  inoutport_aug = pk_aug_if::inoutport_aug; 

  int sz = intsignal_aug.size();
  for(int i=0; i<sz;  ++i)   intsignal_aug[i]->enabled = true; 
  sz= inport_aug.size();
  for(int i=0; i<sz;  ++i)   inport_aug[i]->enabled = true;
  sz= outport_aug.size();
  for(int i=0; i<sz;  ++i) outport_aug[i]->enabled = true;
  sz= inoutport_aug.size();
  for(int i=0; i<sz;  ++i) inoutport_aug[i]->enabled = true;
                                                                                        
  clear_vec(pk_aug_if::intsignal_aug);                                                        
  clear_vec(pk_aug_if::inport_aug);                                                     
  clear_vec(pk_aug_if::outport_aug);                                                    
  clear_vec(pk_aug_if::inoutport_aug);  
 }; 

 void pk_kernel_impl::reset_augs()   
 {
  reset_aug_category(this->outport_aug); 
  reset_aug_category(this->inoutport_aug); 
  reset_aug_category(this->intsignal_aug); 
  reset_aug_category(this->inport_aug); 
  reset_aug_category(this->local_aug);  
 }; 


 void pk_kernel_impl::reset_aug_category( vector<pk_aug_if*>& v )   
 {
  for(unsigned i=0; i<v.size(); i++) 
  {
   pk_augdata_base& pab = ( const_cast<pk_augdata_base&>(v[i]->data()) );
   pab.reset_data();
  }
  return;
 }  

 void pk_kernel_impl::reset_aug_category( pk_aug_local& al)  
 {
  al.partial_comm = 0;
  std::list<pk_aug_if*>::iterator it = al.localsign_aug.begin();
  while( it != al.localsign_aug.end() )
  {
   (*it)->data().reset_data(); 
   ++it;
  }
 };

 
 void pk_kernel_impl::do_cycle_estimation()
 {
  partial_est += pm->get_estimation();
  total_est += partial_est;
 };

 void pk_kernel_impl::do_estimation()
 {
  partial_est = pm->get_estimation();
  total_est += partial_est;
 };


 #ifdef PK_ENABLE_TLM

 void pk_kernel_impl::do_TLM_estimation( int TLM_fc)
 {
  ++target_fc_data.TLMfc_calls[TLM_fc];
  target_fc_data.TLMfc_est[TLM_fc] +=  target_fc_data.TLMfc_pm[TLM_fc]->get_estimation();
 };

 void pk_kernel_impl::print_TLM_est( )
 {
   sc_core::sc_time sim_time_ = (set_simtime ? this->sim_time : sc_core::sc_time_stamp()  );
   result_file<<"overall simulation period: [0 - "<<sim_time_<<"]"<<endl<<endl;
   double time_gap = sim_time_.to_seconds();
   double active_time = 0;
   double overall_energy = 0;
   if(target_on)
   {
    result_file<<"    POWER/ENERGY DISSIPATION OF IMPLEMENTED TLM FUNCTIONS   "<<endl<<endl; 
	pk_tlm::pk_TLMfc_data& fd = target_fc_data;
    for(int i=0; i<pk_tlmfc_nb; ++i)
	 if( fd.TLMfc_pm[i] )   
	 {
	  pk_estimation& est = fd.TLMfc_est[i];
	  result_file<<"function: "<<pk_tlm::pk_fc_names[i]<<endl;
	  result_file<<" function calls = "<<fd.TLMfc_calls[i]<<endl;
	  if(idle_power_on)  active_time += fd.TLMfc_calls[i]*fd.TLMfc_exectimes[i];
      fd.TLMfc_pm[i]->print_custom_result(result_file);
	  result_file<<" "<<est.type_name()<<" estimation = "<<est<<" "<<est.symbol_name()<<endl;
	  result_file<<" average "<<est.rate_type_name()<<" estimation = "
		 <<est.rate_value(time_gap)<<" "<<est.rate_symbol_name()<<endl<<endl;
      TLM_total_est += est;
	 }
    }
   if(socket_nb > 0)
      result_file<<endl<<"    POWER/ENERGY DISSIPATION OF SOCKET TLM FUNCTIONS   "<<endl<<endl;  
   for(int i=0; i<socket_nb; ++i)
   {
	pk_tlm::pk_socket_base* s = socket_aug[i];
	pk_tlm::pk_TLMfc_data& fd = s->fc_data;
	result_file<<endl<<"SOCKET: "<<s->name<<endl<<endl;
	for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)
	{
	 if(fd.TLMfc_on[i])
	 {
	  pk_estimation& est = fd.TLMfc_est[i];
	  if(idle_power_on)  active_time += fd.TLMfc_calls[i]*fd.TLMfc_exectimes[i];
	  result_file<<"function: "<<pk_tlm::pk_fc_names[i]<<endl;;
	  result_file<<" function calls = "<<fd.TLMfc_calls[i]<<endl; 
	  fd.TLMfc_pm[i]->print_custom_result(result_file);
	  result_file<<" "<<est.type_name()<<" estimation = "<<est<<" "<<est.symbol_name()<<endl;
	  result_file<<" average "<<est.rate_type_name()<<" estimation = "
		 <<est.rate_value(time_gap)<<" "<<est.rate_symbol_name()<<endl<<endl;
      TLM_total_est += est;
	 }
	}
   }
    
   result_file<<"overall transaction "<<TLM_total_est.type_name()<<" estimation: "<<TLM_total_est<<" "<<TLM_total_est.symbol_name()<<endl;
   result_file<<"average transaction "<<TLM_total_est.rate_type_name()<<" estimation: "
   <<TLM_total_est.rate_value(time_gap)<<" "<<TLM_total_est.rate_symbol_name()<<endl<<endl;

   overall_energy += (dynamic_cast<pk_energy_type&>(TLM_total_est.value())).value();

   if(idle_power_on) 
   {
     active_time *= (1e-9);
     double idle_time = time_gap - active_time;
     double energy = TLM_static_power*(1e-3)*idle_time;

	 result_file<<endl<<"    ENERGY DISSIPATION IN IDLE STATES     "<<endl<<endl;  
	 result_file<<" overall idle time: "<<idle_time<<endl<<endl;
	 result_file<<" idle energy dissipation: "<<energy<<"J"<<endl;
	 overall_energy += energy;
   }

   result_file<<endl<<endl;
   result_file<<"OVERALL ENERGY ESTIMATION: "<<overall_energy<<" J"<<endl;
   result_file<<"AVERAGE POWER ESTIMATION:  "<<overall_energy/time_gap<<" W"<<endl<<endl;

  };
 

 void pk_kernel_impl::set_socket(pk_tlm::pk_socket_base* s, int TLM_fc )
 {
  if( TLM_on == false ) TLM_on = true;
  if( init_on == false ) init_on = true;
  s->fc_data.TLMfc_on[TLM_fc] = true;
  if (!s->enabled)
  {
   s->enabled = true;
   if(socket_nb >= PK_MAX_SOCKET_AUG_PER_MODULE)
   {
	cout<<"ERROR"<<endl;  // to be completed
	exit(1);
   }
   socket_aug[socket_nb] = s;
   ++socket_nb;
  }
  
 };


 void pk_kernel_impl::set_idle_power_data(const pk_read_cfg_data& dt)
 {
  if(reading_option == 1) 
  {
   pk_cout<<endl<<endl<<"    POWER DISSIPATION IN IDLE STATES "<<endl<<endl;  
  
   pk_cout<<"static power(mW) = ";
   pk_cin>>TLM_static_power;
   pk_cout<<endl<<endl;

   pk_cout<<endl<<endl<<"   Execution times of the selected TLM functions "<<endl<<endl;
   if(this->target_on)
   {
     pk_cout<<endl<<"Implemented functions"<<endl<<endl;
    (const_cast<pk_read_cfg_data&>(dt)).read_exectimes(this->target_fc_data);
   }
   if(this->init_on)
   {
    for(int i=0; i<this->socket_nb; ++i)
	{
	 pk_tlm::pk_socket_base* s = this->socket_aug[i];
	 pk_cout<<endl<<"Socket: "<<s->name<<endl;
	 (const_cast<pk_read_cfg_data&>(dt)).read_exectimes(s->fc_data);  
	}
   }
  }
  else 
  {
   std::ifstream& f = const_cast<std::ifstream&>(dt.infile);
   do 
   {f>>tmp_ch; }
   while(tmp_ch != '=');
   f>>TLM_static_power;
   if(this->target_on)
     (const_cast<pk_read_cfg_data&>(dt)).read_exectimes(this->target_fc_data);
   if(this->init_on)
   {
    for(int i=0; i<this->socket_nb; ++i)
	{
	 pk_tlm::pk_socket_base* s = this->socket_aug[i];
	 (const_cast<pk_read_cfg_data&>(dt)).read_exectimes(s->fc_data);  
	}
   }
  }
 };

 #endif

  void pk_kernel_impl::print_partial_est()
  {
   sc_core::sc_time time_gap = endtime - startime;
   result_file<<"partial "<<partial_est.type_name()<<" estimation: "<<partial_est<<" "<<partial_est.symbol_name()<<endl;
   if (partial_est.is_rate_defined())
   {
    result_file<<"average "<<partial_est.rate_type_name()<<" estimation: "<<partial_est.rate_value(time_gap.to_seconds())
		<<" "<<partial_est.rate_symbol_name()<<endl<<endl;
   };
  };

  void pk_kernel_impl::print_total_est()
  {
   double time_gap = (set_simtime ? this->sim_time : sc_core::sc_time_stamp()  ).to_seconds();
   result_file<<"overall "<<total_est.type_name()<<" estimation: "<<total_est<<" "<<total_est.symbol_name()<<endl;
   result_file<<"average "<<total_est.rate_type_name()<<" estimation: "
   <<total_est.rate_value(time_gap)<<" "<<total_est.rate_symbol_name()<<endl<<endl;
  };



};    //pk_core  

