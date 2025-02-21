#include "systemc.h"
#define RAM_SIZE 1024
using namespace std;
SC_MODULE(Ram) {

	sc_in_clk clock;
	sc_in <bool> write;
	sc_in <bool> read;
	sc_in <sc_uint<32>> value;	
	sc_in <sc_uint<32>> addr_in;	

	sc_out <sc_uint<32>> addr_out;	
	uint32_t memory[RAM_SIZE];
	
	void func(void)
	{
		if( (write.read() == true) && (read.read() == false))
		{
			memory[addr_in.read()] = value.read();
			std::cout << std::hex <<  "@" << sc_time_stamp() << " Write addr[0x" << addr_in.read() <<"] <<-- " << value.read() << std::endl;
			addr_out.write(0x0);
		} else if( (write.read() == false) && (read.read() == true)) {
			addr_out.write(memory[addr_in.read()]);
			std::cout << "@" << sc_time_stamp() <<  "Read addr[0x" << addr_in.read() <<"] == " << memory[addr_in.read()] << std::endl;
		} else {
			std::cout << "@" << sc_time_stamp() << "R/W not specified." << std::endl;
			addr_out.write(0x0);
		}
	}

	SC_CTOR(Ram) {
		std::cout << "constructor Ram" << std::endl;	
		for(int i = 0; i < RAM_SIZE; i++)
		{
			memory[i] = 0x0;
		}

		SC_METHOD(func);
		sensitive << clock.pos();
	}
};

int sc_main(int argc, char *argv[])
{
	Ram r("ram");


	sc_clock clock("clk", 10, SC_NS); // 10 ns period clock
	sc_signal <bool> write;
	sc_signal <bool> read;
	sc_signal <sc_uint<32>> value;	
	sc_signal <sc_uint<32>> addr_in;	
	sc_signal <sc_uint<32>> addr_out;	
	
	
	r.clock(clock);
	r.write(write);
	r.read(read);
	r.value(value);
	r.addr_in(addr_in);
	r.addr_out(addr_out);


	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");
	sc_trace(tf,clock,"clk");
	sc_trace(tf,write,"write");
	sc_trace(tf,read,"read");
	sc_trace(tf,addr_in,"addr_in");
	sc_trace(tf,addr_out,"addr_out");
	
	write.write((bool)1);
	read.write((bool)0);
	value.write(0xabcd);
	addr_in.write(0x100);

	sc_start(10, SC_NS); // Run for 10 ns

	write.write((bool)0);
	read.write((bool)1);
	addr_in.write(0x100);

	sc_start(10, SC_NS); // Run for 10 ns
	write.write((bool)1);
	read.write((bool)1);

	sc_start(10, SC_NS); // Run for 10 ns


	sc_close_vcd_trace_file(tf);

	return 0;
}
