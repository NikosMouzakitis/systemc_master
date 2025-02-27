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

#ifndef SQUARE_INPUT_H
#define SQUARE_INPUT_H



#include "systemc.h"
#include "PKtool.h"




// ----------------------------------------------------------------------------
//  CLASS : square_input sc_module
//
//  main sc_module considered in this example
// -----------------------------------------------------------------------------


SC_MODULE(square_input)
{


    sc_in<bool> standby;
    sc_in_aug<sc_uint<16> > input;   // augmented input port
    sc_out<bool> overflow;
    sc_out_aug<sc_uint<16> > output; // augmented output port
    sc_in_clk clk;


    const unsigned over_value;


    void process()
    {
        while(true)
        {
            if(standby)
            {
                output = 0;
                overflow = false;
                wait();
                wait();
                wait();
            }
            while(standby) wait();
            if( input.read() >= over_value ) {
                output = 0;
                overflow = true;
            }
            else {
                output = (input.read()*input.read());
                overflow = false;
            };
            wait();
        };
    };



    SC_HAS_PROCESS(square_input);


    square_input(sc_module_name name):sc_module(name), over_value(256)
    {
        SC_THREAD(process)
        sensitive<<clk.pos();

        output.initialize(0);

    };

};




// ----------------------------------------------------------------------------
//  CLASS : testbench sc_module
//
//  sc_module that generates the input stimuli for square_input
// -----------------------------------------------------------------------------


SC_MODULE(testbench)
{

    sc_out<bool> standby;
    sc_out<bool> data_ready;
    sc_out<sc_uint<16> > data;
    sc_in_clk clk;


    void process()
    {
        unsigned value = 0;
        while(true)
        {
            value += 5;
            data = (value + 245);
            data_ready.write(true);
            wait(SC_ZERO_TIME);
            wait(SC_ZERO_TIME);
            data_ready.write(false);
            wait();

            if(value > 16)
            {
                value = value%16 + 3;
                data = (value + 245);
            }
            else
            {
                value += 5;
                data = (value + 245);
            };

            data_ready.write(true);
            wait(SC_ZERO_TIME);
            wait(SC_ZERO_TIME);
            data_ready.write(false);
            wait();

            standby = true;

            data_ready.write(true);
            wait(SC_ZERO_TIME);
            wait(SC_ZERO_TIME);
            data_ready.write(false);
            wait();

            standby = true;

            data_ready.write(true);
            wait(SC_ZERO_TIME);
            wait(SC_ZERO_TIME);
            data_ready.write(false);
            wait();

            standby = false;

            data_ready.write(true);
            wait(SC_ZERO_TIME);
            wait(SC_ZERO_TIME);
            data_ready.write(false);
            wait();

            value += 5;
            data = (value + 245);
            data_ready.write(true);
            wait(SC_ZERO_TIME);
            wait(SC_ZERO_TIME);
            data_ready.write(false);
            wait();
        }
    }


    SC_CTOR(testbench)
    {
        standby.initialize(false);
        data.initialize(0);

        SC_THREAD(process);
        dont_initialize();
        sensitive<<clk.pos();


    };

};



// ----------------------------------------------------------------------------
//  CLASS : display sc_module
//
//  sc_module that displays the output data computed by square_input
// -----------------------------------------------------------------------------



SC_MODULE(display)
{

    sc_in<bool> standby,overflow;
    sc_in<sc_uint<16> > input;
    sc_in<sc_uint<16> > result;
    sc_in_clk clk;

    std::ofstream  out_file;


    void process()
    {
        wait(SC_ZERO_TIME);
        while(true)
        {

            if(standby.read())
            {
                for(int i=1; i<=3; ++i)
                {
                    out_file<<"TIME:  "<<sc_core::sc_time_stamp()<<endl;
                    out_file<<"  standby "<<endl<<endl<<endl;
                    wait();
                };
            }

            while(standby.read())
            {
                out_file<<"TIME:  "<<sc_core::sc_time_stamp()<<endl;
                out_file<<"  standby "<<endl<<endl<<endl;
                wait();
            };

            wait(SC_ZERO_TIME);
            out_file<<"TIME:  "<<sc_core::sc_time_stamp()<<endl;
            out_file<<" input = "<<input.read();
            out_file<<"          result = ";
            if(overflow.read()) out_file<<"overflow";
            else out_file<<result.read();

            out_file<<endl<<endl<<endl;
            wait();
        }
    }


    SC_CTOR(display)
    {

        out_file.open("out_file.txt");

        SC_THREAD(process);
        sensitive<<clk.pos();

    };

    ~display()
    {
        out_file.close();
    };

};

#endif


