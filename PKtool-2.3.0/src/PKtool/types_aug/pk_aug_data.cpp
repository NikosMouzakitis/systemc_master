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





#define SC_INCLUDE_FX


#include "systemc"
#include "PKtool/kernel/pk_settings.h"

namespace pk_core    
{

using sc_dt::sc_fix;

void pk_bitarray_conv_fc(const float& value, bool* bit_rep, const int size)
{  
 sc_dt::sc_fix tmp(value, size, PK_FLOAT_INTEGER_BITS); 
 for(int i=0; i<size; ++i)
	bit_rep[i] = ( (tmp[i]) ? true : false ) ;
};


void pk_bitarray_conv_fc(const double& value, bool* bit_rep, const int size)
{  
 sc_dt::sc_fix tmp(value, size, PK_DOUBLE_INTEGER_BITS); 
 for(int i=0; i<size; ++i)
	 bit_rep[i] = ( (tmp[i]) ? true : false ) ;
};
 

}  //pk_core  

