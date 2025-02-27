#include "systemc.h"
//#include "PKtool.h"

using namespace std;


#define nodes 2
#define SIM_TIME  300

typedef sc_uint<1> bit;

//details of a sender each time.
struct sender_details {
	sc_uint<32> id;
	sc_uint<32> data;
};

SC_MODULE(can_node)
{

	sc_in_clk		clock;

	sc_in<bit>		access_granded;
	//reception from bus.
	sc_in<sc_uint<32>>	rx_id;
	sc_in<sc_uint<32>>	rx_data;
	sc_in<bit>		bus_tx;
	//transmission to bus	
	sc_out<sc_uint<32>>	tx_id;
	sc_out<sc_uint<32>>	tx_data;
	//for accessing the bus.	//arbitration.
	sc_out<bit>		access_req;	

	int id;
	int access_req_send = 0;	

	void transmit(void)
	{
	
//		std::cout << "@ " << sc_time_stamp() << "  TX: " << name() << std::endl;
	        int time = static_cast<int>(sc_time_stamp().to_double());
		
		if(access_req_send) {
			
//			std::cout << "@ " << sc_time_stamp() << " " << name() << "checking if access granded finised" <<  std::endl;
			if(access_granded.read() == '1') {
				cout << access_granded.read() <<endl;
			} else {
				access_req.write('0');
				tx_data.write(0x0);	
				tx_id.write(0x0);
			}	
		}

		//request a transmission.	
		if( ( (time > 0) && (time%15)==0) && ( strcmp(name(),"node1")==0 ) && (bus_tx.read() == 0) )
		{
			std::cout << "@ " << sc_time_stamp() << "  TX: " << name() << std::endl;
			access_req.write('1');
			tx_id.write(0x13);
			tx_data.write(0xabcd);
			access_req_send = 1;
			return;
		}
	}
	
	void receive(void)
	{
		if(bus_tx.read() == 0)
			return;	
		std::cout << "@ " << sc_time_stamp() << "  RX: " << name() << " Received <-------ID: " << rx_id << " data: " << rx_data << std::endl;
	}
	
	void init(void)
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
	sc_in_clk		clock;
	//for access request on the bus from nodes.
	sc_in<bit>		access_req[nodes];
	//for receiving message from the respective CAN node who 
	//won the arbitration
	sc_in<sc_uint<32>>	rx_data[nodes];
	sc_in<sc_uint<32>>	rx_id[nodes];

	//granding access to a specific
	//can node to transmit a can message.
	sc_out<bit>		access_granded[nodes];
	//for transmission of bus messages to all
	//can nodes.	
	sc_out<sc_uint<32>>	tx_data;
	sc_out<sc_uint<32>>	tx_id;

	//bus transmit(broadcast CAN message behavior)
	sc_out<bit>		bus_tx;
	
	int ongoing_reception = 0;
	int ongoing_transmission = 0;

	
	sender_details sd[nodes];
	int to_get[nodes];
	int collision = 0;
	int winner;
	int reception = 0; // states that bus have to receive.
	void init(void)
	{
		//initialy no node has access to transmit.
		for(int i = 0; i < nodes; i++) {
			access_granded[i].write('0');	
			bus_tx.write('0');
			tx_data.write(0x0);
			tx_id.write(0x0);	
			to_get[i] = 0;
			sd[i].id = 0;
			sd[i].data = 0;
		}
	}
	void print_bus_access(void)
	{
		std::cout << "@ " << sc_time_stamp() << ", Transmission requests:: " <<std::endl;
		for(int i = 0 ; i < nodes; i++)
			if(to_get[i] == 1)
				std::cout << "ID: " << std::hex << sd[i].id << " Payload: " << sd[i].data << std::endl;
	}
	void perform_arbitration(void)
	{
		//logic when no collision.
		if(!collision) {
			for(int i = 0; i < nodes; i++){
				if(to_get[i] == 1)
					winner = i;
					break;
			}
		}
		// logic for collision arbitration

	}

	
	void entry_func(void)
	{
	//	std::cout << "bus activated" << std::endl;
		if(!ongoing_reception && !ongoing_transmission && (static_cast<int>(sc_time_stamp().to_double()) != 0) )
		{
			for(int i =0; i < nodes; i++) {
				if(access_req[i].read() == 1) {
					to_get[i] = 1;	
					sd[i].id = rx_id[i].read();			
					sd[i].data = rx_data[i].read();			
					collision+=1;
				}	
			}	
			//nothing to receive.	
			if(!collision)
				return;
			if(collision > 1)
				collision = 1; //need for arbitration.
			else
				collision = 0; //no collision
			
			print_bus_access();	
			//ack the arbitration winner to send data.
			//winner[] 's index hold the winner on the arbitration.
			perform_arbitration();
			access_granded[winner].write('1');
			ongoing_reception = 1;
		}

		if(ongoing_reception) {	
			bus_tx.write('1');
			tx_data.write(sd[winner].data);
			tx_id.write(sd[winner].id);
			access_granded[winner].write('0');
			to_get[winner] = 0;
			winner = 0;
			for(int i = 0; i < nodes; i++) {
				sd[i].id=0;
				sd[i].data = 0;
			}

			ongoing_reception = 0;
			ongoing_transmission = 1;
		} else if(ongoing_transmission) {
			tx_data.write(0x0);
			tx_id.write(0x0);
			bus_tx.write('0');	
			ongoing_transmission = 0;
		}

	}

	SC_CTOR(can_bus)
	{
		std::cout << "can bus created:\t" << name() << std::endl;
		SC_METHOD(entry_func);
		sensitive << clock.pos();
	}
};

