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


#include "PKtool/utils/pk_report_syscrefs.h"     
#include "PKtool/kernel/pk_settings.h"  
#include "PKtool/utils/pk_report.h"
#include <iostream>     


namespace pk_core  
{

bool pk_error_condition = false;


// ----------------------------------------------------------------------------
//  CLASS : pk_insert_msg
// ----------------------------------------------------------------------------

class pk_insert_msg
{
 friend class pk_report_handler;

 pk_insert_msg()
 {  pk_report_handler::insert_msg(); }
 
};


// ----------------------------------------------------------------------------
//  CLASS : pk_report
// ----------------------------------------------------------------------------

const std::string pk_report_compose_message(const sc_core::sc_report& );


void pk_report::adaptation()
{
 static char empty_str[] = "";
 if ( m_what != empty_str ) free(m_what);
 m_what = strdup(pk_report_compose_message(*this).c_str()) ;
};


// ----------------------------------------------------------------------------
//  CLASS : pk_report_handler
// ----------------------------------------------------------------------------


sc_core::sc_report_handler::msg_def_items* pk_report_handler::pk_messages = 0;
sc_core::sc_report_handler::msg_def_items* pk_report_handler::sc_messages = 0;

void pk_report_handler::insert_msg()
{
 pk_messages->next = messages->next;
 messages->next = pk_messages;
};

 void pk_report_handler::set_pk_handler()  
 {
  using namespace sc_core;
  sc_messages = messages;
  messages = messages->next;
  sc_report_handler::set_handler(pk_report_handler::report_handler);
 };

 void pk_report_handler::restore_sc_handler() 
 {
  set_handler(sc_report_handler::handler);    
  messages = sc_messages;
 };




pk_report_handler_proc  pk_report_handler::handler = 
                      sc_core::sc_report_handler::default_handler;

const std::string pk_report_compose_message(const sc_core::sc_report& rep)
{
    static const char * severity_names[] = {
	"PKtool Info", "PKtool Warning", "PKtool Error", "PKtool Fatal"
    };
    std::string str;

    str += severity_names[rep.get_severity()];
    str += ": ";

    if ( rep.get_id() >= 0 ) 
    {
	char idstr[64];
	sprintf(idstr, "(%s%c%d) ","PK_",
		"IWEF"[rep.get_severity()], rep.get_id());
	str += idstr;
    }
    str += rep.get_msg_type();

    if( *rep.get_msg() )
    {
	str += ": ";
	str += rep.get_msg();
    }
    if( rep.get_severity() > SC_INFO )
    {
        char line_number_str[16];
	str += "\nIn file: ";
	str += rep.get_file_name();
	str += ":";
	sprintf(line_number_str, "%d", rep.get_line_number());
	str += line_number_str;
	sc_simcontext* simc = sc_get_curr_simcontext();

	#ifdef PK_SYSC_22    
	 if( simc && sc_is_running() )
    #else
	 if( simc && simc->is_running() )  
    #endif
	{
	    const char* proc_name = rep.get_process_name();

	    if( proc_name )
	    {
		str += "\nIn process: ";
		str += proc_name;
		str += " @ ";
		str += rep.get_time().to_string();
	    }
	}
    }

    return str;
}


}  






#define PK_DEFINE_MESSAGE(id,unused,text) extern const char id[] = text;
	

#include "PKtool/utils/pk_report_ids.h"




namespace pk_core  
{


#undef PK_DEFINE_MESSAGE



static sc_msg_def texts[] = {

// same definition of the macro SC_DEFINE_MESSAGE(id,n,unused)
#define PK_DEFINE_MESSAGE(id,n,unused) \
    { (id), 0u, {0u}, 0u, {0u}, 0u, 0u, {0u}, 0, n },
	 


	 #undef PK_KERNEL_IDS_H

	#define PK_INSIDE_PKCORE_NS

     #include "PKtool/utils/pk_report_ids.h"

	#undef PK_INSIDE_PKCORE_NS
	 



};



static sc_report_handler::msg_def_items items = {
    texts, sizeof(texts)/sizeof(*texts), false, 0
};

void pk_report_handler::report(sc_core::sc_severity severity_,  
		       int         id,
		       const char* add_msg,
		       const char* file,
		       int         line)
{ 
  
  using namespace sc_core;
  msg_def_items* old_msgs = messages;
  messages = messages->next;
  sc_report_handler::set_handler(pk_report_handler::report_handler);
  sc_report_handler::report( severity_, id, add_msg, file, line);
  set_handler(&sc_report_handler::default_handler);  
  messages = old_msgs;  
};

void pk_report_handler::report(sc_core::sc_severity severity_,
			       const char * msg_type,
			       const char * msg,
			       const char * file,
			       int          line)
{ 
  static pk_insert_msg insert_obj;
  set_pk_handler();                     
  try
  {
   sc_report_handler::report( severity_, msg_type, msg, file, line);
  }
  catch(sc_report& rep)
  {
   restore_sc_handler();
   pk_report pk_rep(rep);  
   throw pk_rep;
  }
  restore_sc_handler();  
};


void pk_report_handler::add_static_msg_types(sc_core::sc_report_handler::msg_def_items* items)
{
 items->allocated = false;
 items->next = pk_messages;
 pk_messages = items;
};

static ::std::ofstream* log_stream = 0;

void pk_report_handler::report_handler(const sc_core::sc_report& rep, 
	                          const sc_core::sc_actions& actions)
{
	using namespace sc_core;

     if ( actions & SC_DISPLAY )
	 {
	  ::std::cout << ::std::endl << pk_report_compose_message(rep) << 
		::std::endl;
	  ( const_cast<sc_core::sc_actions&>(actions) ) ^= SC_DISPLAY;
	 }
	 if ( (actions & SC_LOG) && get_log_file_name() )
     {
	  if ( !log_stream )
	  {
	   std::string log_name;
	   log_name += "pk_";
	   log_name += get_log_file_name();  
	    log_stream = new ::std::ofstream(log_name.c_str()); 
	  }
	  *log_stream << rep.get_time() << ": "
	    << pk_report_compose_message(rep) << ::std::endl;
	  ( const_cast<sc_core::sc_actions&>(actions) ) ^= SC_LOG;
     }
	 if ( (actions & SC_THROW) ||  (actions & SC_ABORT) )
		 pk_error_condition = true;   
     
	 sc_core::sc_report_handler::default_handler(rep, actions);  
                                                                    
};


};   // pk_core  

static
int initialize()
{
	pk_core::pk_report_handler::add_static_msg_types(& pk_core::items);
    return 42;
}

static int forty_two = initialize();




