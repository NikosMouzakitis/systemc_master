#ifndef OPMODEL_MACROS_H
#define OPMODEL_MACROS_H


 
#define PK_OPMODEL_OP1a_DECL(op, op_sym, op_tp, ret_tp)                     \
  ret_tp operator op (const op_tp##_aug&, const op_tp##_aug&);


#define PK_OPMODEL_OP1a(op, op_sym, op_tp, ret_tp)                                           \
                                                                                           \
ret_tp operator op (const op_tp##_aug& a1, const op_tp##_aug& a2)                          \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast<const op_tp & >(a1) op static_cast<const op_tp & >(a2) );         \
}  



#define PK_OPMODEL_OP1b(op, op_sym, tp, ret_tp)                                            \
                                                                                           \
 template<int n1, int n2>                                                                                        \
   ret_tp operator op (const tp##_aug<n1>& a1, const tp##_aug<n2>& a2)      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast<const tp <n1>& >(a1) op static_cast<const tp <n2>& >(a2));      \
}  


#define PK_OPMODEL_OP1c_DECL(op, op_sym, tp, ret_tp)                                     \
 ret_tp  operator op ( const cpptype_aug< tp >&, const cpptype_aug< tp >& ); 

#define PK_OPMODEL_OP1c(op, op_sym, tp, ret_tp)                                     \
                                                                                           \
                                                                                        \
ret_tp  operator op (const cpptype_aug< tp >& a1, const cpptype_aug< tp >& a2)      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
 return ( (a1.operator const tp &()) op (a2.operator const tp &()) );      \
} 



#define PK_OPMODEL_OP1d_DECL_(op, op_sym, cpp_tp, tp, ret_tp1, ret_tp2)           \
  ret_tp1 operator op (const tp, const cpptype_aug< cpp_tp >& );            \
  ret_tp2 operator op ( const cpptype_aug< cpp_tp >&, const tp );     

