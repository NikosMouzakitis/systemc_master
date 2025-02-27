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

#ifndef PK_FIX_TYPES
#define PK_FIX_TYPES


#include "PKtool/types_aug/pk_aug_signals.h"




namespace pk_dt
{
using sc_dt::sc_fxnum_observer;
using sc_dt::sc_fxnum_subref;
using sc_dt::sc_fxnum_bitref;

using sc_dt::sc_fxnum_fast_observer;
using sc_dt::sc_fxnum_fast_subref;
using sc_dt::sc_fxnum_fast_bitref;

using sc_dt::sc_fxnum_observer;
using sc_dt::sc_fxnum_subref;
using sc_dt::sc_fxnum_bitref;

using sc_dt::SC_DEFAULT_WL_ ;
using sc_dt::SC_DEFAULT_IWL_ ;
using sc_dt::SC_DEFAULT_Q_MODE_ ;
using sc_dt::SC_DEFAULT_O_MODE_ ;
using sc_dt::SC_DEFAULT_N_BITS_ ;


// ----------------------------------------------------------------------------
//  CLASS : sc_fix_aug
//
//  class for the internal augmented signals related to the SystemC type sc_fix_aug
// ----------------------------------------------------------------------------



class sc_fix_aug: public sc_fix, 
	              public pk_core::pk_internal_sgn< sc_fix >
{

 public:

 // constructors
 
 explicit sc_fix_aug( sc_fxnum_observer* ob= 0 ): sc_fix(ob), pk_internal_sgn<sc_fix>(this)
 { }

 sc_fix_aug( int wl, int iwl, sc_fxnum_observer* ob=0 ): 
              sc_fix(wl, iwl, ob), pk_internal_sgn<sc_fix>(this)
 {}

 sc_fix_aug( sc_q_mode qm, sc_o_mode om, sc_fxnum_observer* ob=0 ): 
			  sc_fix(qm, om, ob), pk_internal_sgn<sc_fix>(this) 
 {}

 
 sc_fix_aug( sc_q_mode qm, sc_o_mode om, int nb, sc_fxnum_observer* ob=0 ):
       sc_fix(qm, om, nb, ob), pk_internal_sgn<sc_fix>(this) 
 {}

 sc_fix_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, sc_fxnum_observer* ob=0 ):
	   sc_fix(wl, iwl, qm, om, ob), pk_internal_sgn<sc_fix>(this) 
 {}

 sc_fix_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, int nb, sc_fxnum_observer* ob=0 ):
	   sc_fix(wl, iwl, qm, om, nb, ob), pk_internal_sgn<sc_fix>(this) 
 {}

 explicit sc_fix_aug( const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ):
	   sc_fix(cast_sw, ob), pk_internal_sgn<sc_fix>(this) 
 {}

 sc_fix_aug( int wl, int iwl, const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob=0 ):
	   sc_fix(wl, iwl, cast_sw, ob), pk_internal_sgn<sc_fix>(this)
 {}

 sc_fix_aug( sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw ,
	         sc_fxnum_observer* ob=0 ):
       sc_fix(qm, om, cast_sw, ob), pk_internal_sgn<sc_fix>(this)
 {}
 
 sc_fix_aug( sc_q_mode qm, sc_o_mode om, int nb, const sc_fxcast_switch& cast_sw,
	         sc_fxnum_observer* ob=0 ):
       sc_fix(qm, om, nb, cast_sw, ob), pk_internal_sgn<sc_fix>(this) 
 {}
 
 sc_fix_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw, 
			 sc_fxnum_observer* ob=0 ):
       sc_fix(wl, iwl, qm, om, cast_sw, ob), pk_internal_sgn<sc_fix>(this) 
 {}

 sc_fix_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, int nb,
	         const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob=0 ):
       sc_fix(wl, iwl, qm, om, nb, cast_sw, ob), pk_internal_sgn<sc_fix>(this) 
 {}

 explicit sc_fix_aug( const sc_fxtype_params& type_params, sc_fxnum_observer* ob=0 ):
       sc_fix(type_params, ob),pk_internal_sgn<sc_fix>(this) 
 {}

 sc_fix_aug( const sc_fxtype_params& type_params, const sc_fxcast_switch& cast_sw,
	         sc_fxnum_observer* ob=0 ):
       sc_fix(type_params, cast_sw, ob), pk_internal_sgn<sc_fix>(this) 
 {}


 #define PK_DEFN_CTORS_T(tp)                                                       \
  sc_fix_aug( tp val, int wl_, int iwl_, sc_fxnum_observer* ob= 0 ):               \
         sc_fix(val, wl_, iwl_, ob ), pk_internal_sgn<sc_fix>(this)                \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_fix_aug( tp val, sc_q_mode qm, sc_o_mode om, sc_fxnum_observer* ob= 0 ):      \
         sc_fix(val, qm, om, ob ), pk_internal_sgn<sc_fix>(this)                   \
              {}                                                                   \
			                                                                       \
			                                                                       \
  sc_fix_aug( tp val, sc_q_mode qm, sc_o_mode om, int nb,                          \
	                             sc_fxnum_observer* ob= 0 ):                       \
         sc_fix(val, qm, om, nb, ob ), pk_internal_sgn<sc_fix>(this)               \
              {}                                                                   \
			                                                                       \
			                                                                       \
  sc_fix_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om,               \
	                             sc_fxnum_observer* ob= 0 ):                       \
         sc_fix(val, wl_, iwl_, qm, om, ob ), pk_internal_sgn<sc_fix>(this)        \
              { }                                                                  \
			                                                                       \
                                                                                   \
			                                                                       \
  sc_fix_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om, int nb,       \
	                             sc_fxnum_observer* ob= 0 ):                       \
         sc_fix(val, wl_, iwl_, qm, om, nb, ob ), pk_internal_sgn<sc_fix>(this)    \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_fix_aug( tp val, const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ): \
         sc_fix(val, cast_sw, ob ), pk_internal_sgn<sc_fix>(this)                  \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_fix_aug( tp val, int wl_, int iwl_, const sc_fxcast_switch& cast_sw,          \
	                               sc_fxnum_observer* ob= 0 ):                     \
         sc_fix(val, wl_, iwl_, cast_sw, ob ), pk_internal_sgn<sc_fix>(this)       \
              { }                                                                  \
			                                                                       \
                                                                                   \
			                                                                       \
  sc_fix_aug( tp val, sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw, \
	                             sc_fxnum_observer* ob= 0 ):                       \
         sc_fix(val, qm, om, cast_sw, ob ), pk_internal_sgn<sc_fix>(this)          \
              { }                                                                  \
			                                                                       \
                                                                                   \
			                                                                       \
  sc_fix_aug( tp val, sc_q_mode qm, sc_o_mode om, int nb,                          \
	           const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ):        \
         sc_fix(val, qm, om, nb, cast_sw, ob ), pk_internal_sgn<sc_fix>(this)      \
              { }                                                                  \
               	                                                                   \
                                                                                   \
			                                                                      \
         sc_fix_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om,        \
                     const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ):  \
		    sc_fix(val, wl_, iwl_, qm, om, cast_sw, ob ), pk_internal_sgn<sc_fix>(this)   \
				{ }                                                              \
                                                                                 \
				                                                                 \
			                                                                     \
      sc_fix_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om, int nb,   \
                     const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ):  \
		    sc_fix(val, wl_, iwl_, qm, om, nb, cast_sw, ob ), pk_internal_sgn<sc_fix>(this)   \
				{ }                                                                \
                                                                                   \
				                                                                   \
			                                                                     \
  sc_fix_aug( tp val, const sc_fxtype_params& fp, sc_fxnum_observer* ob= 0 ):      \
         sc_fix(val, fp, ob ), pk_internal_sgn<sc_fix>(this)                       \
			  { }                                                                 \
                                                                                  \
                                                                                  \
  sc_fix_aug( tp val, const sc_fxtype_params& fp, const sc_fxcast_switch& cast_sw, \
                                                  sc_fxnum_observer* ob= 0 ):      \
	     sc_fix(val, fp, cast_sw, ob ), pk_internal_sgn<sc_fix>(this)              \
              { }                                                                  
                      
                 
              
 
                      
  #define PK_DEFN_CTORS_T_A(tp)                                                     \
          sc_fix_aug( tp val, sc_fxnum_observer* ob= 0 ):                           \
	        sc_fix(val, ob ), pk_internal_sgn<sc_fix>(this)                         \
			    { }                                                                 \
	  PK_DEFN_CTORS_T(tp)                                                          

  #define PK_DEFN_CTORS_T_B(tp)                                                    \
     explicit sc_fix_aug( tp val, sc_fxnum_observer* ob= 0 ):                      \
		 sc_fix(val, ob ), pk_internal_sgn<sc_fix>(this)                           \
              { }                                                                  \
    PK_DEFN_CTORS_T(tp)                                                                  
    
   
    PK_DEFN_CTORS_T_A(int)
    PK_DEFN_CTORS_T_A(unsigned int)
    PK_DEFN_CTORS_T_A(long)
    PK_DEFN_CTORS_T_A(unsigned long)
    PK_DEFN_CTORS_T_A(double)
    PK_DEFN_CTORS_T_A(const char*)
    PK_DEFN_CTORS_T_A(const sc_fxval&)
    PK_DEFN_CTORS_T_A(const sc_fxval_fast&)
    PK_DEFN_CTORS_T_A(const sc_fxnum&)
    PK_DEFN_CTORS_T_A(const sc_fxnum_fast&)
 #ifndef SC_FX_EXCLUDE_OTHER
    PK_DEFN_CTORS_T_B(int64)
    PK_DEFN_CTORS_T_B(uint64)
    PK_DEFN_CTORS_T_B(const sc_int_base&)
    PK_DEFN_CTORS_T_B(const sc_uint_base&)
    PK_DEFN_CTORS_T_B(const sc_signed&)
    PK_DEFN_CTORS_T_B(const sc_unsigned&)
 #endif

 #undef PK_DEFN_CTORS_T
 #undef PK_DEFN_CTORS_T_A
 #undef PK_DEFN_CTORS_T_B

 sc_fix_aug( const sc_fix& fx ):
	  sc_fix( fx ), pk_internal_sgn<sc_fix>(this)         
 { }

 sc_fix_aug( const sc_fix_aug& fx ): sc_fix( static_cast<const sc_fix& >(fx) ),
	                                   pk_internal_sgn<sc_fix>(this)
 { }
 
                                                                    
 // assignment operators

 sc_fix_aug& operator=( const sc_fix& fx )
 {
  compute_data();
  sc_fix::operator =(fx);
  return *this;
 }

 sc_fix_aug& operator=( const sc_fix_aug& fx )
 {
  return this->operator =( static_cast< const sc_fix& >(fx));
 }

 #define PK_DEFN_ASN_OP_T(op,tp)                                              \
    sc_fix_aug& operator op ( tp val )                                        \
    {                                                                         \
     compute_data();                                                            \
     sc_fix::operator op (val);                                               \
     return *this;                                                            \
    }

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DEFN_ASN_OP_OTHER(op)                                             \
    PK_DEFN_ASN_OP_T(op,int64)                                                \
    PK_DEFN_ASN_OP_T(op,uint64)                                               \
    PK_DEFN_ASN_OP_T(op,const sc_int_base&)                                   \
    PK_DEFN_ASN_OP_T(op,const sc_uint_base&)                                  \
    PK_DEFN_ASN_OP_T(op,const sc_signed&)                                     \
    PK_DEFN_ASN_OP_T(op,const sc_unsigned&)                                    
#else
#define PK_DEFN_ASN_OP_OTHER(op)
#endif

#define PK_DEFN_ASN_OP(op)                                                       \
    PK_DEFN_ASN_OP_T(op,int)                                                     \
    PK_DEFN_ASN_OP_T(op,unsigned int)                                            \
    PK_DEFN_ASN_OP_T(op,long)                                                    \
    PK_DEFN_ASN_OP_T(op,unsigned long)                                           \
    PK_DEFN_ASN_OP_T(op,double)                                                  \
    PK_DEFN_ASN_OP_T(op,const char*)                                             \
    PK_DEFN_ASN_OP_T(op,const sc_fxval&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxval_fast&)                                    \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum_fast&)                                    \
    PK_DEFN_ASN_OP_OTHER(op)                   

    PK_DEFN_ASN_OP(=)

    PK_DEFN_ASN_OP(*=)
    PK_DEFN_ASN_OP(/=)
    PK_DEFN_ASN_OP(+=)
    PK_DEFN_ASN_OP(-=)

    PK_DEFN_ASN_OP_T(<<=,int)
    PK_DEFN_ASN_OP_T(>>=,int)

    PK_DEFN_ASN_OP_T(&=,const sc_fix&)
    PK_DEFN_ASN_OP_T(&=,const sc_fix_fast&)
    PK_DEFN_ASN_OP_T(|=,const sc_fix&)
    PK_DEFN_ASN_OP_T(|=,const sc_fix_fast&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix_fast&)

  #undef PK_DEFN_ASN_OP_T
  #undef PK_DEFN_ASN_OP_OTHER
  #undef PK_DEFN_ASN_OP

