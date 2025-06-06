/*
 * Mouzakitis N. 2025.
 */


#include "systemc.h"
#include "mesh_router.h"
#include "mesh_packet.h"
#include "mesh.cpp"
#include "thermal_model.h"
#include <set>
#include <random>
#include <fstream>
#include <iomanip>
#include <map>
#include <iostream>
#include <vector>

using namespace std;
//extern const int MESH_SIZE = 3;

Mesh m; //mesh for controlling cores-memories.

#define SC_ALLOW_DEPRECATED_IEEE_API 1

#define ROUTER_BUFFER_SIZE	8 //affects the dropped packets observation
#define TRAFFIC_INJECTION_RATE 14
#define SIMULATION_TIME	 7000
#define PE_ROUTER_FIFO_SIZE 4
#define ROUTER_ROUTER_FIFO_SIZE 4

//traffic patterns
#define UNI		1  //uniform random traffic pattern.
#define BT		2  //bit complement traffic pattern.
#define TRANSPOSE	3  //Transpose traffic pattern. //not-used since we don't send self messages.
#define CUSTOM		4

std::set<uint32_t> global_sent_packets; //storing sent packets sequence no.
std::set<uint32_t> global_received_packets; //storing received packets sequence no.

int traffic_pattern = UNI;

// incorporation of data from PARSEC-PINTOOL
struct MemoryAccess {
	int id;
	int core_id;
	char access_type; // 'R' or 'W'
	uint64_t address;
};

// This will hold all memory access traces.
std::vector<MemoryAccess> trace_data;

void load_trace_from_file(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Failed to open trace file: " << filename << std::endl;
		return;
	}

	MemoryAccess access;
	while (file >> access.id >> access.core_id >> access.access_type >> std::hex >> access.address) {
		trace_data.push_back(access);
	}

	std::cout << "Loaded " << trace_data.size() << " memory accesses." << std::endl;
}



double get_random_probability() {
	static std::random_device rd;  // True random number generator
	static std::mt19937 gen(rd()); // Mersenne Twister engine
	static std::uniform_real_distribution<> dis(0.0, 1.0);

	return dis(gen);
}

void print_thermal_heatmap(const ThermalModel& thermal, int size) {
	static std::ofstream thermal_log("thermal_data.csv", std::ios::app);
	static bool header_written = false;
	double current_time = sc_time_stamp().to_seconds();

	// Print to console (your original code)
	cout << "\n\t\t\t\t\t\t Thermal Heatmap: @ " << sc_time_stamp() <<"\n";
	cout << "     ";
	cout << "\t\t\t\t\t" ;
	for (int x = 0; x < size; x++) cout << "    X=" << x << "  ";
	cout << "\n";

	for (int y = 0; y < size; y++) {
		cout << "\t\t\t\t\t" ;
		cout << "Y=" << y << " ";
		for (int x = 0; x < size; x++) {
			double temp = thermal.get_temperature(x, y);
			// Color coding based on temperature
			if (temp > 70.0) cout << "\033[1;31m"; // Red
			else if (temp > 60.0) cout << "\033[1;33m"; // Yellow
			else cout << "\033[1;32m"; // Green
			cout << std::fixed << std::setprecision(1) << temp << "°C\033[0m  ";
		}
		cout << endl;
	}

	// Log data to CSV file
	if (!header_written) {
		thermal_log << "Time";
		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				thermal_log << ",Core_" << x << "_" << y;
			}
		}
		thermal_log << "\n";
		header_written = true;
	}

	thermal_log << current_time;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			thermal_log << "," << thermal.get_temperature(x, y);
		}
	}
	thermal_log << "\n";
}


/////////////////////SPLITTING PROCESSING ELEMENTS into cores and memories /////////////

