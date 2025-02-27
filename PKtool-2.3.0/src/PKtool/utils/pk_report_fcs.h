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

#ifndef PK_REPORT_FCS_H
#define PK_REPORT_FCS_H

// the functionalities reported in this file are partially realized and cannot be used 
// at the moment, their implementation will be completed in the next version


namespace pk_core
{

// ----------------------------------------------------------------------------
//  CLASS : pk_report_fcs
// ----------------------------------------------------------------------------

#include <string>
#include "PKtool/utils/pk_report.h"


//forward declarations

class pk_report_actions;


// ----------------------------------------------------------------------------
//  CLASS : pk_report_actions
// ----------------------------------------------------------------------------

/*
class pk_report_actions
{
 
 public:
 
 virtual bool check() = 0;
 //virtual std::string report_msg() = 0; 
 
 pk_report make_report();


};

*/

#define PK_MAKE_REPORT_FC( return_type, name, impl_type )                                                  \
                                                                                                           \
template<class PF>                                                                                         \
return_type* name ( PF pf )                                                                                \
{                                                                                                          \
 pk_null_class& pnc = pk_null_class::null_obj();                                                           \
 return new impl_type<PF, pk_null_class, pk_null_class, pk_null_class>(pf, pnc, pnc, pnc);                 \
}                                                                                                          \
                                                                                                           \
template<class PF, class P1>                                                                               \
return_type* name ( PF pf, const P1& p1 )                                                                  \
{                                                                                                          \
 pk_null_class& pnc = pk_null_class::null_obj();                                                           \
 return new impl_type<PF, P1, pk_null_class, pk_null_class>(pf, p1, pnc, pnc);                             \
}                                                                                                          \
                                                                                                           \
template<class PF, class P1, class P2>                                                                     \
return_type* name ( PF pf, const P1& p1, const P2& p2 )                                                    \
{                                                                                                          \
 pk_null_class& pnc = pk_null_class::null_obj();                                                           \
 return new impl_type<PF, P1, P2, pk_null_class>(pf, p1, p2, pnc);                                         \
}                                                                                                          \
                                                                                                           \
template<class PF, class P1, class P2, class P3>                                                           \
return_type* name ( PF pf, const P1& p1, const P2& p2, const P3& p3 )                                      \
        { return new impl_type<PF, P1, P2, P3>(pf, p1, p2, p3); } 



// ----------------------------------------------------------------------------
//  CLASS : pk_null_class
// ----------------------------------------------------------------------------


class pk_null_class   
{
 public:

 static pk_null_class& null_obj()
 {
  static pk_null_class n_obj;
  return n_obj;
 };

};

inline void pk_null_fc()
{};

inline void pk_null_fc(pk_null_class)
{};

inline void pk_null_fc(pk_null_class, pk_null_class)
{};

inline void pk_null_fc(pk_null_class, pk_null_class, pk_null_class)
{};


// ----------------------------------------------------------------------------
//  CLASS : pk_report_fc_t
//
//  template implementation class for report functions; it can handle a function
//  with arbitrary output return type and input parameters types; the number
//  of input parameters can may vary from 0 to 3.
// ----------------------------------------------------------------------------


template<class O, class P1 = pk_null_class, class P2 = pk_null_class, class P3 = pk_null_class > 
         class pk_report_fc_t
{
 public:

   typedef O (*pnt_fc_0) ();
   typedef O (*pnt_fc_1) (const P1&);
   typedef O (*pnt_fc_2) (const P1&, const P2&);
   typedef O (*pnt_fc_3) (const P1&, const P2&, const P3&);

   typedef pk_null_class pk_nc;

 // constructors

 pk_report_fc_t( pnt_fc_0 pf, const pk_nc& p1, const pk_nc& p2, const pk_nc& p3  ): 
                  pf_0(pf), param_nb(0), param1(p1), param2(p2), param3(p3)  
 { };

 pk_report_fc_t( pnt_fc_1 pf, const P1& p1, const pk_nc& p2, const pk_nc& p3 ): 
				  pf_1(pf), param_nb(1), param1(p1), param2(p2), param3(p3)  
 { };

 pk_report_fc_t( pnt_fc_2 pf, const P1& p1, const P2& p2, const pk_nc& p3 ):
                  pf_2(pf), param_nb(2), param1(p1), param2(p2), param3(p3)  
 { };

