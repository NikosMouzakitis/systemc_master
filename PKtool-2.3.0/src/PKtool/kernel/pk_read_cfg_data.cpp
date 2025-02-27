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


#include <fstream>
#include <iostream>
#include <string>

#include "PKtool/utils/pk_report_ids.h"
#include "PKtool/power_models/power_model_b.h"
#include "PKtool/power_models/pk_model_lib_decl.h"
#include "sysc/kernel/sc_module.h"
#include "PKtool/utils/pk_report.h"
#include "PKtool/utils/pk_report_fcs.h"    
#include "PKtool/kernel/pk_kernel_impl.h"  
#include "PKtool/kernel/power_kernel.h"
#include "PKtool/kernel/power_module_b.h"
#include "PKtool/kernel/pk_read_cfg_data.h"
#include "PKtool/utils/pk_iostream.h"
#include "PKtool/kernel/pk_read_cfg_data.h"

#ifdef PK_ENABLE_TLM

#include "PKtool/tlm/pk_tlm_power_model_b.h"

#endif




using std::ifstream;
using std::ofstream;
using std::string;
class pk_kernel_impl;



namespace
{
 std::string message;

 const char* warning_msg1()
 { 
   message.clear();
   message += "the configuration file is defined but no data are reported.";
   message += "The required data will be forced to be achieved through the window interaction.";
   return message.c_str();
 };

  const char* error_msg1(char c)
 { 
  message.clear();
  message += "invalid value for  the setting ";
  message +="\"monitored power_module\"\n";
  message +="expected value: one among y,Y,n,N \n";
  message +="reported value: ";
  message += c;
  return message.c_str();
 };

 const char* error_msg2()
 { 
   message.clear();
   message += " the estimation type is wrong.";
   message += " Expected types: \"energy\" or \"commutations\"; \n";
   message += "Advice: retry the simulation selecting the option 1";
   return message.c_str();
 };

 const char* error_msg3(char c)
 { 
  message.clear();
  message += "invalid value for  the setting ";
  message +="\"enable window menu\".\n";
  message +="expected value: one among y,Y,n,N \n";
  message +="reported value: ";
  message += c;
  return message.c_str();
 };

 const char* error_msg4(const char* val_rng, int val)
 {
  message.clear();
  message += "\nselectable values: ";
  message += val_rng;
  message+="\nspecified value: ";
   char val_str[50]; 
  ::sprintf(val_str,"%d",val);   
  message += val_str;
  message+="\n"; 
  return message.c_str();
  };

 const char* error_msg5(int val, int state_nb)
 {
  message.clear();
  char val_str[10];  
  char stnb_str[10];
  ::sprintf(val_str, "%d", val);
  ::sprintf(stnb_str, "%d", state_nb);
  message += "the number of the power states is ";
  message += stnb_str;
  message += ", and you must specify an integer value in the range ";
  message += "[1-"; message += stnb_str; message += "]; " ;
  message += "\nspecified value: " ;
  message += val_str;
  message += "\n"; 
  return message.c_str();
  };

 const char* error_msg6(int val, int state_nb)
 {
  message.clear();
  char val_str[10];  
  char stnb_str[10];
  ::sprintf(val_str, "%d", val);
  ::sprintf(stnb_str, "%d", state_nb);
  message += "the number of the power states is ";
  message += stnb_str;
  message += ". In the configuration file you must report an integer value in the range ";
  message += "[1-"; message += stnb_str; message += "]; " ;
  message += "\ninserted value: " ;
  message += val_str;
  message += "\n"; 
  return message.c_str();
  };

 
 const char* error_msg7( )
 {
  message.clear();
  message += "The specified data are incomplete";
  return message.c_str();
  };

