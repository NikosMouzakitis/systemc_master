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
#ifndef PK_SET_DATA_FC
#define PK_SET_DATA_FC




#include "PKtool/utils/pk_iostream.h"
#include "PKtool/power_models/pk_estimation.h"
#include "PKtool/power_models/pk_model_creator.h"

#ifdef PK_ENABLE_TLM

namespace pk_tlm
{
 struct pk_TLMfc_data;
 class pk_socket_base;
}

#endif



namespace pk_core
{

 class power_kernel;
 class pk_kernel_impl; 
 class power_module_b;
 
 extern char tmp_ch;

 extern int reading_option;  

 extern const char* order_token[];  

 extern const char* get_order_token( int );  

 

// ----------------------------------------------------------------------------
//  CLASS : pk_read_cfg_data   
// ----------------------------------------------------------------------------


 class pk_read_cfg_data   
{
 
 friend class pk_core::pk_kernel_impl;
 friend class pk_core::power_module_b;

 pk_read_cfg_data( pk_kernel_impl* );

 void read_cfg_data();

 void read_cfg_data_();   

 bool monitorable_powmod();

 bool enable_window_options();  

 void set_reading_option();

 int read_options();   

 void stream_init();  

 void read_from_window();

 void read_from_file();

 void no_monitoring();

 void read_model_data();

 #ifdef PK_ENABLE_TLM

 void read_target_model_data();

 void read_socket_model_data( pk_tlm::pk_socket_base* );

 void read_TLM_model_data( pk_tlm::pk_TLMfc_data&, bool = false );

 void read_exectimes( pk_tlm::pk_TLMfc_data& );

 #endif
 
 template<class T> void read_data(char* str, T& data);

 template<bool> void read_data(char* str, bool& data);

 template<pk_est_type> void read_data(char* str, pk_est_type& data);

 void read_model_data_from_window();

 void read_model_data_from_file();  

 void set_init_pmodel();  
 
 ~pk_read_cfg_data();
 
 private:
 
 pk_kernel_impl* k_impl;
 ofstream outfile;
 std::ifstream infile;

 public: 
 static std::ifstream* curr_infile;

};

 template<class T>  inline void 
   pk_read_cfg_data::read_data(char* str, T& data)
 {
  pk_cout<<str;
  pk_cin>>data;
  pk_cout<<endl<<endl;
 }

template<>  inline void   
   pk_read_cfg_data::read_data<bool>(char* str, bool& data)
 {
  pk_cout<<str;
  char tmp = 'a';  
  cin>>tmp;
  while((tmp != 'y')&&(tmp != 'Y')&&(tmp != 'n')&&(tmp != 'N'))
  {
   cout<<str;
   cin>>tmp;
  };
  if((tmp == 'y')||(tmp == 'Y'))
  {
   data = true;
   outfile<<'Y';
  }
  else
  {
   data = false;
   outfile<<'N';
  }
  pk_cout<<endl<<endl;
 }
 

template<>  inline void   
   pk_read_cfg_data::read_data<pk_est_type>(char* str, pk_est_type& data)
 {
  pk_cout<<str;
  char tmp = 'a';  
  cin>>tmp;
  while((tmp != 'e')&&(tmp != 'E')&&(tmp != 'c')&&(tmp != 'C'))
  {
   cout<<"You must insert the char 'e' or 'c' =";
   cin>>tmp;
  };
  if((tmp == 'e')||(tmp == 'E'))
  {
   data = pk_est_type(pk_energy);
   outfile<<'E';
  }
  else
  {
   data = pk_comm;
   outfile<<'C';
  }
  pk_cout<<endl<<endl;
 }

 

 template<class T, class O, class I>  
	 void read_data_from_window(const char* str, T& param, O& ostr, I& istr, 
	                                                    const char tkn='=' )   
 {
  ostr<<str<<" "<<tkn<<" ";    
  istr >> param;
  ostr<<endl;   
 }

 template<class T>  void read_array_from_window(const char* str, T* param, int sz)
 {
  pk_cout<<str<<" = ";
  if(sz<=0)
  {
   cout<<"ERROR: array with invalid size"<<endl;  
   exit(1);
  }
  else
  {
   for(int i=0; i<sz; ++i)
   {
    pk_cin >> param[i];
    pk_cout<<' ';
   };
  };
  pk_cout<<endl;
 }

 template<class T>  void read_data_from_file( T& param, const char tkn='=' )
 {                                                       
   do (*pk_read_cfg_data::curr_infile) >> tmp_ch;
   while(tmp_ch != tkn);                                                       
  (*pk_read_cfg_data::curr_infile) >> param;
 }


 template<class T>  void read_array_from_file(T* array, int sz, const char tkn='=')
 {
  if(sz<=0)
  {
   cout<<"ERROR: array with invalid size"<<endl;  
   exit(1);
  }
  else
  {
   do (*pk_read_cfg_data::curr_infile) >> tmp_ch;                                                           
   while(tmp_ch != tkn);
   for(int i=0; i<sz; ++i)
    (*pk_read_cfg_data::curr_infile) >> array[i];
  };
 }


 void initialize(const sc_core::sc_module*);

 bool enable_window_option();

}  //pk_core

#endif

