/***********************************************************************

Copyright (C) 2007 - 2011 by Giovanni B. Vece

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


 Original Author: Pedale Raffaele, Maria Celeste Rago

 Affiliation: Università Politecnica delle Marche (Italy)


************************************************************************/




#ifndef POWER_MODULES
#define POWER_MODULES


#include "stage1.h"
#include "stage2.h"
#include "stage3.h"
#include "PKtool.h"



// ----------------------------------------------------------------------------
//  CLASS : POWER_MODULE_CLASS( stage1 )
//
//  power_module associated to stage1 sc_module
// -----------------------------------------------------------------------------

POWER_MODULE_CLASS( stage1 )			
{
 
  PK_USES_COMMUTATION_MODELS 

  POWER_MODULE_CTOR(stage1)				
 {   
	  
		PK_INPORT_SENSITIVITY
		sensitive << clk.pos();
 };

};


// ----------------------------------------------------------------------------
//  CLASS : POWER_MODULE_CLASS( stage2 )
//
//  power_module associated to stage2 sc_module
// -----------------------------------------------------------------------------


POWER_MODULE_CLASS( stage2 )
{
 
 
 PK_USES_COMMUTATION_MODELS 
  
 
 POWER_MODULE_CTOR(stage2)			
 {   
	    
		PK_INPORT_SENSITIVITY
		sensitive << clk.pos();
 };

};


// ----------------------------------------------------------------------------
//  CLASS : POWER_MODULE_CLASS( stage3 )
//
//  power_module associated to stage3 sc_module
// -----------------------------------------------------------------------------


POWER_MODULE_CLASS( stage3 )
{


 PK_USES_COMMUTATION_MODELS 
 
 POWER_MODULE_CTOR(stage3)		
 {   
	     
		PK_INPORT_SENSITIVITY
		sensitive<<clk.pos();    
 };

};

#endif