  const char* error_msg8(int index, bool* enabled_mod)
  {
   message.clear();
   char index_str[10];  
   ::sprintf( index_str, "%d", index );

   message += "you have specified a power model index ";
   message += "not associated to an available power model "; 
   message += "\n";
   message += "indexes of the available power models: ";
   for(int i=0; i<PK_MAX_MODEL_NB; ++i)
   {
    if( enabled_mod[i] )
	{
     char model_str[10];  
     ::sprintf( model_str, "%d", i );
     message += model_str;  message +=" ";
	}
   }
   message += "\n"; 
   message += "specified index: ";    
   message += index_str;
   message += "\n"; 

  return message.c_str();
 };

 #ifdef PK_ENABLE_TLM

  const char* error_msg9(int index, bool* enabled_mod)
  {
   message.clear();
   char index_str[10];  
   ::sprintf( index_str, "%d", index );

   message += "you have specified a power model index ";
   message += "not associated to an available TLM power model "; 
   message += "\n";
   message += "indexes of the available TLM power models: ";
   for(int i=0; i<PK_MAX_MODEL_NB; ++i)
   {
    if( enabled_mod[i] )
	{
     char model_str[10];  
     ::sprintf( model_str, "%d", i );
     message += model_str;  message +=" ";
	}
   }
   message += "\n"; 
   message += "specified index: ";    
   message += index_str;
   message += "\n"; 

  return message.c_str();
 };

 
 const char* error_msg10(double exectime)
 {
  message.clear();
  char exectime_str[10];  
  ::sprintf( exectime_str, "%f", exectime );

  message += "you have specified a negative execution time: ";   
  message += exectime_str;
  message += "\n"; 

  return message.c_str();
 }; 

 #endif

};


namespace pk_core
{

 extern bool pk_error_condition;

 const char* order_token[] = { "st", "nd", "rd", "th" };  

 const char* get_order_token( int i )   
 {
  int index = i%10;    
  if(index>3) index = 3;
  return order_token[index];
 };

 pk_creator_register* pcr = 0;

 pk_model_lib_handler* modlib_h = 0;

 void create_model(pk_kernel_impl* k_impl, unsigned mod_index) 
 { 
  pcr = &(modlib_h->creator_reg);   
  static int  arr_index = 0;
  k_impl->power_models[arr_index] = pcr->create_model(mod_index, *k_impl); 
  if( arr_index < (k_impl->state_nb -1) )++arr_index;   
  else arr_index = 0;      
 };

 #ifdef PK_ENABLE_TLM

 void create_TLM_model(pk_kernel_impl* k_impl, pk_tlm::tlm_power_model_b*& pm, unsigned mod_index)  
 { 
  pcr = &(modlib_h->creator_reg); 
  pm = dynamic_cast<pk_tlm::tlm_power_model_b*>( pcr->create_model(mod_index, *k_impl) );
 };

 #endif



 string cfg_fname, res_fname;
 char tmp_ch;
 const char* mod_name;
 int reading_option = 0;



  

 bool monitorable_powmod(const char* mod_nm)
 { pk_lnk = 6;  
  std::ifstream infile;
  mod_name= mod_nm;
  char tmp_ch=' ';
  cfg_fname=string("pk_");
  cfg_fname.append( mod_nm ).append("_cfg").append(".txt"); 
  infile.open(cfg_fname.c_str());
  if(!(infile))  return true;
  bool eof_=false;
  do infile>>tmp_ch;
  while( (tmp_ch!='=') && (!(eof_=infile.eof())) ); 
  if(tmp_ch=='=') infile>>tmp_ch;
  if( eof_ || (tmp_ch=='Y') || (tmp_ch=='y') ) return true; 
  else if((tmp_ch=='N') || (tmp_ch=='n')) 
  {
   std::string res_fname("pk_");
   res_fname.append(mod_nm).append("_res.txt");
   ofstream res_file(res_fname.c_str());
   res_file<<endl<<"*************** SIMULATION RESULTS ***************"<<endl<<endl<<endl;
         res_file<<"            NOT MONITORED POWER MODULE            "<<endl;
   infile.close();
   return false;
  }
  else
  {
   PK_REPORT_ERROR(PK_CORRUPTED_CFG_FILE_,  error_msg1(tmp_ch) );
  };
  return false;  
 };





