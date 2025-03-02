#include "systemc.h"

using namespace std;


#define nodes 3
#define SIM_TIME  10000

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
	//statistics
	int total_tx=0;
	int success_tx = 0;
	int failed_tx=0;	

	void transmit(void)
	{
		while(true)
		{

			std::cout << "["<<name()<<"]" << "@ " << sc_time_stamp() << "  TX(success/total) " << std::dec <<  success_tx <<  "/" << total_tx << std::hex << std::endl;
			int time = static_cast<int>(sc_time_stamp().to_double());

			if(access_req_send)
			{
				wait();
				//check to see if granted.
				//cout << name() << "check if granted request" << endl;
				if(access_granded.read() == 1) {
					success_tx +=1;
					failed_tx = 0;
					tx_id.write(0x0);
					tx_data.write(0x0);
					access_req.write('0');
					access_req_send = 0;
				} else {
					tx_id.write(0x0);
					tx_data.write(0x0);
					access_req.write('0');
					access_req_send = 0;
					failed_tx=1;
				}	
			}

			if( (((time > 0) && (time%15000)==0) && ( strcmp(name(),"node3")==0) && (bus_tx.read() == 0)) || (failed_tx && ( strcmp(name(),"node3")==0))) 
			{
				std::cout << "["<<name()<<"]" << "@ " << sc_time_stamp() << "  TX: " << "request to transmit" << std::endl;
				access_req.write('1');
				tx_id.write(0x123);
				tx_data.write(0xcafebabe);
				total_tx++;
				access_req_send = 1;
			} else if( ( ((time > 0) && ((time%12000)==0)) && (bus_tx.read() == 0)) || failed_tx)
			{
				cout << std::dec<<time <<std::hex << endl;
				//periodic transmission or retry from previous failure.
				std::cout << "["<<name()<<"]" << "@ " << sc_time_stamp() << "  TX: " << "request to transmit" << std::endl;
				access_req.write('1');
				if(strcmp(name(),"node1") == 0) { 
					tx_id.write(0x43);
					tx_data.write(0xabcd);
					total_tx++;
				} else if(strcmp(name(),"node2") == 0 ) {
					tx_id.write(0x82);
					tx_data.write(0xf3e5);
					total_tx++;
				}
				access_req_send = 1;
			}
			
			wait();
		}
	}

	void receive(void)
	{
		while(true)
		{
			if(bus_tx.read() == 1)
				std::cout <<"["<<name()<<"]" <<  "@ " << sc_time_stamp() << "  RX: " << " Received <-------ID: " << rx_id << " data: " << rx_data << std::endl;
			wait();
		}
	}
	
	void init(void)
	{
		tx_id.write(0x0);
		tx_data.write(0x0);
		access_req.write(0x0);
	}

	SC_CTOR(can_node)
	{
		std::cout << "CAN node created:\t" << name() << std::endl;
		SC_THREAD(transmit);
		sensitive << clock.pos();
		SC_THREAD(receive);
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
		for(int i = 0 ; i < nodes; i++)
			if(to_get[i] == 1)
				std::cout <<  "[BUS-request]: " "ID: " << std::hex << sd[i].id << " Payload: " << sd[i].data << std::endl;
	
	}
	
	void entry_func(void)
	{
		int winner;
		while(true) {
			std::cout << "[BUS]: " << "@ " << sc_time_stamp() << std::endl;
			if(!ongoing_reception && !ongoing_transmission && (static_cast<int>(sc_time_stamp().to_double()) != 0) )
			{
				for(int i =0; i < nodes; i++) {
					if(access_req[i].read() == 1) {
						to_get[i] = 1;	
					//	cout << "wanna send" << i << endl;
						sd[i].id = rx_id[i].read();
						sd[i].data = rx_data[i].read();
						collision+=1;
						ongoing_reception = 1;
					}	
				}	
				//nothing to receive.	
			}

			if(ongoing_reception) {	
			
				if(collision > 1) {
					collision = 1; //need for arbitration.
				} else {
					collision = 0; //no collision
				}
					
				print_bus_access();	

				//arbitration step.
				if(!collision) {
					std::cout <<  "[BUS-request]: NO-COLLISION"<< std::endl;
					for(int i = 0; i < nodes; i++){
						if(access_req[i].read() == 1){
							winner = i;
							break;
						}
					}
					
				} else {

					// logic for collision arbitration
					std::cout <<  "[BUS-request]: COLLISION"<< std::endl;
					int winner_id = 0xfff;
					int winner_idx = -1;
					for(int i = 0; i < nodes; i++)
					{
						if(to_get[i] == 1) {
							if(sd[i].id < winner_id) {
								winner_id = sd[i].id;
								winner_idx = i;
							}
						}
					}
					//cout << winner_id << " " << winner_idx << endl;	
					//ack winner
					winner = winner_idx;
				}
				access_granded[winner].write('1');
				//unack not winners. notify them that their transmission didn't won the arbitration.
				for(int i = 0; i < nodes; i++)
					if(i!=winner)
						access_granded[i].write('0');

				bus_tx.write('1');
				tx_data.write(sd[winner].data);
				tx_id.write(sd[winner].id);
				std::cout <<  "[BUS-TX]: " "ID: " << std::hex << sd[winner].id << " Payload: " << sd[winner].data << std::endl;
				to_get[winner] = 0;
				winner = 0;
					
				//reset structures.
				for(int i = 0; i < nodes; i++) {
					sd[i].id=0;
					sd[i].data = 0;
				}
				ongoing_transmission = 1;
				ongoing_reception = 0;
			} else if(ongoing_transmission)
			{
				access_granded[winner].write('0');
				tx_id.write(0x0);
				tx_data.write(0x0);
				bus_tx.write('0');	
				ongoing_transmission =0;
				for(int i = 0; i < nodes; i++)
					access_granded[i].write('0');


			}

			wait();

		}
	}

	SC_CTOR(can_bus)
	{
		std::cout << "can bus created:\t" << name() << std::endl;
		SC_THREAD(entry_func);
		sensitive << clock.pos();
	}
};

int sc_main(int argc, char *argv[])
{
	sc_clock clk("clk",5,SC_NS); 
	//initialization of nodes.
	can_node n1("node1");
	can_node n2("node2");
	can_node n3("node3");
	can_bus bus("can_bus1");	
	
	sc_signal<bit>		access_req_signal[nodes];
	sc_signal<sc_uint<32>>	rx_data_signal[nodes];
	sc_signal<sc_uint<32>>	rx_id_signal[nodes];
	sc_signal<bit>		access_granded_signal[nodes];
	sc_signal<sc_uint<32>>	tx_data_signal;
	sc_signal<sc_uint<32>>	tx_id_signal;
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

	
	//can node 3
	n3.clock(clk);
	n3.access_granded(access_granded_signal[2]);
	n3.rx_id(tx_id_signal);
	n3.rx_data(tx_data_signal);
	n3.tx_id(rx_id_signal[2]);
	n3.tx_data(rx_data_signal[2]);
	n3.access_req(access_req_signal[2]);
	n3.bus_tx(bus_tx_signal);
	

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
	n3.init();
	bus.init();
	//create the waveform
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
	//simulation
	sc_start(sc_time(SIM_TIME,SC_NS));
	//close trace waveform file.
	sc_close_vcd_trace_file(tf);

	return 0;

}