// Simple Processing Element (PE) for testing
SC_MODULE(ProcessingElement) {

	sc_port<sc_fifo_in_if<MeshPacket>> in_port;
	sc_port<sc_fifo_out_if<MeshPacket>> out_port;
	uint32_t x_pos, y_pos;

	bool use_trace;
	int core_id;


	SC_CTOR(ProcessingElement) : x_pos(0), y_pos(0), use_trace(false), core_id(-1) {

		//assignation of cores and memories in the Routers of the NoC.
		m.assignCore(0,0,0);
		m.assignCore(0,1,1);
		m.assignCore(0,2,2);
		m.assignCore(1,0,3);
		m.assignMemory(2,2,204); 
	//	m.assignMemory(1,2,101);
	//	m.assignMemory(2,0,205);
	//	m.assignMemory(2,1,302);
		
		//m.displayMesh();	
		m.splitMemoryAddresses(0x800000000000);

		SC_THREAD(pe_process);
		SC_THREAD(traffic_gen);
		//sensitive << in_port;
	}

	void set_position(uint32_t x, uint32_t y) {
		x_pos = x;
		y_pos = y;
	}

	void set_core_id(int id) {
		core_id = id;
	}
	//random uniform traffic generation within' the Network on Chip.
	/*
		void traffic_gen(void) {
			static uint32_t seq_cnt = 0;
			size_t trace_index = 0;
			while (true) {

				wait(TRAFFIC_INJECTION_RATE, SC_NS);  // Inject a packet every 100ns (adjust as needed)


				if(strcmp(this->name(),"PE_0_3") == 0)
					continue;
				if(strcmp(this->name(),"PE_0_2") == 0)
					continue;
				if(strcmp(this->name(),"PE_0_1") == 0)
					continue;
				if(strcmp(this->name(),"PE_0_0") == 0)
					continue;
				if(strcmp(this->name(),"PE_1_3") == 0)
					continue;
				if(strcmp(this->name(),"PE_1_2") == 0)
					continue;
				if(strcmp(this->name(),"PE_1_1") == 0)
					continue;
				if(strcmp(this->name(),"PE_1_0") == 0)
					continue;

				if( (traffic_pattern == CUSTOM) && (strcmp(this->name(),"PE_1_1") == 0))
					continue;

				MeshPacket pkt;
				pkt.source_x = x_pos;
				pkt.source_y = y_pos;
				pkt.sequence = seq_cnt++;
				do {
					switch(traffic_pattern) {
					case(UNI):      // Uniform random destination (excluding self)
						pkt.dest_x = rand() % MESH_SIZE;
						pkt.dest_y = rand() % MESH_SIZE;
						break;
					case(BT) :	// Bit complement destination
						pkt.dest_x = MESH_SIZE - 1 - x_pos;
						pkt.dest_y = MESH_SIZE - 1 - y_pos;
						break;
					case(TRANSPOSE):
						pkt.dest_x = y_pos;
						pkt.dest_y = x_pos;
						break;
					case(CUSTOM):
						pkt.dest_x = 1;
						pkt.dest_y = 1;
						break;
					}
				} while (pkt.dest_x == x_pos && pkt.dest_y == y_pos);

				//timestamp it.

				pkt.timestamp = sc_time_stamp();
				//forwarding packet to router.
				out_port->write(pkt);
				global_sent_packets.insert(pkt.sequence); //logging the packet as sent with this sequence number.
				cout << this->name() << " sent packet to (" << pkt.dest_x << "," << pkt.dest_y << ") @ " << sc_time_stamp() << endl;
			}
		}
	*/


	//from reading the PIN out file.
	void traffic_gen(void) {

		static uint32_t seq_cnt = 0;
		size_t trace_index = 0;
	
		while (true) {
			// If we're not using trace traffic, you can skip or run your old synthetic generator
			if (!use_trace) {
				wait(TRAFFIC_INJECTION_RATE, SC_NS);
				continue;
			}

			// Scan until we find a matching entry
			while (trace_index < trace_data.size() && trace_data[trace_index].core_id != core_id) {
				trace_index++;
			}
			
			if (trace_index >= trace_data.size()) {
				// All relevant entries for this core have been sent
				wait(1, SC_MS); // Just idle to not exit the thread
				continue;
			}

			const auto& access = trace_data[trace_index++];

			MeshPacket pkt;
			pkt.source_x = x_pos;
			pkt.source_y = y_pos;
			pkt.sequence = seq_cnt++;
		/*	
			cout << std::hex << access.address <<endl;
			cout << std::hex << (access.address >>3) <<endl;
			cout << std::hex << (access.address >>6) <<endl;
			unsigned long tt = access.address;
			cout << std::hex << tt <<endl;
			while(1);
		*/
			// Address to destination mapping
//			pkt.dest_x = (access.address >> 3) % MESH_SIZE;
//			pkt.dest_y = (access.address >> 6) % MESH_SIZE;
			
			int mem_id = m.getMemoryIdByAddress(access.address);
			auto dest_coords = m.getCoordinatesByMemoryId(mem_id);

			pkt.dest_x = dest_coords.first;
			pkt.dest_y = dest_coords.second;

			if (pkt.dest_x == x_pos && pkt.dest_y == y_pos) {
				wait(TRAFFIC_INJECTION_RATE, SC_NS);
				continue;  // skip sending to self
			}

			pkt.timestamp = sc_time_stamp();
			pkt.payload.raw[0] = (access.access_type == 'W') ? 0xAA : 0xBB;

			out_port->write(pkt);
			global_sent_packets.insert(pkt.sequence);

			std::cout << this->name() << " [TRACE] sent "
			          << access.access_type << " to ("
			          << pkt.dest_x << "," << pkt.dest_y << ") [0x"
			          << std::hex << access.address << "] @ "
			          << sc_time_stamp() << std::endl;

			wait(TRAFFIC_INJECTION_RATE, SC_NS);
		}
	}

	//reception process of processing element.
	void pe_process() {
		// Receive packets
		while (true) {
			MeshPacket pkt = in_port->read();
			sc_time latency = sc_time_stamp() - pkt.timestamp;

			//logging operation.
			global_received_packets.insert(pkt.sequence);

			cout << "-----------------------------------------------------" << endl;
			cout << "PE(" << x_pos << "," << y_pos << ") received packet sequence: "
			     << pkt.sequence << " from (" << pkt.source_x
			     << "," << pkt.source_y << ") at " << sc_time_stamp() << " PACKET's LATENCY:  " << latency << endl;
			cout << "Raw[0] value: 0x" << std::hex <<  static_cast<int>(pkt.payload.raw[0]) << endl;
			cout << "pkt's timestamp: " << std::dec <<  pkt.timestamp << endl;
			cout << "-----------------------------------------------------" << endl;
		}
	}
};

