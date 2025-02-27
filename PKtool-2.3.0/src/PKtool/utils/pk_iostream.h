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

#ifndef PK_IOSTREAM
#define PK_IOSTREAM
#include <iostream>
#include <fstream> 




using std::istream;
using std::ostream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;




namespace pk_core
{

// ----------------------------------------------------------------------------
//  CLASS : pk_istream
// ----------------------------------------------------------------------------

class pk_istream
{
 public:

 pk_istream(): file(0)
 {
 };

 pk_istream& operator >> (short&);
 pk_istream& operator >> (int&);
 pk_istream& operator >> (long&);

 pk_istream& operator >> (unsigned short&);
 pk_istream& operator >> (unsigned int&);
 pk_istream& operator >> (unsigned long&);

 pk_istream& operator >> (float&);
 pk_istream& operator >> (double&);
 pk_istream& operator >> (long double&);

 pk_istream& operator >> (char&);
 pk_istream& operator >> (unsigned char&);
 pk_istream& operator >> (signed char&);

 pk_istream& operator >> (bool&);
 pk_istream& operator >> (void*&);

 void link(ofstream& f)
 {
  file = &f;
 };
 

 operator  istream&() const
 { 
  return cin;
 };
 

 private:


 template<class T> class check_value_cl   
 {
  public:

  typedef void (*check_fc) (const T&);

  check_value_cl()
  {};

  void check_value(const T& val)
  {  if(fc) fc(val);  };

  void check_value_fc (check_fc f)
  { fc = f; };

  check_fc fc;

 };

 template<class T> void check_value(const T&)
 {
  check_value_cl<T> obj;
 
 }




 ofstream* file;
 
 //disabled

 pk_istream(const pk_istream&);
 pk_istream& operator = (const pk_istream&);
 
};


// ----------------------------------------------------------------------------
//  CLASS : pk_ostream
// ----------------------------------------------------------------------------

class pk_ostream
{
 public:

 typedef std::basic_ostream<char> b_ostr;
 typedef std::ios_base ios_b;
 typedef std::basic_ios<char> b_ios;
 typedef std::basic_streambuf<char> b_sb;
 typedef b_ostr& (*b_ostr_pf)(b_ostr&); 
 typedef ios_b& (*ios_b_pf)(ios_b&); 
 typedef b_ios& (*b_ios_pf)(b_ios&);  
 typedef b_sb& (*b_sb_pf)(b_sb&);  


 pk_ostream(): file(0)
 {
 };

 pk_ostream& operator << (short);
 pk_ostream& operator << (int);
 pk_ostream& operator << (long);

 
 pk_ostream& operator << (unsigned short);
 pk_ostream& operator << (unsigned int);
 pk_ostream& operator << (unsigned long);

 pk_ostream& operator << (float);
 pk_ostream& operator << (double);
 pk_ostream& operator << (long double);

 pk_ostream& operator << (char);
 pk_ostream& operator << (unsigned char);
 pk_ostream& operator << (signed char);

 pk_ostream& operator << (const char*);
 pk_ostream& operator << (const unsigned char*);
 pk_ostream& operator << (const signed char*);

 pk_ostream& operator << (bool);
 pk_ostream& operator << (const void*);

 pk_ostream& operator << ( b_ostr& ( *Pfn)(b_ostr&));
 pk_ostream& operator << ( ios_b& ( *Pfn)(ios_b&));
 pk_ostream& operator << ( b_ios& ( *Pfn)(b_ios&));
 pk_ostream& operator << ( b_sb& ( *Pfn)(b_sb&));

 
 void link(ofstream& f)
 {
  file = &f;
 };
 

 operator ostream&() const
 { 
  return cout;
 };
 
 
 ostream& cout_() const
 { 
  return operator ostream& ();
 };

 ofstream& file_() const  
 {
  return *file;
 };
 

 private:
 ofstream* file;

 //disabled
 pk_ostream(const pk_ostream&);
 pk_ostream& operator = (const pk_ostream&);
 
};

extern pk_istream pk_cin;

extern pk_ostream pk_cout;

}   // pk_core   




#endif
