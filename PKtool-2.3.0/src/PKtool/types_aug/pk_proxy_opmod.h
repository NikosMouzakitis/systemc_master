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

#ifndef PK_PROXY_OPMOD_H   
#define PK_PROXY_OPMOD_H

#include "PKtool/kernel/pk_settings.h" 

namespace pk_default_energy_lib
{
 struct pk_opmodel_b;
}


template<typename T> class pk_proxy_opmod: public T
{
 public:

 typedef pk_default_energy_lib::pk_opmodel_b pk_opmodel;

 pk_proxy_opmod() : opmodel(0)
 { };

 void set(const T& t)
 { *static_cast< T* >(this) = t; }

 const T& get( ) const
 { return *this; };

 void set_opm(pk_opmodel* op)  
 { opmodel = op; } 

 inline void opmodel_task(const char c) const
 { opmodel->op_task(c);  }

 inline bool enabled_opmodel() const
 { return ( (opmodel != 0) ? true : false );  }

 pk_opmodel* opmodel;

};



// specializations for C++ native types

#define PK_PROXY_OPM_SPEC( tp )                  \
                                                 \
template< > class pk_proxy_opmod< tp >           \
{                                                \
 public:                                         \
												 \
 pk_proxy_opmod(): r(0), opmodel(0)				 \
 { };                                            \
												 \
 void set(const tp &t)							 \
 { r = &t; }								     \
                                                 \
 const tp& get( ) const                          \
 { return *r; };                                 \
                                                 \
                                                 \
void set_opm(pk_default_energy_lib::pk_opmodel_b* op)  \
 { opmodel = op; }                               \
                                                 \
 operator const tp& () const                     \
 { return *r;}                                   \
                                                 \
 inline bool enabled_opmodel() const             \
 { return ( (opmodel != 0) ? true : false );  }  \
                                                 \
 inline void opmodel_task(const char c) const    \
 { opmodel->op_task(c);  }                       \
                                                 \
 private:                                        \
                                                 \
 const tp *r;                                    \
 pk_default_energy_lib::pk_opmodel_b* opmodel;   \
                                                 \
};                                               \
                                                 \
                                                 \
                                                \



PK_PROXY_OPM_SPEC( int )
PK_PROXY_OPM_SPEC( short )
PK_PROXY_OPM_SPEC( long )
PK_PROXY_OPM_SPEC( unsigned )
PK_PROXY_OPM_SPEC( float )
PK_PROXY_OPM_SPEC( double )









#endif