 // ----------------------------------------------------------------------------
//  CLASS : pk_read_cfg_data
// -----------------------------------------------------------------------------

  ifstream* pk_read_cfg_data::curr_infile=0;

 pk_read_cfg_data::pk_read_cfg_data(pk_kernel_impl* p):k_impl(p)  
 { modlib_h = k_impl->modlib_h; };

 void pk_read_cfg_data::stream_init()
 {
  cfg_fname=string("pk_");
  cfg_fname.append( k_impl->mod_name ).append("_cfg").append(".txt");
  infile.open(cfg_fname.c_str());
  curr_infile= &infile;
  pk_cin.link(outfile);
  pk_cout.link(outfile);
  res_fname.clear();
  res_fname.append("pk_").append(k_impl->mod_name).append("_res.txt");
  k_impl->result_file.open(res_fname.c_str());
  k_impl->result_file<<endl<<"*************** SIMULATION RESULTS ***************"<<endl<<endl<<endl;
 };


void pk_read_cfg_data::read_cfg_data()
{ 
 stream_init(); 
 if( enable_window_options() )
 { 
  set_reading_option(); 
  switch(reading_option)    
  {
   case 1:
   read_from_window();
   break;
   case 2:
   read_from_file();   
   break;
   case 3: 
   no_monitoring();
  };
 }
 else read_from_file(); 
};

int pk_read_cfg_data::read_options()  
{ 
 stream_init(); 
 if( enable_window_options() )
  set_reading_option(); 
 else reading_option = 2; 
 return reading_option;
};

void pk_read_cfg_data::read_cfg_data_()  
{
 switch(reading_option)    
  {
   case 1:
   read_from_window();
   break;
   case 2:
   read_from_file();   
   break;
  }; 
}
 
 bool pk_read_cfg_data::enable_window_options()
 {
  bool eof_=false;   
  if(!infile) return true;
  do infile>>tmp_ch;
  while(tmp_ch != '=');  
  do infile>>tmp_ch;
  while( (tmp_ch != '=') && (!(eof_ = infile.eof())) ); 
  if(tmp_ch=='=') infile>>tmp_ch;
  if( eof_ || (tmp_ch=='Y') || (tmp_ch=='y') ) return true;  
  else if((tmp_ch == 'N') || (tmp_ch == 'n')) 
  {
   infile>>tmp_ch;
   eof_= infile.eof();  
   if( eof_  )return true;
   else return false;
  }
  else PK_REPORT_ERROR(PK_WRONG_SETTING_IN_FILE, error_msg3(tmp_ch));
  return false;
 };

 void pk_read_cfg_data::set_reading_option()
 {
  cout<<"-----------------------------------"<<endl;   
  cout<<"     POWER_MODULE: "<<k_impl->mod_name<<endl;    
  cout<<"-----------------------------------"<<endl<<endl<<endl;  
  if(k_impl->one_state) cout<<"OPTIONS FOR SPECIFYING THE POWER MODEL       "<<endl<<endl;
  else  cout<<"OPTIONS FOR SPECIFYING THE POWER MODELS       "<<endl<<endl;
  if(infile.eof())
  {
   PK_REPORT_WARNING(PK_NO_DATA_IN_CFG_FILE_, warning_msg1());
   reading_option = 1;    
   return;
  };
  bool bad_option = false;
  const char* value_range = "1, 2 or 3";
  do
  {
   try
   {
   cout<<"1: interaction with window "<<endl;
   cout<<"2: reading from configuration file"<<endl;
   cout<<"3: no monitoring "<<endl;
   cout<<endl<<"select an option ("<<value_range<<") = ";
   cin>>reading_option;   
   cout<<endl;
   if( (reading_option != 1 ) && (reading_option != 2) && (reading_option != 3)  )
    PK_REPORT_ERROR( PK_WRONG_VALUE_SELECTED_, error_msg4( value_range, reading_option ) );  
   else bad_option = false;
  }
  catch(const pk_report& x)
  {
	std::cout<<x.what()<<endl;
    std::cout<<"\nRepeat the selection"<<endl<<endl;
	pk_error_condition = false;
    bad_option = true;
	cin.clear();  
  }
  }
  while(bad_option);
 };


 