// other writing operators and methods

 const sc_fxval operator ++ ( int i)
 {
  compute_data();
  return sc_fix:: operator ++ ( i ); 
 }

 const sc_fxval operator -- ( int i)
 {
  compute_data();
  return sc_fix:: operator -- ( i ); 
 }

 sc_fix_aug& operator ++ ()
 {
  compute_data();
  sc_fix::operator ++( );
  return *this;
 }

 sc_fix_aug& operator -- ()
 {
  compute_data();
  sc_fix::operator --( );
  return *this;
 }
 
 sc_fxnum_bitref operator [] (int i)
 {
  compute_data();
  return sc_fix::operator[] (i);
 }

 sc_fxnum_bitref bit (int i)
 {
  compute_data();
  return sc_fix::bit (i);
 }

 sc_fxnum_subref operator() (int i, int j)
 {
  compute_data();
  return sc_fix::operator () (i,j);
 }

 sc_fxnum_subref range (int i, int j)
 {
  compute_data();
  return sc_fix::range (i,j);
 }

 sc_fxnum_subref operator() ()
 {
  compute_data();
  return sc_fix::operator () ();
 }

 sc_fxnum_subref range ( )
 {
  compute_data();
  return sc_fix::range ( );
 }


 void scan (istream & is=cin)
 {
  compute_data();
  sc_fix::scan( is );
 }

 



 // writing friend functions (declarations)

 friend void b_not( sc_fix_aug&, const sc_fix& );
 friend void b_and( sc_fix_aug&, const sc_fix&, const sc_fix& );
 friend void b_and( sc_fix_aug&, const sc_fix&, const sc_fix_fast& );
 friend void b_and( sc_fix_aug&, const sc_fix_fast&, const sc_fix& );
 friend void b_or ( sc_fix_aug&, const sc_fix&, const sc_fix& );
 friend void b_or ( sc_fix_aug&, const sc_fix&, const sc_fix_fast& );
 friend void b_or ( sc_fix_aug&, const sc_fix_fast&, const sc_fix& );
 friend void b_xor( sc_fix_aug&, const sc_fix&, const sc_fix& );
 friend void b_xor( sc_fix_aug&, const sc_fix&, const sc_fix_fast& );
 friend void b_xor( sc_fix_aug&, const sc_fix_fast&, const sc_fix& );

 

 friend void neg( sc_fix_aug&, const sc_fxnum& );
 friend void lshift( sc_fix_aug&, const sc_fxnum&, int );
 friend void rshift( sc_fix_aug&, const sc_fxnum&, int );

 #define PK_DECL_BIN_FNC_T(fnc,tp)                                            \
    friend void fnc ( sc_fix_aug&, const sc_fxnum&, tp );                     \
    friend void fnc ( sc_fix_aug&, tp, const sc_fxnum& );

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DECL_BIN_FNC_OTHER(fnc)                                              \
    PK_DECL_BIN_FNC_T(fnc,int64)                                                 \
    PK_DECL_BIN_FNC_T(fnc,uint64)                                                \
    PK_DECL_BIN_FNC_T(fnc,const sc_int_base&)                                    \
    PK_DECL_BIN_FNC_T(fnc,const sc_uint_base&)                                   \
    PK_DECL_BIN_FNC_T(fnc,const sc_signed&)                                      \
    PK_DECL_BIN_FNC_T(fnc,const sc_unsigned&)
 #else
 #define PK_DECL_BIN_FNC_OTHER(fnc)
 #endif

 #define PK_DECL_BIN_FNC(fnc)                                                    \
    friend void fnc ( sc_fix_aug&, const sc_fxnum&, const sc_fxnum& );           \
    PK_DECL_BIN_FNC_T(fnc,int)                                                   \
    PK_DECL_BIN_FNC_T(fnc,unsigned int)                                          \
    PK_DECL_BIN_FNC_T(fnc,long)                                                  \
    PK_DECL_BIN_FNC_T(fnc,unsigned long)                                         \
    PK_DECL_BIN_FNC_T(fnc,double)                                                \
    PK_DECL_BIN_FNC_T(fnc,const char*)                                           \
    PK_DECL_BIN_FNC_T(fnc,const sc_fxval&)                                       \
    PK_DECL_BIN_FNC_T(fnc,const sc_fxval_fast&)                                  \
    PK_DECL_BIN_FNC_T(fnc,const sc_fxnum_fast&)                                  \
    PK_DECL_BIN_FNC_OTHER(fnc)

    PK_DECL_BIN_FNC(mult)
    PK_DECL_BIN_FNC(div)
    PK_DECL_BIN_FNC(add)
    PK_DECL_BIN_FNC(sub)

 #undef PK_DECL_BIN_FNC_T
 #undef PK_DECL_BIN_FNC_OTHER
 #undef PK_DECL_BIN_FNC

};


// writing friend functions (definitions)

inline
void
b_not( sc_fix_aug& c, const sc_fix& a )
{
 c.compute_data();
 sc_dt:: b_not(static_cast<sc_fix&>(c), a) ;
};

#define PK_DEFN_BIN_FNC_1(fnc,tp1,tp2)                                                          \
inline void fnc ( sc_fix_aug& c, const tp1& a, const tp2& b )                                   \
{c.compute_data();                                                                                \
 sc_dt:: fnc(static_cast<sc_fix&>(c), a, b );                                                   \
};


PK_DEFN_BIN_FNC_1(b_and,sc_fix,sc_fix)
PK_DEFN_BIN_FNC_1(b_and,sc_fix,sc_fix_fast)
PK_DEFN_BIN_FNC_1(b_and,sc_fix_fast,sc_fix)

PK_DEFN_BIN_FNC_1(b_or,sc_fix,sc_fix)
PK_DEFN_BIN_FNC_1(b_or,sc_fix,sc_fix_fast)
PK_DEFN_BIN_FNC_1(b_or,sc_fix_fast,sc_fix)

PK_DEFN_BIN_FNC_1(b_xor,sc_fix,sc_fix)
PK_DEFN_BIN_FNC_1(b_xor,sc_fix,sc_fix_fast)
PK_DEFN_BIN_FNC_1(b_xor,sc_fix_fast,sc_fix)


#define PK_DEFN_BIN_FNC_2(fnc,tp)                                             \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_aug& c, const sc_fxnum& a, tp b )                                \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                    \
}                                                                             \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_aug& c, tp a, const sc_fxnum& b )                                \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                            \
}                                                                               

#ifndef SC_FX_EXCLUDE_OTHER
#define PK_DEFN_BIN_FNC_OTHER(fnc)                                               \
PK_DEFN_BIN_FNC_2(fnc,int64)                                                     \
PK_DEFN_BIN_FNC_2(fnc,uint64)                                                    \
PK_DEFN_BIN_FNC_2(fnc,const sc_int_base&)                                        \
PK_DEFN_BIN_FNC_2(fnc,const sc_uint_base&)                                       \
PK_DEFN_BIN_FNC_2(fnc,const sc_signed&)                                          \
PK_DEFN_BIN_FNC_2(fnc,const sc_unsigned&)
#else
#define PK_DEFN_BIN_FNC_OTHER(fnc)
#endif

#define PK_DEFN_BIN_FNC(fnc)                                                  \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_aug& c, const sc_fxnum& a, const sc_fxnum& b )                   \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                           \
}                                                                             \
	                                                                          \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_aug& c, const sc_fxnum& a, const sc_fxval& b )                   \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                           \
}                                                                             \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_aug& c, const sc_fxval& a, const sc_fxnum& b )                   \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                           \
}                                                                             \
                                                                              \
PK_DEFN_BIN_FNC_2(fnc,int)                                                    \
PK_DEFN_BIN_FNC_2(fnc,unsigned int)                                           \
PK_DEFN_BIN_FNC_2(fnc,long)                                                   \
PK_DEFN_BIN_FNC_2(fnc,unsigned long)                                          \
PK_DEFN_BIN_FNC_2(fnc,double)                                                 \
PK_DEFN_BIN_FNC_2(fnc,const char*)                                            \
PK_DEFN_BIN_FNC_2(fnc,const sc_fxval_fast&)                                   \
PK_DEFN_BIN_FNC_2(fnc,const sc_fxnum_fast&)                                   \
PK_DEFN_BIN_FNC_OTHER(fnc)

PK_DEFN_BIN_FNC(mult)
PK_DEFN_BIN_FNC(div)
PK_DEFN_BIN_FNC(add)
PK_DEFN_BIN_FNC(sub)

#undef PK_DEFN_BIN_FNC_1
#undef PK_DEFN_BIN_FNC_2
#undef PK_DEFN_BIN_FNC_OTHER
#undef PK_DEFN_BIN_FNC


// ----------------------------------------------------------------------------
//  CLASS : sc_fix_fast_aug
//
//  class for the internal augmented signals related to the SystemC type sc_fix_fast_aug
// ----------------------------------------------------------------------------


class sc_fix_fast_aug: public sc_fix_fast, 
	                   public pk_core::pk_internal_sgn< sc_fix_fast >
{
 public:

 // constructors

 explicit sc_fix_fast_aug( sc_fxnum_fast_observer* ob= 0 ): 
             sc_fix_fast(ob), pk_internal_sgn<sc_fix_fast>(this)
 { }

 sc_fix_fast_aug( int wl, int iwl, sc_fxnum_fast_observer* ob=0 ): 
              sc_fix_fast(wl, iwl, ob), pk_internal_sgn<sc_fix_fast>(this)
 { }

 sc_fix_fast_aug( sc_q_mode qm, sc_o_mode om, sc_fxnum_fast_observer* ob=0 ): 
			  sc_fix_fast(qm, om, ob), pk_internal_sgn<sc_fix_fast>(this)
 { }

 
 sc_fix_fast_aug( sc_q_mode qm, sc_o_mode om, int nb, sc_fxnum_fast_observer* ob=0 ):
       sc_fix_fast(qm, om, nb, ob), pk_internal_sgn<sc_fix_fast>(this)
 { }

 sc_fix_fast_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, sc_fxnum_fast_observer* ob=0 ):
	   sc_fix_fast(wl, iwl, qm, om, ob), pk_internal_sgn<sc_fix_fast>(this) 
 { }

 sc_fix_fast_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, int nb, sc_fxnum_fast_observer* ob=0 ):
	   sc_fix_fast(wl, iwl, qm, om, nb, ob), pk_internal_sgn<sc_fix_fast>(this)
 { }

 explicit sc_fix_fast_aug( const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ):
	   sc_fix_fast(cast_sw, ob), pk_internal_sgn<sc_fix_fast>(this) 
 { }

 sc_fix_fast_aug( int wl, int iwl, const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob=0 ):
	   sc_fix_fast(wl, iwl, cast_sw, ob), pk_internal_sgn<sc_fix_fast>(this) 
 { }

 sc_fix_fast_aug( sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw ,
	         sc_fxnum_fast_observer* ob=0 ):
       sc_fix_fast(qm, om, cast_sw, ob), pk_internal_sgn<sc_fix_fast>(this)
 { }
 
 sc_fix_fast_aug( sc_q_mode qm, sc_o_mode om, int nb, const sc_fxcast_switch& cast_sw,
	         sc_fxnum_fast_observer* ob=0 ):
       sc_fix_fast(qm, om, nb, cast_sw, ob), pk_internal_sgn<sc_fix_fast>(this) 
 { }
 
 sc_fix_fast_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw, 
			 sc_fxnum_fast_observer* ob=0 ):
       sc_fix_fast(wl, iwl, qm, om, cast_sw, ob), pk_internal_sgn<sc_fix_fast>(this) 
 { }

 sc_fix_fast_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, int nb,
	         const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob=0 ):
       sc_fix_fast(wl, iwl, qm, om, nb, cast_sw, ob), pk_internal_sgn<sc_fix_fast>(this)
 { }

 explicit sc_fix_fast_aug( const sc_fxtype_params& type_params, sc_fxnum_fast_observer* ob=0 ):
       sc_fix_fast(type_params, ob), pk_internal_sgn<sc_fix_fast>(this) 
 { }

 sc_fix_fast_aug( const sc_fxtype_params& type_params, const sc_fxcast_switch& cast_sw,
	         sc_fxnum_fast_observer* ob=0 ):
       sc_fix_fast(type_params, cast_sw, ob), pk_internal_sgn<sc_fix_fast>(this) 
 { }


 #define PK_DEFN_CTORS_T(tp)                                                       \
  sc_fix_fast_aug( tp val, int wl_, int iwl_, sc_fxnum_fast_observer* ob= 0 ):     \
         sc_fix_fast(val, wl_, iwl_, ob ), pk_internal_sgn<sc_fix_fast>(this)      \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_fix_fast_aug( tp val, sc_q_mode qm, sc_o_mode om, sc_fxnum_fast_observer* ob= 0 ): \
         sc_fix_fast(val, qm, om, ob ), pk_internal_sgn<sc_fix_fast>(this)         \
              { }                                                                  \
			                                                                       \
			                                                                      \
  sc_fix_fast_aug( tp val, sc_q_mode qm, sc_o_mode om, int nb,                     \
	                             sc_fxnum_fast_observer* ob= 0 ):                  \
         sc_fix_fast(val, qm, om, nb, ob ), pk_internal_sgn<sc_fix_fast>(this)     \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_fix_fast_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om,               \
	                             sc_fxnum_fast_observer* ob= 0 ):                       \
         sc_fix_fast(val, wl_, iwl_, qm, om, ob ), pk_internal_sgn<sc_fix_fast>(this)   \
              { }                                                                 \
			                                                                      \
                                                                                  \
			                                                                      \
  sc_fix_fast_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om, int nb,       \
	                             sc_fxnum_fast_observer* ob= 0 ):                       \
         sc_fix_fast(val, wl_, iwl_, qm, om, nb, ob ), pk_internal_sgn<sc_fix_fast>(this)           \
              { }                                                                \
			                                                                     \
			                                                                     \
  sc_fix_fast_aug( tp val, const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ): \
         sc_fix_fast(val, cast_sw, ob ), pk_internal_sgn<sc_fix_fast>(this)        \
              { }                                                                   \
			                                                                       \
			                                                                       \
  sc_fix_fast_aug( tp val, int wl_, int iwl_, const sc_fxcast_switch& cast_sw,          \
	                               sc_fxnum_fast_observer* ob= 0 ):                     \
         sc_fix_fast(val, wl_, iwl_, cast_sw, ob ), pk_internal_sgn<sc_fix_fast>(this)  \
              { }                                                                        \
			                                                                        \
                                                                                    \
			                                                                        \
  sc_fix_fast_aug( tp val, sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw, \
	                             sc_fxnum_fast_observer* ob= 0 ):                       \
         sc_fix_fast(val, qm, om, cast_sw, ob ), pk_internal_sgn<sc_fix_fast>(this)     \
              { }                                                                        \
			                                                                       \
                                                                                   \
			                                                                     \
  sc_fix_fast_aug( tp val, sc_q_mode qm, sc_o_mode om, int nb,                          \
	           const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ):        \
         sc_fix_fast(val, qm, om, nb, cast_sw, ob ), pk_internal_sgn<sc_fix_fast>(this) \
              { }                                                                        \
                	                                                                \
                                                                                    \
			                                                                        \
         sc_fix_fast_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om,        \
                     const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ):  \
		    sc_fix_fast(val, wl_, iwl_, qm, om, cast_sw, ob ), pk_internal_sgn<sc_fix_fast>(this)   \
				{ }                                                                      \
                                                                                 \
				                                                                 \
			                                                                     \
      sc_fix_fast_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om, int nb,   \
                     const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ):  \
		    sc_fix_fast(val, wl_, iwl_, qm, om, nb, cast_sw, ob ), pk_internal_sgn<sc_fix_fast>(this)   \
				{  }                                                                       \
                                                                                   \
				                                                                   \
			                                                                       \
  sc_fix_fast_aug( tp val, const sc_fxtype_params& fp, sc_fxnum_fast_observer* ob= 0 ):      \
         sc_fix_fast(val, fp, ob ), pk_internal_sgn<sc_fix_fast>(this)             \
			  { }                                                                   \
                                                                                   \
                                                                                  \
  sc_fix_fast_aug( tp val, const sc_fxtype_params& fp, const sc_fxcast_switch& cast_sw, \
                                                  sc_fxnum_fast_observer* ob= 0 ):      \
	     sc_fix_fast(val, fp, cast_sw, ob ), pk_internal_sgn<sc_fix_fast>(this)         \
              { }                                                                        
                       
                    
              
 
                      
  #define PK_DEFN_CTORS_T_A(tp)                                                     \
          sc_fix_fast_aug( tp val, sc_fxnum_fast_observer* ob= 0 ):                 \
	        sc_fix_fast(val, ob ), pk_internal_sgn<sc_fix_fast>(this)               \
			    { }                                                                 \
	  PK_DEFN_CTORS_T(tp)                                                          

  #define PK_DEFN_CTORS_T_B(tp)                                                    \
     explicit sc_fix_fast_aug( tp val, sc_fxnum_fast_observer* ob= 0 ):            \
		 sc_fix_fast(val, ob ), pk_internal_sgn<sc_fix_fast>(this)                 \
              { }                                                                  \
    PK_DEFN_CTORS_T(tp)                                                                  
    
   
    PK_DEFN_CTORS_T_A(int)
    PK_DEFN_CTORS_T_A(unsigned int)
    PK_DEFN_CTORS_T_A(long)
    PK_DEFN_CTORS_T_A(unsigned long)
    PK_DEFN_CTORS_T_A(double)
    PK_DEFN_CTORS_T_A(const char*)
    PK_DEFN_CTORS_T_A(const sc_fxval&)
    PK_DEFN_CTORS_T_A(const sc_fxval_fast&)
    PK_DEFN_CTORS_T_A(const sc_fxnum&)
    PK_DEFN_CTORS_T_A(const sc_fxnum_fast&)
 #ifndef SC_FX_EXCLUDE_OTHER
    PK_DEFN_CTORS_T_B(int64)
    PK_DEFN_CTORS_T_B(uint64)
    PK_DEFN_CTORS_T_B(const sc_int_base&)
    PK_DEFN_CTORS_T_B(const sc_uint_base&)
    PK_DEFN_CTORS_T_B(const sc_signed&)
    PK_DEFN_CTORS_T_B(const sc_unsigned&)
 #endif

 #undef PK_DEFN_CTORS_T
 #undef PK_DEFN_CTORS_T_A
 #undef PK_DEFN_CTORS_T_B

 sc_fix_fast_aug( const sc_fix_fast& fx ):
	  sc_fix_fast( fx ), pk_internal_sgn<sc_fix_fast>(this)          
 { }

 sc_fix_fast_aug( const sc_fix_fast_aug& fx ): 
        sc_fix_fast( static_cast<const sc_fix_fast& >(fx) ), pk_internal_sgn<sc_fix_fast>(this)
 { }
 
                                                                    
 // assignment operators

 sc_fix_fast_aug& operator=( const sc_fix_fast& fx )
 {
  compute_data();
  sc_fix_fast::operator =(fx);
  return *this;
 }

 sc_fix_fast_aug& operator=( const sc_fix_fast_aug& fx )
 {
  return this->operator =( static_cast< const sc_fix_fast& >(fx));
 }

 #define PK_DEFN_ASN_OP_T(op,tp)                                              \
    sc_fix_fast_aug& operator op ( tp val )                                   \
    {                                                                         \
     compute_data();                                                            \
     sc_fix_fast::operator op (val);                                          \
     return *this;                                                            \
    }

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DEFN_ASN_OP_OTHER(op)                                             \
    PK_DEFN_ASN_OP_T(op,int64)                                                \
    PK_DEFN_ASN_OP_T(op,uint64)                                               \
    PK_DEFN_ASN_OP_T(op,const sc_int_base&)                                   \
    PK_DEFN_ASN_OP_T(op,const sc_uint_base&)                                  \
    PK_DEFN_ASN_OP_T(op,const sc_signed&)                                     \
    PK_DEFN_ASN_OP_T(op,const sc_unsigned&)                                    
