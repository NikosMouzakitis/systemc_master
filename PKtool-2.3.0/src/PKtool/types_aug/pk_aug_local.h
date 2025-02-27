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

#ifndef PK_AUG_LOCAL_
#define PK_AUG_LOCAL_

#include <list>
#include "PKtool/types_aug/pk_augdata_base.h"  

#ifdef PK_ENABLE_OPMODELS


namespace pk_default_energy_lib
{
 struct pk_opmodel_b;
}

#endif


namespace pk_core
{

 class pk_aug_if;

// ----------------------------------------------------------------------------
//  STRUCT : pk_aug_local    
// ----------------------------------------------------------------------------


 struct pk_aug_local
 {

  pk_aug_local(bool en_sgn = false, bool en_totcomm = false, int tot_comm = 0):
     enabled_signals(en_sgn), enabled_totcomm(en_totcomm), partial_comm(tot_comm)
     #ifdef PK_ENABLE_OPMODELS  
		 ,opm(0)  
     #endif
  {};

  inline void set_(bool en_sgn = false, bool en_totcomm = false, int tot_comm = 0)
  { enabled_signals = en_sgn; enabled_totcomm = en_totcomm; partial_comm = tot_comm; }

  inline int total_comm()
  {
   int tot_comm = partial_comm;
   std::list<pk_aug_if*>::iterator it = localsign_aug.begin();
   while( it != localsign_aug.end() )
   {
    tot_comm += (*it)->data().total_comm();
    ++it;
   }
   return tot_comm;
  }

  bool enabled_signals, enabled_totcomm;
  std::list<pk_aug_if*> localsign_aug;
  int partial_comm;

  #ifdef PK_ENABLE_OPMODELS
  
  pk_default_energy_lib::pk_opmodel_b* opm;

  #endif

 };

}

#endif

