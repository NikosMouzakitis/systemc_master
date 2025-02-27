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
51 Franklin Street, Fifth Floor, Boston, MA 02110+1301 USA.

************************************************************************/

/***********************************************************************


 Original Author: Giovanni B. Vece

 Affiliation: Università Politecnica delle Marche (Italy)


************************************************************************/

#include "PKtool/utils/pk_iostream.h"





// ----------------------------------------------------------------------------
//  CLASS : pk_istream
// ----------------------------------------------------------------------------


namespace pk_core
{

#define PK_ISTREAM_OP_IMPL(obj)                                               \
    cin>> obj ;                                                               \
    (*file)<< obj ;                                                           \
	return *this;                                                             

pk_istream& pk_istream::operator >> (short& n)
{
 PK_ISTREAM_OP_IMPL(n)
};

pk_istream& pk_istream::operator >> (int& n)
{
 PK_ISTREAM_OP_IMPL(n)
};

pk_istream& pk_istream::operator >> (long& n)
{
 PK_ISTREAM_OP_IMPL(n)
};


pk_istream& pk_istream::operator >> (float& f)
{
 PK_ISTREAM_OP_IMPL(f)
};

pk_istream& pk_istream::operator >> (double& f)
{
 PK_ISTREAM_OP_IMPL(f)
};

pk_istream& pk_istream::operator >> (long double& f)
{
 PK_ISTREAM_OP_IMPL(f)
};


pk_istream& pk_istream::operator >> (unsigned short& u)
{
 PK_ISTREAM_OP_IMPL(u)
};

pk_istream& pk_istream::operator >> (unsigned int& u)
{
 PK_ISTREAM_OP_IMPL(u)
};

pk_istream& pk_istream::operator >> (unsigned long& u)
{
 PK_ISTREAM_OP_IMPL(u)
};

pk_istream& pk_istream::operator >> (char& c)
{
 PK_ISTREAM_OP_IMPL(c)
};

pk_istream& pk_istream::operator >> (unsigned char& c)
{
 PK_ISTREAM_OP_IMPL(c)
};

pk_istream& pk_istream::operator >> (signed char& c)
{
 PK_ISTREAM_OP_IMPL(c)
};

pk_istream& pk_istream::operator >> (bool& b)
{
 PK_ISTREAM_OP_IMPL(b)
};

pk_istream& pk_istream::operator >> (void*& pv)
{
 PK_ISTREAM_OP_IMPL(pv)
};

pk_istream pk_cin;


// ----------------------------------------------------------------------------
//  CLASS : pk_ostream
// ----------------------------------------------------------------------------


#define PK_OSTREAM_OP_IMPL(obj)                                               \
    cout<< obj ;                                                              \
    (*file)<< obj ;                                                           \
	return *this;                                                             

pk_ostream& pk_ostream::operator << (short n)
{
 PK_OSTREAM_OP_IMPL(n)
};

pk_ostream& pk_ostream::operator << (int n)
{
 PK_OSTREAM_OP_IMPL(n)
};

pk_ostream& pk_ostream::operator << (long n)
{
 PK_OSTREAM_OP_IMPL(n)
};


pk_ostream& pk_ostream::operator << (float f)
{
 PK_OSTREAM_OP_IMPL(f)
};

pk_ostream& pk_ostream::operator << (double f)
{
 PK_OSTREAM_OP_IMPL(f)
};

pk_ostream& pk_ostream::operator << (long double f)
{
 PK_OSTREAM_OP_IMPL(f)
};


pk_ostream& pk_ostream::operator << (unsigned short u)
{
 PK_OSTREAM_OP_IMPL(u)
};

pk_ostream& pk_ostream::operator << (unsigned int u)
{
 PK_OSTREAM_OP_IMPL(u)
};

pk_ostream& pk_ostream::operator << (unsigned long u)
{
 PK_OSTREAM_OP_IMPL(u)
};

pk_ostream& pk_ostream::operator << (char c)
{
 PK_OSTREAM_OP_IMPL(c)
};

pk_ostream& pk_ostream::operator << (unsigned char c)
{
 PK_OSTREAM_OP_IMPL(c)
};

pk_ostream& pk_ostream::operator << (signed char c)
{
 PK_OSTREAM_OP_IMPL(c)
};

pk_ostream& pk_ostream::operator << (const char* pc)
{
 PK_OSTREAM_OP_IMPL(pc)
};

pk_ostream& pk_ostream::operator << (const unsigned char* pc)
{
 PK_OSTREAM_OP_IMPL(pc)
};

pk_ostream& pk_ostream::operator << (const signed char* pc)
{
 PK_OSTREAM_OP_IMPL(pc)
};

pk_ostream& pk_ostream::operator << (bool b)
{
 PK_OSTREAM_OP_IMPL(b)
};

pk_ostream& pk_ostream::operator << (const void* pv)
{
 PK_OSTREAM_OP_IMPL(pv)
};


pk_ostream& pk_ostream::operator << (b_ostr_pf pf)
{
 PK_OSTREAM_OP_IMPL(pf)
};

pk_ostream& pk_ostream::operator << (ios_b_pf pf)
{
 PK_OSTREAM_OP_IMPL(pf)
};

pk_ostream& pk_ostream::operator << (b_ios_pf pf)
{
 PK_OSTREAM_OP_IMPL(pf)
};

pk_ostream& pk_ostream::operator << (b_sb_pf pf)
{
 PK_OSTREAM_OP_IMPL(pf)
};



pk_ostream pk_cout;

};       // pk_core