 void pk_read_cfg_data::read_from_window()
 {
  outfile.open(cfg_fname.c_str());
  pcr = &(modlib_h->creator_reg);
  pk_cout.file_()<<"   Configuration file    power_module: "<<k_impl->mod_name<<endl<<endl;  
  outfile<<"monitored power_module (Y/N)= Y"<<endl<<endl;  
  outfile<<"enable window menu (Y/N)= Y"<<endl<<endl; 
  outfile<<endl<<endl;

  #ifdef PK_ENABLE_TLM
  if(k_impl->TLM_on)
  { pk_cout<<endl<<"    POWER MODEL SPECIFICATION FOR TLM FUNCTIONS"<<endl<<endl;  
    modlib_h->print_TLM_info(pk_cout);
	if(k_impl->target_on)
	{
     pk_cout<<endl<<"                  IMPLEMENTED FUNCTIONS"<<endl<<endl;
     pk_cout<<"TLM functions selected: ";
     for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)                
     { if(k_impl->target_fc_data.TLMfc_on[i]) pk_cout<<pk_tlm::pk_fc_names[i]<<"  "; } 
	 pk_cout<<endl;
     read_target_model_data();
	}
   if(k_impl->init_on)
   {
    pk_cout<<endl<<endl<<"       SOCKET-RELATED FUNCTIONS"<<endl<<endl;
    for(int i=0; i<k_impl->socket_nb; ++i)
	{
	 pk_tlm::pk_socket_base* s = k_impl->socket_aug[i];
	 pk_cout<<endl<<"SOCKET: "<<s->name<<endl;
	 pk_cout<<"TLM functions selected: ";
	 for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)                
     { if(s->fc_data.TLMfc_on[i]) pk_cout<<pk_tlm::pk_fc_names[i]<<"  "; } 
	 pk_cout<<endl;
     read_socket_model_data(s);   
	}
   }
   if(k_impl->idle_power_on) 
	   k_impl->set_idle_power_data(*this);
   return;
  }
  #endif

  if(k_impl->state_nb != 1)
	  pk_cout<<"number of power states: "<<k_impl->state_nb<<endl; 

  modlib_h->print_general_info(pk_cout);

  if(k_impl->state_nb == 1)  
	      k_impl->init_st = -1;  
  else 
  {
   bool wrong_value = false;
   do   
   {
    try
	{
	 pk_core::read_data_from_window( "initial power state" , k_impl->init_st, cout, cin );  
	 for(int i=1; i<=k_impl->state_nb; ++i)               
	 {
	  if( i == k_impl->state_nb )
         PK_REPORT_ERROR(PK_WRONG_VALUE_INSERTED_, error_msg5(k_impl->init_st, k_impl->state_nb ) );  
	  if( k_impl->init_st == i )  { 
		  k_impl->init_st = i; wrong_value = false; 
		  outfile<<"initial power state = "<<k_impl->init_st<<endl;
		  break; }  
	 };     
	}
	catch(const pk_report& x)
    {
	 std::cout<<x.what()<<endl;
     std::cout<<"\nInsert a new value"<<endl<<endl;
	 pk_error_condition = false;
     wrong_value = true;
	 cin.clear();  
    }
   }
   while(wrong_value);
  };
  k_impl->curr_st = k_impl->past_st = k_impl->init_st;
  read_model_data();
 };



 void pk_read_cfg_data::read_from_file()  
 {
  bool eof_= false;
  char tmp_ch = ' '; 

  #ifdef PK_ENABLE_TLM

  if(k_impl->TLM_on)
  { 
   if(k_impl->target_on)
     read_target_model_data();
   if(k_impl->init_on)
   {
    for(int i=0; i<k_impl->socket_nb; ++i)
      read_socket_model_data(k_impl->socket_aug[i]);
   }
   if(k_impl->idle_power_on) 
	        k_impl->set_idle_power_data(*this);
   return;
  };
   
  #endif

  if( k_impl->state_nb != 1 )
  {
   do infile>>tmp_ch;
   while( (tmp_ch!=':') && (!(eof_=infile.eof())) );  
   if(eof_)
     { PK_REPORT_ERROR( PK_CORRUPTED_CFG_FILE_, error_msg7() ); };
  };
  /*
  do infile>>tmp_ch;
  while( (tmp_ch!=':') && (!(eof_=infile.eof())) );
  if(eof_)
    { PK_REPORT_ERROR( PK_CORRUPTED_CFG_FILE_, error_msg7() ); }; 
  
  do infile>>tmp_ch;
  while(tmp_ch!=':'); 
  */
  for(int j=0; j<4; ++j)
  {
	do infile>>tmp_ch;
    while( (tmp_ch!=':') && (!(eof_=infile.eof())) );
    if(eof_)
    { PK_REPORT_ERROR( PK_CORRUPTED_CFG_FILE_, error_msg7() ); };
  }
  if(k_impl->state_nb == 1)     
          k_impl->init_st = -1;  
  else
  {
   do infile>>tmp_ch;
   while(tmp_ch != '=');
   infile>>k_impl->init_st;
   for(int i=1; i<=k_impl->state_nb; ++i)               
   {
	if( k_impl->init_st == i )  { k_impl->init_st = i;  break; } 
	if( i == k_impl->state_nb )
    PK_REPORT_ERROR(PK_WRONG_SETTING_IN_FILE, error_msg6(k_impl->init_st, k_impl->state_nb ) );  
   };    
   k_impl->curr_st = k_impl->past_st = k_impl->init_st;  
  };
  read_model_data();
  
 };


 void pk_read_cfg_data::set_init_pmodel()  
 { 
  const int& init_st_ = k_impl->init_st;    
  if(init_st_ == -1) k_impl->pm = k_impl->power_models[0];   
  else k_impl->pm = k_impl->power_models[init_st_ - 1];       
  k_impl->pm->set_signals(*k_impl); 
  return;
 }; 

