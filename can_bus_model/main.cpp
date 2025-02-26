#include "systemc.h"
using namespace std;


#define nodes 2
typedef sc_uint<1> bit;

SC_MODULE(can_node)
{

	sc_in_clk		clock;

	sc_in<bit>		access_granded;
	//reception from bus.
	sc_in<sc_uint<32>>	rx_id;
	sc_in<sc_uint<32>>	rx_data;
	//transmision to bus	
	sc_out<sc_uint<32>>	tx_id;
	sc_out<sc_uint<32>>	tx_data;
	//for accessing the bus.	//arbitration.
	sc_out<bit>		access_req;	

	int id;
	int access_req_send = 0;	

	void transmit(void)
	{
		std::cout << "@ " << sc_time_stamp() << "  TX: " << name() << std::endl;
	        int time = static_cast<int>(sc_time_stamp().to_double());

		if( ( (time%15)==0) && ( strcmp(name(),"node1")==0 ) )
		{
			std::cout << "need to TX: " << name() << std::endl;
			access_req.write('1');
			access_req_send = 1;
			sc_stop();
		}


	}
	
	void receive(void)
	{
		std::cout << "@ " << sc_time_stamp() << "  RX: " << name() << std::endl;
		
	}
	
	void init()
	{
		tx_id.write(0x0);
		tx_data.write(0x0);
		access_req.write(0x0);
	}
	SC_CTOR(can_node)
	{
		std::cout << "can node created:\t" << name() << std::endl;
		SC_METHOD(transmit);
		sensitive << clock.pos();
		SC_METHOD(receive);
		sensitive << clock.pos();

	
	}

};

SC_MODULE(can_bus)
{
	sc_in_clk clock;
	//for access request on the bus from nodes.
	sc_in<bit>access_req[nodes];
	//for receiving message from the respective CAN node who 
	//won the arbitration
	sc_in<sc_uint<32>> rx_data[nodes];
	sc_in<sc_uint<32>> rx_id[nodes];

	//granding access to a specific
	//can node to transmit a can message.
	sc_out<bit> access_granded[nodes];
	//for transmision of bus messages to all
	//can nodes.	
	sc_out<sc_uint<32>> tx_data;
	sc_out<sc_uint<32>> tx_id;

	void init()
	{
		//initialy no node has access to transmit.
		for(int i = 0; i < nodes; i++) {
			access_granded[i].write('0');	
			tx_data.write(0x0);
			tx_id.write(0x0);	
	}

	}
	SC_CTOR(can_bus)
	{
		std::cout << "can bus created:\t" << name() << std::endl;


		//initialy no node has access to transmit.
		for(int i = 0; i < nodes; i++) {
			access_granded[i].write('0');	
			tx_data.write(0x0);
			tx_id.write(0x0);	
		}
	}
};

int sc_main(int argc, char *argv[])
{
	sc_clock clk("clk",10,SC_NS); 

	//initialization of nodes.
	can_node n1("node1");
	can_node n2("node2");
	can_bus bus("can_bus1");	
	
	sc_signal<bit> access_req_signal[nodes];
	sc_signal<sc_uint<32>> rx_data_signal[nodes];
	sc_signal<sc_uint<32>> rx_id_signal[nodes];
	sc_signal<bit> access_granded_signal[nodes];
	sc_signal<sc_uint<32>> tx_data_signal;
	sc_signal<sc_uint<32>> tx_id_signal;

	//port mapping --automate the mappings.
	n1.clock(clk);
	n1.access_granded(access_granded_signal[0]);
	n1.rx_id(tx_id_signal);
	n1.rx_data(tx_data_signal);
	n1.tx_id(rx_id_signal[0]);
	n1.tx_data(rx_data_signal[0]);
	n1.access_req(access_req_signal[0]);

	n2.clock(clk);
	n2.access_granded(access_granded_signal[1]);
	n2.rx_id(tx_id_signal);
	n2.rx_data(tx_data_signal);
	n2.tx_id(rx_id_signal[1]);
	n2.tx_data(rx_data_signal[1]);
	n2.access_req(access_req_signal[1]);
	

	
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
	

//	n1.init();
//	n2.init();
//	bus.init();

	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");

	sc_trace(tf,access_req_signal,"access_request");
	sc_trace(tf,access_granded_signal,"access_granded");


	sc_start();
	sc_start(sc_time(100,SC_NS));

	sc_close_vcd_trace_file(tf);
	return 0;

}
