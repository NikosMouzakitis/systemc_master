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

#ifndef PK_AUG_BASE_H    
#define PK_AUG_BASE_H    


#include "PKtool/types_aug/pk_aug_data.h"
#include "PKtool/types_aug/pk_aug_if.h"
#include "PKtool/types_aug/pk_compute_comm_fcs.h"


namespace pk_core    
{


// ----------------------------------------------------------------------------
//  CLASS : pk_aug_base<T>
//
//  2nd level basic class for augmented signals. 
//  It contains the common routines depending on the value type (T) carried
//  by a signal.  
// ----------------------------------------------------------------------------
 


template<class T> class pk_aug_base: public pk_aug_if   
{

 friend class power_module_b;

 protected:

 pk_aug_base( aug_category at, const T* sgn_h = new T() ): 
       pk_aug_if(at), augdata_T(sgn_h)
 { augdata = &augdata_T; };
 


 inline void compute_data( )    
 {
  if(enabled)
  { augdata_T.compute_data( ); };
 };


 inline void update_data()                      
 {  augdata_T.compute_data();  };



 protected:
   
 pk_aug_data<T> augdata_T; 


 private:

 pk_aug_base(const pk_aug_base&);
 pk_aug_base& operator = (const pk_aug_base&);

};


}    // pk_core    


#endif
