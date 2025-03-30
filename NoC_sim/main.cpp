#include <systemc.h>
#include "mesh_router.h"
#include "mesh_packet.h"

// Simple Processing Element (PE) for testing
SC_MODULE(ProcessingElement) {

	sc_port<sc_fifo_in_if<MeshPacket>> in_port;
	sc_port<sc_fifo_out_if<MeshPacket>> out_port;
	uint32_t x_pos, y_pos;

	SC_CTOR(ProcessingElement) : x_pos(0), y_pos(0) {
		
		SC_THREAD(pe_process);
		sensitive << in_port;
	}

	void set_position(uint32_t x, uint32_t y) {
		x_pos = x;
		y_pos = y;
	}

	void pe_process() {

		// Generate a test packet
	
		if(strcmp(this->name(),"PE_0_0") == 0) {
			cout << this->name() << " sending test packet " << endl;
			MeshPacket pkt;
			pkt.source_x = x_pos;
			pkt.source_y = y_pos;
			pkt.dest_x = 2;
			pkt.dest_y = 2;
			pkt.sequence = 0;
			pkt.type = DATA_PACKET;
			pkt.timestamp = sc_time_stamp().to_default_time_units();
			pkt.payload.raw[0] = 0x00;
			out_port->write(pkt);
			cout << "PE(" << x_pos << "," << y_pos << ") sent packet " << pkt.sequence
			     << " at " << sc_time_stamp() << endl;
			wait(10, SC_NS);
		}
	
		if(strcmp(this->name(),"PE_2_2") == 0) {
			cout << this->name() << " sending test packet " << endl;
			MeshPacket pkt;
			pkt.source_x = x_pos;
			pkt.source_y = y_pos;
			pkt.dest_x = 0;
			pkt.dest_y = 0;
			pkt.sequence = 1;
			pkt.type = DATA_PACKET;
			pkt.timestamp = sc_time_stamp().to_default_time_units();
			pkt.payload.raw[0] = 0x22;
			out_port->write(pkt);
			cout << "PE(" << x_pos << "," << y_pos << ") sent packet " << pkt.sequence
			     << " at " << sc_time_stamp() << endl;
			wait(10, SC_NS);
		}


		// Receive packets
		while (true) {
			MeshPacket pkt = in_port->read();
			cout << "-----------------------------------------------------" << endl;
			cout << "PE(" << x_pos << "," << y_pos << ") received packet "
			     << pkt.sequence << " from (" << pkt.source_x
			     << "," << pkt.source_y << ") at " << sc_time_stamp() << endl;
			cout << "Raw[0] value: 0x" << std::hex <<  static_cast<int>(pkt.payload.raw[0]) << endl;
			cout << "pkt's timestamp: " << std::dec <<  pkt.timestamp << endl;
			cout << "-----------------------------------------------------" << endl;
		}
	}
};