#define PK_OPMODEL_OP1d_DECL(op, op_sym, cpp_tp, tp, ret_tp)            \
         PK_OPMODEL_OP1d_DECL_(op, op_sym, cpp_tp, tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP1d_(op, op_sym, cpp_tp, tp, ret_tp1, ret_tp2)       \
                                                                        \
                                                                       \
ret_tp1 operator op (const cpptype_aug< cpp_tp >& a1, const tp a2)      \
{                                                                       \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                 \
   return ( (a1.operator const cpp_tp &()) op a2   );                  \
}                                                                      \
	                                                                   \
                                                                       \
ret_tp2 operator op (const tp a1, const cpptype_aug< cpp_tp >& a2)    \
{                                                                     \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                \
   return ( a1 op (a2.operator const cpp_tp &()) );                   \
}                                                                

#define PK_OPMODEL_OP1d(op, op_sym, cpp_tp, tp, ret_tp)         \
   PK_OPMODEL_OP1d_(op, op_sym, cpp_tp, tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP1e1_DECL_(op, op_sym, aug_tp1, aug_tp2, ret_tp1,ret_tp2)           \
 ret_tp1 operator op ( const aug_tp1##_aug&, const aug_tp2##_aug& );    \
 ret_tp2 operator op ( const aug_tp2##_aug&, const aug_tp1##_aug& );


#define PK_OPMODEL_OP1e1_DECL(op, op_sym, aug_tp1, aug_tp2, ret_tp)      \
   PK_OPMODEL_OP1e1_DECL_(op, op_sym, aug_tp1, aug_tp2, ret_tp, ret_tp)


#define PK_OPMODEL_OP1e1_(op, op_sym, aug_tp1, aug_tp2, ret_tp1, ret_tp2)                   \
                                                                                           \
                                                                                           \
ret_tp1 operator op (const aug_tp1##_aug& a1, const aug_tp2##_aug& a2)                      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( (a1.operator const aug_tp1 &()) op (a2.operator const aug_tp2 &()) );      \
}                                                                                          \
                                                                                           \
ret_tp2 operator op (const aug_tp2##_aug& a1, const aug_tp1##_aug& a2)                      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( (a1.operator const aug_tp2 &()) op (a2.operator const aug_tp1 &()) );        \
} 

#define PK_OPMODEL_OP1e1(op, op_sym, aug_tp1, aug_tp2, ret_tp)                \
          PK_OPMODEL_OP1e1_(op, op_sym, aug_tp1, aug_tp2, ret_tp, ret_tp)




#define PK_OPMODEL_OP1e2_DECL_(op, op_sym, aug_tp1, aug_tp2, ret_tp1,ret_tp2)           \
 ret_tp1 operator op ( const aug_tp1##_aug&, const aug_tp2##_aug& );    \
 ret_tp2 operator op ( const aug_tp2##_aug&, const aug_tp1##_aug& );


#define PK_OPMODEL_OP1e2_DECL(op, op_sym, aug_tp1, aug_tp2, ret_tp)      \
   PK_OPMODEL_OP1e2_DECL_(op, op_sym, aug_tp1, aug_tp2, ret_tp, ret_tp)


#define PK_OPMODEL_OP1e2_(op, op_sym, aug_tp1, aug_tp2, ret_tp1, ret_tp2)                   \
                                                                                           \
                                                                                           \
ret_tp1 operator op (const aug_tp1##_aug& a1, const aug_tp2##_aug& a2)                      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( (a1.operator const aug_tp1 &()) op static_cast< const aug_tp2 & >(a2) );      \
}                                                                                          \
                                                                                           \
ret_tp2 operator op (const aug_tp2##_aug& a1, const aug_tp1##_aug& a2)                      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast< const aug_tp2 & >(a1) op (a2.operator const aug_tp1 &()) );        \
} 

#define PK_OPMODEL_OP1e2(op, op_sym, aug_tp1, aug_tp2, ret_tp)                \
          PK_OPMODEL_OP1e2_(op, op_sym, aug_tp1, aug_tp2, ret_tp, ret_tp)



#define PK_OPMODEL_OP1e3_(op, op_sym, aug_tp1, aug_tp2, ret_tp1, ret_tp2)                   \
                                                                                           \
template<int n>                                                                                           \
ret_tp1 operator op (const aug_tp1##_aug<n>& a1, const aug_tp2##_aug& a2)                      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast< const aug_tp1<n> & >(a1) op (a2.operator const aug_tp2 &()) );      \
}                                                                                          \
template<int n>                                                                                            \
ret_tp2 operator op (const aug_tp2##_aug& a1, const aug_tp1##_aug<n>& a2)                      \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( (a1.operator const aug_tp2 &()) op static_cast< const aug_tp1<n> & >(a2) );    \
} 

#define PK_OPMODEL_OP1e3(op, op_sym, aug_tp1, aug_tp2, ret_tp)                \
          PK_OPMODEL_OP1e3_(op, op_sym, aug_tp1, aug_tp2, ret_tp, ret_tp)


#define PK_OPMODEL_OP1e4_(op, op_sym, aug_tp1, aug_tp2, ret_tp1, ret_tp2)                   \
                                                                                           \
template<int n1, int n2>                                                                                           \
ret_tp1 operator op (const aug_tp1##_aug<n1>& a1, const aug_tp2##_aug<n2>& a2)                      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast< const aug_tp1<n1> & >(a1) op static_cast< const aug_tp2<n2> & >(a2) );      \
}                                                                                          \
template<int n1, int n2>                                                                                            \
ret_tp2 operator op (const aug_tp2##_aug<n2>& a1, const aug_tp1##_aug<n1>& a2)                      \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( static_cast< const aug_tp2<n2> & >(a1) op static_cast< const aug_tp1<n1> & >(a2) );    \
} 

#define PK_OPMODEL_OP1e4(op, op_sym, aug_tp1, aug_tp2, ret_tp)                \
          PK_OPMODEL_OP1e4_(op, op_sym, aug_tp1, aug_tp2, ret_tp, ret_tp)


#define PK_OPMODEL_OP1f_DECL_(op, op_sym, aug_tp, op_tp, ret_tp1, ret_tp2)            \
 ret_tp1 operator op ( const aug_tp##_aug&, const op_tp );           \
 ret_tp2 operator op ( const op_tp, const aug_tp##_aug& );


#define PK_OPMODEL_OP1f_DECL(op, op_sym, aug_tp, op_tp, ret_tp)              \
         PK_OPMODEL_OP1f_DECL_(op, op_sym, aug_tp, op_tp, ret_tp, ret_tp)


#define PK_OPMODEL_OP1f_(op, op_sym, aug_tp, op_tp, ret_tp1, ret_tp2)                      \
                                                                                           \
                                                                                           \
ret_tp1 operator op (const aug_tp##_aug& a1, const op_tp a2)                               \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
      return ( static_cast<const aug_tp & >(a1) op a2 );                                    \
}                                                                                          \
                                                                                           \
ret_tp2 operator op (const op_tp a1, const aug_tp##_aug& a2)                                \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
	return ( a1 op static_cast<const aug_tp & >(a2) );                                        \
}

#define PK_OPMODEL_OP1f(op, op_sym, aug_tp, op_tp, ret_tp)             \
         PK_OPMODEL_OP1f_(op, op_sym, aug_tp, op_tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP1g_(op, op_sym, aug_tp, op_tp, ret_tp1, ret_tp2)                      \
                                                                                           \
template<int n>                                                                            \
ret_tp1 operator op (const aug_tp##_aug<n>& a1, const op_tp a2)                            \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
      return ( static_cast<const aug_tp<n> & >(a1) op a2 );                                \
}                                                                                          \
template<int n>                                                                            \
ret_tp2 operator op (const op_tp a1, const aug_tp##_aug<n>& a2)                                \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
	return ( a1 op static_cast<const aug_tp<n> & >(a2) );                                        \
}

#define PK_OPMODEL_OP1g(op, op_sym, aug_tp, op_tp, ret_tp)             \
         PK_OPMODEL_OP1g_(op, op_sym, aug_tp, op_tp, ret_tp, ret_tp)



       



#define PK_OPMODEL_OP2a_DECL(op, op_sym, port_tp, ret_tp)                              \
 ret_tp operator op ( const sc_in_aug< port_tp >& a1, const sc_in_aug< port_tp >& a2 );    


#define PK_OPMODEL_OP2a(op, op_sym, port_tp, ret_tp)                                        \
                                                                                           \
                                                                                           \
ret_tp operator op ( const sc_in_aug< port_tp >& a1, const sc_in_aug< port_tp >& a2 )      \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( static_cast<const sc_in< port_tp > & >(a1) op static_cast<const sc_in< port_tp > & >(a2) );                             \
} 

#define PK_OPMODEL_OP2b(op, op_sym, port_tp, ret_tp)                                          \
                                                                                           \
template<int n1, int n2>                                                                                           \
ret_tp operator op (const sc_in_aug< port_tp<n1> >& a1, const sc_in_aug< port_tp<n2> >& a2)                    \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
      return ( static_cast<const sc_in< port_tp<n1> > & >(a1) op static_cast<const sc_in< port_tp<n2> > & >(a2) );                                        \
} 

#define PK_OPMODEL_OP2c_DECL_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)    \
 ret_tp1 operator op ( const sc_in_aug< port_tp >&, const tp  );            \
 ret_tp2 operator op ( const tp, const sc_in_aug< port_tp >& );

#define PK_OPMODEL_OP2c_DECL(op, op_sym, port_tp, tp, ret_tp)              \
         PK_OPMODEL_OP2c_DECL_(op, op_sym, port_tp, tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP2c_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                        \
                                                                                           \
                                                                                           \
ret_tp1 operator op ( const sc_in_aug< port_tp >& a1, const tp a2 )                       \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast<const sc_in< port_tp > & >(a1) op a2 );      \
}                                                                                          \
                                                                                           \
ret_tp2 operator op (const tp a1, const sc_in_aug< port_tp >& a2)                           \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( a1 op static_cast<const sc_in< port_tp > & >(a2) );                             \
}                                                                                          \

#define PK_OPMODEL_OP2c(op, op_sym, port_tp, tp, ret_tp)          \
   PK_OPMODEL_OP2c_(op, op_sym, port_tp, tp, ret_tp, ret_tp)


#define PK_OPMODEL_OP2d_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                           \
                                                                                           \
template<int n>                                                                                           \
ret_tp1 operator op (const sc_in_aug< port_tp >& a1, const tp<n>& a2)                    \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
      return ( static_cast<const sc_in< port_tp > & >(a1) op a2 );                                        \
}                                                                                          \
                                                                                           \
template<int n> 																		   \
ret_tp2 operator op (const tp<n>& a1, const sc_in_aug< port_tp >& a2)                             \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
	return ( a1 op static_cast<const sc_in< port_tp > & >(a2) );                                        \
}

#define PK_OPMODEL_OP2d(op, op_sym, port_tp, tp, ret_tp)              \
        PK_OPMODEL_OP2d_(op, op_sym, port_tp, tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP2e_DECL_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)     \
 ret_tp1 operator op ( const sc_in_aug< port_tp >&, const tp##_aug&  );       \
 ret_tp2 operator op ( const tp##_aug&, const sc_in_aug< port_tp >& );

#define PK_OPMODEL_OP2e_DECL(op, op_sym, port_tp, tp, ret_tp)               \
       PK_OPMODEL_OP2e_DECL_(op, op_sym, port_tp, tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP2e_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                               \
                                                                                           \
                                                                                           \
ret_tp1 operator op ( const sc_in_aug< port_tp >& a1, const tp##_aug& a2 )                       \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast<const sc_in< port_tp > & >(a1) op static_cast<const tp& >(a2) );      \
}                                                                                          \
                                                                                           \
ret_tp2 operator op (const tp##_aug& a1, const sc_in_aug< port_tp >& a2)                           \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( static_cast<const tp& >(a1) op static_cast<const sc_in< port_tp > & >(a2) );                             \
}                                                                                          \


#define PK_OPMODEL_OP2e(op, op_sym, port_tp, tp, ret_tp)           \
      PK_OPMODEL_OP2e_(op, op_sym, port_tp, tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP2f_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                          \
                                                                                           \
template<int n>                                                                                           \
ret_tp1 operator op (const sc_in_aug< port_tp >& a1, const tp##_aug<n>& a2)                    \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( static_cast<const sc_in< port_tp > & >(a1) op static_cast<const tp<n>& >(a2) ); \
}                                                                                          \
                                                                                           \
template<int n> 																		   \
ret_tp2 operator op (const tp##_aug<n>& a1, const sc_in_aug< port_tp >& a2)                             \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
  return ( static_cast<const tp<n>& >(a1) op static_cast<const sc_in< port_tp > & >(a2) );                                        \
}


#define PK_OPMODEL_OP2f(op, op_sym, port_tp, tp, ret_tp)             \
         PK_OPMODEL_OP2f_(op, op_sym, port_tp, tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP2g_DECL_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)        \
 ret_tp1 operator op ( const sc_in_aug< port_tp1 >&, const sc_in_aug< port_tp2 >&  );  \
 ret_tp2 operator op ( const sc_in_aug< port_tp2 >&, const sc_in_aug< port_tp1 >& );

#define PK_OPMODEL_OP2g_DECL(op, op_sym, port_tp1, port_tp2, ret_tp)               \
       PK_OPMODEL_OP2g_DECL_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)



#define PK_OPMODEL_OP2g_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)                 \
                                                                                           \
                                                                                           \
ret_tp1 operator op ( const sc_in_aug< port_tp1 >& a1, const sc_in_aug< port_tp2 >& a2  )  \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( static_cast<const sc_in< port_tp1 > & >(a1) op static_cast<const sc_in< port_tp2 > & >(a2) );      \
}                                                                                          \
                                                                                           \
ret_tp2 operator op ( const sc_in_aug< port_tp2 >& a1, const sc_in_aug< port_tp1 >& a2 )   \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( static_cast<const sc_in< port_tp2 > & >(a1) op static_cast<const sc_in< port_tp1 > & >(a2) );                             \
}                                                                                          \


#define PK_OPMODEL_OP2g(op, op_sym, port_tp1, port_tp2, ret_tp)           \
      PK_OPMODEL_OP2g_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)


#define PK_OPMODEL_OP2h_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)                 \
                                                                                           \
template<int n>                                                                                           \
ret_tp1 operator op ( const sc_in_aug< port_tp1 >& a1, const sc_in_aug< port_tp2<n> >& a2  )  \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( static_cast<const sc_in< port_tp1 > & >(a1) op static_cast<const sc_in< port_tp2<n> > & >(a2) );    \
}                                                                                          \
template<int n>                                                                                            \
ret_tp2 operator op ( const sc_in_aug< port_tp2<n> >& a1, const sc_in_aug< port_tp1 >& a2 )   \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( static_cast<const sc_in< port_tp2<n> > & >(a1) op static_cast<const sc_in< port_tp1 > & >(a2) );    \
}                                                                                          \


#define PK_OPMODEL_OP2h(op, op_sym, port_tp1, port_tp2, ret_tp)           \
      PK_OPMODEL_OP2h_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)



