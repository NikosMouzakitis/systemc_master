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


#ifndef PK_USER_MACROS_H
#define PK_USER_MACROS_H



#define POWER_MODULE_CLASS( sc_mod )  struct POWER_MODULE(sc_mod) : public sc_mod, public pk_core::power_module_b  

#define POWER_MODULE( sc_mod ) pk_powmod_##sc_mod

 
#define PK_POWER_MODEL_ESTIMATION_TYPE( tp )                                    \
	template<int n,class A = pk_used_##tp##_lib::pk_power_model_tag<n> >        \
                                                struct power_model_real_type    \
     {  typedef typename A::pk_pm_name  model_type;  };                         \
                                                                                \
                                                                                \
                                                                                \
	  pk_core::pk_set_estype< pk_core::pk_##tp##_type > pk_set_estype_ob;


#define PK_USES_ENERGY_MODELS     PK_POWER_MODEL_ESTIMATION_TYPE(energy)

#define PK_USES_COMMUTATION_MODELS   PK_POWER_MODEL_ESTIMATION_TYPE(comm)


#define PK_DYNDATA_FC(state, pm_ind)                                                    \
                                                                                        \
  class pk_dyndata_##state : private pk_core::pk_dyndata_fc                             \
  {                                                                                     \
   public:                                                                              \
                                                                                        \
   typedef power_model_real_type< pm_ind >::model_type  pm_real_type;                   \
                                                                                        \
                                                                                        \
   private:                                                                             \
                                                                                        \
   void pk_mod_fnc()                                                                    \
   {                                                                                    \
    static powmod_type& powmod = dynamic_cast<powmod_type&>(*powmod_h);                 \
	pk_core::power_model_b* pm_pnt = power_model();                                     \
	pm_real_type* pm =  dynamic_cast<pm_real_type*>(pm_pnt);                            \
    if(!pm)                                                                             \
	  { PK_REPORT_ERROR( PK_MODEL_MISMATCH_IN_DYNDATA_FC_, error_msg1( pm_ind, pm_ind ) );  }   \
	else                                                                                \
	{ powmod.pk_dyndata_##state##_fc (*pm);  };                                         \
   };                                                                                   \
                                                                                        \
  const char* error_msg1(	int index, int model_index ) 							    \
  {	 																					\
   static std::string message;                                                          \
   message.clear();                                                                     \
   char index_str[10];                                                                  \
   char model_index_str[10];                                                            \
   ::sprintf( index_str, "%d", index );                                                 \
   ::sprintf( model_index_str, "%d", model_index );                                     \
                                                                                        \
   message += "the power model index specified in a dynamic data function ";			\
   message += "doesn't correspond with the real power model index.";  message += "\n";	\
   message += "specified index: ";   message += index_str;  message += "\n";            \
   message += "real model index: ";   message += model_index_str;  message += "\n";	    \
																						\
   return message.c_str();																\
  };																					\
																						\
																						\
  public:                                                                               \
                                                                                        \
  pk_dyndata_##state () : pk_dyndata_fc( state )                                        \
  { };                                                                                  \
	                                                                                    \
                                                                                        \
                                                                                        \
                                                                                        \
                                                                                        \
 };                                                                                     \
 pk_dyndata_##state dyndata_obj##state;                                                 \
                                                                                        \
																						\
void pk_dyndata_##state##_fc (pk_dyndata_##state ::pm_real_type& model)

#define PK_STATE_FC(state)                                                             \
                                                                                        \
class pk_##state##_fc: private pk_core::pk_state_fc                                              \
 {                                                                                      \
                                                                                        \
                                                                                        \
   unsigned state_fc()                                                                  \
   {                                                                                    \
    powmod_type* mod = dynamic_cast< powmod_type* >(powmod_h);                                \
	if(!mod)                                                                            \
	{                                                                                   \
	 cout<<"ERROR"<<endl;                                                               \
     exit(1);                                                                           \
	}                                                                                   \
	else return mod-> state##_fc();                                                            \
   };                                                                                   \
                                                                                        \
    public:                                                                             \
                                                                                        \
  pk_##state##_fc():   pk_state_fc( state)                                              \
  {                                                                                    \
	                                                                                   \
  };                                                                                    \
                                                                                        \
                                                                                        \
                                                                                        \
 };                                                                                     \
                                                                                        \
 pk_##state##_fc state##_obj;                                                           \
                                                                                        \
 unsigned state##_fc()


#ifdef  PK_SYSC_22                     
   #define    pk_declare_method_proc(func)                                      \
              sensitive.set(base_module::sensitive, monitored);                 \
              sensitive_pos.set(base_module::sensitive_pos, monitored);         \
              sensitive_neg.set(base_module::sensitive_neg, monitored);         \
              ::sc_core::sc_process_handle func ## handle =                     \
			  sc_core::sc_get_curr_simcontext()->create_method_process( #func,  \
              false, SC_MAKE_FUNC_PTR( power_module_b, func ),                  \
              static_cast<power_module_b*>(this), 0 );                          \
              this->sensitive << func ## handle;                                \
              this->sensitive_pos << func ## handle;                            \
              this->sensitive_neg << func ## handle;                            
#else
   #define    pk_declare_method_proc(func)                                      \
              sensitive.set(base_module::sensitive, monitored);                 \
              sensitive_pos.set(base_module::sensitive_pos, monitored);         \
              sensitive_neg.set(base_module::sensitive_neg, monitored);         \
              ::sc_core::sc_thread_process* func ## handle =                    \
			  pk_core::power_module_b::simcontext()->register_method_process( #func,     \
              SC_MAKE_FUNC_PTR( power_module_b, func ),                         \
              static_cast<power_module_b*>(this) );                             \
              sensitive << func ## handle;                                      \
              sensitive_pos << func ## handle;                                  \
              sensitive_neg << func ## handle;  
#endif


#ifdef  PK_SYSC_22                     
   #define    pk_declare_thread_proc(func)                                      \
              sensitive.set(base_module::sensitive, monitored);                 \
              sensitive_pos.set(base_module::sensitive_pos, monitored);         \
              sensitive_neg.set(base_module::sensitive_neg, monitored);         \
              ::sc_core::sc_process_handle func ## handle =                     \
			  sc_core::sc_get_curr_simcontext()->create_thread_process( #func,  \
              false, SC_MAKE_FUNC_PTR( power_module_b, func ),                  \
              static_cast<power_module_b*>(this), 0 );                          \
              this->sensitive << func ## handle;                                \
              this->sensitive_pos << func ## handle;                            \
              this->sensitive_neg << func ## handle;                            
#else
   #define    pk_declare_thread_proc(func)                                      \
              sensitive.set(base_module::sensitive, monitored);                 \
              sensitive_pos.set(base_module::sensitive_pos, monitored);         \
              sensitive_neg.set(base_module::sensitive_neg, monitored);         \
              ::sc_core::sc_thread_process* func ## handle =                    \
			  pk_core::power_module_b::simcontext()->register_thread_process( #func,     \
              SC_MAKE_FUNC_PTR( power_module_b, func ),                         \
              static_cast<power_module_b*>(this) );                             \
              sensitive << func ## handle;                                      \
              sensitive_pos << func ## handle;                                  \
              sensitive_neg << func ## handle;  
#endif

     
#define PK_METHOD(func) pk_declare_method_proc(func)

#define PK_THREAD(func) pk_declare_thread_proc(func)  


							
#ifdef PK_ENABLE_TLM


#define    PK_B_TRANSPORT_1(socket)                                                   \
	         if(monitored) set_socket(dynamic_cast<pk_tlm::pk_socket_base*>( & socket ), pk_tlm::PK_B_TRANS);

#define    PK_NB_TRANSPORT_FW_1(socket)                                                \
	           if(monitored) set_socket(dynamic_cast<pk_tlm::pk_socket_base*>( & socket ),   pk_tlm::PK_NB_FW_TRANS);

#define    PK_NB_TRANSPORT_BW_1(socket)                                                \
	           if(monitored) set_socket(dynamic_cast<pk_tlm::pk_socket_base*>( & socket ), pk_tlm::PK_NB_BW_TRANS);

#define    PK_GET_DIRECT_MEM_PTR_1(socket)                                              \
	          if(monitored)  set_socket(dynamic_cast<pk_tlm::pk_socket_base*>( & socket ), pk_tlm::PK_FW_DIR_MEM_IF);

#define    PK_INVALIDATE_DIRECT_MEM_PTR_1(socket)                                       \
	          if(monitored)  set_socket(dynamic_cast<pk_tlm::pk_socket_base*>( & socket ), pk_tlm::PK_BW_DIR_MEM_IF);


#define    PK_B_TRANSPORT_2                                                           \
	       pk_tlm::pk_enable_tlm_fc< pk_tlm::PK_B_TRANS > pk_b_trans_ob;              \
           void b_transport                                                           \
              ( tlm::tlm_generic_payload& gp,                                         \
                sc_core::sc_time& t)                                                  \
			    {                                                                     \
                 if(monitored) b_trans_estim(gp, t);                                  \
                 return base_module::b_transport(gp, t);                              \
				}                                                                     \


#define    PK_NB_TRANSPORT_FW_2                                                 \
	       pk_tlm::pk_enable_tlm_fc< pk_tlm::PK_NB_FW_TRANS > pk_nb_trfw_ob;    \
           tlm::tlm_sync_enum    nb_transport_fw                                \
              ( tlm::tlm_generic_payload &gp,                                   \
                tlm::tlm_phase           &phase,                                \
			    sc_core::sc_time         &delay_time)                           \
              {                                                                 \
			   tlm::tlm_sync_enum status = base_module::nb_transport_fw(gp,phase,delay_time);        \
               if(monitored)  nb_transfw_estim(gp, phase, delay_time, status);   \
			   return status;                                                    \
              };                                                               
                                       
                                                                                
                                                                                                                                                                      

#define    PK_NB_TRANSPORT_BW_2                                                 \
	       pk_tlm::pk_enable_tlm_fc< pk_tlm::PK_NB_BW_TRANS > pk_nb_trbw_ob;    \
           tlm::tlm_sync_enum    nb_transport_bw                                \
              ( tlm::tlm_generic_payload &gp,                                   \
                tlm::tlm_phase           &phase,                                \
			    sc_core::sc_time         &delay_time)                           \
              {                                                                 \
                                                                                \
               tlm::tlm_sync_enum status = base_module::nb_transport_bw(gp,phase,delay_time);        \
			   if(monitored) nb_transbw_estim(gp, phase, delay_time, status);           \
			   return status;                                                    \
              }; 


#define    PK_GET_DIRECT_MEM_PTR_2                                                     \
	       pk_tlm::pk_enable_tlm_fc< pk_tlm::PK_FW_DIR_MEM_IF > pk_get_dirmem_ob;      \
           bool get_direct_mem_ptr                                                     \
              ( tlm::tlm_generic_payload &gp,                                          \
                tlm::tlm_dmi           &dmi_data)                                      \
			    {                                                                      \
                                                                                       \
                 if(monitored) get_dirmem_estim(gp, dmi_data );                        \
                 return base_module::get_direct_mem_ptr(gp,dmi_data);                  \
				}                                                                      \

#define    PK_INVALIDATE_DIRECT_MEM_PTR_2                                               \
	       pk_tlm::pk_enable_tlm_fc< pk_tlm::PK_BW_DIR_MEM_IF > pk_inv_dirmem_ob;       \
           void   invalidate_direct_mem_ptr                                             \
              ( sc_dt::uint64 start_range,                                              \
                sc_dt::uint64 end_range )                                               \
			    {                                                                       \
                 if(monitored) inv_dirmem_estim(start_range, end_range );               \
                 return base_module::invalidate_direct_mem_ptr(start_range, end_range); \
				}                                                                       \



#define    PK_TLM_ENABLE_IDLE_ESTIM                   \
             enable_TLM_idle_estim();


// for backward compatibility with beta-8 release

#define PK_TLM_ENABLE_STATIC_POWER  PK_TLM_ENABLE_IDLE_ESTIM

#endif
		




#define PK_HAS_PROCESS( sc_mod )                                               \
	                                                                           \
                                                                               \
			     typedef sc_mod   base_module;                                 \
				 typedef pk_powmod_##sc_mod powmod_type;                       \
					                                                           \
				                                                               \
					                                                           \
			                                                                   \
			      pk_core::pk_sensitive sensitive;                             \
				  pk_core::pk_sensitive_pos sensitive_pos;                     \
				  pk_core::pk_sensitive_neg sensitive_neg;                    \
				  using pk_core::power_module_b::simcontext;                  \
                                                                              \
                  void make_base_procs()                                      \
				  {                                                           \
				    if(!initialized) initialize();                            \
					                                                          \
                                                                              \
																			  \
                     PK_THREAD(initialize_augs)                               \
                                                                              \
					 if( psh->make_inport_proc() )                            \
					 {                                                        \
                      PK_METHOD(update_inport_proc)                           \
					  pk_core::power_module_b::dont_initialize();             \
                      sensitive<<sensitivity_ev;                              \
					 };                                                       \
                                                                              \
                     if( psh->make_cyclemodel_proc() )                        \
					 {                                                        \
                      PK_THREAD(modelcycle_proc)                              \
                      pk_core::power_module_b::dont_initialize();             \
					  sensitive<<sensitivity_ev;                              \
					 };                                                       \
                                                                              \
                     if( psh->make_FSM_proc() )                               \
					 {                                                        \
                      PK_THREAD(powerFSM_proc)                                \
                      pk_core::power_module_b::dont_initialize();             \
                      sensitive<<sensitivity_ev;                              \
					 };                                                       \
				    if(psh) delete psh;                                       \
				  };                                                          \
				                                                              \
			      ~pk_powmod_##sc_mod()                                       \
				  {                                                           \
				   final_action();                                            \
				   this->powmod_dtor();                           			  \
				  };                                                          \
																	          \
                  SC_HAS_PROCESS( power_module_b )


#define PK_PMB_CTOR power_module_b( static_cast< base_module *>(this)->name() )

#define POWER_MODULE_CTOR( sc_mod ) PK_HAS_PROCESS( sc_mod );                              \
	             POWER_MODULE(sc_mod) (::sc_core::sc_module_name nm):                          \
				   sc_mod(nm), PK_PMB_CTOR





#define PK_INPORT_SENSITIVITY                                                       \
	                                                                                \
		if(!initialized) initialize();  			        						\
                                                                                    \
            psh->inportsens_enabled = true;                                         \
                                                                                    \
            PK_METHOD(update_inport_proc)                                           \
		    pk_core::power_module_b::dont_initialize();         



#define PK_CYCLEMODEL_SENSITIVITY                                                   \
                                                                                    \
            if(!initialized) initialize();                                          \
																					\
			                                                                        \
             psh->modelsens_enabled = true;                                         \
			                                                                        \
             PK_THREAD(modelcycle_proc)                                             \
		     pk_core::power_module_b::dont_initialize();  


#define POWERFSM_SENSITIVITY                                                        \
                                                                                    \
			if(!initialized) initialize();											\
			                                                                        \
			                                                                        \
			 psh->FSMsens_enabled = true;    										\
			                                                                        \
			 PK_THREAD(powerFSM_proc)                                               \
			 pk_core::power_module_b::dont_initialize();  




#define PK_MODULE_SENSITIVITY                                                       \
                                                                                    \
			if(!initialized) initialize();              							\
			                                                                        \
			                                                                        \
			 PK_THREAD(sensitivity_proc)                                            \
			 pk_core::power_module_b::dont_initialize();    



#define POWER_MODULE_DTOR   void powmod_dtor()








#define PK_DECLARE_ENERGY_LIB( name )                \
	namespace name                                   \
	{                                                \
	typedef pk_core::energy_power_model  lib_power_model;    \
	                                                 \
     template<int n> class pk_power_model_tag        \
	 {};                                             \
                                                     \
     struct pk_lib_model_creator                     \
		{                                            \
	   virtual ~pk_lib_model_creator(){};            \
		                                             \
        } ;                                          \
                                                     \
                                                     \
	                                                 \
	 inline pk_core::pk_model_lib_handler& model_library()	 \
	 {												 \
	   static pk_core::pk_model_lib_handler					 \
		library_handler(*(new pk_core::pk_energy_type()), #name);	 \
		return  library_handler;                     \
	 }	                                             \
													 \
	}     


#define PK_DECLARE_COMM_LIB( name )                  \
	namespace name                                   \
	{                                                \
	 typedef pk_core::comm_power_model  lib_power_model;      \
	                                                 \
     template<int n> class pk_power_model_tag        \
     {                                               \
      public:                                        \
                                                     \
                                                     \
     };                                              \
                                                     \
     struct pk_lib_model_creator                     \
	 {                                               \
	   virtual ~pk_lib_model_creator(){};            \
	 } ;                                             \
		                                             \
			                                         \
	                                                 \
     inline pk_core::pk_model_lib_handler& model_library()	 \
	 {												 \
	   static pk_core::pk_model_lib_handler					 \
		library_handler(*(new pk_core::pk_comm_type()), #name);	     \
		return  library_handler;                     \
	 }	                                             \
                                                     \
	} 




#endif