void inspect_sc_fifo(sc_fifo<MeshPacket>& fifo, const std::string& fifo_name) {
	size_t num_packets = fifo.num_available();
	if (num_packets > 0) {
		cout << "  " << fifo_name << ": " << num_packets << " packets" << endl;
		cout << "  Contents:" << endl;
		for (size_t i = 0; i < num_packets; ++i) {
			MeshPacket pkt = fifo.read(); // Read packet from FIFO
			cout << "    Seq: " << pkt.sequence << " from (" << pkt.source_x << "," << pkt.source_y
			     << ") to (" << pkt.dest_x << "," << pkt.dest_y << ")" << endl;
			fifo.write(pkt); // Write packet back to FIFO to preserve its state
		}
	} else {
		cout << "  " << fifo_name << ": EMPTY" << endl;
	}
}

int sc_main(int argc, char* argv[]) {

	ThermalModel thermal(MESH_SIZE);

	MeshRouter* routers[MESH_SIZE][MESH_SIZE];
	ProcessingElement* pes[MESH_SIZE][MESH_SIZE];

	cout << "=== Initializing Network ===" << endl;

	load_trace_from_file("noc_trace.out");
	

//	while(1);

	// Initialize routers and PEs
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			// Create router
			std::string router_name = "Router_" + std::to_string(x) + "_" + std::to_string(y);
			routers[x][y] = new MeshRouter(router_name.c_str(), x, y, MESH_SIZE, ROUTER_BUFFER_SIZE);
			cout << "Created " << router_name << endl;

			// Create PE
			std::string pe_name = "PE_" + std::to_string(x) + "_" + std::to_string(y);
			pes[x][y] = new ProcessingElement(pe_name.c_str());
			pes[x][y]->set_position(x, y);
			pes[x][y]->use_trace=true;
			
			//getter integrating mesh class.
//			pes[x][y]->set_core_id(y*MESH_SIZE+x); //unique id per PE.
			pes[x][y]->set_core_id(m.getMemoryIdByCoordinates(x, y));
			cout << "Created " << pe_name << endl;
		}
	}

	//set ptrs of routers to thermal model.
	for(int y=0; y<MESH_SIZE; y++) {
		for(int x=0; x<MESH_SIZE; x++) {
			thermal.set_router_ptr(x, y, routers[x][y]);
		}
	}

	// Connect PEs to routers
	cout << "\n=== Connecting PEs ===" << endl;
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			auto* pe_to_router = new sc_fifo<MeshPacket>(PE_ROUTER_FIFO_SIZE);
			auto* router_to_pe = new sc_fifo<MeshPacket>(PE_ROUTER_FIFO_SIZE);

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
				north_channels[x][y] = new sc_fifo<MeshPacket>(ROUTER_ROUTER_FIFO_SIZE);
				routers[x][y]->out_north->bind(*north_channels[x][y]);
				routers[x][y+1]->in_south->bind(*north_channels[x][y]);
			}

			if (!south_channels[x][y]) {
				south_channels[x][y] = new sc_fifo<MeshPacket>(ROUTER_ROUTER_FIFO_SIZE);
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
				east_channels[x][y] = new sc_fifo<MeshPacket>(ROUTER_ROUTER_FIFO_SIZE);
				routers[x][y]->out_east->bind(*east_channels[x][y]);
				routers[x+1][y]->in_west->bind(*east_channels[x][y]);
			}

			if (!west_channels[x][y]) {
				west_channels[x][y] = new sc_fifo<MeshPacket>(ROUTER_ROUTER_FIFO_SIZE);
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
	sc_time sim_time = sc_time(SIMULATION_TIME,SC_NS);
	sc_time thermal_update_interval(100,SC_NS);
	while(sc_time_stamp() < sim_time)
	{
		sc_start(thermal_update_interval);
		thermal.update_temperatures();
		print_thermal_heatmap(thermal, MESH_SIZE);
	}

	//sc_start(SIMULATION_TIME, SC_NS);


	// Check for lost packets after simulation ends
	cout << "\n=== Packet Loss Report(Sent but not received) ===" << endl;
	std::set<uint32_t> lost_packets;

	cout << "Total sent Packets:  " << global_sent_packets.size() << endl;
	// Compare sent and received packets
	for (uint32_t seq : global_sent_packets) {
		if (global_received_packets.find(seq) == global_received_packets.end()) {
			lost_packets.insert(seq);  // Packet was never received
		}
	}

	// Print lost packets
	if (lost_packets.empty()) {
		cout << "No packets lost!" << endl;
	} else {
		cout << "Total lost packets: " << lost_packets.size() << endl;
		cout << "Lost sequences: ";
		for (uint32_t seq : lost_packets) {
			cout << seq << " ";
		}
		cout << endl;
	}
	cout << "\n=== Packets Still in Router Buffers and PE-ROUTER FIFOS ===" << endl;
	size_t total_buffered_packets = 0;

	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			// Calculate packets in router buffers
			size_t router_buffered = routers[x][y]->i_buffer.size() + routers[x][y]->o_buffer.size();

			// Print router buffer contents
			if (router_buffered > 0) {
				cout << "Router_" << x << "_" << y << " has " << router_buffered << " packets:" << endl;
				cout << "  i_buffer: " << routers[x][y]->i_buffer.size() << " packets" << endl;
				cout << "  o_buffer: " << routers[x][y]->o_buffer.size() << " packets" << endl;

				// Optional: Print details of buffered packets
				std::deque<MeshPacket> temp_i = routers[x][y]->i_buffer;
				std::deque<MeshPacket> temp_o = routers[x][y]->o_buffer;

				cout << "  i_buffer contents:" << endl;
				while (!temp_i.empty()) {
					MeshPacket pkt = temp_i.front();
					cout << "    Seq: " << pkt.sequence << " from (" << pkt.source_x << "," << pkt.source_y
					     << ") to (" << pkt.dest_x << "," << pkt.dest_y << ")" << endl;
					temp_i.pop_front();
				}

				cout << "  o_buffer contents:" << endl;
				while (!temp_o.empty()) {
					MeshPacket pkt = temp_o.front();
					cout << "    Seq: " << pkt.sequence << " from (" << pkt.source_x << "," << pkt.source_y
					     << ") to (" << pkt.dest_x << "," << pkt.dest_y << ")" << endl;
					temp_o.pop_front();
				}
			}

			// Check PE-to-router FIFOs
			if (routers[x][y]->in_pe.get_interface()) {
				sc_fifo<MeshPacket>* fifo = dynamic_cast<sc_fifo<MeshPacket>*>(routers[x][y]->in_pe.get_interface());
				size_t pe_to_router_packets = fifo->num_available();
				if (pe_to_router_packets > 0) {
					cout << "Router_" << x << "_" << y << " PE-to-router FIFOs: " << pe_to_router_packets << " packets" << endl;
					inspect_sc_fifo(*fifo, "in_pe");
				}
				total_buffered_packets += pe_to_router_packets;
			}

			// Check router-to-PE FIFOs
			if (routers[x][y]->out_pe.get_interface()) {
				sc_fifo<MeshPacket>* fifo = dynamic_cast<sc_fifo<MeshPacket>*>(routers[x][y]->out_pe.get_interface());
				size_t router_to_pe_packets = fifo->num_available();
				if (router_to_pe_packets > 0) {
					cout << "Router_" << x << "_" << y << " router-to-PE FIFOs: " << router_to_pe_packets << " packets" << endl;
					inspect_sc_fifo(*fifo, "out_pe");
				}
				total_buffered_packets += router_to_pe_packets;
			}

			// Accumulate total buffered packets (router buffers)
			total_buffered_packets += router_buffered;
		}
	}