#define PK_OPMODEL_OP2cc_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                        \
                                                                                           \
template<int n>                                                                                           \
ret_tp1 operator op ( const sc_in_aug< port_tp <n> >& a1, const tp a2 )                       \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast<const sc_in< port_tp <n> > & >(a1) op a2 );      \
}                                                                                          \
template<int n>                                                                                            \
ret_tp2 operator op (const tp a1, const sc_in_aug< port_tp <n> >& a2)                           \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( a1 op static_cast<const sc_in< port_tp <n> > & >(a2) );                             \
}                                                                                          \

#define PK_OPMODEL_OP2cc(op, op_sym, port_tp, tp, ret_tp)          \
   PK_OPMODEL_OP2cc_(op, op_sym, port_tp, tp, ret_tp, ret_tp)


#define PK_OPMODEL_OP2dd_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                           \
                                                                                           \
template<int W, int n>                                                                                           \
ret_tp1 operator op (const sc_in_aug< port_tp <W> >& a1, const tp<n>& a2)                    \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
      return ( static_cast<const sc_in< port_tp <W> > & >(a1) op a2 );                                        \
}                                                                                          \
                                                                                           \
template<int W, int n>  																		   \
ret_tp2 operator op (const tp<n>& a1, const sc_in_aug< port_tp <W> >& a2)                             \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
	return ( a1 op static_cast<const sc_in< port_tp <W> > & >(a2) );                                        \
}

