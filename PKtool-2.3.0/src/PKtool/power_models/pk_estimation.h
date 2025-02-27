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


#ifndef PK_ESTIMATION_H
#define PK_ESTIMATION_H


#include "PKtool/power_models/pk_estimation_type.h"

namespace pk_core    
{

struct pk_initializer;
class power_module_b;


// ----------------------------------------------------------------------------
//  CLASS : pk_set_estype_b
// ----------------------------------------------------------------------------



class pk_set_estype_b
{
 friend struct pk_initializer;
 friend class power_module_b;

 protected:

 pk_set_estype_b(const pk_est_type = pk_no_estype);  


};


// ----------------------------------------------------------------------------
//  CLASS : pk_set_estype
// ----------------------------------------------------------------------------



template<class T> struct pk_set_estype 
{ };



template<> struct pk_set_estype<pk_energy_type>: public pk_set_estype_b
{
 pk_set_estype(): pk_set_estype_b(pk_energy)
 {};

};



template<> struct pk_set_estype<pk_comm_type>: public pk_set_estype_b
{
 pk_set_estype(): pk_set_estype_b(pk_comm)
 {};

};





// ----------------------------------------------------------------------------
//  CLASS : pk_estimation
// ----------------------------------------------------------------------------


class pk_estimation
{
 public:

 friend ostream& operator<<(ostream&,const pk_estimation&);  

 pk_estimation(pk_est_type et=pk_no_estype)
 { set_type( et);  };


 const char*  type_name()  const
 {return pvalue->type_name(); };

 const char*  unit_name() const
 {return pvalue->unit_name(); };

 const char*  symbol_name() const 
 {return pvalue->symbol_name(); };

 bool is_rate_defined()
 { return pvalue->is_rate_defined();};

 const char*  rate_type_name()  const 
 {return pvalue->rate_type_name(); };

 const char*  rate_unit_name() const 
 {return pvalue->rate_unit_name(); };

 const char*  rate_symbol_name() const 
 {return pvalue->rate_symbol_name(); };


 ostream& print_estim(ostream& os) const
 {  return pvalue->print_estim(os);};
 
 pk_estimation_type& value() const
 { return *pvalue;   };

 double rate_value(double time_gap)  const  
 { return pvalue->rate_value(time_gap);   };

 pk_estimation& operator=(const pk_estimation&);

 pk_estimation& operator+=( const pk_estimation&);

 template<typename T> pk_estimation& operator+=( const T v )
 {  
  pvalue->add( v );
  return *this;
 }


 void set_type(const pk_est_type et);    

 pk_estimation_type* pvalue;

};

ostream& operator<<(ostream&,const pk_estimation&); 



}  //pk_core  



#endif
