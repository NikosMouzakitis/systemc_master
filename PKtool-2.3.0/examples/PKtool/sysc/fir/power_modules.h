/***********************************************************************

Copyright (C) 2004 - 2011 by Giovanni B. Vece

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


 Original Authors: Raffaele Pedale, Maria Celeste Rago and Giovanni B. Vece

 Affiliation: Università Politecnica delle Marche (Italy)


************************************************************************/



#ifndef POWER_MODULES_H
#define POWER_MODULES_H

// The PKtool header is already included in the file fir.h

#include "fir.h"
#include "fir_data.h"


// uncomment this macro for enabling the fsm-based FIR version

//#define PK_FIR_RTL



#ifndef PK_FIR_RTL


POWER_MODULE_CLASS( fir )
{


  
 PK_USES_ENERGY_MODELS      

 														      
 
 
 POWER_MODULE_CTOR(fir)							
 {  
  
  PK_MODULE_SENSITIVITY 
  sensitive<<CLK.pos();
	    
 };

};


#else


POWER_MODULE_CLASS( fir_data )
{
	

  
 PK_USES_ENERGY_MODELS      

 
 POWER_MODULE_CTOR(fir_data)							
 {  
  
	    
 };

};


#endif


#endif