#else
#define PK_DEFN_ASN_OP_OTHER(op)
#endif

#define PK_DEFN_ASN_OP(op)                                                       \
    PK_DEFN_ASN_OP_T(op,int)                                                     \
    PK_DEFN_ASN_OP_T(op,unsigned int)                                            \
    PK_DEFN_ASN_OP_T(op,long)                                                    \
    PK_DEFN_ASN_OP_T(op,unsigned long)                                           \
    PK_DEFN_ASN_OP_T(op,double)                                                  \
    PK_DEFN_ASN_OP_T(op,const char*)                                             \
    PK_DEFN_ASN_OP_T(op,const sc_fxval&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxval_fast&)                                    \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum_fast&)                                    \
    PK_DEFN_ASN_OP_OTHER(op)                   

    PK_DEFN_ASN_OP(=)

    PK_DEFN_ASN_OP(*=)
    PK_DEFN_ASN_OP(/=)
    PK_DEFN_ASN_OP(+=)
    PK_DEFN_ASN_OP(-=)

    PK_DEFN_ASN_OP_T(<<=,int)
    PK_DEFN_ASN_OP_T(>>=,int)

    PK_DEFN_ASN_OP_T(&=,const sc_fix&)
    PK_DEFN_ASN_OP_T(&=,const sc_fix_fast&)
    PK_DEFN_ASN_OP_T(|=,const sc_fix&)
    PK_DEFN_ASN_OP_T(|=,const sc_fix_fast&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix_fast&)

  #undef PK_DEFN_ASN_OP_T
  #undef PK_DEFN_ASN_OP_OTHER
  #undef PK_DEFN_ASN_OP

// other writing operators and methods

 const sc_fxval_fast operator ++ ( int i)
 {
  compute_data();
  return sc_fix_fast:: operator ++ ( i ); 
 }

 const sc_fxval_fast operator -- ( int i)
 {
  compute_data();
  return sc_fix_fast:: operator -- ( i ); 
 }

 sc_fix_fast_aug& operator ++ ()
 {
  compute_data();
  sc_fix_fast::operator ++( );
  return *this;
 }

 sc_fix_fast_aug& operator -- ()
 {
  compute_data();
  sc_fix_fast::operator --( );
  return *this;
 }
 
 sc_fxnum_fast_bitref operator [] (int i)
 {
  compute_data();
  return sc_fix_fast::operator[] (i);
 }

 sc_fxnum_fast_bitref bit (int i)
 {
  compute_data();
  return sc_fix_fast::bit (i);
 }

 sc_fxnum_fast_subref operator() (int i, int j)
 {
  compute_data();
  return sc_fix_fast::operator () (i,j);
 }

 sc_fxnum_fast_subref range (int i, int j)
 {
  compute_data();
  return sc_fix_fast::range (i,j);
 }

 sc_fxnum_fast_subref operator() ()
 {
  compute_data();
  return sc_fix_fast::operator () ();
 }

 sc_fxnum_fast_subref range ( )
 {
  compute_data();
  return sc_fix_fast::range ( );
 }


 void scan (istream & is=cin)
 {
  compute_data();
  sc_fix_fast::scan( is );
 }

 // writing friend functions (declarations)

 friend void b_not( sc_fix_fast_aug&, const sc_fix_fast& );
 friend void b_and( sc_fix_fast_aug&, const sc_fix_fast&, const sc_fix_fast& );
 friend void b_or ( sc_fix_fast_aug&, const sc_fix_fast&, const sc_fix_fast& );
 friend void b_xor( sc_fix_fast_aug&, const sc_fix_fast&, const sc_fix_fast& );

 
 
 friend void neg( sc_fix_fast_aug&, const sc_fxnum& );
 friend void lshift( sc_fix_fast_aug&, const sc_fxnum_fast&, int );
 friend void rshift( sc_fix_fast_aug&, const sc_fxnum_fast&, int );

 #define DECL_BIN_FNC_T(fnc,tp)                                               \
    friend void fnc ( sc_fix_fast_aug&, const sc_fxnum_fast&, tp );           \
    friend void fnc ( sc_fix_fast_aug&, tp, const sc_fxnum_fast& );

 #ifndef SC_FX_EXCLUDE_OTHER
 #define DECL_BIN_FNC_OTHER(fnc)                                              \
    DECL_BIN_FNC_T(fnc,int64)                                                 \
    DECL_BIN_FNC_T(fnc,uint64)                                                \
    DECL_BIN_FNC_T(fnc,const sc_int_base&)                                    \
    DECL_BIN_FNC_T(fnc,const sc_uint_base&)                                   \
    DECL_BIN_FNC_T(fnc,const sc_signed&)                                      \
    DECL_BIN_FNC_T(fnc,const sc_unsigned&)
 #else
 #define DECL_BIN_FNC_OTHER(fnc)
 #endif

 #define DECL_BIN_FNC(fnc)                                                    \
    friend void fnc ( sc_fix_fast_aug&, const sc_fxnum_fast&, const sc_fxnum_fast& );        \
    DECL_BIN_FNC_T(fnc,int)                                                   \
    DECL_BIN_FNC_T(fnc,unsigned int)                                          \
    DECL_BIN_FNC_T(fnc,long)                                                  \
    DECL_BIN_FNC_T(fnc,unsigned long)                                         \
    DECL_BIN_FNC_T(fnc,double)                                                \
    DECL_BIN_FNC_T(fnc,const char*)                                           \
    DECL_BIN_FNC_T(fnc,const sc_fxval&)                                       \
    DECL_BIN_FNC_T(fnc,const sc_fxval_fast&)                                  \
    DECL_BIN_FNC_T(fnc,const sc_fxnum&)                                       \
    DECL_BIN_FNC_OTHER(fnc)

    DECL_BIN_FNC(mult)
    DECL_BIN_FNC(div)
    DECL_BIN_FNC(add)
    DECL_BIN_FNC(sub)

 #undef DECL_BIN_FNC_T
 #undef DECL_BIN_FNC_OTHER
 #undef DECL_BIN_FNC

};

// writing friend functions (definitions)

inline
void
b_not( sc_fix_fast_aug& c, const sc_fix_fast& a )
{
 c.compute_data();
 sc_dt:: b_not(static_cast<sc_fix_fast&>(c), a) ;
};

#define PK_DEFN_BIN_FNC_1(fnc,tp1,tp2)                                                               \
inline void fnc ( sc_fix_fast_aug& c, const tp1& a, const tp2& b )                                   \
{c.compute_data();                                                                                     \
 sc_dt:: fnc(static_cast<sc_fix_fast&>(c), a, b );                                                   \
};


PK_DEFN_BIN_FNC_1(b_and,sc_fix_fast,sc_fix_fast)
PK_DEFN_BIN_FNC_1(b_or,sc_fix_fast,sc_fix_fast)
PK_DEFN_BIN_FNC_1(b_xor,sc_fix_fast,sc_fix_fast)

#define PK_DEFN_BIN_FNC_2(fnc,tp)                                             \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_fast_aug& c, const sc_fxnum_fast& a, tp b )                      \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );                      \
}                                                                             \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_fast_aug& c, tp a, const sc_fxnum_fast& b )                      \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );                      \
}                                                                               

#ifndef SC_FX_EXCLUDE_OTHER
#define PK_DEFN_BIN_FNC_OTHER(fnc)                                               \
PK_DEFN_BIN_FNC_2(fnc,int64)                                                     \
PK_DEFN_BIN_FNC_2(fnc,uint64)                                                    \
PK_DEFN_BIN_FNC_2(fnc,const sc_int_base&)                                        \
PK_DEFN_BIN_FNC_2(fnc,const sc_uint_base&)                                       \
PK_DEFN_BIN_FNC_2(fnc,const sc_signed&)                                          \
PK_DEFN_BIN_FNC_2(fnc,const sc_unsigned&)
#else
#define PK_DEFN_BIN_FNC_OTHER(fnc)
#endif

#define PK_DEFN_BIN_FNC(fnc)                                                  \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_fast_aug& c, const sc_fxnum_fast& a, const sc_fxnum_fast& b )                   \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );                      \
}                                                                             \
	                                                                          \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_fast_aug& c, const sc_fxnum_fast& a, const sc_fxval_fast& b )    \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );                      \
}                                                                             \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_fix_fast_aug& c, const sc_fxval_fast& a, const sc_fxnum_fast& b )    \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );                      \
}                                                                             \
                                                                              \
PK_DEFN_BIN_FNC_2(fnc,int)                                                    \
PK_DEFN_BIN_FNC_2(fnc,unsigned int)                                           \
PK_DEFN_BIN_FNC_2(fnc,long)                                                   \
PK_DEFN_BIN_FNC_2(fnc,unsigned long)                                          \
PK_DEFN_BIN_FNC_2(fnc,double)                                                 \
PK_DEFN_BIN_FNC_2(fnc,const char*)                                            \
PK_DEFN_BIN_FNC_2(fnc,const sc_fxval&)                                        \
PK_DEFN_BIN_FNC_2(fnc,const sc_fxnum&)                                        \
PK_DEFN_BIN_FNC_OTHER(fnc)

PK_DEFN_BIN_FNC(mult)
PK_DEFN_BIN_FNC(div)
PK_DEFN_BIN_FNC(add)
PK_DEFN_BIN_FNC(sub)

#undef PK_DEFN_BIN_FNC_1
#undef PK_DEFN_BIN_FNC_2
#undef PK_DEFN_BIN_FNC_OTHER
#undef PK_DEFN_BIN_FNC




// ----------------------------------------------------------------------------
//  CLASS : sc_fixed_aug
//
//  class for the internal augmented signals related to the SystemC type sc_fixed
// ----------------------------------------------------------------------------