void pk_read_cfg_data::no_monitoring()
{
  k_impl->monitored = false;
  #ifdef PK_ENABLE_TLM
   k_impl->TLM_on = false;
   for(int i=0; i<k_impl->socket_nb; ++i) 
    for(int j=0; j<pk_tlm::pk_tlmfc_nb; ++j)
		      k_impl->socket_aug[i]->fc_data.TLMfc_on[j] = false;
  
   for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)
	    k_impl-> target_fc_data.TLMfc_on[i] = false;

  #endif
  outfile.open(cfg_fname.c_str()); 
  outfile<<"   Configuration file    power_module: "<<k_impl->mod_name<<endl<<endl;  
  outfile<<"monitored power_module (Y/N)= N"<<endl<<endl; 
  k_impl->result_file<<"            NOT MONITORED POWER_MODULE      "<<endl;
};



 void pk_read_cfg_data::read_model_data()
 {
  if(reading_option == 1) read_model_data_from_window();   
  else read_model_data_from_file();
 };


 #ifdef PK_ENABLE_TLM

 void pk_read_cfg_data::read_target_model_data()
 { read_TLM_model_data(k_impl->target_fc_data); }

 void pk_read_cfg_data::read_socket_model_data(pk_tlm::pk_socket_base* s)
 {  read_TLM_model_data( s->fc_data, true ); }


