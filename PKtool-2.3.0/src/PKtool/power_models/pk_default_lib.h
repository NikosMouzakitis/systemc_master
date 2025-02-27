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


 Original Author: Giovanni B. Vece

 Affiliation: Università Politecnica delle Marche (Italy)


************************************************************************/

#ifndef PK_DEFAULT_LIB_H
#define PK_DEFAULT_LIB_H



PK_MODEL_LIB( pk_default_energy_lib ) 
{

 PK_MODEL_BEGIN(fixed_energy, 0)
{
 public: 

 float en;    


 // constructor

 PK_MODEL_CTOR(fixed_energy)
 { };  
 

  void set_static_data()
 { PK_SET_SINGLE_MODEL_DATA( energy (nJ), en ) };

 estimation_type do_estimationation()
 {
  static const double en_units = 1e-9;
  return en*en_units;
 }

};
PK_MODEL_END(fixed_energy, 0)

PK_MODEL_BEGIN(fixed_power, 1)
{
 public:   
 float power;    


 // constructor

 PK_MODEL_CTOR(fixed_power)
 { };  

 void set_static_data()
 { PK_SET_SINGLE_MODEL_DATA( power (mW), power ) };

 estimation_type do_estimationation()
 {
  static const double pow_unit = 1e-3;
  double energy = power*pow_unit*simulation_time();
  return energy;
 }


};
PK_MODEL_END(fixed_power, 1)



PK_MODEL_BEGIN(model_2, 2)
{
 public:

 float coeff;   
 
 // constructor

 PK_MODEL_CTOR(model_2)
 { };
  

 void set_static_data()
 { PK_SET_SINGLE_MODEL_DATA( coefficient (nano units), coeff ) };

 void set_augdata()
 {   PK_SET_TOTALCOMM   };

 estimation_type do_estimationation()
 {
  static const double en_units = 1e-9;
  unsigned comm = total_comm();  

  estimation_type res = comm*coeff*en_units;
  return res;
 }

};
PK_MODEL_END(model_2, 2)


PK_MODEL_BEGIN(model_3, 3)
{
 public:   
    
 float Ist, coeff, cap, Vdd;
 

 // constructor

 PK_MODEL_CTOR(model_3)
 { }; 

  void set_static_data()
 {
  PK_SET_SINGLE_MODEL_DATA( coefficient (units), coeff )
  PK_SET_SINGLE_MODEL_DATA( power supply (V), Vdd )
  PK_SET_SINGLE_MODEL_DATA( capacitance (nF), cap )
 };

 void set_augdata()
 {  PK_SET_TOTALCOMM   };
 
 

 estimation_type do_estimationation()
 {
  static const double cap_unit = 1e-9;
  unsigned comm = total_comm();
  
  estimation_type res = 0.5*coeff*cap*cap_unit*Vdd*Vdd*comm;
  return res;

 } 
 

};

PK_MODEL_END(model_3, 3)



PK_MODEL_BEGIN(model_4, 4)
{ 
 public:   
    
 float Ilk, Ng, cap, Vdd, mean_comms;
 

 // constructor

 PK_MODEL_CTOR(model_4)
 { }; 

 void set_augdata()
 { PK_SET_TOTALCOMM };
 

 estimation_type do_estimationation()
 { 
  static const double cap_unit = 1e-9;
  static const double Ilk_unit = 1e-9;

  estimation_type term1 = Ilk*Ilk_unit*Vdd*simulation_time();

  
  unsigned comm = total_comm();
  unsigned bit_sum = 0;
 
  int size = inport_aug.size();
  for(int i=0; i<size; ++i) 
    bit_sum += inport_aug[i]->data().size();  
   
  size = outport_aug.size();
  for(int i=0; i<size; ++i) 
    bit_sum += outport_aug[i]->data().size();

  size = inoutport_aug.size();
  for(int i=0; i<size; ++i) 
    bit_sum += inoutport_aug[i]->data().size(); 

  size = intsignal_aug.size();
  for(int i=0; i<size; ++i) 
    bit_sum += intsignal_aug[i]->data().size();

  mean_comms = float(comm)/bit_sum;   
  
  estimation_type term2 = 0.5*Ng*cap*cap_unit*Vdd*Vdd*mean_comms;
  
  estimation_type res = term1 + term2;
  return res; 
 } 
 
 void set_static_data()
 {
  PK_SET_SINGLE_MODEL_DATA( Ileak (nA), Ilk )
  PK_SET_SINGLE_MODEL_DATA( number of gates (units), Ng )
  PK_SET_SINGLE_MODEL_DATA( power supply (V), Vdd )
  PK_SET_SINGLE_MODEL_DATA( capacitance (nF), cap )
 };

 

};

PK_MODEL_END(model_4, 4)


// functions for common tasks related to table-based power models


inline int find_closest_indexes
           (const double value, const double* index_array, int sz, int* res_ind, const double tol = 0.01)
{
 for(int i=0; i<sz; ++i)
  {
   if( value == index_array[i] ) { res_ind[0] = i; res_ind[1] = -1; return 1; }
   else if ( (value < index_array[i]) && (i==0) ) { res_ind[0] = 0; res_ind[1] = -1; return 1; }
   else if ( (index_array[i] < value) && (i == (sz-1)) ) 
                         { res_ind[0] = (sz-1); res_ind[1] = -1; return 1; }
   else 
   { 
	if( (index_array[i] < value) && (value < index_array[i+1]) )
	{
	 if( value < (index_array[i] + tol) ) 
	        { res_ind[0] = i; res_ind[1] = -1; return 1; } 
	 else if((index_array[i+1] - tol) < value) 
	               { res_ind[0] = (i+1); res_ind[1] = -1; return 1;}  
	 else{  res_ind[0] = i; res_ind[1] = i+1;  return 2;  }
	}
   }
  }
  return 0;
}

inline double compute_1Ddistance
(const double* array, const int ind, const double& ref_val)
{
 double val = array[ind];
 if(ref_val > val) return (ref_val - val);
 else return (val - ref_val);
}

inline double compute_2Ddistance
(const double* array1, const double* array2, const int ind1, const int ind2,
  const double& ref_val1, const double& ref_val2)
{
 double val1 = array1[ind1];
 double val2 = array2[ind2];

 double diff1 = ref_val1 - val1 ;
 double diff2 = ref_val2 - val2 ;

 return (diff1*diff1 + diff2*diff2) ; 
}

inline double compute_3Ddistance
(const double* array1, const double* array2, const double* array3,
 const int ind1, const int ind2, const int ind3,
 const double& ref_val1, const double& ref_val2, const double& ref_val3)
{
 double val1 = array1[ind1];
 double val2 = array2[ind2];
 double val3 = array3[ind3];

 double diff1 = ref_val1 - val1 ;
 double diff2 = ref_val2 - val2 ;
 double diff3 = ref_val3 - val3 ;

 return (diff1*diff1 + diff2*diff2 + diff3*diff3) ; 
}

inline double compute_1Dinterpolated_estim
(const double* array, const int ind1, const int ind2, const double& ref_val,
 const double* table)
{

 double dist1 = compute_1Ddistance(array, ind1, ref_val);
 double en1 = table[ind1];

 double dist2 = compute_1Ddistance(array, ind2, ref_val);
 double en2 = table[ind2];


 double dist_sum = ( dist1 + dist2 );
 double coeff1 = 1 - (dist1/dist_sum);
 double coeff2 = 1 - (dist2/dist_sum);


 return (coeff1*en1 + coeff2*en2);

}


inline double compute_2Dinterpolated_estim
( int indexes[4][2], int index_num, const double* array1, const double* array2, 
 const double& ref_val1, const double& ref_val2, double** table)
{
  
 static double distances[2];
 distances[0] = compute_2Ddistance(array1, array2, indexes[0][0],
	                                      indexes[0][1], ref_val1, ref_val2 );
 distances[1] = compute_2Ddistance(array1, array2, indexes[1][0],
	                                      indexes[1][1], ref_val1, ref_val2 );

  static double dist_tmp;
  for(int i=2; i<index_num; ++i)
  {
   dist_tmp = compute_2Ddistance(array1, array2, indexes[i][0],
	                                indexes[i][1], ref_val1, ref_val2 );
   if( (dist_tmp < distances[0]) )
   {
	distances[1] = distances[0];  distances[0] = dist_tmp;
	indexes[1][0] = indexes[0][0];  indexes[1][1] = indexes[0][1];
    indexes[0][0] = indexes[i][0];  indexes[0][1] = indexes[i][1];
   }
   else if( (dist_tmp < distances[1]) )
   {
	distances[1] = dist_tmp; 
	indexes[1][0] = indexes[i][0];  indexes[1][1] = indexes[i][1];
   }
  }


 double en1 = table[ indexes[0][0] ][ indexes[0][1] ];
 double en2 = table[ indexes[1][0] ][ indexes[1][1] ];

 double dist_sum = ( distances[0] + distances[1] );
 double coeff1 = 1 - (distances[0]/dist_sum);
 double coeff2 = 1 -(distances[1]/dist_sum);

 return double(coeff1*en1 + coeff2*en2);

}


inline double compute_estim_from_1Dtable
    ( const float value, const double* array, int size, double* table)
{
 int closest_ind[2];
 int index_num;

 index_num = find_closest_indexes(value, array, size, closest_ind);

 if(index_num == 1)
 {
  int ind = closest_ind[0];

  return table[ind];
 }
 else 
 {
  int ind1 = closest_ind[0];  
  int ind2 = closest_ind[1];  
  
  return compute_1Dinterpolated_estim(array, ind1, ind2, value, table);
 }

}


inline double compute_estim_from_2Dtable
    ( const double value1, double value2, const double* ind_array1, 
	  const double* ind_array2, int size1, int size2, double** table, bool** valid_ind = 0)
 {

  static int closest_ind1[2];
  static int closest_ind2[2];
  static int indexes[4][2];
  int index_num = 0;

  find_closest_indexes(value1, ind_array1, size1, closest_ind1);
  find_closest_indexes(value2, ind_array2, size2, closest_ind2);

  for(int i=0; i<2; ++i)
  {
   if(closest_ind1[i] != -1)
   {
	for(int j=0; j<2; ++j)
	{
	 if(closest_ind2[j] != -1)
	 {
	  if( (valid_ind[ closest_ind1[i] ][ closest_ind2[j] ]) ||  (valid_ind == 0) )
	   {
		indexes[index_num][0] = closest_ind1[i];  indexes[index_num][1] = closest_ind2[j]; 
          ++index_num;	   
	   }
	  }
	 }
    }
   }


  if(index_num == 0)
  { return float(0); }
  else if(index_num == 1)
  { 
   double res = table[ indexes[0][0] ][ indexes[0][1] ];
   return res;
  }
  else
  { 
   return compute_2Dinterpolated_estim( indexes, index_num, ind_array1, ind_array2,
	   value1, value2, table); 
  }

}


//table-based power models


PK_MODEL_BEGIN(table_1, 21)
{

 PK_CYCLE_ACCURATE 
 
 // constructor

 PK_MODEL_CTOR(table_1) 
 { };


 void set_augdata()
 { PK_SET_TOTALCOMM  };
  

 void set_static_data()
 { 
  using pk_core::reading_option;
  using pk_core::pk_cout;
  using pk_core::get_order_token;

  if(reading_option == 1)
  {
    pk_cout<<endl<<"Specification of the data for building the lookup table"<<endl<<endl;
  }
  
  PK_SET_SINGLE_MODEL_DATA( number of stored energy values (positive integer), Hd_nb )

  Hd_vals = new double[Hd_nb];
  table = new double[Hd_nb];
  
  if(reading_option == 1) pk_cout<<"Hd values ("<<Hd_nb<<" float values)";
  PK_SET_ARRAY_MODEL_DATA( , Hd_vals, Hd_nb )

  if(reading_option == 1)  pk_cout<<"corresponding energy values (nJ)";
  PK_SET_ARRAY_MODEL_DATA( ,table, Hd_nb ) 

 }



 estimation_type do_estimationation()
 {
  static const double en_units = 1e-9;
  unsigned in_comm = 0;
  unsigned in_bitsz = 0;

  int size = inport_aug.size();
  for(int i=0; i<size; ++i) 
  {
	in_comm += inport_aug[i]->data().total_comm();
    in_bitsz += inport_aug[i]->data().size();  
  }



  if(in_comm == 0) return estimation_type(0);


  float average_Hd = float(in_comm)/in_bitsz;


  estimation_type res = compute_estim_from_1Dtable(average_Hd, Hd_vals, 
	                                                     Hd_nb,table);

  return (res*en_units);
 }

 PK_MODEL_DTOR(table_1)
 { 
  delete[] Hd_vals;  delete[] table;
 };

 private:

 int Hd_nb;
 double* Hd_vals;
 double* table;

};
PK_MODEL_END(table_1, 21)



PK_MODEL_BEGIN(table_2, 22)
{
 
 PK_CYCLE_ACCURATE 

 public:

 // constructor

 PK_MODEL_CTOR(table_2)
 { 
  old_bitvals = 0;
 };
  

 void set_static_data()
 {  
  using pk_core::reading_option;
  using pk_core::pk_cout;
  using pk_core::get_order_token;


  if(reading_option == 1)
  {
    pk_cout<<endl<<"Specification of the data for building the lookup table"<<endl<<endl;
  }
  
  PK_SET_SINGLE_MODEL_DATA( number of Hd values (positive integer), Hd_nb )
  Hd_vals = new double[Hd_nb];

  if(reading_option == 1) pk_cout<<"Hd values ("<<Hd_nb<<" float values)";
  PK_SET_ARRAY_MODEL_DATA( , Hd_vals, Hd_nb )

  PK_SET_SINGLE_MODEL_DATA( number of stable zeros (positive integer), zero_nb )
  zero_vals = new double[zero_nb];

  if(reading_option == 1) pk_cout<<"normalized stable zero values ("<<zero_nb<<" float values)";
  PK_SET_ARRAY_MODEL_DATA( , zero_vals, zero_nb )

  table = new double*[Hd_nb];
  valid_indexes = new bool*[Hd_nb];

  for(int i=0; i<Hd_nb; ++i)  
  {
   table[i] = new double[zero_nb];
   valid_indexes[i] = new bool[zero_nb]; 
  }
  
  pk_cout<<endl;
  for(int i=0; i<Hd_nb; ++i)
  { 
   if(reading_option == 1) 
   {
    pk_cout<<"Hd: "<<Hd_vals[i]<<"     stable zeros:";
	for(int j=0; j<zero_nb; ++j) pk_cout<<" "<<zero_vals[j]<<"  ";
	pk_cout<<endl<<endl<<"energy values (nJ) ";
   }
   PK_SET_ARRAY_MODEL_DATA(  ,table[i], zero_nb )
   pk_cout<<endl<<endl;
  }
  
  for(int i=0; i<Hd_nb; ++i)
  { 
	  for(int j=0; j<zero_nb; ++j)
	valid_indexes[i][j] =  ( table[i][j] < 0 ? false : true );  
  }  


 };

 void set_augdata()
 { 
  PK_SET_BITVAL 
  PK_SET_TOTALCOMM  
  
  int inport_nb = inport_aug.size();
  in_bits = 0;

  for(int i=0; i<inport_nb; ++i) 
	   in_bits += inport_aug[i]->data().size();
  
  if(! old_bitvals)
  old_bitvals = new bool[in_bits];
  
  int port_bits;
  int pos = 0;
  for(int i=0; i<inport_nb; ++i)
   {
    port_bits = inport_aug[i]->data().size();
   
    for(int j=0; j<port_bits; ++j) 
	    old_bitvals[pos + j] = inport_aug[i]->data().bit_value(j); 
    pos = port_bits;
  }
 };



 estimation_type do_estimationation()
 {
  
  static const double en_units = 1e-9;
  unsigned in_Hd = 0;
  int inport_nb = inport_aug.size();

  for(int i=0; i<inport_nb; ++i)  in_Hd += inport_aug[i]->data().total_comm();

  if(in_Hd == 0) return 0;

  double avg_Hd = double(in_Hd)/in_bits;

  int stb_zeros = 0;
  int port_bits;
  int pos = 0;

  for(int i=0; i<inport_nb; ++i)
  {
   port_bits = inport_aug[i]->data().size();

   for(int j=0; j<port_bits; ++j)   
   {
	if( (old_bitvals[pos + j] == false) && (inport_aug[i]->data().bit_value(j) == false) )
		     ++stb_zeros; 
    old_bitvals[pos + j] = inport_aug[i]->data().bit_value(j);
   }
   pos = port_bits;
  }

  double avg_zeros = float(stb_zeros)/in_bits;
  
  pos = 0;
  
  
  
   estimation_type res = compute_estim_from_2Dtable(avg_Hd, avg_zeros, Hd_vals,
 	                      zero_vals, Hd_nb, zero_nb, table, valid_indexes);

  return (res*en_units);

 }

 PK_MODEL_DTOR(table_2)
 { 
  delete [] Hd_vals;
  delete [] zero_vals;
  delete [] old_bitvals;

  for(int i=0; i<Hd_nb; ++i)
  {
   delete[] table[i];
   delete[] valid_indexes[i];
  }
 
  delete[] table;
  delete[] valid_indexes;
 };

 private:  

 int Hd_nb;              //number of values for the input average Hamming distance
 int zero_nb;           //number of values for the input stable zeros
 double* Hd_vals;     //addressing values for the input average Hamming distance
 double* zero_vals;   //addressing values for the input stable zeros
 int in_bits;
 bool* old_bitvals;
 double** table;
 bool** valid_indexes;

};
PK_MODEL_END(table_2, 22)



PK_MODEL_BEGIN(table_3, 23)
{
 

 public:
 
 // constructor

 PK_MODEL_CTOR(table_3)
 { };
  

 void set_static_data()
 { 
  using pk_core::reading_option;
  using pk_core::pk_cout;
  using pk_core::get_order_token;

  PK_SET_SINGLE_MODEL_DATA( clock frequency (Mhz), freq )

  if(reading_option == 1)
  {
    pk_cout<<endl<<"Specification of the data for building the lookup table"<<endl<<endl;
  }
  
  PK_SET_SINGLE_MODEL_DATA( number of Pin values (positive integer), Pin_nb )
  Pin_vals = new double[Pin_nb];

  if(reading_option == 1) pk_cout<<"Pin values ("<<Pin_nb<<" float values)";
  PK_SET_ARRAY_MODEL_DATA( , Pin_vals, Pin_nb )

  PK_SET_SINGLE_MODEL_DATA( number of Din values (positive integer), Din_nb )
  Din_vals = new double[Din_nb];

  if(reading_option == 1) pk_cout<<"Din values ("<<Din_nb<<" float values)";
  PK_SET_ARRAY_MODEL_DATA( , Din_vals, Din_nb )

  valid_index = new bool*[Pin_nb];
  Dout_vals = new double**[Pin_nb];
  Dout_nb = new int*[Pin_nb];
  table = new double**[Pin_nb];

  for(int i=0; i<Pin_nb; ++i)  
  {
   valid_index[i] = new bool[Din_nb];
   Dout_vals[i] = new double*[Din_nb];
   Dout_nb[i] = new int[Din_nb];
   table[i] = new double*[Din_nb];
  }

  for(int i=0; i<Pin_nb; ++i)
  { 
   double limit = ( (Pin_vals[i] > 0.5) ? 
	                    (1 - 2*(Pin_vals[i]-0.5)) : (1 - 2*(0.5 - Pin_vals[i])) );
   for(int j=0; j<Din_nb; ++j)
	   valid_index[i][j] = ( (Din_vals[j] <= limit) ? true : false );
  }

  
  for(int i=0; i<Pin_nb; ++i)
  { 
   
   for(int j=0; j<Din_nb; ++j)
	   cout<<valid_index[i][j] ;
   cout<<endl;
  }


  if(reading_option == 1)
  {
    pk_cout<<endl<<"Specification of the values of Dout and energy for each"<<endl;
    pk_cout<<"(Pin,Din) couple:"<<endl<<endl;
  }


  for(int i=0; i<Pin_nb; ++i)
  { 
   for(int j=0; j<Din_nb; ++j)
   {
    if(valid_index[i][j])
	{
    if(reading_option == 1) 
	 pk_cout<<"Pin: "<<Pin_vals[i]<<"  Din: "<<Din_vals[j]<<endl<<endl;
	PK_SET_SINGLE_MODEL_DATA( number of Dout values (positive integer), Dout_nb[i][j] )
	int sz = Dout_nb[i][j];
	Dout_vals[i][j] = new double[sz];
	table[i][j] = new double[sz];

	if(reading_option == 1) pk_cout<<"Dout values ("<<sz<<" float values)";
	 PK_SET_ARRAY_MODEL_DATA( , Dout_vals[i][j], sz )
	 
	if(reading_option == 1) pk_cout<<"corresponding energy values (nJ)";
	 PK_SET_ARRAY_MODEL_DATA( , table[i][j], sz )
	}
   }
  }


 };

 void set_augdata()
 { 
  PK_SET_TOTALCOMM  
  PK_SET_BITPROB
 };



 estimation_type do_estimationation()
 {
  
  static const double en_units = 1e-9;
  static const double freq_units = 1e6;

  double in_probs = 0;
  unsigned in_comms = 0;
  unsigned out_comms = 0;
  unsigned in_bitsz = 0;
  unsigned out_bitsz = 0;
  

  double sim_time = simulation_time();
  int size = inport_aug.size();

  for(int i=0; i<size; ++i) 
  {
    in_bitsz += inport_aug[i]->data().size(); 
    in_comms += inport_aug[i]->data().total_comm();
	
    for( unsigned j=0; j<in_bitsz; ++j)
		in_probs += inport_aug[i]->data().bit_probability(j, sim_time);
  }

  double Pin = in_probs/in_bitsz;
  double avg_incomm = double(in_comms)/in_bitsz;
  double Din = avg_incomm/(freq*freq_units*sim_time);

  
  size = outport_aug.size();

  for(int i=0; i<size; ++i) 
  {
    out_bitsz += outport_aug[i]->data().size(); 
    out_comms += outport_aug[i]->data().total_comm();
  }

  double avg_outcomm = double(out_comms)/out_bitsz;
  double Dout = avg_outcomm/(freq*freq_units*sim_time);
  

  int closest_ind1[2];
  int closest_ind2[2];
  int closest_ind3[2];
  int indexes[8][3];
  find_closest_indexes(Pin, Pin_vals, Pin_nb, closest_ind1);
  find_closest_indexes(Din, Din_vals, Din_nb, closest_ind2);

  
  int index_num = 0;

  for(int i=0; i<2; ++i)
  {
   if(closest_ind1[i] != -1)
   {
	for(int j=0; j<2; ++j)
	{
	 if(closest_ind2[j] != -1)
	 {
	  if(valid_index[ closest_ind1[i] ][ closest_ind2[j] ])
	  {
	   find_closest_indexes(Dout, Dout_vals[i][j], Dout_nb[i][j], closest_ind3);
	   
	   if(closest_ind3[0] != -1)
	   {
		indexes[index_num][0] = closest_ind1[i];  indexes[index_num][1] = closest_ind2[j]; 
        indexes[index_num][2] = closest_ind3[0];  ++index_num;	   
	   }
	   if(closest_ind3[1] != -1)
	   {
		indexes[index_num][0] = closest_ind1[i];  indexes[index_num][1] = closest_ind2[j]; 
        indexes[index_num][2] = closest_ind3[1]; ++index_num;	   
	   }
	  }
	 }
    }
   }
  }

  

  if(index_num == 0)
  { return estimation_type(0); }
  else if(index_num == 1)
  { 
   estimation_type res = table[ indexes[0][0] ][ indexes[0][1] ] [ indexes[0][2] ];
   return res*en_units;
  }
  else
  { return ( compute_interpolated_estim( indexes, index_num, Pin, Din, Dout)*en_units ); }
  
 }

 estimation_type compute_interpolated_estim( int indexes[8][3], int index_num,
	 const double& val1, const double& val2, const double& val3)
 {
  double distances[2];
  distances[0] = compute_3Ddistance(Pin_vals, Din_vals, Dout_vals[ indexes[0][0] ][ indexes[0][1] ], 
	            indexes[0][0], indexes[0][1], indexes[0][2], val1, val2, val3);
  distances[1] = compute_3Ddistance(Pin_vals, Din_vals, Dout_vals[ indexes[1][0] ][ indexes[1][1] ], 
	            indexes[1][0], indexes[1][1], indexes[1][2], val1, val2, val3);
  
  double dist_tmp;
  for(int i=2; i<index_num; ++i)
  {
   dist_tmp = compute_3Ddistance(Pin_vals, Din_vals, Dout_vals[ indexes[i][0] ][ indexes[i][1] ], 
	            indexes[i][0], indexes[i][1], indexes[i][2], val1, val2, val3);
   if( (dist_tmp < distances[0]) )
   {
	distances[1] = distances[0];  distances[0] = dist_tmp;
	indexes[1][0] = indexes[0][0];  indexes[1][1] = indexes[0][1];
	indexes[1][2] = indexes[0][2]; 
    indexes[0][0] = indexes[i][0];  indexes[0][1] = indexes[i][1];
	indexes[0][2] = indexes[i][2];   
   }
   else if( (dist_tmp < distances[1]) )
   {
	distances[1] = dist_tmp; 
	indexes[1][0] = indexes[i][0];  indexes[1][1] = indexes[i][1];
	indexes[1][2] = indexes[i][2]; 
   }
  }

  

  double en1 = table[ indexes[0][0] ][ indexes[0][1] ] [ indexes[0][2] ];
  double en2 = table[ indexes[1][0] ][ indexes[1][1] ] [ indexes[1][2] ];
  double dist_sum = ( distances[0] + distances[1] );
  double coeff1 = 1 - (distances[0]/dist_sum);
  double coeff2 = 1 - (distances[1]/dist_sum);
 
  return estimation_type(coeff1*en1 + coeff2*en2);

 }




 PK_MODEL_DTOR(table_3)
 {
  delete[] Pin_vals;  delete[] Din_vals;

  for(int i=0; i<Pin_nb; ++i)
  {
   delete[] Dout_nb[i];
   for(int j=0; i<Pin_nb; ++i)
   {
    if(valid_index[i][j])
    {
     delete[] Dout_vals[i][j];
    } 
   }
   delete[] Dout_vals[i];
  }

  delete[] Dout_vals;  delete[] Dout_nb;

  for(int i=0; i<Pin_nb; ++i)
  {  delete[] valid_index[i];  }

  delete[] valid_index;

 };

 private:

 double freq;
 int Pin_nb, Din_nb;
 double* Pin_vals; 
 double* Din_vals;
 bool** valid_index;
 double*** Dout_vals;
 int** Dout_nb;
 double*** table;

};
PK_MODEL_END(table_3, 23)




//operator-based power models

#ifdef PK_ENABLE_OPMODELS

#ifndef PK_AUG_IF_H

struct pk_opmodel_b
 {

  virtual void op_task(const char) =0;

 };

#endif


PK_MODEL_BEGIN(operators_1, 41)  , pk_opmodel_b
{
 
 struct operator_data
 {
  enum{ avail_opnb = 4};

  int enabl_opnb;
  bool enabled_op[avail_opnb];
  float op_energy[avail_opnb];
  int op_cnt[avail_opnb];
  char op_symbols[avail_opnb];
  int* curr_opcnt_h;

  operator_data(): enabl_opnb(0),  curr_opcnt_h(0)
  { 
   op_symbols[0] = '+'; op_symbols[1] = '-'; op_symbols[2] = '*'; op_symbols[3] = '/';
   for(int i=0; i<avail_opnb; ++i)
   {
    op_cnt[i] = 0;  op_energy[i] = 0;  enabled_op[i] = false;
   }
  };

  void enable_operator(const char s)
  {  enabled_op[ op_index(s) ] = true;  }

  int op_index(const char s) const
  {
    switch(s)
    {
     case '+': 
	  return 0;
	  break;
     case '-': 
	  return 1;
	  break;
     case '*': 
	  return 2;
	  break;
     case '/': 
	  return 3;
	  break;
	 default: 
	 return -1;
    };
  }
  
  void op_incr(const char s)
  { ++op_cnt[ op_index(s) ]; }

  void set_op_energy(const char s, float en_val)
  {  op_energy[ op_index(s) ] = en_val;  };

  float energy_est() 
  { 
   float est = 0;
   for(int i=0; i<avail_opnb; ++i)
	   if(enabled_op[i]) est += ( op_energy[i] * op_cnt[i] );

   return est;
  };

  void print_op_statistics(ofstream& f, float en_units = 1e-9)  const
  {
   for(int i=0; i<avail_opnb; ++i)
     if(enabled_op[i]) 
	 {
	  f<<"number of "<<op_symbols[i]<<" operations: "<<op_cnt[i]
	  <<"      related energy contribution: " 
		  <<( op_energy[i] * op_cnt[i] * en_units )<<endl;
	 };
    f<<endl;
  }

 };


 public:
 
 
 // constructor

 PK_MODEL_CTOR(operators_1)
 { };



 void set_static_data()
 { 
  using pk_core::reading_option;
  using pk_core::pk_cout;
  using pk_core::get_order_token;

  if(reading_option == 1)
  {
   pk_cout<<"available operators: ";
   for(int i=0; i<operator_data::avail_opnb; ++i)
	     pk_cout<<" "<<op_data.op_symbols[i];
   pk_cout<<endl<<endl;
  }

  PK_SET_SINGLE_MODEL_DATA( number of enabled operators, op_data.enabl_opnb )
  
  char* en_ops = new char[op_data.enabl_opnb];

  PK_SET_ARRAY_MODEL_DATA( enabled operators, en_ops, op_data.enabl_opnb )
  
  char op_sym;
  for(int i=0; i<op_data.enabl_opnb; ++i)
  { 
   op_sym = en_ops[i];
   op_data.enable_operator(op_sym);
   float en_val; 
   if(reading_option == 1) pk_cout<<"operator "<<op_sym<<endl;
   PK_SET_SINGLE_MODEL_DATA( energy cost (nJ units), en_val )
   op_data.set_op_energy( op_sym, en_val );
  }

 };                    

 void set_augdata()
 { 
  PK_SET_OP_DATA
  set_opmodel_on_augs(this);
 };


 void op_task(const char s)
 {  op_data.op_incr(s);  };

 estimation_type do_estimationation()
 {  
  static const double en_units = 1e-9;
  estimation_type res = ( op_data.energy_est() * en_units );
  return res; 
 }

 void print_custom_result(ofstream& f) 
 {   op_data.print_op_statistics(f); };

 PK_MODEL_DTOR(operators_1)
 { };

 private:

 operator_data op_data;

};
PK_MODEL_END(operators_1, 41)

#endif


} // pk_default_energy_lib