// Check router-to-router FIFOs
	cout << "\n=== Packets Still in Router-to-Router FIFOs ===" << endl;
	for (int y = 0; y < MESH_SIZE - 1; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			if (north_channels[x][y]) {
				size_t north_packets = north_channels[x][y]->num_available();
				if (north_packets > 0) {
					cout << "north_channels[" << x << "][" << y << "]: " << north_packets << " packets" << endl;
					inspect_sc_fifo(*north_channels[x][y], "north_channels[" + std::to_string(x) + "][" + std::to_string(y) + "]");
				}
				total_buffered_packets += north_packets;
			}
			if (south_channels[x][y]) {
				size_t south_packets = south_channels[x][y]->num_available();
				if (south_packets > 0) {
					cout << "south_channels[" << x << "][" << y << "]: " << south_packets << " packets" << endl;
					inspect_sc_fifo(*south_channels[x][y], "south_channels[" + std::to_string(x) + "][" + std::to_string(y) + "]");
				}
				total_buffered_packets += south_packets;
			}
		}
	}

	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE - 1; x++) {
			if (east_channels[x][y]) {
				size_t east_packets = east_channels[x][y]->num_available();
				if (east_packets > 0) {
					cout << "east_channels[" << x << "][" << y << "]: " << east_packets << " packets" << endl;
					inspect_sc_fifo(*east_channels[x][y], "east_channels[" + std::to_string(x) + "][" + std::to_string(y) + "]");
				}
				total_buffered_packets += east_packets;
			}
			if (west_channels[x][y]) {
				size_t west_packets = west_channels[x][y]->num_available();
				if (west_packets > 0) {
					cout << "west_channels[" << x << "][" << y << "]: " << west_packets << " packets" << endl;
					inspect_sc_fifo(*west_channels[x][y], "west_channels[" + std::to_string(x) + "][" + std::to_string(y) + "]");
				}
				total_buffered_packets += west_packets;
			}
		}
	}

	cout << "Total packets still in transit (buffers + FIFOs): " << total_buffered_packets << endl;


	uint32_t total_dropped_pkts = 0;
	for(int y = 0; y < MESH_SIZE; y++)
		for(int x = 0; x < MESH_SIZE; x++)
			total_dropped_pkts += routers[x][y]->get_dropped_packets();





	/// total stats regarding packets in the system.
	// Updated packet loss statistics to account for buffered packets