void pk_read_cfg_data::read_TLM_model_data( pk_tlm::pk_TLMfc_data& fcd, bool socket )
 {
  if(reading_option == 1)
  {
   bool enabled_models[PK_MAX_MODEL_NB];
   bool wrong_value = false; 
   int ind = 0;
   k_impl->modlib_h->model_indexes_in_TLM(enabled_models, true);
   for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)                
   { 
    if(fcd.TLMfc_on[i])
	{
     pk_cout<<endl<<"function: "<<pk_tlm::pk_fc_names[i]<<endl;
     do
     {
	 wrong_value = false;
	 try
	 { 
	  read_data_from_window("power model", fcd.TLMpm_indexs[i], std::cout, std::cin);
	  ind = fcd.TLMpm_indexs[i]; 
	 
	  if((ind<0) || (PK_MAX_MODEL_NB<=ind))
       { PK_REPORT_ERROR(PK_WRONG_VALUE_INSERTED_, error_msg9(ind, enabled_models) ); } 
	  else if( !enabled_models[ind] )
       { PK_REPORT_ERROR(PK_WRONG_VALUE_INSERTED_, error_msg9(ind, enabled_models) ); }
	  else ;
	 }
	 catch(const pk_report& x)
	 {
	  std::cout<<x.what()<<endl;
      std::cout<<"\nInsert a new value"<<endl<<endl;
	  pk_error_condition = false;
      wrong_value = true;
	  cin.clear();  
     }
    }
    while(wrong_value);	
    create_TLM_model(k_impl, fcd.TLMfc_pm[i], ind);
    pk_tlm::tlm_power_model_b* pm = fcd.TLMfc_pm[i];
    pk_cout<<"power model: "<<pm->name()<<"  numeric index: "<<pm->numeric_id()<<endl;
    pm->set_static_data();
    }
   }
  }  
  else 
  {
   bool eof_= false;
   int iter = 3;
   if(socket && k_impl->target_on) iter = 2;
   else if( socket && !k_impl->target_on ) iter = 4;
   for(int i=0; i<iter; ++i)  
   {
	do infile>>tmp_ch;  
    while( (tmp_ch!=':') && (!(eof_=infile.eof())) );
   };
   for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)               
   { 
    if(fcd.TLMfc_on[i]) 
    {   
	do infile>>tmp_ch;
    while( (tmp_ch!=':') && (!(eof_=infile.eof())) );
    do infile>>tmp_ch;
    while( (tmp_ch!=':') && (!(eof_=infile.eof())) );
	read_data_from_file( fcd.TLMpm_indexs[i], ':' );
	create_TLM_model(k_impl, fcd.TLMfc_pm[i], fcd.TLMpm_indexs[i]);
    pk_tlm::tlm_power_model_b* pm = fcd.TLMfc_pm[i];
    pm->set_static_data();
   };
  };
 };   
};


 void pk_read_cfg_data::read_exectimes( pk_tlm::pk_TLMfc_data& fcd )
 {
  if(reading_option == 1)
  {
   bool wrong_value = false;
   double exec_time = 0;
   for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)                
   { 
    if(fcd.TLMfc_on[i])
	{
     pk_cout<<endl<<"function: "<<pk_tlm::pk_fc_names[i]<<endl;
     do
     {
	 wrong_value = false;
	 try
	 { 
	  read_data_from_window("average execution time (ns)", fcd.TLMfc_exectimes[i], std::cout, std::cin);
	  exec_time = fcd.TLMfc_exectimes[i]; 
	 
	  if(exec_time<0) 
      { PK_REPORT_ERROR(PK_WRONG_VALUE_INSERTED_, error_msg10(exec_time) ); } 
	 }
	 catch(const pk_report& x)
	 {
	  std::cout<<x.what()<<endl;
      std::cout<<"\nInsert a new value"<<endl<<endl;
	  pk_error_condition = false;
      wrong_value = true;
	  cin.clear();  
     }
    }
    while(wrong_value);	
	outfile<<"average execution time (ns) = "<<exec_time<<endl;
    }
   }
  }  
  else 
  {  
   for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)               
   { 
    if(fcd.TLMfc_on[i]) 
    { 
	 read_data_from_file( fcd.TLMfc_exectimes[i], '=' );
   };
  }; 
	  
   /*
   bool eof_= false;
   int iter = 3;
   if(socket && k_impl->target_on) iter = 2;
   else if( socket && !k_impl->target_on ) iter = 4;
   for(int i=0; i<iter; ++i)  
   {
	do infile>>tmp_ch;  
    while( (tmp_ch!=':') && (!(eof_=infile.eof())) );
   };
   for(int i=0; i<pk_tlm::pk_tlmfc_nb; ++i)               
   { 
    if(fcd.TLMfc_on[i]) 
    {   
	do infile>>tmp_ch;
    while( (tmp_ch!=':') && (!(eof_=infile.eof())) );
    do infile>>tmp_ch;
    while( (tmp_ch!=':') && (!(eof_=infile.eof())) );
	read_data_from_file( fcd.TLMpm_indexs[i], ':' );
	create_TLM_model(k_impl, fcd.TLMfc_pm[i], fcd.TLMpm_indexs[i]);
    pk_tlm::tlm_power_model_b* pm = fcd.TLMfc_pm[i];
    pm->set_static_data();
   };
  };  */
 };   
};
 