#define PK_OPMODEL_OP2dd(op, op_sym, port_tp, tp, ret_tp)              \
        PK_OPMODEL_OP2dd_(op, op_sym, port_tp, tp, ret_tp, ret_tp)


#define PK_OPMODEL_OP2ee_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                               \
                                                                                           \
template<int n>                                                                                           \
ret_tp1 operator op ( const sc_in_aug< port_tp <n> >& a1, const tp##_aug& a2 )                       \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
   return ( static_cast<const sc_in< port_tp <n> > & >(a1) op static_cast<const tp& >(a2) );      \
}                                                                                          \
template<int n>                                                                                            \
ret_tp2 operator op (const tp##_aug& a1, const sc_in_aug< port_tp <n> >& a2)                           \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( static_cast<const tp& >(a1) op static_cast<const sc_in< port_tp <n> > & >(a2) );                             \
}                                                                                          \


#define PK_OPMODEL_OP2ee(op, op_sym, port_tp, tp, ret_tp)           \
      PK_OPMODEL_OP2ee_(op, op_sym, port_tp, tp, ret_tp, ret_tp)



#define PK_OPMODEL_OP2ff_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                          \
                                                                                           \
template<int W, int n>                                                                                           \
ret_tp1 operator op (const sc_in_aug< port_tp <W> >& a1, const tp##_aug<n>& a2)                    \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( static_cast<const sc_in< port_tp <W> > & >(a1) op static_cast<const tp<n>& >(a2) ); \
}                                                                                          \
                                                                                           \
