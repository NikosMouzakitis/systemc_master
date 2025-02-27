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


#ifndef POWER_MODEL_B_H
#define POWER_MODEL_B_H

#include "PKtool/power_models/pk_estimation.h"
#include "PKtool/kernel/pk_settings.h"   
#include "PKtool/utils/pk_iostream.h"
#include "PKtool/types_aug/pk_aug_if.h"
#include "PKtool/kernel/pk_kernel_impl.h"  


#ifdef PK_ENABLE_OPMODELS

namespace pk_default_energy_lib
{
 struct pk_opmodel_b;
}

#endif


namespace pk_core    
{


// ----------------------------------------------------------------------------
//  CLASS : power_model_b
// ----------------------------------------------------------------------------

class power_model_b
{
 friend class pk_core::pk_read_cfg_data;
 friend class power_kernel;
 friend class pk_kernel_impl;


 public:

 virtual const char* name() const = 0;
 virtual const unsigned numeric_id() const = 0 ;

 virtual pk_est_type output_type() = 0;
                             
 virtual pk_estimation get_estimation(){return pk_estimation();};

 
 void set_signals( const pk_kernel_impl& );
 

 inline bool cycle_accurate() const
 {  return cycle_acc; }

 public:
 
 power_model_b(pk_kernel_impl&);

 virtual ~power_model_b();


 protected:

 virtual void set_static_data() 
 {};


 virtual void set_augdata()   
 {};


 void set_augdata_(pk_aug_if::aug_data ad);   
 

 unsigned total_comm();   
 
 inline double simulation_time()
 { return (pk_impl.endtime - pk_impl.startime).to_seconds();  };
  

#ifdef PK_ENABLE_OPMODELS

 void set_opmodel_on_augs( pk_default_energy_lib::pk_opmodel_b*);

#endif


 pk_kernel_impl& pk_impl;
 bool cycle_acc;        
 static char tmp_ch;   
 std::ifstream& infile;
 
 vector<pk_aug_if*> intsignal_aug;
 vector<pk_aug_if*> inport_aug;
 vector<pk_aug_if*> outport_aug;
 vector<pk_aug_if*> inoutport_aug;

 pk_aug_local* local_aug;  

 struct set_cycle_acc
 { set_cycle_acc(); };

 friend struct power_model_b::set_cycle_acc;

 private:      

 virtual void print_custom_result(ofstream& ) 
 {};

 virtual void print_total_result(ofstream& ) 
 {};

 static bool* cycle_acc_ref;
 
};

// ----------------------------------------------------------------------------
//  CLASS : energy_power_model
// ----------------------------------------------------------------------------


 class energy_power_model: public power_model_b   
 {

  public:  

  inline pk_estimation get_estimation()
  {
   pk_energy_type* tmp = static_cast<pk_energy_type*>(est_obj.pvalue);
   tmp->set(this->do_estimationation());
   return est_obj;  
  };
		     
  pk_est_type output_type()               
  { return pk_est_type(pk_energy); };  
			                                                        
  typedef pk_energy_type::estimation_type estimation_type;         
                                                           
  //constructor

  energy_power_model(pk_kernel_impl& p): power_model_b(p) {};            
                                                                        
  protected:                                      
                                                            
  virtual estimation_type do_estimationation(){return 0;}; 

  estimation_type out_value;                          

	

	private:
    static pk_estimation est_obj;

 };    



 // ----------------------------------------------------------------------------
//  CLASS : comm_power_model
// ----------------------------------------------------------------------------

 class comm_power_model: public power_model_b   
 { 
	public:                                        
		   
	pk_est_type output_type()               
	{ return pk_est_type(pk_comm); };  
			                                                      
	typedef pk_comm_type::estimation_type estimation_type;         
                                                           
    // constructor

	comm_power_model(pk_kernel_impl& p): power_model_b(p) {};            
                                                                        
    protected:                                      
                                                            
    virtual estimation_type do_estimationation(){return 0;}; 
	estimation_type out_value;                        
            
	pk_estimation get_estimation()
	{
	 pk_comm_type* tmp = static_cast<pk_comm_type*>(est_obj.pvalue);
	 tmp->set(this->do_estimationation());
	 return est_obj;  
	};

	 private:
		
	 static pk_estimation est_obj;

};  

}    //pk_core  


#endif
