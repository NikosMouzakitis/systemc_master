#include "systemc.h"


SC_MODULE(port_access) {
	
	sc_in < sc_bit> a;
	sc_in < sc_bit> b;
	sc_in <bool> en;
	sc_out<sc_lv<2>> out;

	//method to manipulate output
	//if enable, out is sum of a and b.
	void body() {
		if(en.read() == 1) {
			out.write(a.read() + b.read());	
		}
	}	
	
	void monitor() {
		cout << "@" << sc_time_stamp() << " a: " << a << " b: " << b << " en: " << en  << " out: " << out.read() << endl;  

	}

	SC_CTOR(port_access)
	{
		SC_METHOD(body);
		sensitive << a << b << en;
		SC_METHOD(monitor);
		sensitive << a << b << en << out;
	}
};

//testbench to generate test vectors
int sc_main(int argc, char *argv[])
{
	sc_signal < sc_bit> a;
	sc_signal < sc_bit> b;
	sc_signal <bool> en;
	sc_signal <sc_lv<2>> out;

	//creation and mapping.
	port_access prt_ac("PORT ACCESS");
	prt_ac.a(a);
	prt_ac.b(b);
	prt_ac.en(en);
	prt_ac.out(out);

	sc_start(sc_time(10,SC_NS));
	//open vcd file.
	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");
	sc_trace(tf,a,"a");
	sc_trace(tf,b,"b");
	sc_trace(tf,en,"en");
	sc_trace(tf,out,"out");
	
	//simulation
	en = sc_bit('1'); // set enable.	
	sc_start(sc_time(10,SC_NS));
	a = sc_bit('0');
	b = sc_bit('0');
	sc_start(sc_time(10,SC_NS));
	a = sc_bit('0');
	b = sc_bit('1');
	sc_start(sc_time(10,SC_NS));
	a = sc_bit('1');
	b = sc_bit('0');
	sc_start(sc_time(10,SC_NS));
	a = sc_bit('1');
	b = sc_bit('1');
	sc_start(sc_time(10,SC_NS));

	sc_close_vcd_trace_file(tf);

}
