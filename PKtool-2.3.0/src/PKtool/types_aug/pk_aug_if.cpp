
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


#include "PKtool/types_aug/pk_aug_if.h"

namespace  pk_core      
{

void pk_clear_aug_vector(vector<pk_aug_if*>& vec)    
 {
  unsigned sz = vec.size();
  for(unsigned i=0; i<sz; ++i) vec[i]=0;
  vec.clear();
 };


// ----------------------------------------------------------------------------
//  CLASS : pk_aug_if
// ----------------------------------------------------------------------------



vector<pk_aug_if*> pk_aug_if::intsignal_aug(0);
vector<pk_aug_if*> pk_aug_if::inoutport_aug(0);
vector<pk_aug_if*> pk_aug_if::inport_aug(0);
vector<pk_aug_if*> pk_aug_if::outport_aug(0);


pk_aug_if::pk_aug_if(aug_category at): sgn_category(at), enabled(false), augdata(0)
 {  
	#ifdef PK_ENABLE_OPMODELS
    opmodel = 0;
    #endif
 };

}  // pk_core    
