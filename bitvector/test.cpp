#include "systemc.h"



int sc_main(int argc, char *argv[])
{
	sc_bv<8> data_bus ; 
	sc_bv<16> addr_bus;
	sc_bit parity;


	data_bus="00001011";
	cout << "data bus: " << data_bus << endl;

	addr_bus.range(1,0) = data_bus;
	cout << "addr_bus: " << addr_bus << endl;

	//assigns in reverse order.
	addr_bus.range(0,7) = data_bus;
	cout << "addr_bus: " << addr_bus << endl;

	addr_bus[15]='1';
	addr_bus[14]='1';
	addr_bus[12]='1';

	cout << "addr_bus: " << addr_bus << endl;

	cout << "parity data bus: " << data_bus.xor_reduce() <<  endl;
	cout << "parity addr bus: " << addr_bus.xor_reduce() <<  endl;
	return 0;
}
