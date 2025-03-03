#include "systemc.h"
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#define nodes 2

using namespace tlm;
using namespace tlm_utils;

struct CAN_message
{
	int id;
	char data[8];
};

// can_node module.
SC_MODULE(can_node)
{
	// initiator socket for transmission on CAN bus.
	simple_initiator_socket<can_node> tx_socket;
	
	int id;

	SC_CTOR(can_node) : tx_socket("tx_socket")
	{
		SC_THREAD(run);
	}

	void run(void)
	{
		while(1)
		{
			// Create a payload
			CAN_message m;	
			tlm_generic_payload payload;
			sc_time delay = SC_ZERO_TIME;

			if(strcmp(name(),"top.node1") == 0)
			{
				m.id = 0x13;
				strcpy(m.data,"cafe");
				// Set up the payload
				payload.set_command(TLM_WRITE_COMMAND);
				payload.set_data_ptr(reinterpret_cast<unsigned char*>(&m));
				payload.set_data_length(sizeof(CAN_message));
				// Send the payload
				cout << name() << " TX id = " << std::hex << m.id << " data:" << m.data <<  " at time " << sc_time_stamp() << endl;
				tx_socket->b_transport(payload, delay);
				wait(sc_time(20,SC_NS));
			} else if(strcmp(name(),"top.node2") == 0)
			{
				m.id = 0x14;
				strcpy(m.data,"1293");
				// Set up the payload
				payload.set_command(TLM_WRITE_COMMAND);
				payload.set_data_ptr(reinterpret_cast<unsigned char*>(&m));
				payload.set_data_length(sizeof(CAN_message));
				// Send the payload
				cout << name() << " TX id = " << std::hex << m.id << " data:" << m.data <<  " at time " << sc_time_stamp() << endl;
				tx_socket->b_transport(payload, delay);
				wait(sc_time(30,SC_NS));
			} 
		}
	}
};

// can_bus module.
SC_MODULE(can_bus)
{
	// initiator socket for transmission on CAN bus.
	simple_target_socket<can_bus> rx_socket[nodes];

	SC_CTOR(can_bus) 
	{
		for(int i = 0; i < nodes; i++) {
			char socket_name[20];
			// Format the socket name ("rx_socket0" etc.)
			std::sprintf(socket_name, "rx_socket%d", i);
			// Register b_transport callback
			rx_socket[i].register_b_transport(this, &can_bus::b_transport);
		}	
	}

	//override b_transport()  
	void b_transport(tlm_generic_payload& payload, sc_time& delay) {
		// Read the data
		CAN_message data = *reinterpret_cast<CAN_message*>(payload.get_data_ptr());
		//unsigned int data = *reinterpret_cast<unsigned int*>(payload.get_data_ptr());
		cout << name() << "[BUS reception]  id: " << std::hex << data.id << " data: " <<data.data << " at time " << sc_time_stamp() << endl;
	}

};

// Top Module
SC_MODULE(Top) {
    can_node n1;
    can_bus b;
    can_node n2;
    SC_CTOR(Top) : n1("node1"), n2("node2"), b("bus") {
        n1.tx_socket.bind(b.rx_socket[0]);
        n2.tx_socket.bind(b.rx_socket[1]);
    }
};

int sc_main(int argc, char* argv[]) {
    Top top("top");
    sc_start(100, SC_NS);
    return 0;
}
