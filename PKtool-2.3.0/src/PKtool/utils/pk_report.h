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

#ifndef PK_REPORT_H
#define PK_REPORT_H

namespace pk_core
{

class sc_report_handler_base;


// ----------------------------------------------------------------------------
//  CLASS : pk_report
//
//  adapter class for sc_report objects 
// ----------------------------------------------------------------------------

class pk_report: public sc_core::sc_report
{
 public:

 typedef sc_core::sc_report base_type;

 // constructor

 pk_report(const base_type& rep):sc_report(rep)
 {
  adaptation();
 };

 private:
 void adaptation();
 
};


// ----------------------------------------------------------------------------
//  CLASS : pk_report_handler
//
//  report-manager class customized for PKtool.
// ----------------------------------------------------------------------------

class pk_insert_msg;

typedef sc_core::sc_report_handler_proc pk_report_handler_proc;


class pk_report_handler: public sc_core::sc_report_handler
{
 friend class pk_insert_msg;
 public:

 static void add_static_msg_types(sc_core::sc_report_handler::msg_def_items *);

 // constructor

 static void report(sc_core::sc_severity,
		       const char* msg_type,
		       const char* msg,
		       const char* file,
		       int line);

 static void report(sc_core::sc_severity,
		            int         id,
		            const char* add_msg,
		            const char* file,
		            int         line);

 static void report_handler(const sc_core::sc_report& , 
	                          const sc_core::sc_actions& ); 

 static pk_report_handler_proc  handler;
 
 private:

 static void insert_msg();

 static void set_pk_handler();

 static void restore_sc_handler();  

 static sc_core::sc_report_handler::msg_def_items* pk_messages;
 static sc_core::sc_report_handler::msg_def_items* sc_messages;  

};


#define PK_REPORT_WARNING(id,msg)                                             \
	pk_report_handler::report( sc_core::SC_WARNING, id, msg, __FILE__, __LINE__ )

#define PK_REPORT_ERROR(id,msg)                                             \
	pk_report_handler::report( sc_core::SC_ERROR, id, msg, __FILE__, __LINE__ )



}   // pk_core  

#endif
