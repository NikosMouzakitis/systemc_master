/***********************************************************************

Copyright (C) 2004 - 2009 by Giovanni B. Vece

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

#ifndef PK_REPORT_IDS_H
#define PK_REPORT_IDS_H




#ifndef PK_DEFINE_MESSAGE

#define PK_DEFINE_MESSAGE(id,unused1,unused2) \
    extern const char id [] ; 

#endif

PK_DEFINE_MESSAGE(PK_NON_ALLOWED_OBJECT_INSTANCED_, 101, "?non allowed? object instanced") 


PK_DEFINE_MESSAGE(PK_BADLY_DEFINED_POWER_MODEL_, 201, "badly defined power model")

PK_DEFINE_MESSAGE(PK_MODEL_MISMATCH_IN_DYNDATA_FC_, 302, "power model mismatch in dynamic data function") 

PK_DEFINE_MESSAGE(PK_NO_DATA_IN_CFG_FILE_, 502, "no data reported in the configuration file") 
PK_DEFINE_MESSAGE(PK_WRONG_VALUE_SELECTED_, 503, "wrong value selected")
PK_DEFINE_MESSAGE(PK_WRONG_VALUE_INSERTED_, 504, "wrong value inserted")
PK_DEFINE_MESSAGE(PK_CORRUPTED_CFG_FILE_, 505, "the configuration file is corrupted")
PK_DEFINE_MESSAGE(PK_WRONG_SETTING_IN_FILE, 506, "wrong setting in the configuration file")
PK_DEFINE_MESSAGE(PK_UNDEFINED_STATE_FC_, 515, "undefined state function") 

// to be completed in the next versions





#endif
