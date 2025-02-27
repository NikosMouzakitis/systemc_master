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

#ifndef PK_TLM_POWER_MODELS_H
#define PK_TLM_POWER_MODELS_H

#include "tlm.h"
#include "PKtool/tlm/pk_tlm_power_model_b.h"


namespace tlm
{
 class tlm_generic_payload;
}

PK_MODEL_LIB( pk_default_energy_lib )
{     

 PK_TLM_MODEL_BEGIN(TLM_1, 51)   
 {
  public: 

  // constructor

  PK_MODEL_CTOR(TLM_1) ,en_units(float(1e-9))
  { };  
 
  inline void set_static_data()
  { PK_SET_SINGLE_MODEL_DATA( energy (nJ), energy ) };

  estimation_type do_estimationation()
  { return do_est(); };

  inline double b_trans_estim(const tlm::tlm_generic_payload&, 
    	               const sc_core::sc_time&)
  { return do_est(); };

  inline double nb_transfw_estim(const tlm::tlm_generic_payload&,
 	                      const tlm::tlm_phase&,
 	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum)
  { return do_est(); };

  inline double nb_transbw_estim(const tlm::tlm_generic_payload&,
	                      const tlm::tlm_phase&,
	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum )
  { return do_est(); };

  inline double get_dirmem_estim(const tlm::tlm_generic_payload&,
	                      const tlm::tlm_dmi& )
  { return do_est(); };
  
 
  inline double inv_dirmem_estim(const sc_dt::uint64&,
	                      const sc_dt::uint64& )  
  
  { return do_est(); };

  private:

  inline double do_est()
  { return energy*en_units; };

  float energy;
  const float en_units;

 };
 PK_TLM_MODEL_END(TLM_1, 51)


 
 PK_TLM_MODEL_BEGIN(TLM_2, 52)   
 {
  public: 

  // constructor

  PK_MODEL_CTOR(TLM_2) ,en_units(float(1e-9))
  { 
   read_nb = write_nb = ignore_nb = 0;
  };  
 
  inline void set_static_data()
  { 
   PK_SET_SINGLE_MODEL_DATA( read energy (nJ), read_en ) 
   PK_SET_SINGLE_MODEL_DATA( write energy (nJ), write_en )
   PK_SET_SINGLE_MODEL_DATA( ignore energy (nJ), ignore_en )
   read_en *= en_units;  write_en *= en_units; ignore_en *= en_units;
  };


  inline double b_trans_estim(const tlm::tlm_generic_payload& gp, 
    	               const sc_core::sc_time&)
  { return do_est(gp); };

  inline double nb_transfw_estim(const tlm::tlm_generic_payload& gp,
 	                      const tlm::tlm_phase&,
 	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum)
  { return do_est(gp); };

  inline double nb_transbw_estim(const tlm::tlm_generic_payload& gp,
	                      const tlm::tlm_phase&,
	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum )
  { return do_est(gp); };

  inline double get_dirmem_estim(const tlm::tlm_generic_payload& gp,
	                      const tlm::tlm_dmi& )
  { return do_est(gp); };
  
 
  inline double inv_dirmem_estim(const sc_dt::uint64&,
	                      const sc_dt::uint64& )  
  
  { return 0; };

  private:

  inline double do_est(const tlm::tlm_generic_payload& gp)
  { 
	switch( gp.get_command() )
	{
	 case tlm::TLM_READ_COMMAND :
		  ++read_nb;
	      return read_en;
	      break;
     case tlm::TLM_WRITE_COMMAND :
	      ++write_nb;
	      return write_en;
	      break;
	 case tlm::TLM_IGNORE_COMMAND :
	      ++ignore_nb;
	      return ignore_en;
	      break;
	 default: 
		  return 0;
	}
	  
  };

  void print_custom_result(ofstream& f) 
  {
   f<<endl<<" number of read operations = "<<read_nb<<endl;
   f<<" energy estimation of read operations = "<<(read_nb*read_en)<<" J"<<endl;
   f<<" number of write operations = "<<write_nb<<endl;
   f<<" energy estimation of write operations = "<<(write_nb*write_en)<<" J"<<endl;
   f<<" number of ignore operations = "<<ignore_nb<<endl;
   f<<" energy estimation of ignore operations = "<<(ignore_nb*ignore_en)<<" J"<<endl<<endl;
  }

  float read_en, write_en, ignore_en;
  int read_nb, write_nb, ignore_nb;
  const float en_units;

 };
 PK_TLM_MODEL_END(TLM_2, 52)




 PK_TLM_MODEL_BEGIN(TLM_3, 53)   
 {
  public: 

  // constructor

  PK_MODEL_CTOR(TLM_3) ,en_units(float(1e-9))
  { 
   begreq_nb = endreq_nb = begresp_nb = endresp_nb = 0;
  };  
 
  
  inline void set_static_data()
  { 
   PK_SET_SINGLE_MODEL_DATA( BEGIN_REQ energy (nJ), begreq_en ) 
   PK_SET_SINGLE_MODEL_DATA( END_REQ energy (nJ), endreq_en )
   PK_SET_SINGLE_MODEL_DATA( BEGIN_RESP energy (nJ), begresp_en )
   PK_SET_SINGLE_MODEL_DATA( END_RESP energy (nJ), endresp_en )

   begreq_en *= en_units;  endreq_en *= en_units; 
   begresp_en *= en_units;  endresp_en *= en_units;
  };


  inline double b_trans_estim(const tlm::tlm_generic_payload& , 
    	               const sc_core::sc_time&)
  { return 0; };

  inline double nb_transfw_estim(const tlm::tlm_generic_payload& ,
 	                      const tlm::tlm_phase& ph,
 	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum)
  { return do_est(ph); };

  inline double nb_transbw_estim(const tlm::tlm_generic_payload& ,
	                      const tlm::tlm_phase& ph,
	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum )
  { return do_est(ph); };

  inline double get_dirmem_estim(const tlm::tlm_generic_payload& ,
	                      const tlm::tlm_dmi& )
  { return 0; };
  
 
  inline double inv_dirmem_estim(const sc_dt::uint64&,
	                      const sc_dt::uint64& )  
  
  { return 0; };


  private:

  inline double do_est(const tlm::tlm_phase& ph)
  { 
	switch( ph )
	{
	 case tlm::BEGIN_REQ:
		  ++begreq_nb;
	      return begreq_en;
	      break;
     case tlm::END_REQ:
	      ++endreq_nb;
	      return endreq_en;
	      break;
	 case tlm::BEGIN_RESP:
		  ++begresp_nb;
	      return begresp_en;
	      break;
     case tlm::END_RESP:
	      ++endresp_nb;
	      return endresp_en;
	      break;
	 default: 
		  return 0;
	}
	  
  };

  void print_custom_result(ofstream& f) 
  {
   f<<endl;
   f<<" energy estimation of BEGIN_REQ phase = "<<(begreq_nb*begreq_en)<<" J"<<endl;
   f<<" energy estimation of END_REQ phase = "<<(endreq_nb*endreq_en)<<" J"<<endl;
   f<<" energy estimation of BEGIN_RESP phase = "<<(begresp_nb*begresp_en)<<" J"<<endl;
   f<<" energy estimation of END_RESP phase = "<<(endresp_nb*endresp_en)<<" J"<<endl;  }

  double begreq_en, endreq_en, begresp_en, endresp_en;
  int begreq_nb, endreq_nb, begresp_nb, endresp_nb;
  const float en_units;


 };
 PK_TLM_MODEL_END(TLM_3, 53)


  PK_TLM_MODEL_BEGIN(TLM_4, 54)   
 {
  public: 

  // constructor

  PK_MODEL_CTOR(TLM_4) ,en_units(float(1e-9))
  { 
   ACCEPTED_nb = UPDATED_nb = COMPLETED_nb = 0;
  };  
 
  
  
  inline void set_static_data()
  { 
   PK_SET_SINGLE_MODEL_DATA( TLM_ACCEPTED energy (nJ), ACCEPTED_en ) 
   PK_SET_SINGLE_MODEL_DATA( TLM_UPDATED energy (nJ), UPDATED_en )
   PK_SET_SINGLE_MODEL_DATA( TLM_COMPLETED energy (nJ), COMPLETED_en )

   ACCEPTED_en *= en_units;  UPDATED_en *= en_units; 
   COMPLETED_en *= en_units; 
  };


  inline double b_trans_estim(const tlm::tlm_generic_payload& , 
    	               const sc_core::sc_time&)
  { return 0; };

  inline double nb_transfw_estim(const tlm::tlm_generic_payload& ,
 	                      const tlm::tlm_phase& ph,
 	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum status)
  { return do_est(status); };

  inline double nb_transbw_estim(const tlm::tlm_generic_payload& ,
	                      const tlm::tlm_phase& ph,
	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum status)
  { return do_est(status); };

  inline double get_dirmem_estim(const tlm::tlm_generic_payload& ,
	                      const tlm::tlm_dmi& )
  { return 0; };
  
 
  inline double inv_dirmem_estim(const sc_dt::uint64&,
	                      const sc_dt::uint64& )  
  
  { return 0; };


      

  inline double do_est(const tlm::tlm_sync_enum status)
  { 
	switch( status )
	{
	 case tlm::TLM_ACCEPTED:
		  ++ACCEPTED_nb;
	      return ACCEPTED_en;
	      break;
     case tlm::TLM_UPDATED:
	      ++UPDATED_nb;
	      return UPDATED_en;
	      break;
	 case tlm::TLM_COMPLETED:
		  ++COMPLETED_nb;
	      return COMPLETED_en;
	      break;
	 default: 
		  return 0;
	}
	  
  };

  void print_custom_result(ofstream& f) 
  {
   f<<endl;
   f<<" energy estimation of TLM_ACCEPTED status = "<<(ACCEPTED_nb*ACCEPTED_en)<<" J"<<endl;
   f<<" energy estimation of TLM_UPDATED status = "<<(UPDATED_nb*UPDATED_en)<<" J"<<endl;
   f<<" energy estimation of TLM_COMPLETED status = "<<(COMPLETED_nb*COMPLETED_en)<<" J"<<endl; 
  }

  double ACCEPTED_en, UPDATED_en, COMPLETED_en;
  int ACCEPTED_nb, UPDATED_nb, COMPLETED_nb;
  const float en_units;


 };
 PK_TLM_MODEL_END(TLM_4, 54)



 PK_TLM_MODEL_BEGIN(TLM_5, 55)   
 {
  public: 

  // constructor

  PK_MODEL_CTOR(TLM_5) ,en_units(float(1e-9))
  { 
   BEGREQ_ACC_nb = BEGREQ_UPD_nb = BEGREQ_COMP_nb = 0; 
   ENDREQ_ACC_nb = ENDREQ_UPD_nb = ENDREQ_COMP_nb = 0;
   BEGRESP_ACC_nb = BEGRESP_UPD_nb = BEGRESP_COMP_nb = 0; 
   ENDRESP_ACC_nb = ENDRESP_UPD_nb = ENDRESP_COMP_nb = 0;
  };  
 
  
  inline void set_static_data()
  { 
   pk_core::pk_cout<<endl<<"PHASE: BEGREQ"<<endl;
   PK_SET_SINGLE_MODEL_DATA( TLM_ACCEPTED energy (nJ), BEGREQ_ACC_en ) 
   PK_SET_SINGLE_MODEL_DATA( TLM_UPDATED energy (nJ), BEGREQ_UPD_en )
   PK_SET_SINGLE_MODEL_DATA( TLM_COMPLETED energy (nJ), BEGREQ_COMP_en )
   pk_core::pk_cout<<endl;

   pk_core::pk_cout<<"PHASE: ENDREQ"<<endl;
   PK_SET_SINGLE_MODEL_DATA( TLM_ACCEPTED energy (nJ), ENDREQ_ACC_en ) 
   PK_SET_SINGLE_MODEL_DATA( TLM_UPDATED energy (nJ), ENDREQ_UPD_en )
   PK_SET_SINGLE_MODEL_DATA( TLM_COMPLETED energy (nJ), ENDREQ_COMP_en )
   pk_core::pk_cout<<endl;

   pk_core::pk_cout<<"PHASE: BEGRESP"<<endl;
   PK_SET_SINGLE_MODEL_DATA( TLM_ACCEPTED energy (nJ), BEGRESP_ACC_en ) 
   PK_SET_SINGLE_MODEL_DATA( TLM_UPDATED energy (nJ), BEGRESP_UPD_en )
   PK_SET_SINGLE_MODEL_DATA( TLM_COMPLETED energy (nJ), BEGRESP_COMP_en )
   pk_core::pk_cout<<endl;

   pk_core::pk_cout<<"PHASE: ENDRESP"<<endl;
   PK_SET_SINGLE_MODEL_DATA( TLM_ACCEPTED energy (nJ), ENDRESP_ACC_en ) 
   PK_SET_SINGLE_MODEL_DATA( TLM_UPDATED energy (nJ), ENDRESP_UPD_en )
   PK_SET_SINGLE_MODEL_DATA( TLM_COMPLETED energy (nJ), ENDRESP_COMP_en )
   pk_core::pk_cout<<endl;


   BEGREQ_ACC_en *= en_units;  BEGREQ_UPD_en *= en_units;  BEGREQ_COMP_en *= en_units; 
   ENDREQ_ACC_en *= en_units;  ENDREQ_UPD_en *= en_units;  ENDREQ_COMP_en *= en_units;
   BEGRESP_ACC_en *= en_units;  BEGRESP_UPD_en *= en_units;  BEGRESP_COMP_en *= en_units; 
   ENDRESP_ACC_en *= en_units;  ENDRESP_UPD_en *= en_units;  ENDRESP_COMP_en *= en_units;

   
  };


  inline double b_trans_estim(const tlm::tlm_generic_payload& , 
    	               const sc_core::sc_time&)
  { return 0; };

  inline double nb_transfw_estim(const tlm::tlm_generic_payload& ,
 	                      const tlm::tlm_phase& ph,
 	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum status)
  { return do_est(ph, status); };

  inline double nb_transbw_estim(const tlm::tlm_generic_payload& ,
	                      const tlm::tlm_phase& ph,
	                      const sc_core::sc_time&,
						  const tlm::tlm_sync_enum status)
  { return do_est(ph, status); };

  inline double get_dirmem_estim(const tlm::tlm_generic_payload& ,
	                      const tlm::tlm_dmi& )
  { return 0; };
  
 
  inline double inv_dirmem_estim(const sc_dt::uint64&,
	                      const sc_dt::uint64& )  
  
  { return 0; };


    


  inline double do_est(const tlm::tlm_phase& ph, const tlm::tlm_sync_enum status)
  { 

   if(ph == tlm::BEGIN_REQ)
   {
	switch( status )
	{
	 case tlm::TLM_ACCEPTED:
		  ++BEGREQ_ACC_nb;
	      return BEGREQ_ACC_en;
	      break;
     case tlm::TLM_UPDATED:
	      ++BEGREQ_UPD_nb;
	      return BEGREQ_UPD_en;
	      break;
	 case tlm::TLM_COMPLETED:
		  ++BEGREQ_COMP_nb;
	      return BEGREQ_COMP_en;
	      break;
	 default: 
		  return 0;
	}
   }

   else if(ph == tlm::END_REQ)
   {
	switch( status )
	{
	 case tlm::TLM_ACCEPTED:
		  ++ENDREQ_ACC_nb;
	      return ENDREQ_ACC_en;
	      break;
     case tlm::TLM_UPDATED:
	      ++ENDREQ_UPD_nb;
	      return ENDREQ_UPD_en;
	      break;
	 case tlm::TLM_COMPLETED:
		  ++ENDREQ_COMP_nb;
	      return ENDREQ_COMP_en;
	      break;
	 default: 
		  return 0;
	}
   }

   else if(ph == tlm::BEGIN_RESP)
   {
	switch( status )
	{
	 case tlm::TLM_ACCEPTED:
		  ++BEGRESP_ACC_nb;
	      return BEGRESP_ACC_en;
	      break;
     case tlm::TLM_UPDATED:
	      ++BEGRESP_UPD_nb;
	      return BEGRESP_UPD_en;
	      break;
	 case tlm::TLM_COMPLETED:
		  ++BEGRESP_COMP_nb;
	      return BEGRESP_COMP_en;
	      break;
	 default: 
		  return 0;
	}
   }

   else 
   {
	switch( status )
	{
	 case tlm::TLM_ACCEPTED:
		  ++ENDRESP_ACC_nb;
	      return ENDRESP_ACC_en;
	      break;
     case tlm::TLM_UPDATED:
	      ++ENDRESP_UPD_nb;
	      return ENDRESP_UPD_en;
	      break;
	 case tlm::TLM_COMPLETED:
		  ++ENDRESP_COMP_nb;
	      return ENDRESP_COMP_en;
	      break;
	 default: 
		  return 0;
	}
   }

  };


  void print_custom_result(ofstream& f) 
  {
   
   f<<endl<<endl<<"PHASE: BEGIN_REQ"<<endl;
   f<<" TLM_ACCEPTED energy estimation = "<<(BEGREQ_ACC_nb*BEGREQ_ACC_en)<<" J"<<endl;
   f<<" TLM_UPDATED energy estimation = "<<(BEGREQ_UPD_nb*BEGREQ_UPD_en)<<" J"<<endl;
   f<<" TLM_COMPLETED energy estimation = "<<(BEGREQ_COMP_nb*BEGREQ_COMP_en)<<" J"<<endl; 
 
   f<<endl<<"PHASE: END_REQ"<<endl;
   f<<" TLM_ACCEPTED energy estimation = "<<(ENDREQ_ACC_nb*ENDREQ_ACC_en)<<" J"<<endl;
   f<<" TLM_UPDATED energy estimation = "<<(ENDREQ_UPD_nb*ENDREQ_UPD_en)<<" J"<<endl;
   f<<" TLM_COMPLETED energy estimation = "<<(ENDREQ_COMP_nb*ENDREQ_COMP_en)<<" J"<<endl; 

   f<<endl<<"PHASE: BEGIN_RESP"<<endl;
   f<<" TLM_ACCEPTED energy estimation = "<<(BEGRESP_ACC_nb*BEGRESP_ACC_en)<<" J"<<endl;
   f<<" TLM_UPDATED energy estimation = "<<(BEGRESP_UPD_nb*BEGRESP_UPD_en)<<" J"<<endl;
   f<<" TLM_COMPLETED energy estimation = "<<(BEGRESP_COMP_nb*BEGRESP_COMP_en)<<" J"<<endl; 
 
   f<<endl<<"PHASE: END_RESP"<<endl;
   f<<" TLM_ACCEPTED energy estimation = "<<(ENDRESP_ACC_nb*ENDRESP_ACC_en)<<" J"<<endl;
   f<<" TLM_UPDATED energy estimation = "<<(ENDRESP_UPD_nb*ENDRESP_UPD_en)<<" J"<<endl;
   f<<" TLM_COMPLETED energy estimation = "<<(ENDRESP_COMP_nb*ENDRESP_COMP_en)<<" J"<<endl<<endl; 

  }

  double BEGREQ_ACC_en, BEGREQ_UPD_en, BEGREQ_COMP_en;
  int BEGREQ_ACC_nb, BEGREQ_UPD_nb, BEGREQ_COMP_nb;

  double ENDREQ_ACC_en, ENDREQ_UPD_en, ENDREQ_COMP_en;
  int ENDREQ_ACC_nb, ENDREQ_UPD_nb, ENDREQ_COMP_nb;

  double BEGRESP_ACC_en, BEGRESP_UPD_en, BEGRESP_COMP_en;
  int BEGRESP_ACC_nb, BEGRESP_UPD_nb, BEGRESP_COMP_nb;

  double ENDRESP_ACC_en, ENDRESP_UPD_en, ENDRESP_COMP_en;
  int ENDRESP_ACC_nb, ENDRESP_UPD_nb, ENDRESP_COMP_nb;

  const float en_units;


 };
 PK_TLM_MODEL_END(TLM_5, 55)



}  // pk_default_energy_lib




#endif