template <int W, int I,
	  sc_q_mode Q = SC_DEFAULT_Q_MODE_,
	  sc_o_mode O = SC_DEFAULT_O_MODE_, int N = SC_DEFAULT_N_BITS_>
class sc_fixed_aug : public sc_fix_aug 
{
 public:

 //constructors

 explicit sc_fixed_aug( sc_fxnum_observer* ob_ = 0 ): 
          sc_fix_aug( W, I, Q, O, N, ob_ )
 {}

 explicit sc_fixed_aug( const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_ = 0 ): 
          sc_fix_aug( W, I, Q, O, N, fs_, ob_ )
 {}

 
    
#define PK_DEFN_CTORS_T_A(tp)                                                             \
  sc_fixed_aug( tp val, sc_fxnum_observer* ob_= 0 ):                                      \
   sc_fix_aug( a, W, I, Q, O, N, ob_ )                                                    \
  {}                                                                                      \
                                                                                          \
  sc_fixed_aug( tp val, const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_= 0 ):         \
    sc_fix( a, W, I, Q, O, N, fs_, ob_ )                                                  \
  { }

  #define PK_DEFN_CTORS_T_B(tp)                                                           \
  explicit sc_fixed_aug( tp val, sc_fxnum_observer* ob_= 0 ):                             \
    sc_fix_aug( a, W, I, Q, O, N, ob_ )                                                   \
  {}                                                                                      \
                                                                                          \
  sc_fixed_aug( tp val, const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_= 0 ):         \
    sc_fix( a, W, I, Q, O, N, fs_, ob_ )                                                  \
  {}                                                                    


             

    PK_DEFN_CTORS_T_A(int)
    PK_DEFN_CTORS_T_A(unsigned int)
    PK_DEFN_CTORS_T_A(long)
    PK_DEFN_CTORS_T_A(unsigned long)
    PK_DEFN_CTORS_T_A(double)
    PK_DEFN_CTORS_T_A(const char*)
    PK_DEFN_CTORS_T_A(const sc_fxval&)
    PK_DEFN_CTORS_T_A(const sc_fxval_fast&)
    PK_DEFN_CTORS_T_A(const sc_fxnum&)
    PK_DEFN_CTORS_T_A(const sc_fxnum_fast&)
#ifndef SC_FX_EXCLUDE_OTHER
    PK_DEFN_CTORS_T_B(int64)
    PK_DEFN_CTORS_T_B(uint64)
    PK_DEFN_CTORS_T_B(const sc_int_base&)
    PK_DEFN_CTORS_T_B(const sc_uint_base&)
    PK_DEFN_CTORS_T_B(const sc_signed&)
    PK_DEFN_CTORS_T_B(const sc_unsigned&)
#endif

#undef PK_DEFN_CTORS_T_A
#undef PK_DEFN_CTORS_T_B

 sc_fixed_aug( const sc_fixed<W,I,Q,O,N>& fxd ):
	  sc_fix_aug( static_cast< const sc_fix& >(fxd) )          
 { }

 sc_fixed_aug( const sc_fixed_aug<W,I,Q,O,N>& fxd ): 
   sc_fix_aug( static_cast< const sc_fix_aug& >(fxd) )
 { }



 // assignment operators
 
 sc_fixed_aug<W,I,Q,O,N>& operator = ( const sc_fixed<W,I,Q,O,N>& fxd )
 {                                                                                                     
  sc_fix_aug::operator = ( static_cast< const sc_fix& >(fxd) );                               
  return *this;                                            
 } 

 sc_fixed_aug<W,I,Q,O,N>& operator = ( const sc_fixed_aug<W,I,Q,O,N>& fxd )
 {
  sc_fix_aug::operator = ( static_cast< const sc_fix_aug& >(fxd) );                               
  return *this;                                                                                                   
 } 
 
 #define PK_DEFN_ASN_OP_T(op,tp)                                               \
  sc_fixed_aug<W,I,Q,O,N>& operator op ( tp val )                              \
  {                                                                            \
                                                                               \
   sc_fix_aug:: operator op( val );                                                  \
   return *this;                                                               \
  }                                                                            \

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DEFN_ASN_OP_OTHER(op)                                             \
    PK_DEFN_ASN_OP_T(op,int64)                                                \
    PK_DEFN_ASN_OP_T(op,uint64)                                               \
    PK_DEFN_ASN_OP_T(op,const sc_int_base&)                                   \
    PK_DEFN_ASN_OP_T(op,const sc_uint_base&)                                  \
    PK_DEFN_ASN_OP_T(op,const sc_signed&)                                     \
    PK_DEFN_ASN_OP_T(op,const sc_unsigned&)
 #else
 #define PK_DEFN_ASN_OP_OTHER(op)
 #endif

 #define PK_DEFN_ASN_OP(op)                                                      \
    PK_DEFN_ASN_OP_T(op,int)                                                     \
    PK_DEFN_ASN_OP_T(op,unsigned int)                                            \
    PK_DEFN_ASN_OP_T(op,long)                                                    \
    PK_DEFN_ASN_OP_T(op,unsigned long)                                           \
    PK_DEFN_ASN_OP_T(op,double)                                                  \
    PK_DEFN_ASN_OP_T(op,const char*)                                             \
    PK_DEFN_ASN_OP_T(op,const sc_fxval&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxval_fast&)                                    \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum_fast&)                                    \
    PK_DEFN_ASN_OP_OTHER(op)
    
    PK_DEFN_ASN_OP(=)

    PK_DEFN_ASN_OP(*=)
    PK_DEFN_ASN_OP(/=)
    PK_DEFN_ASN_OP(+=)
    PK_DEFN_ASN_OP(-=)

    PK_DEFN_ASN_OP_T(<<=,int)
    PK_DEFN_ASN_OP_T(>>=,int)

    PK_DEFN_ASN_OP_T(&=,const sc_fix&)
    PK_DEFN_ASN_OP_T(&=,const sc_fix_fast&)
    PK_DEFN_ASN_OP_T(|=,const sc_fix&)
    PK_DEFN_ASN_OP_T(|=,const sc_fix_fast&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix_fast&)

 #undef PK_DEFN_ASN_OP_T
 #undef PK_DEFN_ASN_OP_OTHER
 #undef PK_DEFN_ASN_OP
 
 const sc_fxval operator ++ ( int )                                         
  {                                                                                                                                          
   return sc_fix_aug:: operator ++( 0 );                                                                                                      
  }    

  const sc_fxval operator -- ( int )                                         
  {                                                                                                                                          
   return sc_fix_aug:: operator --( 0 );                                                                                                      
  }  

  sc_fixed_aug<W,I,Q,O,N>& operator ++ ()                                         
  {                                                                                                                                          
   sc_fix_aug:: operator ++();  
   return *this;
  }    

  sc_fixed_aug<W,I,Q,O,N>& operator -- ()                                         
  {                                                                                                                                          
   sc_fix_aug:: operator --();  
   return *this;
  } 

};


// ----------------------------------------------------------------------------
//  CLASS : sc_fixed_fast_aug
//
//  class for the internal augmented signals related to the SystemC type sc_fixed_fast_aug
// ----------------------------------------------------------------------------




template <int W, int I,
	  sc_q_mode Q = SC_DEFAULT_Q_MODE_,
	  sc_o_mode O = SC_DEFAULT_O_MODE_, int N = SC_DEFAULT_N_BITS_>
class sc_fixed_fast_aug : public sc_fix_fast_aug
{
 public:

 //constructors

 explicit sc_fixed_fast_aug( sc_fxnum_observer* ob_ = 0 ): 
    sc_fix_fast_aug( W, I, Q, O, N, ob_ )        
 {}

 explicit sc_fixed_fast_aug( const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_ = 0 ): 
           sc_fix_fast_aug( W, I, Q, O, N, fs_, ob_ )
 {}
    
#define PK_DEFN_CTORS_T_A(tp)                                                              \
 sc_fixed_fast_aug( tp val, sc_fxnum_observer* ob_= 0 ):                                   \
       sc_fix_fast_aug(val, W, I, Q, O, N, ob_ )                                           \
		  {}                                                                               \
 sc_fixed_fast_aug( tp val, const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_= 0 ):      \
     sc_fix_fast_aug(val, W, I, Q, O, N, fs_, ob_ )                                        \
		  {}

  #define PK_DEFN_CTORS_T_B(tp)                                                            \
  explicit sc_fixed_fast_aug( tp val, sc_fxnum_observer* ob_= 0 ):                         \
        sc_fix_fast_aug(val, W, I, Q, O, N, ob_ )                                          \
  {}                                                                                       \
                                                                                           \
  sc_fixed_fast_aug( tp val, const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_= 0 ):     \
    sc_fix_fast_aug(val, W, I, Q, O, N, fs_, ob_ )                                         \
  {}                                                                    


             

    PK_DEFN_CTORS_T_A(int)
    PK_DEFN_CTORS_T_A(unsigned int)
    PK_DEFN_CTORS_T_A(long)
    PK_DEFN_CTORS_T_A(unsigned long)
    PK_DEFN_CTORS_T_A(double)
    PK_DEFN_CTORS_T_A(const char*)
    PK_DEFN_CTORS_T_A(const sc_fxval&)
    PK_DEFN_CTORS_T_A(const sc_fxval_fast&)
    PK_DEFN_CTORS_T_A(const sc_fxnum&)
    PK_DEFN_CTORS_T_A(const sc_fxnum_fast&)
#ifndef SC_FX_EXCLUDE_OTHER
    PK_DEFN_CTORS_T_B(int64)
    PK_DEFN_CTORS_T_B(uint64)
    PK_DEFN_CTORS_T_B(const sc_int_base&)
    PK_DEFN_CTORS_T_B(const sc_uint_base&)
    PK_DEFN_CTORS_T_B(const sc_signed&)
    PK_DEFN_CTORS_T_B(const sc_unsigned&)
#endif

#undef PK_DEFN_CTORS_T_A
#undef PK_DEFN_CTORS_T_B

 sc_fixed_fast_aug( const sc_fixed_fast<W,I,Q,O,N>& fxd ):
	  sc_fix_fast_aug( static_cast< const sc_fix_fast& >(fxd) )         
 {}

 sc_fixed_fast_aug( const sc_fixed_fast_aug<W,I,Q,O,N>& fxd ): 
       sc_fix_fast_aug( static_cast< const sc_fix_fast_aug& >(fxd) )
 {}



 // assignment operators
 
 sc_fixed_fast_aug<W,I,Q,O,N>& operator = ( const sc_fixed_fast<W,I,Q,O,N>& fxd )
 {                                                                                                    
  sc_fix_fast_aug::operator =( static_cast< const sc_fix_fast& >(fxd) )                               
  return *this;                                            
 } 

 sc_fixed_fast_aug<W,I,Q,O,N>& operator = ( const sc_fixed_fast_aug<W,I,Q,O,N>& fxd )
 {
  sc_fix_fast_aug::operator =( static_cast< const sc_fix_fast_aug& >(fxd) )                               
  return *this;                                                                                                 
 } 

 #define PK_DEFN_ASN_OP_T(op,tp)                                               \
  sc_fixed_fast_aug<W,I,Q,O,N>& operator op ( tp val )                                    \
  {                                                                            \
                                                                               \
   sc_fix_fast_aug:: operator op ( val );                                             \
   return *this;                                                               \
  }                                                                            \

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DEFN_ASN_OP_OTHER(op)                                                \
    PK_DEFN_ASN_OP_T(op,int64)                                                   \
    PK_DEFN_ASN_OP_T(op,uint64)                                                  \
    PK_DEFN_ASN_OP_T(op,const sc_int_base&)                                      \
    PK_DEFN_ASN_OP_T(op,const sc_uint_base&)                                     \
    PK_DEFN_ASN_OP_T(op,const sc_signed&)                                        \
    PK_DEFN_ASN_OP_T(op,const sc_unsigned&)
 #else
 #define PK_DEFN_ASN_OP_OTHER(op)
 #endif

 #define PK_DEFN_ASN_OP(op)                                                      \
    PK_DEFN_ASN_OP_T(op,int)                                                     \
    PK_DEFN_ASN_OP_T(op,unsigned int)                                            \
    PK_DEFN_ASN_OP_T(op,long)                                                    \
    PK_DEFN_ASN_OP_T(op,unsigned long)                                           \
    PK_DEFN_ASN_OP_T(op,double)                                                  \
    PK_DEFN_ASN_OP_T(op,const char*)                                             \
    PK_DEFN_ASN_OP_T(op,const sc_fxval&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxval_fast&)                                    \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum_fast&)                                    \
    PK_DEFN_ASN_OP_OTHER(op)
    
    PK_DEFN_ASN_OP(=)

    PK_DEFN_ASN_OP(*=)
    PK_DEFN_ASN_OP(/=)
    PK_DEFN_ASN_OP(+=)
    PK_DEFN_ASN_OP(-=)

    PK_DEFN_ASN_OP_T(<<=,int)
    PK_DEFN_ASN_OP_T(>>=,int)

    PK_DEFN_ASN_OP_T(&=,const sc_fix&)
    PK_DEFN_ASN_OP_T(&=,const sc_fix_fast&)
    PK_DEFN_ASN_OP_T(|=,const sc_fix&)
    PK_DEFN_ASN_OP_T(|=,const sc_fix_fast&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix_fast&)

 #undef PK_DEFN_ASN_OP_T
 #undef PK_DEFN_ASN_OP_OTHER
 #undef PK_DEFN_ASN_OP

 const sc_fxval_fast operator ++ ( int )                                         
  {                                                                                                                                           
   return sc_fix_fast_aug:: operator ++( 0 );                                                                                                      
  }    

 const sc_fxval_fast operator -- ( int )                                         
  {                                                                            
   return sc_fix_fast_aug:: operator --( 0 );                                                                                                  
  }  

  sc_fixed_fast_aug<W,I,Q,O,N>& operator ++ ()                                         
  {                                                                                                                                          
   return sc_fix_fast_aug:: operator ++(); 
   return *this;
  }    

  sc_fixed_fast_aug<W,I,Q,O,N>& operator -- ()                                         
  {                                                                            
   return sc_fix_fast_aug:: operator --();
   return *this;
  } 

};