template<int W, int n>  																		   \
ret_tp2 operator op (const tp##_aug<n>& a1, const sc_in_aug< port_tp <W> >& a2)                             \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
  return ( static_cast<const tp<n>& >(a1) op static_cast<const sc_in< port_tp <W> > & >(a2) );                                        \
}


#define PK_OPMODEL_OP2ff(op, op_sym, port_tp, tp, ret_tp)             \
         PK_OPMODEL_OP2ff_(op, op_sym, port_tp, tp, ret_tp, ret_tp)


#define PK_OPMODEL_OP2gg_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)                 \
                                                                                           \
template<int n>                                                                                            \
ret_tp1 operator op ( const sc_in_aug< port_tp1 <n> >& a1, const sc_in_aug< port_tp2 >& a2  )  \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( static_cast<const sc_in< port_tp1 <n> > & >(a1) op static_cast<const sc_in< port_tp2 > & >(a2) );      \
}                                                                                          \
template<int n>                                                                                           \
ret_tp2 operator op ( const sc_in_aug< port_tp2 >& a1, const sc_in_aug< port_tp1 <n> >& a2 )   \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( static_cast<const sc_in< port_tp2 > & >(a1) op static_cast<const sc_in< port_tp1 <n> > & >(a2) );                             \
}                                                                                          \


#define PK_OPMODEL_OP2gg(op, op_sym, port_tp1, port_tp2, ret_tp)           \
      PK_OPMODEL_OP2gg_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)


#define PK_OPMODEL_OP2hh_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)                 \
                                                                                           \
template<int W, int n>                                                                                          \
ret_tp1 operator op ( const sc_in_aug< port_tp1 <W> >& a1, const sc_in_aug< port_tp2<n> >& a2  )  \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( static_cast<const sc_in< port_tp1 <W> > & >(a1) op static_cast<const sc_in< port_tp2<n> > & >(a2) );    \
}                                                                                          \
template<int W, int n>                                                                                             \
ret_tp2 operator op ( const sc_in_aug< port_tp2<n> >& a1, const sc_in_aug< port_tp1 <W> >& a2 )   \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
   return ( static_cast<const sc_in< port_tp2<n> > & >(a1) op static_cast<const sc_in< port_tp1 <W> > & >(a2) );    \
}                                                                                          \


#define PK_OPMODEL_OP2hh(op, op_sym, port_tp1, port_tp2, ret_tp)           \
      PK_OPMODEL_OP2hh_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)









#define PK_OPMODEL_OP3a_DECL(op, op_sym, port_tp, ret_tp)                                          \
ret_tp operator op ( const pk_proxy_opmod< port_tp >& a1, const pk_proxy_opmod< port_tp >& a2 );    


#define PK_OPMODEL_OP3a(op, op_sym, port_tp, ret_tp)                                                  \
                                                                                                      \
                                                                                                      \
ret_tp operator op ( const pk_proxy_opmod< port_tp >& a1, const pk_proxy_opmod< port_tp >& a2 )      \
{                                                                                                     \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                                \
  return ( a1.get() op a2.get() );                                                                     \
} 


#define PK_OPMODEL_OP3b(op, op_sym, port_tp, ret_tp)                                   \
                                                                                           \
template<int n1, int n2>                                                                   \
ret_tp operator op (const pk_proxy_opmod< port_tp <n1> >& a1, const pk_proxy_opmod< port_tp <n2> >& a2)                    \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
      return ( a1.get() op a2.get() );                                                      \
}    

#define PK_OPMODEL_OP3c_DECL_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)   \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp >& , const tp );       \
ret_tp2 operator op ( const tp , const pk_proxy_opmod< port_tp >& );

#define PK_OPMODEL_OP3c_DECL(op, op_sym, port_tp, tp, ret_tp)             \
          PK_OPMODEL_OP3c_DECL_(op, op_sym, port_tp, tp, ret_tp, ret_tp)


#define PK_OPMODEL_OP3c_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                   \
                                                                                                      \
                                                                                                      \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp >& a1, const tp a2 )                               \
{                                                                                                     \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                                \
  return ( a1.get() op a2 );                                                                           \
}                                                                                                     \
                                                                                                      \
ret_tp2 operator op ( const tp a1, const pk_proxy_opmod< port_tp >& a2 )                               \
{                                                                                                     \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                                \
  return ( a1 op a2.get() );                                                                           \
}

#define PK_OPMODEL_OP3c(op, op_sym, port_tp, tp, ret_tp)                \
           PK_OPMODEL_OP3c_(op, op_sym, port_tp, tp, ret_tp, ret_tp)

 

#define PK_OPMODEL_OP3cc_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                   \
                                                                                                      \
template<int n>                                                                                       \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp <n> >& a1, const tp a2 )                               \
{                                                                                                     \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                                \
  return ( a1.get() op a2 );                                                                           \
}                                                                                                     \
template<int n>                                                                                                       \
ret_tp2 operator op ( const tp a1, const pk_proxy_opmod< port_tp <n> >& a2 )                               \
{                                                                                                     \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                                \
  return ( a1 op a2.get() );                                                                           \
}