int sc_main(int argc, char *argv[])
{
	sc_clock clk("clk",10,SC_NS); 

	//initialization of nodes.
	can_node n1("node1");
	can_node n2("node2");
	can_bus bus("can_bus1");	
	
	sc_signal<bit>		access_req_signal[nodes];
	sc_signal<sc_uint<32>>	rx_data_signal[nodes];
	sc_signal<sc_uint<32>>	rx_id_signal[nodes];
	sc_signal<bit>		access_granded_signal[nodes];
	sc_signal<sc_uint<32>>	tx_data_signal;
	sc_signal<sc_uint<32>>	tx_id_signal;
	sc_signal<bit>		bus_tx_signal;

	//port mapping --automate the mappings.
	n1.clock(clk);
	n1.access_granded(access_granded_signal[0]);
	n1.rx_id(tx_id_signal);
	n1.rx_data(tx_data_signal);
	n1.tx_id(rx_id_signal[0]);
	n1.tx_data(rx_data_signal[0]);
	n1.access_req(access_req_signal[0]);
	n1.bus_tx(bus_tx_signal);

	n2.clock(clk);
	n2.access_granded(access_granded_signal[1]);
	n2.rx_id(tx_id_signal);
	n2.rx_data(tx_data_signal);
	n2.tx_id(rx_id_signal[1]);
	n2.tx_data(rx_data_signal[1]);
	n2.access_req(access_req_signal[1]);
	n2.bus_tx(bus_tx_signal);
	

	
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

	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");
	for (int i = 0; i < nodes; i++) {
		sc_trace(tf, access_req_signal[i], "access_request_" + std::to_string(i));
		sc_trace(tf, access_granded_signal[i], "access_granted_" + std::to_string(i));
		sc_trace(tf, rx_id_signal[i], "rx_id_" + std::to_string(i));
		sc_trace(tf, rx_data_signal[i], "rx_data_" + std::to_string(i));
	}
	sc_trace(tf, tx_id_signal, "tx_id");
	sc_trace(tf, tx_data_signal, "tx_data");
	sc_trace(tf, bus_tx_signal, "bus_transmission");
	sc_trace(tf, clk, "clock");


	sc_start(sc_time(SIM_TIME,SC_NS));

	sc_close_vcd_trace_file(tf);


	return 0;

}