// ----------------------------------------------------------------------------
//  CLASS : sc_ufix_aug
//
//  class for the internal augmented signals related to the SystemC type sc_ufix_aug
// ----------------------------------------------------------------------------



class sc_ufix_aug: public sc_ufix, public pk_core::pk_internal_sgn< sc_ufix >
{

 public:

 // constructors
 
 explicit sc_ufix_aug( sc_fxnum_observer* ob= 0 ): sc_ufix(ob), pk_internal_sgn<sc_ufix>(this)
 { }

 sc_ufix_aug( int wl, int iwl, sc_fxnum_observer* ob=0 ): 
              sc_ufix(wl, iwl, ob), pk_internal_sgn<sc_ufix>(this) 
 { }

 sc_ufix_aug( sc_q_mode qm, sc_o_mode om, sc_fxnum_observer* ob=0 ): 
			  sc_ufix(qm, om, ob), pk_internal_sgn<sc_ufix>(this) 
 { }

 
 sc_ufix_aug( sc_q_mode qm, sc_o_mode om, int nb, sc_fxnum_observer* ob=0 ):
       sc_ufix(qm, om, nb, ob), pk_internal_sgn<sc_ufix>(this) 
 { }

 sc_ufix_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, sc_fxnum_observer* ob=0 ):
	   sc_ufix(wl, iwl, qm, om, ob), pk_internal_sgn<sc_ufix>(this)
 { }

 sc_ufix_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, int nb, sc_fxnum_observer* ob=0 ):
	   sc_ufix(wl, iwl, qm, om, nb, ob), pk_internal_sgn<sc_ufix>(this) 
 { }

 explicit sc_ufix_aug( const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ):
	   sc_ufix(cast_sw, ob), pk_internal_sgn<sc_ufix>(this) 
 { }

 sc_ufix_aug( int wl, int iwl, const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob=0 ):
	   sc_ufix(wl, iwl, cast_sw, ob), pk_internal_sgn<sc_ufix>(this)
 { }

 sc_ufix_aug( sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw ,
	         sc_fxnum_observer* ob=0 ):
       sc_ufix(qm, om, cast_sw, ob), pk_internal_sgn<sc_ufix>(this)
 { }
 
 sc_ufix_aug( sc_q_mode qm, sc_o_mode om, int nb, const sc_fxcast_switch& cast_sw,
	         sc_fxnum_observer* ob=0 ):
       sc_ufix(qm, om, nb, cast_sw, ob), pk_internal_sgn<sc_ufix>(this) 
 { }
 
 sc_ufix_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw, 
			 sc_fxnum_observer* ob=0 ):
       sc_ufix(wl, iwl, qm, om, cast_sw, ob), pk_internal_sgn<sc_ufix>(this)
 { }

 sc_ufix_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, int nb,
	         const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob=0 ):
       sc_ufix(wl, iwl, qm, om, nb, cast_sw, ob), pk_internal_sgn<sc_ufix>(this) 
 { }

 explicit sc_ufix_aug( const sc_fxtype_params& type_params, sc_fxnum_observer* ob=0 ):
       sc_ufix(type_params, ob), pk_internal_sgn<sc_ufix>(this) 
 { }

 sc_ufix_aug( const sc_fxtype_params& type_params, const sc_fxcast_switch& cast_sw,
	         sc_fxnum_observer* ob=0 ):
       sc_ufix(type_params, cast_sw, ob), pk_internal_sgn<sc_ufix>(this)
 { }


 #define PK_DEFN_CTORS_T(tp)                                                       \
  sc_ufix_aug( tp val, int wl_, int iwl_, sc_fxnum_observer* ob= 0 ):               \
         sc_ufix(val, wl_, iwl_, ob ), pk_internal_sgn<sc_ufix>(this)               \
              {  }                                                                  \
			                                                                        \
			                                                                       \
  sc_ufix_aug( tp val, sc_q_mode qm, sc_o_mode om, sc_fxnum_observer* ob= 0 ):      \
         sc_ufix(val, qm, om, ob ), pk_internal_sgn<sc_ufix>(this)                  \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_ufix_aug( tp val, sc_q_mode qm, sc_o_mode om, int nb,                          \
	                             sc_fxnum_observer* ob= 0 ):                       \
         sc_ufix(val, qm, om, nb, ob ), pk_internal_sgn<sc_ufix>(this)             \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_ufix_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om,               \
	                             sc_fxnum_observer* ob= 0 ):                       \
         sc_ufix(val, wl_, iwl_, qm, om, ob ), pk_internal_sgn<sc_ufix>(this)       \
              { }                                                                  \
			                                                                       \
                                                                                   \
			                                                                      \
  sc_ufix_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om, int nb,       \
	                             sc_fxnum_observer* ob= 0 ):                       \
         sc_ufix(val, wl_, iwl_, qm, om, nb, ob ), pk_internal_sgn<sc_ufix>(this)  \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_ufix_aug( tp val, const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ): \
         sc_ufix(val, cast_sw, ob ), pk_internal_sgn<sc_ufix>(this)                \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_ufix_aug( tp val, int wl_, int iwl_, const sc_fxcast_switch& cast_sw,          \
	                               sc_fxnum_observer* ob= 0 ):                     \
         sc_ufix(val, wl_, iwl_, cast_sw, ob ), pk_internal_sgn<sc_ufix>(this)     \
              { }                                                                  \
			                                                                       \
                                                                                   \
			                                                                      \
  sc_ufix_aug( tp val, sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw, \
	                             sc_fxnum_observer* ob= 0 ):                       \
         sc_ufix(val, qm, om, cast_sw, ob ), pk_internal_sgn<sc_ufix>(this)        \
              { }                                                                  \
			                                                                       \
                                                                                   \
			                                                                       \
  sc_ufix_aug( tp val, sc_q_mode qm, sc_o_mode om, int nb,                          \
	           const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ):        \
         sc_ufix(val, qm, om, nb, cast_sw, ob ), pk_internal_sgn<sc_ufix>(this)    \
              {  }                                                                 \
                                                                               	   \
                                                                                   \
			                                                                       \
         sc_ufix_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om,        \
                     const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ):  \
		    sc_ufix(val, wl_, iwl_, qm, om, cast_sw, ob ), pk_internal_sgn<sc_ufix>(this)       \
				{ }                                                               \
                                                                                  \
				                                                                  \
			                                                                      \
      sc_ufix_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om, int nb,   \
                     const sc_fxcast_switch& cast_sw, sc_fxnum_observer* ob= 0 ):  \
		    sc_ufix(val, wl_, iwl_, qm, om, nb, cast_sw, ob ), pk_internal_sgn<sc_ufix>(this) \
				{ }                                                                 \
                                                                                    \
				                                                                    \
			                                                                        \
  sc_ufix_aug( tp val, const sc_fxtype_params& fp, sc_fxnum_observer* ob= 0 ):      \
         sc_ufix(val, fp, ob ), pk_internal_sgn<sc_ufix>(this)                     \
			  { }                                                                   \
                                                                                   \
                                                                                   \
  sc_ufix_aug( tp val, const sc_fxtype_params& fp, const sc_fxcast_switch& cast_sw, \
                                                  sc_fxnum_observer* ob= 0 ):      \
	     sc_ufix(val, fp, cast_sw, ob ), pk_internal_sgn<sc_ufix>(this)            \
              { }                                                      
                         
                  
              
 
                      
  #define PK_DEFN_CTORS_T_A(tp)                                                     \
          sc_ufix_aug( tp val, sc_fxnum_observer* ob= 0 ):                           \
	        sc_ufix(val, ob ), pk_internal_sgn<sc_ufix>(this)                       \
			    { }                                                                 \
	  PK_DEFN_CTORS_T(tp)                                                          

  #define PK_DEFN_CTORS_T_B(tp)                                                    \
     explicit sc_ufix_aug( tp val, sc_fxnum_observer* ob= 0 ):                      \
		 sc_ufix(val, ob ), pk_internal_sgn<sc_ufix>(this)                         \
              { }                                                                  \
    PK_DEFN_CTORS_T(tp)                                                                  
    
   
    PK_DEFN_CTORS_T_A(int)
    PK_DEFN_CTORS_T_A(unsigned int)
    PK_DEFN_CTORS_T_A(long)
    PK_DEFN_CTORS_T_A(unsigned long)
    PK_DEFN_CTORS_T_A(double)
    PK_DEFN_CTORS_T_A(const char*)
    PK_DEFN_CTORS_T_A(const sc_fxval&)
    PK_DEFN_CTORS_T_A(const sc_fxval_fast&)
    PK_DEFN_CTORS_T_A(const sc_fxnum&)
    PK_DEFN_CTORS_T_A(const sc_fxnum_fast&)
 #ifndef SC_FX_EXCLUDE_OTHER
    PK_DEFN_CTORS_T_B(int64)
    PK_DEFN_CTORS_T_B(uint64)
    PK_DEFN_CTORS_T_B(const sc_int_base&)
    PK_DEFN_CTORS_T_B(const sc_uint_base&)
    PK_DEFN_CTORS_T_B(const sc_signed&)
    PK_DEFN_CTORS_T_B(const sc_unsigned&)
 #endif

 #undef PK_DEFN_CTORS_T
 #undef PK_DEFN_CTORS_T_A
 #undef PK_DEFN_CTORS_T_B

 sc_ufix_aug( const sc_ufix& fx ):
	  sc_ufix( fx ), pk_internal_sgn<sc_ufix>(this)          
 { }

 sc_ufix_aug( const sc_ufix_aug& fx ): 
       sc_ufix( static_cast<const sc_ufix& >(fx) ), pk_internal_sgn<sc_ufix>(this)
 { }


 // assignment operators

 sc_ufix_aug& operator=( const sc_ufix& fx )
 {
  compute_data();
  sc_ufix::operator =(fx);
  return *this;
 }

 sc_ufix_aug& operator=( const sc_ufix_aug& fx )
 {
  return this->operator =( static_cast< const sc_ufix& >(fx));
 }

 #define PK_DEFN_ASN_OP_T(op,tp)                                              \
    sc_ufix_aug& operator op ( tp val )                                        \
    {                                                                         \
     compute_data();                                                            \
     sc_ufix::operator op (val);                                               \
     return *this;                                                            \
    }

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DEFN_ASN_OP_OTHER(op)                                             \
    PK_DEFN_ASN_OP_T(op,int64)                                                \
    PK_DEFN_ASN_OP_T(op,uint64)                                               \
    PK_DEFN_ASN_OP_T(op,const sc_int_base&)                                   \
    PK_DEFN_ASN_OP_T(op,const sc_uint_base&)                                  \
    PK_DEFN_ASN_OP_T(op,const sc_signed&)                                     \
    PK_DEFN_ASN_OP_T(op,const sc_unsigned&)                                    
#else
#define PK_DEFN_ASN_OP_OTHER(op)
#endif