#define PK_OPMODEL_OP3cc(op, op_sym, port_tp, tp, ret_tp)                \
           PK_OPMODEL_OP3cc_(op, op_sym, port_tp, tp, ret_tp, ret_tp)


                                                                                                    

#define PK_OPMODEL_OP3d_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                              \
                                                                                                      \
 template<int n>                                                                                      \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp >& a1, const tp <n> &a2 )                          \
{                                                                                                     \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                                \
  return ( a1.get() op a2 );                                                                           \
}                                                                                                     \
template<int n>                                                                                       \
ret_tp2 operator op ( const tp <n> &a1, const pk_proxy_opmod< port_tp >& a2 )                          \
{                                                                                                     \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                                \
  return ( a1 op a2.get() );                                                                           \
}

#define PK_OPMODEL_OP3d(op, op_sym, port_tp, tp, ret_tp )              \
     PK_OPMODEL_OP3d_(op, op_sym, port_tp, tp, ret_tp, ret_tp)

 

#define PK_OPMODEL_OP3dd_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                              \
                                                                                                      \
 template<int n, int W>                                                                           \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp <W> >& a1, const tp <n> &a2 )                          \
{                                                                                                     \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                                \
  return ( a1.get() op a2 );                                                                           \
}                                                                                                     \
template<int n, int W>                                                                                        \
ret_tp2 operator op ( const tp <n> &a1, const pk_proxy_opmod< port_tp <W> >& a2 )                          \
{                                                                                                     \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                                \
  return ( a1 op a2.get() );                                                                           \
}

#define PK_OPMODEL_OP3dd(op, op_sym, port_tp, tp, ret_tp )              \
     PK_OPMODEL_OP3dd_(op, op_sym, port_tp, tp, ret_tp, ret_tp)




#define PK_OPMODEL_OP3e_DECL_(op, op_sym, port_tp, cpp_tp, ret_tp1, ret_tp2)                \
 ret_tp1 operator op (const pk_proxy_opmod< port_tp >& , const cpptype_aug< cpp_tp >& );     \
 ret_tp2 operator op ( const cpptype_aug< cpp_tp >&, const pk_proxy_opmod< port_tp >& );     


#define PK_OPMODEL_OP3e_DECL(op, op_sym, port_tp, cpp_tp, ret_tp)            \
         PK_OPMODEL_OP3e_DECL_(op, op_sym, port_tp, cpp_tp, ret_tp, ret_tp)

#define PK_OPMODEL_OP3e_(op, op_sym, port_tp, cpp_tp, ret_tp1, ret_tp2 )                                  \
                                                                                         \
                                                                                          \
ret_tp1 operator op (const pk_proxy_opmod< port_tp >& a1, const cpptype_aug< cpp_tp >& a2) \
{                                                                       \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                  \
   return ( a1.get() op (a2.operator const cpp_tp &()) );               \
}                                                                       \
	                                                                    \
                                                                        \
ret_tp2 operator op ( const cpptype_aug< cpp_tp >& a1, const pk_proxy_opmod< port_tp >& a2)    \
{                                                                     \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                \
   return ( (a1.operator const cpp_tp &()) op a2.get()  );                   \
}  

#define PK_OPMODEL_OP3e(op, op_sym, port_tp, cpp_tp, ret_tp )                    \
          PK_OPMODEL_OP3e_(op, op_sym, port_tp, cpp_tp, ret_tp, ret_tp )


 

#define PK_OPMODEL_OP3ee_(op, op_sym, port_tp, cpp_tp, ret_tp1, ret_tp2 )                                  \
                                                                                         \
template<int n>                                                                                          \
ret_tp1 operator op (const pk_proxy_opmod< port_tp <n> >& a1, const cpptype_aug< cpp_tp >& a2) \
{                                                                       \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                  \
   return ( a1.get() op (a2.operator const cpp_tp &()) );               \
}                                                                       \
	                                                                    \
template<int n>                                                                        \
ret_tp2 operator op ( const cpptype_aug< cpp_tp >& a1, const pk_proxy_opmod< port_tp <n> >& a2)    \
{                                                                     \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                \
   return ( (a1.operator const cpp_tp &()) op a2.get()  );                   \
}  

#define PK_OPMODEL_OP3ee(op, op_sym, port_tp, cpp_tp, ret_tp )                    \
          PK_OPMODEL_OP3ee_(op, op_sym, port_tp, cpp_tp, ret_tp, ret_tp )




