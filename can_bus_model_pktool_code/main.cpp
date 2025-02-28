//#include "and2_gt.h"
//
#include "systemc.h"
#include "can.h"
#include "power_module_can.h"

//fix for working with g++-5
std::string to_string_fallback(int val)
{
	std::ostringstream oss;
	oss << val;
	return oss.str();
}

using namespace std;

int sc_main(int argc, char *argv[])
{
	sc_clock clk("clk",10,SC_NS); 

	//initialization of nodes.
	//
	POWER_MODULE(can_node) n1("node1");
	//can_node n1("node1");
//	can_node n2("node2");
	POWER_MODULE(can_node) n2("node2");
	can_bus bus("can_bus1");	
	
	sc_signal<bit>		access_req_signal[nodes];
	sc_signal< sc_uint<32> >	rx_data_signal[nodes];
	sc_signal< sc_uint<32> >	rx_id_signal[nodes];
	sc_signal<bit>		access_granded_signal[nodes];
	sc_signal< sc_uint<32> >	tx_data_signal;
	sc_signal< sc_uint<32> >	tx_id_signal;
	sc_signal<bit>		bus_tx_signal;

	//port mapping --automate the mappings.
	//can node1.
	n1.clock(clk);
	n1.access_granded(access_granded_signal[0]);
	n1.rx_id(tx_id_signal);
	n1.rx_data(tx_data_signal);
	n1.tx_id(rx_id_signal[0]);
	n1.tx_data(rx_data_signal[0]);
	n1.access_req(access_req_signal[0]);
	n1.bus_tx(bus_tx_signal);
	//CAN node2.
	n2.clock(clk);
	n2.access_granded(access_granded_signal[1]);
	n2.rx_id(tx_id_signal);
	n2.rx_data(tx_data_signal);
	n2.tx_id(rx_id_signal[1]);
	n2.tx_data(rx_data_signal[1]);
	n2.access_req(access_req_signal[1]);
	n2.bus_tx(bus_tx_signal);
	//bus mapping 	
	bus.clock(clk);
	for(int i = 0; i < nodes; i++)
	{
		bus.access_req[i](access_req_signal[i]);
		bus.access_granded[i](access_granded_signal[i]);
		bus.rx_id[i](rx_id_signal[i]);
		bus.rx_data[i](rx_data_signal[i]);
	}
	bus.tx_id(tx_id_signal);
	bus.tx_data(tx_data_signal);
	bus.bus_tx(bus_tx_signal);

	//initialize signals
	n1.init();
	n2.init();
	bus.init();
	//create the waveform
	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");
	for (int i = 0; i < nodes; i++) {
		sc_trace(tf, access_req_signal[i], "access_request_" + to_string_fallback(i));
		sc_trace(tf, access_granded_signal[i], "access_granted_" + to_string_fallback(i));
		sc_trace(tf, rx_id_signal[i], "rx_id_" + to_string_fallback(i));
		sc_trace(tf, rx_data_signal[i], "rx_data_" + to_string_fallback(i));
	}
	sc_trace(tf, tx_id_signal, "tx_id");
	sc_trace(tf, tx_data_signal, "tx_data");
	sc_trace(tf, bus_tx_signal, "bus_transmission");
	sc_trace(tf, clk, "clock");
	//simulation
	sc_start(sc_time(SIM_TIME,SC_NS));
	//close trace waveform file.
	sc_close_vcd_trace_file(tf);

	return 0;
}
