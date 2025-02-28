#ifndef CAN_H
#define CAN_H

#include "systemc.h"
#include "PKtool.h"

using namespace std;

#define nodes 2
#define SIM_TIME  400

typedef sc_uint<1> bit;

//details of a sender each time.
struct sender_details {
	sc_uint<32> id;
	sc_uint<32> data;
};

SC_MODULE(can_node)
{
	//ports
	sc_in_clk		clock;
	sc_in_aug<bit>		access_granded;
	//reception from bus.
	sc_in_aug< sc_uint<32> >	rx_id;
	sc_in_aug< sc_uint<32> >	rx_data;
	sc_in_aug<bit>		bus_tx;
	//transmission to bus	
	sc_out_aug< sc_uint<32> >	tx_id;
	sc_out_aug< sc_uint<32> >	tx_data;
	//for accessing the bus.	//arbitration.
	sc_out_aug<bit>		access_req;	

	int id;
	int access_req_send = 0;	
	//statistics
	int total_tx=0;
	int success_tx = 0;

	void transmit(void)
	{
		while(true)
		{
			std::cout << "["<<name()<<"]" << "@ " << sc_time_stamp() << "  TX_SUCCES: " << success_tx <<  "/ TX_TOTAL: " << total_tx << std::endl;
			int time = static_cast<int>(sc_time_stamp().to_double());
			
			if(access_req_send)
			{
				//check to see if granted.
				if(access_granded.read() == 1)
					success_tx +=1;
				tx_id.write(0x0);
				tx_data.write(0x0);
				access_req.write('0');
			}

			if( ( (time > 0) && (time%15)==0) &&(bus_tx.read() == 0) )
			//if( ( (time > 0) && (time%15)==0) && ( strcmp(name(),"node1")==0 ) && (bus_tx.read() == 0) )
			{
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
		std::cout << "can node created:\t" << name() << std::endl;
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
	sc_in< sc_uint<32> >	rx_data[nodes];
	sc_in< sc_uint<32> >	rx_id[nodes];

	//granding access to a specific
	//can node to transmit a can message.
	sc_out<bit>		access_granded[nodes];
	//for transmission of bus messages to all
	//can nodes.	
	sc_out< sc_uint<32> >	tx_data;
	sc_out< sc_uint<32> >	tx_id;

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
						cout << "wanna send" << i << endl;
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
						if(to_get[i] == 1)
							winner = i;
							cout << "winner is " << i << endl;
							cout << "winner is " << winner << endl;
							break;
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
					cout << winner_id << " " << winner_idx << endl;	
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
#endif