#define PK_OPMODEL_OP3f_DECL_(op, op_sym, port_tp, aug_tp, ret_tp1, ret_tp2 )      \
 ret_tp1 operator op ( const pk_proxy_opmod< port_tp >&, const aug_tp##_aug& );    \
 ret_tp2 operator op ( const aug_tp##_aug&, const pk_proxy_opmod< port_tp >& );

#define PK_OPMODEL_OP3f_DECL(op, op_sym, port_tp, aug_tp, ret_tp )         \
    PK_OPMODEL_OP3f_DECL_(op, op_sym, port_tp, aug_tp, ret_tp, ret_tp )      

#define PK_OPMODEL_OP3f_(op, op_sym, port_tp, aug_tp, ret_tp1, ret_tp2)                    \
                                                                                           \
                                                                                           \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp >& a1, const aug_tp##_aug& a2 )                                        \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
      return ( a1.get() op static_cast<const aug_tp & >(a2) op a2 );                                        \
}                                                                                          \
                                                                                           \
ret_tp2 operator op ( const aug_tp##_aug& a1, const pk_proxy_opmod< port_tp >& a2 )                                   \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
	return ( static_cast<const aug_tp & >(a1) op a2.get() );                                        \
}

#define PK_OPMODEL_OP3f(op, op_sym, port_tp, aug_tp, ret_tp)       \
	PK_OPMODEL_OP3f_(op, op_sym, port_tp, aug_tp, ret_tp, ret_tp)




#define PK_OPMODEL_OP3ff_(op, op_sym, port_tp, aug_tp, ret_tp1, ret_tp2)                    \
                                                                                           \
template<int n>                                                                                           \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp <n> >& a1, const aug_tp##_aug& a2 )                                        \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
      return ( a1.get() op static_cast<const aug_tp & >(a2) op a2 );                                        \
}                                                                                          \
template<int n>                                                                                           \
ret_tp2 operator op ( const aug_tp##_aug& a1, const pk_proxy_opmod< port_tp <n> >& a2 )                                   \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
	return ( static_cast<const aug_tp & >(a1) op a2.get() );                                        \
}

#define PK_OPMODEL_OP3ff(op, op_sym, port_tp, aug_tp, ret_tp)       \
	PK_OPMODEL_OP3ff_(op, op_sym, port_tp, aug_tp, ret_tp, ret_tp)




#define PK_OPMODEL_OP3g_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                          \
                                                                                           \
template<int n>                                                                                           \
ret_tp1 operator op (const pk_proxy_opmod< port_tp >& a1, const tp##_aug<n>& a2)                    \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( a1.get() op static_cast<const tp<n>& >(a2) ); \
}                                                                                          \
                                                                                           \
template<int n> 																		   \
ret_tp2 operator op (const tp##_aug<n>& a1, const pk_proxy_opmod< port_tp >& a2)            \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
  return ( static_cast<const tp<n>& >(a1) op a2.get() );                                   \
}

#define PK_OPMODEL_OP3g(op, op_sym, port_tp, tp, ret_tp)      \
    PK_OPMODEL_OP3g_(op, op_sym, port_tp, tp, ret_tp, ret_tp) 


#define PK_OPMODEL_OP3gg_(op, op_sym, port_tp, tp, ret_tp1, ret_tp2)                                          \
                                                                                           \
template<int n, int W>                                                                                  \
ret_tp1 operator op (const pk_proxy_opmod< port_tp <W> >& a1, const tp##_aug<n>& a2)                    \
{                                                                                          \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                     \
  return ( a1.get() op static_cast<const tp<n>& >(a2) );                        \
}                                                                                          \
                                                                                           \
template<int n, int W> 																		   \
ret_tp2 operator op (const tp##_aug<n>& a1, const pk_proxy_opmod< port_tp <W> >& a2)            \
{                                                                                          \
 if( a2.enabled_opmodel() ) a2.opmodel_task( op_sym );                                     \
  return ( static_cast<const tp<n>& >(a1) op a2.get() );                                   \
}

#define PK_OPMODEL_OP3gg(op, op_sym, port_tp, tp, ret_tp)      \
    PK_OPMODEL_OP3gg_(op, op_sym, port_tp, tp, ret_tp, ret_tp) 




#define PK_OPMODEL_OP3h_DECL_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)                            \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp1 >& , const pk_proxy_opmod< port_tp2 >& );   \
ret_tp2 operator op ( const pk_proxy_opmod< port_tp2 >& , const pk_proxy_opmod< port_tp1 >& );

#define PK_OPMODEL_OP3h_DECL(op, op_sym, port_tp1, port_tp2, ret_tp)      \
   PK_OPMODEL_OP3h_DECL_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)


#define PK_OPMODEL_OP3h_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)              \
                                                                             \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp1 >& a1, const pk_proxy_opmod< port_tp2 >& a2 ) \
{                                                                                                 \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                            \
 return ( a1.get() op a2.get() );                                                                 \
}                                                                                                 \
                                                                                                  \
ret_tp2 operator op ( const pk_proxy_opmod< port_tp2 >& a1, const pk_proxy_opmod< port_tp1 >& a2 ) \
{                                                                                                 \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                            \
 return ( a1.get() op a2.get() );                                                                 \
}	
	
#define PK_OPMODEL_OP3h(op, op_sym, port_tp1, port_tp2, ret_tp)                \
       PK_OPMODEL_OP3h_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)