//	cout << "\033[1;31m" << endl;//red color
	cout << std::dec ;
	cout << "\033[38;5;202m" << endl;
	cout << "\n\t\t\t\t\t=== Adjusted Packet Delivery Statistics ===" << endl;
	cout << "\t\t\t\t\tTotal sent packets:        " << global_sent_packets.size() << endl;
	cout << "\t\t\t\t\tSuccessfully received:     " << global_received_packets.size() << endl;
	cout << "\t\t\t\t\tStill in transit:          " << total_buffered_packets << endl;
	cout << "\t\t\t\t\tTotal logged dropped pkts: " << total_dropped_pkts << endl;
	cout << "\t\t\t\t\tActually lost packets:     " << lost_packets.size() - total_buffered_packets - total_dropped_pkts << endl;
	cout << "\033[0m" << endl;



	//configuration of simulation details.
	cout << "\n=== Configuration                      ===" << endl;
	cout << "router to router buffer size: " << ROUTER_BUFFER_SIZE
	     << ",Traffic injection rate(ns): " << TRAFFIC_INJECTION_RATE
	     << ",Runtime: " << SIMULATION_TIME	<< ",PE to router fifo size: " << PE_ROUTER_FIFO_SIZE << ",Router to router fifo size: " <<  ROUTER_ROUTER_FIFO_SIZE << endl;
	print_thermal_heatmap(thermal, MESH_SIZE);


	// Cleanup of allocations
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

	// Cleanup Routers
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			delete routers[x][y];
		}
	}

// Cleanup Processing Elements (PEs)
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			delete pes[x][y];
		}
	}

// Cleanup PE-to-router and router-to-PE FIFOs
	for (int y = 0; y < MESH_SIZE; y++) {
		for (int x = 0; x < MESH_SIZE; x++) {
			// Delete PE-to-router FIFO
			if (pes[x][y]->out_port.get_interface()) {
				delete dynamic_cast<sc_fifo<MeshPacket>*>(pes[x][y]->out_port.get_interface());
			}
			// Delete router-to-PE FIFO
			if (pes[x][y]->in_port.get_interface()) {
				delete dynamic_cast<sc_fifo<MeshPacket>*>(pes[x][y]->in_port.get_interface());
			}
		}
	}

	return 0;
}