#define PK_DEFN_ASN_OP(op)                                                       \
    PK_DEFN_ASN_OP_T(op,int)                                                     \
    PK_DEFN_ASN_OP_T(op,unsigned int)                                            \
    PK_DEFN_ASN_OP_T(op,long)                                                    \
    PK_DEFN_ASN_OP_T(op,unsigned long)                                           \
    PK_DEFN_ASN_OP_T(op,double)                                                  \
    PK_DEFN_ASN_OP_T(op,const char*)                                             \
    PK_DEFN_ASN_OP_T(op,const sc_fxval&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxval_fast&)                                    \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum_fast&)                                    \
    PK_DEFN_ASN_OP_OTHER(op)                   

    PK_DEFN_ASN_OP(=)

    PK_DEFN_ASN_OP(*=)
    PK_DEFN_ASN_OP(/=)
    PK_DEFN_ASN_OP(+=)
    PK_DEFN_ASN_OP(-=)

    PK_DEFN_ASN_OP_T(<<=,int)
    PK_DEFN_ASN_OP_T(>>=,int)

    PK_DEFN_ASN_OP_T(&=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(&=,const sc_ufix_fast&)
    PK_DEFN_ASN_OP_T(|=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(|=,const sc_ufix_fast&)
    PK_DEFN_ASN_OP_T(^=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(^=,const sc_ufix_fast&)

  #undef PK_DEFN_ASN_OP_T
  #undef PK_DEFN_ASN_OP_OTHER
  #undef PK_DEFN_ASN_OP

// other writing operators and methods

 const sc_fxval operator ++ ( int )
 {
  compute_data();
  return sc_ufix:: operator ++ ( 0 ); 
 }

 const sc_fxval operator -- ( int )
 {
  compute_data();
  return sc_ufix:: operator -- ( 0 ); 
 }

 sc_ufix_aug& operator ++ ()
 {
  compute_data();
  sc_ufix::operator ++( );
  return *this;
 }

 sc_ufix_aug& operator -- ()
 {
  compute_data();
  sc_ufix::operator --( );
  return *this;
 }
 
 sc_fxnum_bitref operator [] (int i)
 {
  compute_data();
  return sc_ufix::operator[] (i);
 }

 sc_fxnum_bitref bit (int i)
 {
  compute_data();
  return sc_ufix::bit (i);
 }

 sc_fxnum_subref operator() (int i, int j)
 {
  compute_data();
  return sc_ufix::operator () (i,j);
 }

 sc_fxnum_subref range (int i, int j)
 {
  compute_data();
  return sc_ufix::range (i,j);
 }

 sc_fxnum_subref operator() ()
 {
  compute_data();
  return sc_ufix::operator () ();
 }

 sc_fxnum_subref range ( )
 {
  compute_data();
  return sc_ufix::range ( );
 }


 void scan (istream & is=cin)
 {
  compute_data();
  sc_ufix::scan( is );
 }

 // writing friend functions (declarations)

 friend void b_not( sc_ufix_aug&, const sc_ufix& );
 friend void b_and( sc_ufix_aug&, const sc_ufix&, const sc_ufix& );
 friend void b_and( sc_ufix_aug&, const sc_ufix&, const sc_ufix_fast& );
 friend void b_and( sc_ufix_aug&, const sc_ufix_fast&, const sc_ufix& );
 friend void b_or ( sc_ufix_aug&, const sc_ufix&, const sc_ufix& );
 friend void b_or ( sc_ufix_aug&, const sc_ufix&, const sc_ufix_fast& );
 friend void b_or ( sc_ufix_aug&, const sc_ufix_fast&, const sc_ufix& );
 friend void b_xor( sc_ufix_aug&, const sc_ufix&, const sc_ufix& );
 friend void b_xor( sc_ufix_aug&, const sc_ufix&, const sc_ufix_fast& );
 friend void b_xor( sc_ufix_aug&, const sc_ufix_fast&, const sc_ufix& );


 friend void neg( sc_ufix_aug&, const sc_fxnum& );
 friend void lshift( sc_ufix_aug&, const sc_fxnum&, int );
 friend void rshift( sc_ufix_aug&, const sc_fxnum&, int );

 #define PK_DECL_BIN_FNC_T(fnc,tp)                                             \
    friend void fnc ( sc_ufix_aug&, const sc_fxnum&, tp );                     \
    friend void fnc ( sc_ufix_aug&, tp, const sc_fxnum& );

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DECL_BIN_FNC_OTHER(fnc)                                              \
    PK_DECL_BIN_FNC_T(fnc,int64)                                                 \
    PK_DECL_BIN_FNC_T(fnc,uint64)                                                \
    PK_DECL_BIN_FNC_T(fnc,const sc_int_base&)                                    \
    PK_DECL_BIN_FNC_T(fnc,const sc_uint_base&)                                   \
    PK_DECL_BIN_FNC_T(fnc,const sc_signed&)                                      \
    PK_DECL_BIN_FNC_T(fnc,const sc_unsigned&)
 #else
 #define PK_DECL_BIN_FNC_OTHER(fnc)
 #endif

 #define PK_DECL_BIN_FNC(fnc)                                                    \
    friend void fnc ( sc_ufix_aug&, const sc_fxnum&, const sc_fxnum& );          \
    PK_DECL_BIN_FNC_T(fnc,int)                                                   \
    PK_DECL_BIN_FNC_T(fnc,unsigned int)                                          \
    PK_DECL_BIN_FNC_T(fnc,long)                                                  \
    PK_DECL_BIN_FNC_T(fnc,unsigned long)                                         \
    PK_DECL_BIN_FNC_T(fnc,double)                                                \
    PK_DECL_BIN_FNC_T(fnc,const char*)                                           \
    PK_DECL_BIN_FNC_T(fnc,const sc_fxval&)                                       \
    PK_DECL_BIN_FNC_T(fnc,const sc_fxval_fast&)                                  \
    PK_DECL_BIN_FNC_T(fnc,const sc_fxnum_fast&)                                  \
    PK_DECL_BIN_FNC_OTHER(fnc)

    PK_DECL_BIN_FNC(mult)
    PK_DECL_BIN_FNC(div)
    PK_DECL_BIN_FNC(add)
    PK_DECL_BIN_FNC(sub)

 #undef PK_DECL_BIN_FNC_T
 #undef PK_DECL_BIN_FNC_OTHER
 #undef PK_DECL_BIN_FNC

};


// writing friend functions (definitions)

inline
void
b_not( sc_ufix_aug& c, const sc_ufix& a )
{
 c.compute_data();
 sc_dt:: b_not(static_cast<sc_ufix&>(c), a) ;
};

#define PK_DEFN_BIN_FNC_1(fnc,tp1,tp2)                                                          \
inline void fnc ( sc_ufix_aug& c, const tp1& a, const tp2& b )                                   \
{c.compute_data();                                                                                \
 sc_dt:: fnc(static_cast<sc_ufix&>(c), a, b );                                                  \
};


PK_DEFN_BIN_FNC_1(b_and,sc_ufix,sc_ufix)
PK_DEFN_BIN_FNC_1(b_and,sc_ufix,sc_ufix_fast)
PK_DEFN_BIN_FNC_1(b_and,sc_ufix_fast,sc_ufix)

PK_DEFN_BIN_FNC_1(b_or,sc_ufix,sc_ufix)
PK_DEFN_BIN_FNC_1(b_or,sc_ufix,sc_ufix_fast)
PK_DEFN_BIN_FNC_1(b_or,sc_ufix_fast,sc_ufix)

PK_DEFN_BIN_FNC_1(b_xor,sc_ufix,sc_ufix)
PK_DEFN_BIN_FNC_1(b_xor,sc_ufix,sc_ufix_fast)
PK_DEFN_BIN_FNC_1(b_xor,sc_ufix_fast,sc_ufix)


#define PK_DEFN_BIN_FNC_2(fnc,tp)                                             \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_aug& c, const sc_fxnum& a, tp b )                                \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                    \
}                                                                             \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_aug& c, tp a, const sc_fxnum& b )                                \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                            \
}                                                                               

#ifndef SC_FX_EXCLUDE_OTHER
#define PK_DEFN_BIN_FNC_OTHER(fnc)                                               \
PK_DEFN_BIN_FNC_2(fnc,int64)                                                     \
PK_DEFN_BIN_FNC_2(fnc,uint64)                                                    \
PK_DEFN_BIN_FNC_2(fnc,const sc_int_base&)                                        \
PK_DEFN_BIN_FNC_2(fnc,const sc_uint_base&)                                       \
PK_DEFN_BIN_FNC_2(fnc,const sc_signed&)                                          \
PK_DEFN_BIN_FNC_2(fnc,const sc_unsigned&)
#else
#define PK_DEFN_BIN_FNC_OTHER(fnc)
#endif

#define PK_DEFN_BIN_FNC(fnc)                                                  \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_aug& c, const sc_fxnum& a, const sc_fxnum& b )                   \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                    \
}                                                                             \
	                                                                          \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_aug& c, const sc_fxnum& a, const sc_fxval& b )                   \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                    \
}                                                                             \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_aug& c, const sc_fxval& a, const sc_fxnum& b )                   \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum&>( c ), a , b );                    \
}                                                                             \
                                                                              \
PK_DEFN_BIN_FNC_2(fnc,int)                                                    \
PK_DEFN_BIN_FNC_2(fnc,unsigned int)                                           \
PK_DEFN_BIN_FNC_2(fnc,long)                                                   \
PK_DEFN_BIN_FNC_2(fnc,unsigned long)                                          \
PK_DEFN_BIN_FNC_2(fnc,double)                                                 \
PK_DEFN_BIN_FNC_2(fnc,const char*)                                            \
PK_DEFN_BIN_FNC_2(fnc,const sc_fxval_fast&)                                   \
PK_DEFN_BIN_FNC_2(fnc,const sc_fxnum_fast&)                                   \
PK_DEFN_BIN_FNC_OTHER(fnc)

PK_DEFN_BIN_FNC(mult)
PK_DEFN_BIN_FNC(div)
PK_DEFN_BIN_FNC(add)
PK_DEFN_BIN_FNC(sub)

#undef PK_DEFN_BIN_FNC_1
#undef PK_DEFN_BIN_FNC_2
#undef PK_DEFN_BIN_FNC_OTHER
#undef PK_DEFN_BIN_FNC


// ----------------------------------------------------------------------------
//  CLASS : sc_ufix_fast_aug
//
//  class for the internal augmented signals related to the SystemC type sc_ufix_fast
// ----------------------------------------------------------------------------



class sc_ufix_fast_aug: public sc_ufix_fast, 
	                    public pk_core::pk_internal_sgn< sc_ufix_fast >
{


 public:

 // constructors

 explicit sc_ufix_fast_aug( sc_fxnum_fast_observer* ob= 0 ): 
             sc_ufix_fast(ob), pk_internal_sgn<sc_ufix_fast>(this)
 { }

 sc_ufix_fast_aug( int wl, int iwl, sc_fxnum_fast_observer* ob=0 ): 
              sc_ufix_fast(wl, iwl, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }

 sc_ufix_fast_aug( sc_q_mode qm, sc_o_mode om, sc_fxnum_fast_observer* ob=0 ): 
			  sc_ufix_fast(qm, om, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }

 
 sc_ufix_fast_aug( sc_q_mode qm, sc_o_mode om, int nb, sc_fxnum_fast_observer* ob=0 ):
       sc_ufix_fast(qm, om, nb, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }

 sc_ufix_fast_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, sc_fxnum_fast_observer* ob=0 ):
	   sc_ufix_fast(wl, iwl, qm, om, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }

 sc_ufix_fast_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, int nb, sc_fxnum_fast_observer* ob=0 ):
	   sc_ufix_fast(wl, iwl, qm, om, nb, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }

 explicit sc_ufix_fast_aug( const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ):
	   sc_ufix_fast(cast_sw, ob), pk_internal_sgn<sc_ufix_fast>(this)
 { }

 sc_ufix_fast_aug( int wl, int iwl, const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob=0 ):
	   sc_ufix_fast(wl, iwl, cast_sw, ob), pk_internal_sgn<sc_ufix_fast>(this)
 { }

 sc_ufix_fast_aug( sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw ,
	         sc_fxnum_fast_observer* ob=0 ):
       sc_ufix_fast(qm, om, cast_sw, ob), pk_internal_sgn<sc_ufix_fast>(this)
 { }
 
 sc_ufix_fast_aug( sc_q_mode qm, sc_o_mode om, int nb, const sc_fxcast_switch& cast_sw,
	         sc_fxnum_fast_observer* ob=0 ):
       sc_ufix_fast(qm, om, nb, cast_sw, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }
 
 sc_ufix_fast_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw, 
			 sc_fxnum_fast_observer* ob=0 ):
       sc_ufix_fast(wl, iwl, qm, om, cast_sw, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }

 sc_ufix_fast_aug( int wl, int iwl, sc_q_mode qm, sc_o_mode om, int nb,
	         const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob=0 ):
       sc_ufix_fast(wl, iwl, qm, om, nb, cast_sw, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }

 explicit sc_ufix_fast_aug( const sc_fxtype_params& type_params, sc_fxnum_fast_observer* ob=0 ):
       sc_ufix_fast(type_params, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }

 sc_ufix_fast_aug( const sc_fxtype_params& type_params, const sc_fxcast_switch& cast_sw,
	         sc_fxnum_fast_observer* ob=0 ):
       sc_ufix_fast(type_params, cast_sw, ob), pk_internal_sgn<sc_ufix_fast>(this) 
 { }


 #define PK_DEFN_CTORS_T(tp)                                                       \
  sc_ufix_fast_aug( tp val, int wl_, int iwl_, sc_fxnum_fast_observer* ob= 0 ):     \
         sc_ufix_fast(val, wl_, iwl_, ob ), pk_internal_sgn<sc_ufix_fast>(this)     \
              { }                                                                    \
			                                                                        \
			                                                                        \
  sc_ufix_fast_aug( tp val, sc_q_mode qm, sc_o_mode om, sc_fxnum_fast_observer* ob= 0 ): \
         sc_ufix_fast(val, qm, om, ob ), pk_internal_sgn<sc_ufix_fast>(this)         \
              { }                                                                    \
			                                                                        \
			                                                                        \
  sc_ufix_fast_aug( tp val, sc_q_mode qm, sc_o_mode om, int nb,                     \
	                             sc_fxnum_fast_observer* ob= 0 ):                       \
         sc_ufix_fast(val, qm, om, nb, ob ), pk_internal_sgn<sc_ufix_fast>(this)        \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_ufix_fast_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om,               \
	                             sc_fxnum_fast_observer* ob= 0 ):                       \
         sc_ufix_fast(val, wl_, iwl_, qm, om, ob ), pk_internal_sgn<sc_ufix_fast>(this)   \
              { }                                                                          \
			                                                                       \
                                                                                   \
			                                                                       \
  sc_ufix_fast_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om, int nb,       \
	                             sc_fxnum_fast_observer* ob= 0 ):                       \
         sc_ufix_fast(val, wl_, iwl_, qm, om, nb, ob ), pk_internal_sgn<sc_ufix_fast>(this)           \
              { }                                                                         \
			                                                                       \
			                                                                       \
  sc_ufix_fast_aug( tp val, const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ): \
         sc_ufix_fast(val, cast_sw, ob ), pk_internal_sgn<sc_ufix_fast>(this)      \
              { }                                                                  \
			                                                                       \
			                                                                       \
  sc_ufix_fast_aug( tp val, int wl_, int iwl_, const sc_fxcast_switch& cast_sw,          \
	                               sc_fxnum_fast_observer* ob= 0 ):                      \
         sc_ufix_fast(val, wl_, iwl_, cast_sw, ob ), pk_internal_sgn<sc_ufix_fast>(this) \
              {  }                                                                \
			                                                                      \
                                                                                   \
			                                                                      \
  sc_ufix_fast_aug( tp val, sc_q_mode qm, sc_o_mode om, const sc_fxcast_switch& cast_sw, \
	                             sc_fxnum_fast_observer* ob= 0 ):                       \
         sc_ufix_fast(val, qm, om, cast_sw, ob ), pk_internal_sgn<sc_ufix_fast>(this)   \
              { }                                                                 \
			                                                                       \
                                                                                   \
			                                                                       \
  sc_ufix_fast_aug( tp val, sc_q_mode qm, sc_o_mode om, int nb,                     \
	           const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ):     \
         sc_ufix_fast(val, qm, om, nb, cast_sw, ob ), pk_internal_sgn<sc_ufix_fast>(this)  \
              {  }                                                                   \
                                                                                 	\
                                                                                    \
			                                                                       \
         sc_ufix_fast_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om,        \
                     const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ):  \
		    sc_ufix_fast(val, wl_, iwl_, qm, om, cast_sw, ob ), pk_internal_sgn<sc_ufix_fast>(this)   \
				{ }                                                                   \
                                                                                   \
				                                                                   \
			                                                                      \
      sc_ufix_fast_aug( tp val, int wl_, int iwl_, sc_q_mode qm, sc_o_mode om, int nb,   \
                     const sc_fxcast_switch& cast_sw, sc_fxnum_fast_observer* ob= 0 ):  \
		    sc_ufix_fast(val, wl_, iwl_, qm, om, nb, cast_sw, ob ), pk_internal_sgn<sc_ufix_fast>(this)   \
				{ }                                                                 \
                                                                                    \
				                                                                    \
			                                                                       \
  sc_ufix_fast_aug( tp val, const sc_fxtype_params& fp, sc_fxnum_fast_observer* ob= 0 ):      \
         sc_ufix_fast(val, fp, ob ), pk_internal_sgn<sc_ufix_fast>(this)           \
			  { }                                                                   \
                                                                                  \
                                                                                  \
  sc_ufix_fast_aug( tp val, const sc_fxtype_params& fp, const sc_fxcast_switch& cast_sw, \
                                                  sc_fxnum_fast_observer* ob= 0 ):      \
	     sc_ufix_fast(val, fp, cast_sw, ob ), pk_internal_sgn<sc_ufix_fast>(this)     \
              { }                                                                    
                
              
 
                      
  #define PK_DEFN_CTORS_T_A(tp)                                                     \
          sc_ufix_fast_aug( tp val, sc_fxnum_fast_observer* ob= 0 ):               \
	        sc_ufix_fast(val, ob ), pk_internal_sgn<sc_ufix_fast>(this)             \
			    { }                                                                 \
	  PK_DEFN_CTORS_T(tp)                                                          

  #define PK_DEFN_CTORS_T_B(tp)                                                    \
     explicit sc_ufix_fast_aug( tp val, sc_fxnum_fast_observer* ob= 0 ):           \
		 sc_ufix_fast(val, ob ), pk_internal_sgn<sc_ufix_fast>(this)               \
              { }                                                                  \
    PK_DEFN_CTORS_T(tp)                                                                  
    
   
    PK_DEFN_CTORS_T_A(int)
    PK_DEFN_CTORS_T_A(unsigned int)
    PK_DEFN_CTORS_T_A(long)
    PK_DEFN_CTORS_T_A(unsigned long)
    PK_DEFN_CTORS_T_A(double)
    PK_DEFN_CTORS_T_A(const char*)
    PK_DEFN_CTORS_T_A(const sc_fxval&)
    PK_DEFN_CTORS_T_A(const sc_fxval_fast&)
    PK_DEFN_CTORS_T_A(const sc_fxnum&)
    PK_DEFN_CTORS_T_A(const sc_fxnum_fast&)
 #ifndef SC_FX_EXCLUDE_OTHER
    PK_DEFN_CTORS_T_B(int64)
    PK_DEFN_CTORS_T_B(uint64)
    PK_DEFN_CTORS_T_B(const sc_int_base&)
    PK_DEFN_CTORS_T_B(const sc_uint_base&)
    PK_DEFN_CTORS_T_B(const sc_signed&)
    PK_DEFN_CTORS_T_B(const sc_unsigned&)
 #endif

 #undef PK_DEFN_CTORS_T
 #undef PK_DEFN_CTORS_T_A
 #undef PK_DEFN_CTORS_T_B

 sc_ufix_fast_aug( const sc_ufix_fast& fx ):
	  sc_ufix_fast( fx ), pk_internal_sgn<sc_ufix_fast>(this)          
 { }

 sc_ufix_fast_aug( const sc_ufix_fast_aug& fx ): 
        sc_ufix_fast( static_cast<const sc_ufix_fast& >(fx) ), pk_internal_sgn<sc_ufix_fast>(this)
 { }
 
                                                                    
 // assignment operators

 sc_ufix_fast_aug& operator=( const sc_ufix_fast& fx )
 {
  compute_data();
  sc_ufix_fast::operator =(fx);
  return *this;
 }

 sc_ufix_fast_aug& operator=( const sc_ufix_fast_aug& fx )
 {
  return this->operator =( static_cast< const sc_ufix_fast& >(fx));
 }

 #define PK_DEFN_ASN_OP_T(op,tp)                                              \
    sc_ufix_fast_aug& operator op ( tp val )                                   \
    {                                                                         \
     compute_data();                                                            \
     sc_ufix_fast::operator op (val);                                          \
     return *this;                                                            \
    }

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DEFN_ASN_OP_OTHER(op)                                             \
    PK_DEFN_ASN_OP_T(op,int64)                                                \
    PK_DEFN_ASN_OP_T(op,uint64)                                               \
    PK_DEFN_ASN_OP_T(op,const sc_int_base&)                                   \
    PK_DEFN_ASN_OP_T(op,const sc_uint_base&)                                  \
    PK_DEFN_ASN_OP_T(op,const sc_signed&)                                     \
    PK_DEFN_ASN_OP_T(op,const sc_unsigned&)                                    
