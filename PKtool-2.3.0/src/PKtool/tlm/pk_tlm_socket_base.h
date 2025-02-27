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

#ifndef PK_TLM_NS_H
#define PK_TLM_NS_H

namespace pk_core
{

 class pk_read_cfg_data;
 class power_module_b;

}

namespace pk_tlm
{

 class tlm_power_model_b;

 const int pk_tlmfc_nb = 5;

 enum pk_fc_ifs{ PK_B_TRANS = 0, PK_NB_FW_TRANS = 1, PK_NB_BW_TRANS,   
	             PK_FW_DIR_MEM_IF, PK_BW_DIR_MEM_IF };
 
 extern const char* pk_fc_names[pk_tlmfc_nb];

 
 struct pk_enable_tlmfc
 {
  pk_enable_tlmfc(int fc);
 };


// ----------------------------------------------------------------------------
//  STRUCT : pk_enable_tlm_fc  
// ----------------------------------------------------------------------------


 template<int n> struct pk_enable_tlm_fc: private pk_enable_tlmfc
 {
 
  pk_enable_tlm_fc(): pk_enable_tlmfc(n)
  {};
 
 };

// ----------------------------------------------------------------------------
//  STRUCT : pk_TLMfc_data  
// ----------------------------------------------------------------------------

 struct pk_TLMfc_data
 { 

  pk_TLMfc_data()
  {
   for(int i=0; i<pk_tlmfc_nb; ++i)
   {
    TLMfc_on[i] = false;               
	TLMpm_indexs[i] = -1;
	TLMfc_pm[i] = 0;   
	TLMfc_calls[i] = 0;
	TLMfc_exectimes[i] = -1;
   }
  }

  void do_estimation(int TLM_fc);      
  

  inline pk_core::pk_estimation get_estimation(int TLM_fc) const     
  { return TLMfc_est[TLM_fc]; }

  void set_estype(pk_core::pk_est_type);
  
   
  bool TLMfc_on[pk_tlmfc_nb];
  int TLMpm_indexs[pk_tlmfc_nb];  
  tlm_power_model_b*  TLMfc_pm[pk_tlmfc_nb];
  pk_core::pk_estimation TLMfc_est[pk_tlmfc_nb];
  int TLMfc_calls[pk_tlmfc_nb];
  double TLMfc_exectimes[pk_tlmfc_nb];
 };


// ----------------------------------------------------------------------------
//  CLASS : pk_socket_base  
// ----------------------------------------------------------------------------

 class pk_socket_base   
 {
  
  friend class pk_core::pk_kernel_impl;
  friend class pk_core::pk_read_cfg_data;
  friend class pk_core::power_module_b;

  protected:

  pk_socket_base(const char* nm): name(nm), enabled(false)
  { }
  
  const char* name;
  bool enabled; 
  pk_TLMfc_data  fc_data;

  virtual ~pk_socket_base()
  {};

 };


}   //pk_tlm



#endif

