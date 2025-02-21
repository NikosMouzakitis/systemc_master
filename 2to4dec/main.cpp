#include "systemc.h"

using namespace std;

SC_MODULE(dec2to4)
{
	sc_in<sc_bit> enable;
	sc_in<sc_uint<2>> select; //select[0],select[1]
	sc_out <sc_uint<4>> z;
	
	void func(void)
	{
		if(enable.read() == 1)
		{
			switch(select.read()) {
				case 0: z.write((sc_uint<4>)0x1); break;
				case 1: z.write((sc_uint<4>)0x2); break;
				case 2: z.write((sc_uint<4>)0x4); break;
				case 3: z.write((sc_uint<4>)0x8); break;
			}
		}
	}

	SC_CTOR(dec2to4)
	{
		std::cout << "new 2to4dec" << std::endl;
		SC_METHOD(func);
		sensitive << select << enable;
	}

};

int sc_main(int argc, char * argv[])
{
	std::cout << "test" << std::endl;
	
	dec2to4 dec("dec");

	sc_signal<sc_bit> en;
	sc_signal<sc_uint<2>> s;
	sc_signal<sc_uint<4>> z;
		
	dec.enable(en);
	dec.select(s);
	dec.z(z);

	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");

	sc_trace(tf,en,"enable");
	sc_trace(tf,s,"select");
	sc_trace(tf,z,"z");

	en.write((sc_bit)1);

	s.write(0x0);
	sc_start(sc_time(10,SC_NS));
	
	s.write(0x1);
	sc_start(sc_time(10,SC_NS));

	s.write(0x2);
	sc_start(sc_time(10,SC_NS));
	
	s.write(0x3);
	sc_start(sc_time(10,SC_NS));



	sc_close_vcd_trace_file(tf);

	return 0;
}
