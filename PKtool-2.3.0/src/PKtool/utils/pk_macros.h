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

#ifndef PK_MACROS
#define PK_MACROS




#define PK_ENERGY_MODEL_LIB( name)                          \
          namespace name                                    \
		  {                                                 \
           inline const pk_est_type  estimation_type() \
             {return pk_est_type(pk_energy); };           \
                                                              \
                                                              \
		   typedef energy_power_model  lib_power_model;      \
		                                                    \
                                                             \
           template<int n> class pk_power_model_tag         \
		   {public:                                         \
            class nothing_cl{};                             \
			typedef nothing_cl pk_creator_name;             \
		   };                                              \
                                                             \
                                                           \
		 template<int n> inline void  pk_creator_fc() {};   \
	 };                                                     \
		                                                    \
	                                                        \
		  namespace name 


#define PK_COMM_MODEL_LIB( name)                            \
          namespace name                                    \
		  {                                                 \
            inline pk_est_type  estimation_type()    \
            {return pk_est_type(pk_comm); };    \
			                                                \
           template<int n> class pk_power_model_tag         \
		   {};                                              \
		                                                    \
           typedef comm_power_model  lib_power_model;      \
		                                                    \
        template<int n> inline void  pk_creator_fc() {};    \
      };                                                  \
                                                            \
                                                            \
		                                                    \
		  namespace name       

#define PK_MODEL_LIB(name)    namespace name

#define PK_USED_ENERGY_LIB( library )         \
                                              \
 namespace library                            \
 { }                                          \
	                                      \
 namespace pk_used_energy_lib = library;



#define PK_USED_COMM_LIB( library )            \
                                               \
 namespace library                             \
 { }                                           \
                                               \
 namespace pk_used_comm_lib = library;


#define PK_MODEL_BASE_COMMON(nm,index)                                       \
                                                                           \
  class pk_##nm##_model;                                                              \
  class pk_##nm##_creator;                                               \
                                                                           \
  template<> class pk_power_model_tag< index >                             \
  {                                                                        \
   public:                                                                 \
                                                                           \
   typedef pk_##nm##_model  pk_pm_name;                                    \
                                                                           \
  };                                                                       \
                                                                           \
  typedef pk_##nm##_model pk_model##index ;  


/*
#define PK_MODEL_BASE(nm,index)                                       \
                                                                           \
  class pk_##nm##_model;                                                              \
  class pk_##nm##_creator;                                               \
                                                                           \
  template<> class pk_power_model_tag< index >                             \
  {                                                                        \
   public:                                                                 \
                                                                           \
   typedef pk_##nm##_model  pk_pm_name;                                    \
                                                                           \
  };                                                                       \
                                                                           \
  typedef pk_##nm##_model pk_model##index ;                                \
                                                                           \
                                                                           \
                                                                           \
	                                                                       \
                                                                           \
 class pk_##nm##_model_b:public lib_power_model                            \
 {                                                                         \
  public:                                                                  \
                                                                           \
  const unsigned numeric_id() const                                             \
  { return index ;};                                                        \
                                                                           \
  const char* name() const                                                 \
  { return #nm ;};                                                       \
                                                                           \
  pk_##nm##_model_b(pk_core::pk_kernel_impl& p): lib_power_model(p)        \
  {};                                                                      \
 };                                                                       \
                                                                          \
 */