int sc_main(int argc, char* argv[]) {
	// Create 2x2 mesh
	const int MESH_SIZE = 3;
	MeshRouter* routers[MESH_SIZE][MESH_SIZE];
	ProcessingElement* pes[MESH_SIZE][MESH_SIZE];

	cout << "=== Initializing Network ===" << endl;

	// Initialize routers and PEs
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			// Create router
			std::string router_name = "Router_" + std::to_string(x) + "_" + std::to_string(y);
			routers[x][y] = new MeshRouter(router_name.c_str(), x, y, MESH_SIZE);
			cout << "Created " << router_name << endl;

			// Create PE
			std::string pe_name = "PE_" + std::to_string(x) + "_" + std::to_string(y);
			pes[x][y] = new ProcessingElement(pe_name.c_str());
			pes[x][y]->set_position(x, y);
			cout << "Created " << pe_name << endl;
		}
	}

	// Connect PEs to routers
	cout << "\n=== Connecting PEs ===" << endl;
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			auto* pe_to_router = new sc_fifo<MeshPacket>(4);
			auto* router_to_pe = new sc_fifo<MeshPacket>(4);

			pes[x][y]->out_port(*pe_to_router);
			routers[x][y]->in_pe(*pe_to_router);
			cout << "Connected " << "PE_" << x << "_" << y << ".out_port -> "
			     << "Router_" << x << "_" << y << ".in_pe" << endl;

			pes[x][y]->in_port(*router_to_pe);
			routers[x][y]->out_pe(*router_to_pe);
			cout << "Connected " << "Router_" << x << "_" << y << ".out_pe -> "
			     << "PE_" << x << "_" << y << ".in_port" << endl;
		}
	}

	sc_fifo<MeshPacket>* north_channels[MESH_SIZE][MESH_SIZE-1] = {nullptr};
	sc_fifo<MeshPacket>* south_channels[MESH_SIZE][MESH_SIZE-1] = {nullptr};
	//missing code same fashion as the working binding east-west//
	cout << "working binding north-south" << endl;
	for (int y = 0; y < MESH_SIZE - 1; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			if (!north_channels[x][y]) {
				north_channels[x][y] = new sc_fifo<MeshPacket>(4);
				routers[x][y]->out_north->bind(*north_channels[x][y]);
				routers[x][y+1]->in_south->bind(*north_channels[x][y]);
			}

			if (!south_channels[x][y]) {
				south_channels[x][y] = new sc_fifo<MeshPacket>(4);
				routers[x][y+1]->out_south->bind(*south_channels[x][y]);
				routers[x][y]->in_north->bind(*south_channels[x][y]);
			}
		}
	}
	cout << "working binding east-west" << endl;
	sc_fifo<MeshPacket>* east_channels[MESH_SIZE-1][MESH_SIZE] = {nullptr};
	sc_fifo<MeshPacket>* west_channels[MESH_SIZE-1][MESH_SIZE] = {nullptr};

	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE-1; x++) {
			if (!east_channels[x][y]) {
				east_channels[x][y] = new sc_fifo<MeshPacket>(4);
				routers[x][y]->out_east->bind(*east_channels[x][y]);
				routers[x+1][y]->in_west->bind(*east_channels[x][y]);
			}

			if (!west_channels[x][y]) {
				west_channels[x][y] = new sc_fifo<MeshPacket>(4);
				routers[x+1][y]->out_west->bind(*west_channels[x][y]);
				routers[x][y]->in_east->bind(*west_channels[x][y]);
			}
		}
	}

	// Verification prints
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			cout << "\nRouter_" << x << "_" << y << " port status:" << endl;
			cout << "  in_north: " << (routers[x][y]->in_north ? "EXISTS" : "NONE") << endl;
			cout << "  in_south: " << (routers[x][y]->in_south ? "EXISTS" : "NONE") << endl;
			cout << "  in_east: " << (routers[x][y]->in_east ? "EXISTS" : "NONE") << endl;
			cout << "  in_west: " << (routers[x][y]->in_west ? "EXISTS" : "NONE") << endl;
		}
	}



	// After all connections are made, add:
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			cout << "-------------------------------------------------------" << endl;
			cout << "\nRouter_" << x << "_" << y << " PE port status:" << endl;
			cout << "  in_pe: " << (routers[x][y]->in_pe.get_interface() ? "BOUND" : "UNBOUND") << endl;
			cout << "  out_pe: " << (routers[x][y]->out_pe.get_interface() ? "BOUND" : "UNBOUND") << endl;
		}
	}

	// ==============================================
	// PORT BINDING VERIFICATION CODE
	// ==============================================
	auto check_port = [](auto& port, const char* name) {
		if (port) {
			cout << "  " << name << ": "
			     << (port->get_interface() ? "BOUND" : "UNBOUND") << endl;
		} else {
			cout << "  " << name << ": NULL" << endl;
		}
	};

	cout << "\n=== Port Binding Verification ===" << endl;

	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			cout << "\nRouter_" << x << "_" << y << " port status:" << endl;
			// Check directional ports
			check_port(routers[x][y]->out_north, "out_north");
			check_port(routers[x][y]->in_north, "in_north");
			check_port(routers[x][y]->out_south, "out_south");
			check_port(routers[x][y]->in_south, "in_south");
			check_port(routers[x][y]->out_east, "out_east");
			check_port(routers[x][y]->in_east, "in_east");
			check_port(routers[x][y]->out_west, "out_west");
			check_port(routers[x][y]->in_west, "in_west");

			// Check PE ports
			cout << "  in_pe: " << (routers[x][y]->in_pe.get_interface() ? "BOUND" : "UNBOUND") << endl;
			cout << "  out_pe: " << (routers[x][y]->out_pe.get_interface() ? "BOUND" : "UNBOUND") << endl;
		}
	}
	cout << "=================================\n" << endl;


	// Start simulation
	cout << "\n=== Starting Simulation ===" << endl;
	sc_start(200, SC_NS);

	// Cleanup
	cout << "\n=== Cleaning Up ===" << endl;
	// Cleanup North-South channels
	for (int x = 0; x < MESH_SIZE; x++) {
		for (int y = 0; y < MESH_SIZE-1; y++) {
			delete north_channels[x][y];
			delete south_channels[x][y];
		}
	}

	// Cleanup East-West channels
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE-1; x++) {
			delete east_channels[x][y];
			delete west_channels[x][y];
		}
	}
	return 0;
}