#define PK_OPMODEL_OP3i_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)                             \
template<int n>                                                                             \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp1 >& a1, const pk_proxy_opmod< port_tp2 <n> >& a2 ) \
{                                                                                                 \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                            \
 return ( a1.get() op a2.get() );                                                                 \
}                                                                                                 \
template<int n>                                                                                                  \
ret_tp2 operator op ( const pk_proxy_opmod< port_tp2 <n> >& a1, const pk_proxy_opmod< port_tp1 >& a2 )             \
{                                                                                                 \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                            \
 return ( a1.get() op a2.get() );                                                                 \
}	
	
#define PK_OPMODEL_OP3i(op, op_sym, port_tp1, port_tp2, ret_tp)                          \
           PK_OPMODEL_OP3i_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)


#define PK_OPMODEL_OP3ii_(op, op_sym, port_tp1, port_tp2, ret_tp1, ret_tp2)                             \
template<int n, int W>                                                                      \
ret_tp1 operator op ( const pk_proxy_opmod< port_tp1 <W> >& a1, const pk_proxy_opmod< port_tp2 <n> >& a2 ) \
{                                                                                                 \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                            \
 return ( a1.get() op a2.get() );                                                                 \
}                                                                                                 \
template<int n, int W>                                                                                                   \
ret_tp2 operator op ( const pk_proxy_opmod< port_tp2 <n> >& a1, const pk_proxy_opmod< port_tp1 <W> >& a2 )             \
{                                                                                                 \
 if( a1.enabled_opmodel() ) a1.opmodel_task( op_sym );                                            \
 return ( a1.get() op a2.get() );                                                                 \
}	
	
#define PK_OPMODEL_OP3ii(op, op_sym, port_tp1, port_tp2, ret_tp)                          \
           PK_OPMODEL_OP3ii_(op, op_sym, port_tp1, port_tp2, ret_tp, ret_tp)








#define PK_OPMODEL_OP5(tp)                    \
	                                          \
tp##_aug& operator ++ ( )                     \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('+');   \
 pk_base::compute_data();                     \
 sc_type::operator ++ ( );                    \
 return *this;                                \
}                                             \
                                              \
const tp operator ++ ( int)                   \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('+');   \
 pk_base::compute_data();                     \
 return sc_type::operator ++ ( 0 );           \
}                                             \
                                              \
tp##_aug& operator -- ( )                     \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('-');   \
 pk_base::compute_data();                     \
 sc_type::operator -- ( );                    \
 return *this;                                \
}                                             \
                                              \
const tp operator -- ( int)                   \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('-');   \
 pk_base::compute_data();                     \
 return sc_type::operator -- ( 0 );           \
} 


#define PK_OPMODEL_OP6(tp)                    \
	                                          \
tp##_aug<n>& operator ++ ( )                  \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('+');   \
 pk_base::compute_data();                     \
 sc_type::operator ++ ( );                    \
 return *this;                                \
}                                             \
                                              \
const tp <n> operator ++ ( int)              \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('+');   \
 pk_base::compute_data();                     \
 return sc_type::operator ++ ( 0 );           \
}                                             \
                                              \
tp##_aug<n>& operator -- ( )                  \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('-');   \
 pk_base::compute_data();                     \
 sc_type::operator -- ( );                    \
 return *this;                                \
}                                             \
                                              \
const tp <n> operator -- ( int)              \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('-');   \
 pk_base::compute_data();                     \
 return sc_type::operator -- ( 0 );           \
} 

#define PK_OPMODEL_OP6a                    \
	                                          \
cpptype_aug<T>& operator ++ ( )                  \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('+');   \
 ++cpp_type::value_;                         \
 pk_base::compute_data();                    \
 return *this;                                \
}                                             \
                                              \
const T operator ++ ( int)                    \
{                                             \
  T tmp = cpp_type::value_;                  \
  this->operator ++();                       \
  return tmp;                                \
}                                             \
                                              \
cpptype_aug<T>& operator -- ( )                  \
{                                             \
 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task('-');   \
  --cpp_type::value_;                         \
 pk_base::compute_data();                     \
 return *this;                                \
}                                             \
                                              \
const T operator -- ( int)                    \
{                                             \
 T tmp = cpp_type::value_;                    \
 this->operator --();                         \
 return tmp;                                  \
} 


#define PK_OPMODEL_OP7(op, tp, op_sym)                                          \
	template<class T> this_type_r operator op ( const cpptype_aug<T>& val )     \
    {                                                                           \
	 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task( op_sym );          \
	 pk_base::compute_data();                                                    \
     sc_type::operator op (val.operator const T&());                              \
     return *this;                                                                \
    }  


#define PK_OPMODEL_OP7a(op, op_sym, tp)                                         \
     this_type_r operator op ( const cpptype_aug< tp >& val )  \
    {                                                                           \
	 if( pk_base::enabled_opmodel() ) pk_base::opmodel_task( op_sym );          \
	 cpp_type::value_ op (val.operator const tp &());                             \
     pk_base::compute_data();                                                   \
     return *this;                                                              \
    }  


#endif