PK_MODEL_LIB( pk_default_comm_lib )
{

 PK_MODEL_BEGIN(fixed_comm,0)
 {
  public:   
  float comm;    


  void set_static_data()
 { PK_SET_SINGLE_MODEL_DATA( commutations (units), comm )  };


 // constructor

  PK_MODEL_CTOR(fixed_comm)
  { }; 

  estimation_type do_estimationation()
  {
   return comm;
  }


};
PK_MODEL_END(fixed_comm,0)

 PK_MODEL_BEGIN(fixed_rate, 1)
 {
  public:   
  float rate;    

  void set_static_data()
 { PK_SET_SINGLE_MODEL_DATA( commutation rate (Hz), rate )  };

 // constructor

  PK_MODEL_CTOR(fixed_rate)
  { }; 

  estimation_type do_estimationation()
  {
   double comm = rate*simulation_time();
   return comm;
  }

};

PK_MODEL_END(fixed_rate, 1)

PK_MODEL_BEGIN(model_2, 2)
{
 public:   
 float coeff;   


 void set_static_data()
 { PK_SET_SINGLE_MODEL_DATA( coefficient, coeff )  };

 void set_augdata()
 {   PK_SET_TOTALCOMM   };

 

 // constructor

 PK_MODEL_CTOR(model_2)
 { };  
 

 estimation_type do_estimationation()
 {
  estimation_type comm = total_comm();

  return comm*coeff;
 }
 
 


};

PK_MODEL_END(model_2, 2)


PK_MODEL_BEGIN(model_3, 3)
{ 
 public:   
    
 float  Ng, mean_comms;
 

 // constructor

 PK_MODEL_CTOR(model_3)
 { };  
 

 estimation_type do_estimationation()
 { 
  unsigned comm = total_comm();
  unsigned bit_sum = 0;
 
  int size = inport_aug.size();
  for(int i=0; i<size; ++i) 
    bit_sum += inport_aug[i]->data().size();  
   
  size = outport_aug.size();
  for(int i=0; i<size; ++i) 
    bit_sum += outport_aug[i]->data().size();

  size = inoutport_aug.size();
  for(int i=0; i<size; ++i) 
    bit_sum += inoutport_aug[i]->data().size();
   

  size = intsignal_aug.size();
  for(int i=0; i<size; ++i) 
   {
	comm += intsignal_aug[i]->data().total_comm();
    bit_sum += intsignal_aug[i]->data().size();
   } 

  mean_comms = float(comm)/bit_sum;   
  
  estimation_type res = Ng*mean_comms;
  
  return res; 
 } 
 
 void set_static_data()
 {
  PK_SET_SINGLE_MODEL_DATA( number of gates (units), Ng )
 };


};

PK_MODEL_END(model_3, 3)


PK_MODEL_BEGIN(model_4, 4)
{

 public:
 
 float Ng,freq;


 // constructor

 PK_MODEL_CTOR(model_4)
 { };  
 

 estimation_type do_estimationation()
 {
 
  static const double freq_unit = 1e+6;
  double st_time = simulation_time();
  double cycles = st_time*freq*freq_unit;

  unsigned total_bitsize = 0;
  double Hi = 0;
  double Ho = 0;

  estimation_type res = 0;

  int sz = inport_aug.size();
  for(int i=0; i<sz; ++i) 
  {
   total_bitsize += inport_aug[i]->data().size();
   double bit_prob = inport_aug[i]->data().bit_probability(i, st_time);
   Hi += bit_entropy(bit_prob);
  }

  sz = outport_aug.size();
  for(int i=0; i<sz; ++i) 
  {
   total_bitsize += outport_aug[i]->data().size();
   double bit_prob = outport_aug[i]->data().bit_probability(i, st_time);
   Ho += bit_entropy(bit_prob);
  }
  
  const double factor = (2.0/3.0) / double(total_bitsize);
  res = 0.5*factor*( Hi + 2*Ho )*Ng*cycles;

  return res;
 }


 void set_static_data()
 {
  PK_SET_SINGLE_MODEL_DATA( clock frequency (Mhz), freq )
  PK_SET_SINGLE_MODEL_DATA( number of gates (units), Ng )
 };


 void set_augdata()
 {  PK_SET_BITPROB  };

 private:

 double bit_entropy(const double bit_prob) const
 {
  const double& p = bit_prob;
  static const double log10_2 = log10(2.0);

  if( (p==0) || (p==1) )   return double(0);
  else
  {
   double p1 = 1 - p;
   if(p1 <0) p1 = -p1;

   const double log10_p = log10( p );
   const double log10_p1 = log10( p1 );

   const double log2_p = ( log10_p / log10_2 );
   const double log2_p1 = ( log10_p1 / log10_2 );

   double entropy = - ( p*log2_p + p1*log2_p1 );
   return entropy;
  }
 }
 
 
};

PK_MODEL_END(model_4, 4)


} // pk_default_comm_lib

#endif
