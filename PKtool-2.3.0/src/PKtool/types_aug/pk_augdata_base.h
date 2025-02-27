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

#ifndef PK_AUGDATA_BASE_H
#define PK_AUGDATA_BASE_H


#include <iostream>
#include <cmath>

using std::cout;  
using std::cin;
using std::endl;

#include "PKtool/types_aug/pk_aug_if.h"


namespace pk_core    
{

// forward declarations   

class pk_aug_if;
template<class T> class pk_aug_base;
template<class T> class pk_internal_sgn;
template<class T> class sc_in_aug;   
template<class T> class sc_inout_aug;
template<class T> class sc_out_aug;
template<class T> class pk_augdata_T;
template<class T> class pk_aug_data;
class sc_in_resolved_aug;
class sc_inout_resolved_aug;
class sc_out_resolved_aug;
class power_kernel;   
class pk_kernel_impl;


// ----------------------------------------------------------------------------
//  CLASS : pk_augdata_base  
// ----------------------------------------------------------------------------


class pk_augdata_base
{ 

 friend class pk_aug_if;
 template<class T> friend class pk_aug_base;
 template<class T> friend class pk_internal_sgn;
 template<class T> friend class pk_aug_data;
 template<class T> friend class pk_augdata_T;

 template<class T> friend class sc_in_aug;
 template<class T> friend class sc_inout_aug;
 template<class T> friend class sc_out_aug;
 friend class sc_in_resolved_aug;
 friend class sc_out_resolved_aug;
 friend class sc_inout_resolved_aug;
 
 friend class power_kernel;
 friend class pk_kernel_impl;

 typedef pk_aug_if::aug_data aug_data_;


 public:

 
 explicit  pk_augdata_base(int size = -1): 
             dyn_alloc(false), bitcomm_on(false), bitvals_on(false),
			 totcomm_on(false), onetms_on(false) 
 {
  if(size > 0)
  {
   dyn_alloc = true;
   bit_size = size;

   bit_values = new bool[bit_size];  
   bit_comms = new unsigned[bit_size];
   bit_onetimes = new double[bit_size];

   initialize();
  }
 };  

 ~pk_augdata_base()
 {
  if(dyn_alloc)
  {
   delete[] bit_values;  
   delete[] bit_comms;
   delete[] bit_onetimes;
  }
 
 }


 inline unsigned size( ) const
 { return bit_size; }
 
 
 inline unsigned bit_comm(unsigned pos) const
 { 
  if( pos >= bit_size)
  {  
   std::cout<<"ERROR"<<endl;  // to be completed
   exit(1);
  }  
  else return bit_comms[pos]; 
 }

 
 inline bool bit_value(unsigned pos)  //temporary implementation
 { 
  if( (pos < 0) || (pos >= bit_size) )
  {
   cout<<"ERROR"<<endl;    // to be completed
   exit(1);
  }
  return bit_values[pos]; 
 }
 

 inline
 const unsigned total_comm() const
 {    return total_comm_;  };

 virtual double bit_onetime(unsigned pos) = 0;

 inline double bit_probability (unsigned pos, double time_range) 
 { return bit_onetime(pos)/time_range;}

inline double bitcomm_density (unsigned pos, double time_range)   
 { return double(bit_comms[pos])/time_range;}

 
 inline      
 void enable_augdata( aug_data_ ad)     
 { 
  switch(ad)
  {
   case pk_aug_if::bit_comm:
     bitcomm_on = true;
   break;
   case pk_aug_if::bit_values:
     bitvals_on = true;
   break;
   case pk_aug_if::total_comm:
	 totcomm_on = true;
   break;
   case pk_aug_if::bit_onetimes:
     onetms_on = true;
   break;
   case pk_aug_if::bit_prob:
     onetms_on = true;
   break;
   default:
   ;
  }
 }   

       
  inline  void disable_augdata( )     
 {  bitcomm_on = bitvals_on = totcomm_on = onetms_on = false;  }   



 private:

 inline void initialize()
 {
  for(unsigned i=0; i<bit_size; ++i)
  {
   bit_values[i] = false;
   bit_comms[i] = 0;
   bit_onetimes[i] = 0;
  }
  total_comm_ = 0;
 };


 inline void reset_comm()
 {  total_comm_ = 0;   };

 virtual void reset_ontimes() = 0;


 void reset_data()
 {
  if(totcomm_on || bitcomm_on) reset_comm();
  if(onetms_on) reset_ontimes();  
 }

 
 unsigned bit_size;     // bit size of the signal
 bool* bit_values;      // current values of the single bits
 unsigned* bit_comms;   // bit-level commutations occurred from the beginning 
                        // of the simulation or a power state

 double* bit_onetimes;
 unsigned total_comm_;  // total commutations occurred from the beginning 
                        // of the simulation or a power state
 
 
 // unsigned state_comm;  // commutations occurred from the beginning of the simulation
                       // or a power state

 bool dyn_alloc;
 bool bitcomm_on, bitvals_on, totcomm_on, onetms_on;  

}; 


}  //pk_core  


#endif