#else
#define PK_DEFN_ASN_OP_OTHER(op)
#endif

#define PK_DEFN_ASN_OP(op)                                                       \
    PK_DEFN_ASN_OP_T(op,int)                                                     \
    PK_DEFN_ASN_OP_T(op,unsigned int)                                            \
    PK_DEFN_ASN_OP_T(op,long)                                                    \
    PK_DEFN_ASN_OP_T(op,unsigned long)                                           \
    PK_DEFN_ASN_OP_T(op,double)                                                  \
    PK_DEFN_ASN_OP_T(op,const char*)                                             \
    PK_DEFN_ASN_OP_T(op,const sc_fxval&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxval_fast&)                                    \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum_fast&)                                    \
    PK_DEFN_ASN_OP_OTHER(op)                   

    PK_DEFN_ASN_OP(=)

    PK_DEFN_ASN_OP(*=)
    PK_DEFN_ASN_OP(/=)
    PK_DEFN_ASN_OP(+=)
    PK_DEFN_ASN_OP(-=)

    PK_DEFN_ASN_OP_T(<<=,int)
    PK_DEFN_ASN_OP_T(>>=,int)

    PK_DEFN_ASN_OP_T(&=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(&=,const sc_ufix_fast&)
    PK_DEFN_ASN_OP_T(|=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(|=,const sc_ufix_fast&)
    PK_DEFN_ASN_OP_T(^=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(^=,const sc_ufix_fast&)

  #undef PK_DEFN_ASN_OP_T
  #undef PK_DEFN_ASN_OP_OTHER
  #undef PK_DEFN_ASN_OP

// other writing operators and methods

 const sc_fxval_fast operator ++ ( int )
 {
  compute_data();
  return sc_ufix_fast:: operator ++ ( 0 ); 
 }

 const sc_fxval_fast operator -- ( int )
 {
  compute_data();
  return sc_ufix_fast:: operator -- ( 0 ); 
 }

 sc_ufix_fast_aug& operator ++ ()
 {
  compute_data();
  sc_ufix_fast::operator ++( );
  return *this;
 }

 sc_ufix_fast_aug& operator -- ()
 {
  compute_data();
  sc_ufix_fast::operator --( );
  return *this;
 }
 
 sc_fxnum_fast_bitref operator [] (int i)
 {
  compute_data();
  return sc_ufix_fast::operator[] (i);
 }

 sc_fxnum_fast_bitref bit (int i)
 {
  compute_data();
  return sc_ufix_fast::bit (i);
 }

 sc_fxnum_fast_subref operator() (int i, int j)
 {
  compute_data();
  return sc_ufix_fast::operator () (i,j);
 }

 sc_fxnum_fast_subref range (int i, int j)
 {
  compute_data();
  return sc_ufix_fast::range (i,j);
 }

 sc_fxnum_fast_subref operator() ()
 {
  compute_data();
  return sc_ufix_fast::operator () ();
 }

 sc_fxnum_fast_subref range ( )
 {
  compute_data();
  return sc_ufix_fast::range ( );
 }


 void scan (istream & is=cin)
 {
  compute_data();
  sc_ufix_fast::scan( is );
 }

 // writing friend functions (declarations)

 friend void b_not( sc_ufix_fast_aug&, const sc_ufix_fast& );
 friend void b_and( sc_ufix_fast_aug&, const sc_ufix_fast&, const sc_ufix_fast& );
 friend void b_or ( sc_ufix_fast_aug&, const sc_ufix_fast&, const sc_ufix_fast& );
 friend void b_xor( sc_ufix_fast_aug&, const sc_ufix_fast&, const sc_ufix_fast& );

 
 
 friend void neg( sc_ufix_fast_aug&, const sc_fxnum& );
 friend void lshift( sc_ufix_fast_aug&, const sc_fxnum_fast&, int );
 friend void rshift( sc_ufix_fast_aug&, const sc_fxnum_fast&, int );

 #define DECL_BIN_FNC_T(fnc,tp)                                               \
    friend void fnc ( sc_ufix_fast_aug&, const sc_fxnum_fast&, tp );           \
    friend void fnc ( sc_ufix_fast_aug&, tp, const sc_fxnum_fast& );

 #ifndef SC_FX_EXCLUDE_OTHER
 #define DECL_BIN_FNC_OTHER(fnc)                                              \
    DECL_BIN_FNC_T(fnc,int64)                                                 \
    DECL_BIN_FNC_T(fnc,uint64)                                                \
    DECL_BIN_FNC_T(fnc,const sc_int_base&)                                    \
    DECL_BIN_FNC_T(fnc,const sc_uint_base&)                                   \
    DECL_BIN_FNC_T(fnc,const sc_signed&)                                      \
    DECL_BIN_FNC_T(fnc,const sc_unsigned&)
 #else
 #define DECL_BIN_FNC_OTHER(fnc)
 #endif

 #define DECL_BIN_FNC(fnc)                                                    \
    friend void fnc ( sc_ufix_fast_aug&, const sc_fxnum_fast&, const sc_fxnum_fast& );        \
    DECL_BIN_FNC_T(fnc,int)                                                   \
    DECL_BIN_FNC_T(fnc,unsigned int)                                          \
    DECL_BIN_FNC_T(fnc,long)                                                  \
    DECL_BIN_FNC_T(fnc,unsigned long)                                         \
    DECL_BIN_FNC_T(fnc,double)                                                \
    DECL_BIN_FNC_T(fnc,const char*)                                           \
    DECL_BIN_FNC_T(fnc,const sc_fxval&)                                       \
    DECL_BIN_FNC_T(fnc,const sc_fxval_fast&)                                  \
    DECL_BIN_FNC_T(fnc,const sc_fxnum&)                                       \
    DECL_BIN_FNC_OTHER(fnc)

    DECL_BIN_FNC(mult)
    DECL_BIN_FNC(div)
    DECL_BIN_FNC(add)
    DECL_BIN_FNC(sub)

 #undef DECL_BIN_FNC_T
 #undef DECL_BIN_FNC_OTHER
 #undef DECL_BIN_FNC

};

// writing friend functions (definitions)

inline
void
b_not( sc_ufix_fast_aug& c, const sc_ufix_fast& a )
{
 c.compute_data();
 sc_dt:: b_not(static_cast<sc_ufix_fast&>(c), a) ;
};

#define PK_DEFN_BIN_FNC_1(fnc,tp1,tp2)                                                               \
inline void fnc ( sc_ufix_fast_aug& c, const tp1& a, const tp2& b )                                   \
{c.compute_data();                                                                                     \
 sc_dt:: fnc(static_cast<sc_ufix_fast&>(c), a, b );                                            \
};


PK_DEFN_BIN_FNC_1(b_and,sc_ufix_fast,sc_ufix_fast)
PK_DEFN_BIN_FNC_1(b_or,sc_ufix_fast,sc_ufix_fast)
PK_DEFN_BIN_FNC_1(b_xor,sc_ufix_fast,sc_ufix_fast)

#define PK_DEFN_BIN_FNC_2(fnc,tp)                                             \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_fast_aug& c, const sc_fxnum_fast& a, tp b )                      \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );               \
}                                                                             \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_fast_aug& c, tp a, const sc_fxnum_fast& b )                      \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );               \
}                                                                               

#ifndef SC_FX_EXCLUDE_OTHER
#define PK_DEFN_BIN_FNC_OTHER(fnc)                                               \
PK_DEFN_BIN_FNC_2(fnc,int64)                                                     \
PK_DEFN_BIN_FNC_2(fnc,uint64)                                                    \
PK_DEFN_BIN_FNC_2(fnc,const sc_int_base&)                                        \
PK_DEFN_BIN_FNC_2(fnc,const sc_uint_base&)                                       \
PK_DEFN_BIN_FNC_2(fnc,const sc_signed&)                                          \
PK_DEFN_BIN_FNC_2(fnc,const sc_unsigned&)
#else
#define PK_DEFN_BIN_FNC_OTHER(fnc)
#endif

#define PK_DEFN_BIN_FNC(fnc)                                                  \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_fast_aug& c, const sc_fxnum_fast& a, const sc_fxnum_fast& b )                   \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );               \
}                                                                             \
	                                                                          \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_fast_aug& c, const sc_fxnum_fast& a, const sc_fxval_fast& b )    \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );               \
}                                                                             \
                                                                              \
inline                                                                        \
void                                                                          \
fnc ( sc_ufix_fast_aug& c, const sc_fxval_fast& a, const sc_fxnum_fast& b )    \
{                                                                             \
 c.compute_data();                                                              \
 sc_dt:: fnc (static_cast<sc_fxnum_fast&>( c ), a , b );               \
}                                                                             \
                                                                              \
PK_DEFN_BIN_FNC_2(fnc,int)                                                    \
PK_DEFN_BIN_FNC_2(fnc,unsigned int)                                           \
PK_DEFN_BIN_FNC_2(fnc,long)                                                   \
PK_DEFN_BIN_FNC_2(fnc,unsigned long)                                          \
PK_DEFN_BIN_FNC_2(fnc,double)                                                 \
PK_DEFN_BIN_FNC_2(fnc,const char*)                                            \
PK_DEFN_BIN_FNC_2(fnc,const sc_fxval&)                                        \
PK_DEFN_BIN_FNC_2(fnc,const sc_fxnum&)                                        \
PK_DEFN_BIN_FNC_OTHER(fnc)

PK_DEFN_BIN_FNC(mult)
PK_DEFN_BIN_FNC(div)
PK_DEFN_BIN_FNC(add)
PK_DEFN_BIN_FNC(sub)

#undef PK_DEFN_BIN_FNC_1
#undef PK_DEFN_BIN_FNC_2
#undef PK_DEFN_BIN_FNC_OTHER
#undef PK_DEFN_BIN_FNC




// ----------------------------------------------------------------------------
//  CLASS : sc_ufixed_aug
//
//  class for the internal augmented signals related to the SystemC type sc_ufixed
// ----------------------------------------------------------------------------


template <int W, int I,
	  sc_q_mode Q = SC_DEFAULT_Q_MODE_,
	  sc_o_mode O = SC_DEFAULT_O_MODE_, int N = SC_DEFAULT_N_BITS_>
class sc_ufixed_aug : public sc_ufix_aug 
{
 public:

 // constructors

