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

#ifndef POWER_MODULE_FCS
#define POWER_MODULE_FCS


namespace pk_core    
{

class power_kernel;
class power_module_b;
class power_model_b;


// ----------------------------------------------------------------------------
//  CLASS : pk_state_fc
// ----------------------------------------------------------------------------


class pk_state_fc
{
 friend class pk_kernel_impl;

   protected:
   
   pk_state_fc(int st);

   virtual unsigned state_fc() = 0;

   power_kernel* pk_h ;
   power_module_b* powmod_h ;

   private:


   //disabled

   pk_state_fc( const pk_state_fc& );
   pk_state_fc& operator = ( const pk_state_fc& );

};



// ----------------------------------------------------------------------------
//  CLASS : pk_dyndata_fc
// ----------------------------------------------------------------------------

class pk_dyndata_fc
{
 friend class pk_kernel_impl;

   protected:

   pk_dyndata_fc(int st);

   virtual void pk_mod_fnc() = 0;

   power_model_b* power_model() const ;
 

   power_kernel* pk_h; 
   power_module_b* powmod_h ;

   private:

   //disabled

   pk_dyndata_fc( const pk_dyndata_fc& );
   pk_dyndata_fc& operator = ( const pk_dyndata_fc& );
};



}  //pk_core  








#endif