#endif


 void pk_read_cfg_data::read_model_data_from_window()
 {
  int ind = 0;
  bool enabled_models[PK_MAX_MODEL_NB];
  k_impl->modlib_h->model_indexes(enabled_models);  

  bool wrong_value ; 
  for (int i=0; i<k_impl->state_nb; i++) 
  { 
   if(!k_impl->one_state)   
	    pk_cout<<endl<<i+1<<get_order_token(i)<<" POWER STATE"<<endl<<endl;
   do
   {
    wrong_value = false;  
	try
	{ 
	 read_data_from_window("power model", k_impl->pm_indexs[i], std::cout, std::cin);
	 ind = k_impl->pm_indexs[i]; 
	 
	 if((ind<0) || (PK_MAX_MODEL_NB<=ind))
       { PK_REPORT_ERROR(PK_WRONG_VALUE_INSERTED_, error_msg8(ind, enabled_models) ); } 
	 else if( !enabled_models[ind] )
       { PK_REPORT_ERROR(PK_WRONG_VALUE_INSERTED_, error_msg8(ind, enabled_models) ); }
	 else ;
	}
	catch(const pk_report& x)
	{
	 std::cout<<x.what()<<endl;
     std::cout<<"\nInsert a new value"<<endl<<endl;
	 pk_error_condition = false;
     wrong_value = true;
	 cin.clear();  
    }
   }
   while(wrong_value);
   create_model(k_impl, k_impl->pm_indexs[i]);
   power_model_b* pm = k_impl->power_models[i];
   pk_cout<<"power model: "<<pm->name()<<"  numeric index: "<<pm->numeric_id()<<endl;
   pm->set_static_data();
  };
  set_init_pmodel();    
 };



 void pk_read_cfg_data::read_model_data_from_file()   
 { 
  for(int i=0; i<k_impl->state_nb; i++)
  {
   for(int j=0; j<1; ++j)  
    do infile>>tmp_ch;        
    while(tmp_ch!=':'); 
   read_data_from_file( k_impl->pm_indexs[i], ':' );
   create_model(k_impl, k_impl->pm_indexs[i]);
   power_model_b* pm = k_impl->power_models[i];
   pm->set_static_data();   
  };
  set_init_pmodel();  
 };


 pk_read_cfg_data::~pk_read_cfg_data()
 {
  if(infile) infile.close();
 };
 
};