 explicit sc_ufixed_aug( sc_fxnum_observer* ob_ = 0 ): 
          sc_ufix_aug( W, I, Q, O, N, ob_ )
 {}

 explicit sc_ufixed_aug( const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_ = 0 ): 
          sc_ufix_aug( W, I, Q, O, N, fs_, ob_ )
 {}

 
    
#define PK_DEFN_CTORS_T_A(tp)                                                             \
  sc_ufixed_aug( tp val, sc_fxnum_observer* ob_= 0 ):                                      \
   sc_ufix_aug( a, W, I, Q, O, N, ob_ )                                                    \
  {}                                                                                      \
                                                                                          \
  sc_ufixed_aug( tp val, const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_= 0 ):         \
    sc_ufix( a, W, I, Q, O, N, fs_, ob_ )                                                  \
  { }

  #define PK_DEFN_CTORS_T_B(tp)                                                           \
  explicit sc_ufixed_aug( tp val, sc_fxnum_observer* ob_= 0 ):                             \
    sc_ufix_aug( a, W, I, Q, O, N, ob_ )                                                   \
  {}                                                                                      \
                                                                                          \
  sc_ufixed_aug( tp val, const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_= 0 ):         \
    sc_ufix( a, W, I, Q, O, N, fs_, ob_ )                                                  \
  {}                                                                    


             

    PK_DEFN_CTORS_T_A(int)
    PK_DEFN_CTORS_T_A(unsigned int)
    PK_DEFN_CTORS_T_A(long)
    PK_DEFN_CTORS_T_A(unsigned long)
    PK_DEFN_CTORS_T_A(double)
    PK_DEFN_CTORS_T_A(const char*)
    PK_DEFN_CTORS_T_A(const sc_fxval&)
    PK_DEFN_CTORS_T_A(const sc_fxval_fast&)
    PK_DEFN_CTORS_T_A(const sc_fxnum&)
    PK_DEFN_CTORS_T_A(const sc_fxnum_fast&)
#ifndef SC_FX_EXCLUDE_OTHER
    PK_DEFN_CTORS_T_B(int64)
    PK_DEFN_CTORS_T_B(uint64)
    PK_DEFN_CTORS_T_B(const sc_int_base&)
    PK_DEFN_CTORS_T_B(const sc_uint_base&)
    PK_DEFN_CTORS_T_B(const sc_signed&)
    PK_DEFN_CTORS_T_B(const sc_unsigned&)
#endif

#undef PK_DEFN_CTORS_T_A
#undef PK_DEFN_CTORS_T_B

 sc_ufixed_aug( const sc_ufixed<W,I,Q,O,N>& fxd ):
	  sc_ufix_aug( static_cast< const sc_ufix& >(fxd) )          
 { }

 sc_ufixed_aug( const sc_ufixed_aug<W,I,Q,O,N>& fxd ): 
   sc_ufix_aug( static_cast< const sc_ufix_aug& >(fxd) )
 { }



 // assignment operators
 
 sc_ufixed_aug<W,I,Q,O,N>& operator = ( const sc_ufixed<W,I,Q,O,N>& fxd )
 {                                                                                                     
  sc_ufix_aug::operator = ( static_cast< const sc_ufix& >(fxd) );                               
  return *this;                                            
 } 

 sc_ufixed_aug<W,I,Q,O,N>& operator = ( const sc_ufixed_aug<W,I,Q,O,N>& fxd )
 {
  sc_ufix_aug::operator = ( static_cast< const sc_ufix_aug& >(fxd) );                               
  return *this;                                                                                                   
 } 

 #define PK_DEFN_ASN_OP_T(op,tp)                                               \
  sc_ufixed_aug<W,I,Q,O,N>& operator op ( tp val )                                         \
  {                                                                            \
                                                                               \
   sc_ufix_aug:: operator op( val );                                                  \
   return *this;                                                               \
  }                                                                            \

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DEFN_ASN_OP_OTHER(op)                                             \
    PK_DEFN_ASN_OP_T(op,int64)                                                \
    PK_DEFN_ASN_OP_T(op,uint64)                                               \
    PK_DEFN_ASN_OP_T(op,const sc_int_base&)                                   \
    PK_DEFN_ASN_OP_T(op,const sc_uint_base&)                                  \
    PK_DEFN_ASN_OP_T(op,const sc_signed&)                                     \
    PK_DEFN_ASN_OP_T(op,const sc_unsigned&)
 #else
 #define PK_DEFN_ASN_OP_OTHER(op)
 #endif

 #define PK_DEFN_ASN_OP(op)                                                      \
    PK_DEFN_ASN_OP_T(op,int)                                                     \
    PK_DEFN_ASN_OP_T(op,unsigned int)                                            \
    PK_DEFN_ASN_OP_T(op,long)                                                    \
    PK_DEFN_ASN_OP_T(op,unsigned long)                                           \
    PK_DEFN_ASN_OP_T(op,double)                                                  \
    PK_DEFN_ASN_OP_T(op,const char*)                                             \
    PK_DEFN_ASN_OP_T(op,const sc_fxval&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxval_fast&)                                    \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum_fast&)                                    \
    PK_DEFN_ASN_OP_OTHER(op)
    
    PK_DEFN_ASN_OP(=)

    PK_DEFN_ASN_OP(*=)
    PK_DEFN_ASN_OP(/=)
    PK_DEFN_ASN_OP(+=)
    PK_DEFN_ASN_OP(-=)

    PK_DEFN_ASN_OP_T(<<=,int)
    PK_DEFN_ASN_OP_T(>>=,int)

    PK_DEFN_ASN_OP_T(&=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(&=,const sc_ufix_fast&)
    PK_DEFN_ASN_OP_T(|=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(|=,const sc_ufix_fast&)
    PK_DEFN_ASN_OP_T(^=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(^=,const sc_ufix_fast&)

 #undef PK_DEFN_ASN_OP_T
 #undef PK_DEFN_ASN_OP_OTHER
 #undef PK_DEFN_ASN_OP

 const sc_fxval operator ++ ( int )                                         
  {                                                                                                                                          
   return sc_ufix_aug:: operator ++( 0 );                                                                                                      
  }    

  const sc_fxval operator -- ( int )                                         
  {                                                                                                                                          
   return sc_ufix_aug:: operator --( 0 );                                                                                                      
  }  

  sc_ufixed_aug<W,I,Q,O,N>& operator ++ ()                                         
  {                                                                                                                                          
   sc_ufix_aug:: operator ++();  
   return *this;
  }    

  sc_ufixed_aug<W,I,Q,O,N>& operator -- ()                                         
  {                                                                                                                                          
   sc_ufix_aug:: operator --();  
   return *this;
  } 

};


// ----------------------------------------------------------------------------
//  CLASS : sc_ufixed_fast_aug
//
//  class for the internal augmented signals related to the SystemC type sc_ufixed_fast
// ----------------------------------------------------------------------------

template <int W, int I,
	  sc_q_mode Q = SC_DEFAULT_Q_MODE_,
	  sc_o_mode O = SC_DEFAULT_O_MODE_, int N = SC_DEFAULT_N_BITS_>
class sc_ufixed_fast_aug : public sc_ufix_fast_aug
{
 public:

 // constructors

 explicit sc_ufixed_fast_aug( sc_fxnum_observer* ob_ = 0 ): 
    sc_ufix_fast_aug( W, I, Q, O, N, ob_ )        
 {}

 explicit sc_ufixed_fast_aug( const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_ = 0 ): 
           sc_ufix_fast_aug( W, I, Q, O, N, fs_, ob_ )
 {}
    
#define PK_DEFN_CTORS_T_A(tp)                                                              \
 sc_ufixed_fast_aug( tp val, sc_fxnum_observer* ob_= 0 ):                                   \
       sc_ufix_fast_aug(val, W, I, Q, O, N, ob_ )                                           \
		  {}                                                                               \
 sc_ufixed_fast_aug( tp val, const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_= 0 ):      \
     sc_ufix_fast_aug(val, W, I, Q, O, N, fs_, ob_ )                                        \
		  {}

  #define PK_DEFN_CTORS_T_B(tp)                                                            \
  explicit sc_ufixed_fast_aug( tp val, sc_fxnum_observer* ob_= 0 ):                         \
        sc_ufix_fast_aug(val, W, I, Q, O, N, ob_ )                                          \
  {}                                                                                       \
                                                                                           \
  sc_ufixed_fast_aug( tp val, const sc_fxcast_switch& fs_, sc_fxnum_observer* ob_= 0 ):     \
    sc_ufix_fast_aug(val, W, I, Q, O, N, fs_, ob_ )                                         \
  {}                                                                    


             

    PK_DEFN_CTORS_T_A(int)
    PK_DEFN_CTORS_T_A(unsigned int)
    PK_DEFN_CTORS_T_A(long)
    PK_DEFN_CTORS_T_A(unsigned long)
    PK_DEFN_CTORS_T_A(double)
    PK_DEFN_CTORS_T_A(const char*)
    PK_DEFN_CTORS_T_A(const sc_fxval&)
    PK_DEFN_CTORS_T_A(const sc_fxval_fast&)
    PK_DEFN_CTORS_T_A(const sc_fxnum&)
    PK_DEFN_CTORS_T_A(const sc_fxnum_fast&)
#ifndef SC_FX_EXCLUDE_OTHER
    PK_DEFN_CTORS_T_B(int64)
    PK_DEFN_CTORS_T_B(uint64)
    PK_DEFN_CTORS_T_B(const sc_int_base&)
    PK_DEFN_CTORS_T_B(const sc_uint_base&)
    PK_DEFN_CTORS_T_B(const sc_signed&)
    PK_DEFN_CTORS_T_B(const sc_unsigned&)
#endif

#undef PK_DEFN_CTORS_T_A
#undef PK_DEFN_CTORS_T_B

 sc_ufixed_fast_aug( const sc_ufixed_fast<W,I,Q,O,N>& fxd ):
	  sc_ufix_fast_aug( static_cast< const sc_ufix_fast& >(fxd) )         
 {}

 sc_ufixed_fast_aug( const sc_ufixed_fast_aug<W,I,Q,O,N>& fxd ): 
       sc_ufix_fast_aug( static_cast< const sc_ufix_fast_aug& >(fxd) )
 {}



 // assignment operators
 
 sc_ufixed_fast_aug<W,I,Q,O,N>& operator = ( const sc_ufixed_fast<W,I,Q,O,N>& fxd )
 {                                                                                                    
  sc_ufix_fast_aug::operator =( static_cast< const sc_ufix_fast& >(fxd) )                               
  return *this;                                            
 } 

 sc_ufixed_fast_aug<W,I,Q,O,N>& operator = ( const sc_ufixed_fast_aug<W,I,Q,O,N>& fxd )
 {
  sc_ufix_fast_aug::operator =( static_cast< const sc_ufix_fast_aug& >(fxd) )                               
  return *this;                                                                                                 
 } 

 #define PK_DEFN_ASN_OP_T(op,tp)                                               \
  sc_ufixed_fast_aug<W,I,Q,O,N>& operator op ( tp val )                                    \
  {                                                                            \
                                                                               \
   sc_ufix_fast_aug:: operator op ( val );                                             \
   return *this;                                                               \
  }                                                                            \

 #ifndef SC_FX_EXCLUDE_OTHER
 #define PK_DEFN_ASN_OP_OTHER(op)                                                \
    PK_DEFN_ASN_OP_T(op,int64)                                                   \
    PK_DEFN_ASN_OP_T(op,uint64)                                                  \
    PK_DEFN_ASN_OP_T(op,const sc_int_base&)                                      \
    PK_DEFN_ASN_OP_T(op,const sc_uint_base&)                                     \
    PK_DEFN_ASN_OP_T(op,const sc_signed&)                                        \
    PK_DEFN_ASN_OP_T(op,const sc_unsigned&)
 #else
 #define PK_DEFN_ASN_OP_OTHER(op)
 #endif

 #define PK_DEFN_ASN_OP(op)                                                      \
    PK_DEFN_ASN_OP_T(op,int)                                                     \
    PK_DEFN_ASN_OP_T(op,unsigned int)                                            \
    PK_DEFN_ASN_OP_T(op,long)                                                    \
    PK_DEFN_ASN_OP_T(op,unsigned long)                                           \
    PK_DEFN_ASN_OP_T(op,double)                                                  \
    PK_DEFN_ASN_OP_T(op,const char*)                                             \
    PK_DEFN_ASN_OP_T(op,const sc_fxval&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxval_fast&)                                    \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum&)                                         \
    PK_DEFN_ASN_OP_T(op,const sc_fxnum_fast&)                                    \
    PK_DEFN_ASN_OP_OTHER(op)
    
    PK_DEFN_ASN_OP(=)

    PK_DEFN_ASN_OP(*=)
    PK_DEFN_ASN_OP(/=)
    PK_DEFN_ASN_OP(+=)
    PK_DEFN_ASN_OP(-=)

    PK_DEFN_ASN_OP_T(<<=,int)
    PK_DEFN_ASN_OP_T(>>=,int)

    PK_DEFN_ASN_OP_T(&=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(&=,const sc_ufix_fast&)
    PK_DEFN_ASN_OP_T(|=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(|=,const sc_ufix_fast&)
    PK_DEFN_ASN_OP_T(^=,const sc_ufix&)
    PK_DEFN_ASN_OP_T(^=,const sc_fix_fast&)

 #undef PK_DEFN_ASN_OP_T
 #undef PK_DEFN_ASN_OP_OTHER
 #undef PK_DEFN_ASN_OP

 const sc_fxval_fast operator ++ ( int )                                         
  {                                                                                                                                           
   return sc_ufix_fast_aug:: operator ++( 0 );                                                                                                      
  }    

 const sc_fxval_fast operator -- ( int )                                         
  {                                                                            
   return sc_ufix_fast_aug:: operator --( 0 );                                                                                                  
  }  

  sc_ufixed_fast_aug<W,I,Q,O,N>& operator ++ ()                                         
  {                                                                                                                                          
   return sc_ufix_fast_aug:: operator ++(); 
   return *this;
  }    

  sc_ufixed_fast_aug<W,I,Q,O,N>& operator -- ()                                         
  {                                                                            
   return sc_ufix_fast_aug:: operator --();
   return *this;
  } 

};


};  // pk_dt


#endif

