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

#ifndef PK_ESTIMATION_TYPE_H
#define PK_ESTIMATION_TYPE_H

#include<iostream>
#include <cstdlib>
using std::cout;
using std::endl;
using std::ostream;


namespace pk_core    
{


class pk_estimation_type;
class pk_estimation;
class power_module_b;
class pk_model_lib_handler;



// ----------------------------------------------------------------------------
//  ENUM : pk_est_type
// ----------------------------------------------------------------------------

enum pk_est_type{pk_no_estype=0, pk_energy, pk_comm};

extern const char* pk_est_type_name[];



// ----------------------------------------------------------------------------
//  CLASS : pk_estimation_type
// ----------------------------------------------------------------------------


class pk_estimation_type
{
 friend class pk_estimation;
 friend class power_module_b;
 friend class pk_model_lib_handler;

 protected:
 
 virtual const char*  type_name()  const =0;
 virtual const char*  unit_name() const =0; 
 virtual const char*  symbol_name()const =0; 
 virtual const pk_est_type  est_type() const =0;

 virtual bool is_rate_defined() const=0;

 virtual const char*  rate_type_name()  const
 {return " ";};
 virtual const char*  rate_unit_name() const 
 {return " ";}; 
 virtual const char*  rate_symbol_name()const 
 {return " ";};

 virtual double rate_value( double time_gap)
 {  return 0; }

 virtual void assign(const pk_estimation_type&)=0;
 virtual void add(const pk_estimation_type&)=0;
 virtual void add(double) 
 { };
 virtual ostream& print_estim(ostream&)=0;

};


// ----------------------------------------------------------------------------
//  CLASS : pk_energy_type
// ----------------------------------------------------------------------------

class pk_energy_type: public pk_estimation_type
{
 friend class pk_estimation;
 
 public:
 

 pk_energy_type():  type("energy"), unit("Joule"), symbol("J"), 
		                  rate_type("power"), rate_unit("Watt"), rate_symbol("W"), 
		                  est(0)
 {};

 public:

 typedef  double estimation_type;
 typedef pk_energy_type this_type;

 bool is_rate_defined()  const
 {return true;};
 
 
 void set(const estimation_type& e)   
 {est=e;};
 

 void assign(const pk_estimation_type& et)
 {
  const this_type* tmp= dynamic_cast<const this_type*>(&et);
  if(!tmp)
  {
   cout<<"ERROR: output type mismatching"<<endl;
   exit(1);
  };
  
  set(tmp->est);
 }
 
 void add(const pk_estimation_type& et)
 {
  const this_type* tmp= dynamic_cast<const this_type*>(&et);
  if(!tmp)
  {
   cout<<"ERROR: output type mismatching"<<endl;
   exit(1);
  };
  est += tmp->est;
 }

 void add(double v)
 { est += v; }

 ostream& print_estim(ostream& os)
 {
  os<<est;
  return os;
 };

 const char* type_name() const
 { return type;};  

 const char* unit_name() const
 { return unit;};

 const char* symbol_name() const
 { return symbol;}; 



 const char* rate_type_name() const
 { return rate_type;}; 

 const char* rate_unit_name() const
 { return rate_unit;}; 

 const char* rate_symbol_name() const
 { return rate_symbol;}; 

 double rate_value( double time_gap)
 {  return est/time_gap; }



 inline const pk_est_type  est_type() const
 {  return pk_energy; }

 inline const estimation_type  value() const
 {  return est; }



 private:
 const char *type, *unit, *symbol;
 const char *rate_type, *rate_unit, *rate_symbol;

 estimation_type est;
};

// ----------------------------------------------------------------------------
//  CLASS : pk_comm_type
// ----------------------------------------------------------------------------

class pk_comm_type: public pk_estimation_type
{
 public:
 pk_comm_type():  type("commutation"), unit(" "), symbol(" "), 
		                  rate_type("commutation rate"), rate_unit("Hertz"), rate_symbol("Hz"), 
		                  est(0)
 {};

 typedef  double estimation_type;
 typedef pk_comm_type this_type;

 bool is_rate_defined()  const
 {return true;};
 
 
 void set(const estimation_type& e)   
 {est=e;};
 

 void assign(const pk_estimation_type& et)
 {
  const this_type* tmp= dynamic_cast<const this_type*>(&et);
  if(!tmp)
  {
   cout<<"ERROR: output type mismatching"<<endl;
   exit(1);
  };
  set(tmp->est);
 }
 
 void add(const pk_estimation_type& et)
 {
  const this_type* tmp= dynamic_cast<const this_type*>(&et);
  if(!tmp)
  {
   cout<<"ERROR: output type mismatching"<<endl;
   exit(1);
  };
  est+=tmp->est;
 }

 ostream& print_estim(ostream& os)
 {
  os<<est;
  return os;
 };


 pk_comm_type& operator=(const estimation_type& e)
 {  
  this->set(e);
  return *this;
 };


 const char* type_name() const
 { return type;}; 

 const char* unit_name() const
 { return unit;}; 

 const char* symbol_name() const
 { return symbol;}; 



 const char* rate_type_name() const
 { return rate_type;}; 

 const char* rate_unit_name() const
 { return rate_unit;}; 

 const char* rate_symbol_name() const
 { return rate_symbol;}; 

 double rate_value( double time_gap)
 {  return double(est)/time_gap; }


 const pk_est_type  est_type() const
 {  return pk_comm; }

 private:
 const char *type, *unit, *symbol;
 const char *rate_type, *rate_unit, *rate_symbol;

 estimation_type est;
};


}  //pk_core  


#endif