#define PK_MODEL_BASE(nm,index)                                       \
 PK_MODEL_BASE_COMMON(nm,index)                                          \
 class pk_##nm##_model_b:public lib_power_model                            \
 {                                                                         \
  public:                                                                  \
                                                                           \
  const unsigned numeric_id() const                                             \
  { return index ;};                                                        \
                                                                           \
  const char* name() const                                                 \
  { return #nm ;};                                                       \
                                                                           \
  pk_##nm##_model_b(pk_core::pk_kernel_impl& p): lib_power_model(p)        \
  {};                                                                      \
 };    


#define PK_TLM_MODEL_BASE(nm,index)                                       \
 PK_MODEL_BASE_COMMON(nm,index)                                           \
 class pk_##nm##_model_b: public pk_tlm::tlm_power_model_b                 \
 {                                                                         \
  public:                                                                  \
                                                                           \
  const unsigned numeric_id() const                                             \
  { return index ;};                                                        \
                                                                           \
  const char* name() const                                                 \
  { return #nm ;};                                                       \
                                                                          \
  virtual double do_TLM_estimationation                                  \
      (tlm::tlm_generic_payload* gp=0, sc_core::sc_time* t=0)             \
   {return 0;};                                                          \
                                                                          \
                                                                          \
  pk_##nm##_model_b(pk_core::pk_kernel_impl& p): tlm_power_model_b(p)     \
  { };                                                                    \
 }; 


#define PK_MODEL_BEGIN( nm,index )                                   \
                                                                     \
        PK_MODEL_BASE(nm, index )                                    \
        class pk_##nm##_model : public pk_##nm##_model_b 


#define PK_TLM_MODEL_BEGIN( nm,index )                               \
                                                                     \
        PK_TLM_MODEL_BASE(nm, index )                                \
        class pk_##nm##_model : public pk_##nm##_model_b 



#define PK_CYCLE_ACCURATE                                           \
  private:                                                          \
  power_model_b::set_cycle_acc  sca_obj;                            \
                                                                    \
  public:




#define PK_SET_AUGDATA( dt )  set_augdata_( dt );

#define PK_SET_BITVAL    PK_SET_AUGDATA( pk_core::pk_aug_if::bit_values )
#define PK_SET_BITCOMM    PK_SET_AUGDATA( pk_core::pk_aug_if::bit_comm )
#define PK_SET_TOTALCOMM    PK_SET_AUGDATA( pk_core::pk_aug_if::total_comm )
#define PK_SET_ONETIMES    PK_SET_AUGDATA( pk_core::pk_aug_if::bit_onetimes )
#define PK_SET_BITPROB    PK_SET_AUGDATA( pk_core::pk_aug_if::bit_prob )
#define PK_SET_OP_DATA    PK_SET_AUGDATA( pk_core::pk_aug_if::operator_data )





#ifndef PKTOOL_H

#define PK_MODEL_END( nm,index )                                           \
class pk_##nm##_creator: public pk_core::pk_model_creator, public pk_lib_model_creator  \
{                                                                          \
                                                                           \
   friend class pk_core::pk_read_cfg_data;                                 \
   friend class pk_core::power_kernel;                                     \
   friend class pk_##nm##_model;                                           \
                                                                           \
   public:                                                                 \
                                                                           \
   pk_##nm##_creator(): pk_core::pk_model_creator( &model_library )        \
   {                                                                       \
	reg.declare_creator( this, index, &(model_library()) );                \
   };                                                                      \
                                                                           \
  inline  pk_core::power_model_b* create(pk_core::pk_kernel_impl& p) const  \
   { return new pk_##nm##_model(p); };                                      \
  ~pk_##nm##_creator(){};                                                  \
                                                                           \
                                                                           \
 };                                                                        \
                                                                           \
 static pk_##nm##_creator pk_##nm##_creator_ob;                           


#define PK_TLM_MODEL_END( nm,index )                                           \
class pk_##nm##_creator: public pk_core::pk_model_creator, public pk_lib_model_creator  \
{                                                                          \
                                                                           \
   friend class pk_core::pk_read_cfg_data;                                 \
   friend class pk_core::power_kernel;                                     \
   friend class pk_##nm##_model;                                           \
                                                                           \
   public:                                                                 \
                                                                           \
   pk_##nm##_creator(): pk_core::pk_model_creator( &model_library )        \
   {                                                                       \
	reg.declare_TLM_creator( this, index, &(model_library()) );            \
   };                                                                      \
                                                                           \
  inline  pk_core::power_model_b* create(pk_core::pk_kernel_impl& p) const  \
   { return new pk_##nm##_model(p); };                                      \
  ~pk_##nm##_creator(){};                                                  \
                                                                           \
                                                                           \
 };                                                                        \
                                                                           \
 static pk_##nm##_creator pk_##nm##_creator_ob; 



#else


#define PK_MODEL_END( nm,index )

#define PK_TLM_MODEL_END( nm,index )


#endif



#define PK_SET_DATA_FROM_WINDOW( string, param )                                   \
{                                                                                  \
 pk_core::read_data_from_window                                        \
   ( #string,  param, pk_core::pk_cout,pk_core::pk_cin );  \
}                                                                                  



#define PK_SET_ARRAY_FROM_WINDOW( string, param, sz )                           \
 {                                                                              \
  pk_core::read_array_from_window( #string,  param , sz );          \
 }


#define PK_SET_DATA_FROM_FILE( param )                                          \
  do infile>>tmp_ch;                                                        \
  while(tmp_ch != '=');                                                       \
  infile>> param;



#define PK_SET_ARRAY_FROM_FILE( array, sz )                                \
 {                                                                         \
  pk_core::read_array_from_file( array, sz );                  \
 }


#define PK_SET_SINGLE_MODEL_DATA( string, param )                                    \
  if(pk_core::reading_option == 1) PK_SET_DATA_FROM_WINDOW( string, param )   \
  else { PK_SET_DATA_FROM_FILE( param ) } 

#define PK_SET_ARRAY_MODEL_DATA( string, array, size )                                           \
  if(pk_core::reading_option == 1) PK_SET_ARRAY_FROM_WINDOW( string, array, size )   \
  else  PK_SET_ARRAY_FROM_FILE( array, size )  


#define PK_MODEL_CTOR(name)  pk_##name##_model( pk_core::pk_kernel_impl& p): pk_##name##_model_b ( p)
#define PK_MODEL_DTOR(name)  ~pk_##name##_model()

                   
                                                                                 \


                                                                                        \


#endif