 pk_report_fc_t( pnt_fc_3 pf, const P1& p1, const P2& p2, const P3& p3 ):
                  pf_3(pf), param_nb(3), param1(p1), param2(p2), param3(p3)  
 { };
 

 O report_fc()
 {
  switch(param_nb)
  {
   case 0:
    return pf_0( );
   break;

   case 1:
    return pf_1( param1 );
   break;
   
   case 2:
    return pf_2( param1, param2 );
   break;

   case 3:
    return pf_3( param1, param2, param3 );
   break; 

   default:
   return pf_0();
  };   
 };
 
 private:

 pnt_fc_0 pf_0;
 pnt_fc_1 pf_1;
 pnt_fc_2 pf_2;
 pnt_fc_3 pf_3;

 const int param_nb;

 const P1& param1;
 const P2& param2; 
 const P3& param3;

};


// ----------------------------------------------------------------------------
//  CLASS : pk_report_check
// ----------------------------------------------------------------------------


class pk_report_check
{
 friend class pk_report_actions;

 protected:
 public:  

 virtual bool action()
 { return false; }

};

template<class PF, class P1, class P2, class P3> 
                 class pk_repck_impl: public pk_report_check
{

 public:

 pk_repck_impl( PF pf, const P1& p1, const P2& p2, const P3& p3 ):
	                                       repfc_obj(pf, p1, p2, p3)
 {};

 private:
 
 bool action()
 { return repfc_obj.report_fc(); }

 pk_report_fc_t< bool,P1,P2,P3 > repfc_obj;

};

                                     

PK_MAKE_REPORT_FC( pk_report_check, make_repck_fc, pk_repck_impl )  

// ----------------------------------------------------------------------------
//  CLASS : pk_report_domsg
// ----------------------------------------------------------------------------




template<class PF, class P1, class P2, class P3>   class pk_report_msg   
{
 public:

 pk_report_msg( int id_, PF pf, const P1& p1, const P2& p2, const P3& p3 ):
	                                       msg_id_(id_), repfc_msg(pf, p1, p2, p3)
 {};

 inline const char* msg_text()
 {  return repfc_msg.report_fc();  };

 inline const int msg_id()
 {  return msg_id_; };

 private:
 
 int msg_id_;
 pk_report_fc_t< const char*,P1,P2,P3 > repfc_msg;
 

};

//PK_MAKE_REPORT_FC( pk_report_throw, make_repthw_fc, pk_repthw_impl ) 

// ----------------------------------------------------------------------------
//  CLASS : pk_report_throw
// ----------------------------------------------------------------------------

class pk_report_throw
{
 friend class pk_report_actions;

 protected:
 public:  

 virtual void action()
 { }

};

template<class PF, class P1, class P2, class P3> 
                 class pk_repthw_impl: public pk_report_throw
{

 public:

 pk_repthw_impl( PF pf, const P1& p1, const P2& p2, const P3& p3 ):
	                                       repfc_msg(pf, p1, p2, p3)
 {};

 private:
 
 void action()
 { PK_REPORT_ERROR(2, repfc_msg.report_fc() );
  if( severity == sc_core::SC_ERROR )
	  return PK_REPORT_ERROR( repfc_msg.msg_id(), repfc_msg.msg_text() );
  else if ( severity == sc_core::SC_WARNING )
	  return PK_REPORT_WARNING( repfc_msg.msg_id(), repfc_msg.msg_text() );
 }

 sc_core::sc_severity severity;
 pk_report_msg< const char*,P1,P2,P3 > repfc_msg;


};

PK_MAKE_REPORT_FC( pk_report_throw, make_repthw_fc, pk_repthw_impl ) 


// ----------------------------------------------------------------------------
//  CLASS : pk_report_actions
// ----------------------------------------------------------------------------

class pk_report_actions
{
 public:

 pk_report_actions(pk_report_throw* rt = 0, pk_report_check* rc = 0): 
	           check_h(rc), throw_h(rt)
 {};

 inline bool check()
 {
  if(check_h) return check_h->action();  
  else return true;
 };

 inline void throw_()
 { throw_h->action(); }

 private:

 pk_report_check* check_h;
 pk_report_throw* throw_h;

};


};   // pk_core  


#endif


