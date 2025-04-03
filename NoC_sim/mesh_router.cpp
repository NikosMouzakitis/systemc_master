#include "mesh_router.h"

#define PE_ROUTER_DELAY     2
#define ROUTER_ROUTER_DELAY 5

MeshRouter::MeshRouter(sc_module_name name, uint32_t x, uint32_t y, uint32_t mesh_size, uint32_t buf_depth) :
	sc_module(name), x_pos(x), y_pos(y), mesh_size(mesh_size), buffer_depth(buf_depth), in_north(nullptr), in_south(nullptr), in_east(nullptr), in_west(nullptr), out_north(nullptr), out_south(nullptr), out_east(nullptr), out_west(nullptr)
{
	// Create only the needed and used ports for each
	// router based on its position of x and y.
	if (y < mesh_size - 1) {
		out_north = new sc_port<sc_fifo_out_if<MeshPacket>>();
		in_north = new sc_port<sc_fifo_in_if<MeshPacket>>();
		cout << this->name() << " creating in/out NORTH" << endl;
	}
	if (y > 0) {
		out_south = new sc_port<sc_fifo_out_if<MeshPacket>>();
		in_south = new sc_port<sc_fifo_in_if<MeshPacket>>();
		cout << this->name() << " creating in/out SOUTH" << endl;
	}
	if (x < mesh_size - 1) {
		out_east = new sc_port<sc_fifo_out_if<MeshPacket>>();
		in_east = new sc_port<sc_fifo_in_if<MeshPacket>>();
		cout << this->name() << " creating in/out EAST" << endl;
	}
	if (x > 0) {
		out_west = new sc_port<sc_fifo_out_if<MeshPacket>>();
		in_west = new sc_port<sc_fifo_in_if<MeshPacket>>();
		cout << this->name() << " creating in/out WEST" << endl;
	}
	SC_THREAD(router_process);
	SC_THREAD(pe_interface_process);
}

MeshRouter::~MeshRouter() {
	delete in_north;
	delete out_north;
	delete in_south;
	delete out_south;
	delete in_east;
	delete out_east;
	delete in_west;
	delete out_west;
}

bool MeshRouter::push_to_buffer(std::deque<MeshPacket>& buffer, const MeshPacket& packet) {
	if (buffer.size() < buffer_depth) {
		buffer.push_back(packet);
		return true;
	}

	// Print drop information
	cout << "\033[1;31mBuffer overflow!\033[0m Dropping packet: " << packet.sequence
	     << " (dest:" << packet.dest_x << "," << packet.dest_y << ")" << endl;

	// Print current buffer contents
	cout << "Current buffer contents (sequences): [";
	for (const auto& pkt : buffer) {
		cout << pkt.sequence << " (dest:" << pkt.dest_x << "," << pkt.dest_y << "), ";
	}
	cout << "]" << endl;

	dropped_pkts++;
	return false;
}


bool MeshRouter::read_port_conditional(sc_port<sc_fifo_in_if<MeshPacket>>* port, MeshPacket& packet) {
	if (!port || !port->get_interface()) return false;
	sc_fifo_in_if<MeshPacket>* fifo_if = port->operator->();
	if (fifo_if->num_available() > 0) {
		packet = fifo_if->read();
		return true;
	}
	return false;
}

void MeshRouter::route_packet_simultaneous(const MeshPacket& packet) {
	// Skip if packet is already being routed
	if (in_flight_packets.count(packet.sequence)) {
		return;
	}

	if (packet.dest_x == x_pos && packet.dest_y == y_pos) {
		push_to_buffer(i_buffer, packet);
		return;
	}

	in_flight_packets.insert(packet.sequence); // Mark as in-flight

	bool x_routed = false;
	bool y_routed = false;

	// X-dimension routing
	if (packet.dest_x != x_pos) {
		if (packet.dest_x > x_pos && out_east && is_port_available(out_east)) {
			x_routed = write_port_conditional(out_east, packet);
		}
		else if (out_west && is_port_available(out_west)) {
			x_routed = write_port_conditional(out_west, packet);
		}
	}

	// Y-dimension routing (can happen simultaneously with X)
	if (!x_routed && packet.dest_y != y_pos) {
		if (packet.dest_y > y_pos && out_north && is_port_available(out_north)) {
			y_routed = write_port_conditional(out_north, packet);
		}
		else if (out_south && is_port_available(out_south)) {
			y_routed = write_port_conditional(out_south, packet);
		}
	}

	if (!x_routed && !y_routed) {
		push_to_buffer(o_buffer, packet);
	}

	in_flight_packets.erase(packet.sequence); // Clear in-flight status
}

bool MeshRouter::write_port_conditional(sc_port<sc_fifo_out_if<MeshPacket>>* port,
                                        const MeshPacket& packet) {
	if (!port || !port->get_interface()) return false;
	if ((*port)->num_free() > 0) {
		// SAFE: Make a const copy just for display purposes
		const MeshPacket display_pkt = packet;

		// Calculate NEXT HOP coordinates only for display
		int next_hop_x = x_pos;
		int next_hop_y = y_pos;

		if (port == out_north)       next_hop_y = y_pos + 1;
		else if (port == out_south)  next_hop_y = y_pos - 1;
		else if (port == out_east)   next_hop_x = x_pos + 1;
		else if (port == out_west)   next_hop_x = x_pos - 1;

		// Original packet is untouched - we only use its const copy for display
		cout << this->name() << " forwarding seq:" << display_pkt.sequence
		     << " (final dest:" << display_pkt.dest_x << "," << display_pkt.dest_y << ")"
		     << " -> next hop (" << next_hop_x << "," << next_hop_y << ")"
		     << " @ " << sc_time_stamp() << endl;

		// Original packet is written unchanged
		(*port)->write(packet);
		return true;
	}
	return false;
}

void MeshRouter::pe_interface_process() {
	while (true) {
		wait(PE_ROUTER_DELAY, SC_NS);

		// Handle incoming packets from PE
		if (in_pe->num_available() > 0) {
			MeshPacket pkt = in_pe->read();
			cout << "\t\t\t\t\t\t-------------------PE reception-start-----------------------------------" << endl;
			cout <<"\t\t\t\t\t\t"<< this->name() << " received packet, seq: " << pkt.sequence << " from PE @ " << sc_time_stamp() << endl;
			cout << "\t\t\t\t\t\t-------------------PE reception-end-------------------------------------" << endl;
			push_to_buffer(o_buffer, pkt);
		}

		// Handle outgoing packets to PE
		if (!i_buffer.empty() && out_pe->num_free() > 0) {
			MeshPacket pkt = i_buffer.front();
			out_pe->write(pkt);
			i_buffer.pop_front();
			cout << this->name() << " DELIVERED packet, seq: " << pkt.sequence << " to PE @ " << sc_time_stamp() << endl;
		}
	}
}

void MeshRouter::router_process() {
	while (true) {
		wait(ROUTER_ROUTER_DELAY, SC_NS);

		// Process all input ports in parallel
		MeshPacket packets[4]; // NORTH, SOUTH, EAST, WEST
		bool has_packet[4] = {false};


		if (in_north && read_port_conditional(in_north, packets[0])) {
			cout <<"\t\t\t\t"<< "-----------------"<<this->name()<<"-------------------------------------------"<<endl;
			cout <<"\t\t\t\t"<< this->name() << " received packet seq:" << packets[0].sequence
			     << " from NORTH (source:" << packets[0].source_x << "," << packets[0].source_y << ")"
			     << " (dest:" << packets[0].dest_x << "," << packets[0].dest_y << ")"
			     << " @ " << sc_time_stamp() << endl;
			cout << "\t\t\t\t"<< "----------------------------------------------------------------------------------"<<endl;
			has_packet[0] = true;
		}
		if (in_south && read_port_conditional(in_south, packets[1])) {
			cout <<"\t\t\t\t"<< "-----------------"<<this->name()<<"-------------------------------------------"<<endl;
			cout <<"\t\t\t\t"<< this->name() << " received packet seq:" << packets[0].sequence
			     << " from SOUTH (source:" << packets[1].source_x << "," << packets[1].source_y << ")"
			     << " (dest:" << packets[1].dest_x << "," << packets[1].dest_y << ")"
			     << " @ " << sc_time_stamp() << endl;
			has_packet[1] = true;
		}
		if (in_east && read_port_conditional(in_east, packets[2])) {
			cout <<"\t\t\t\t"<< "-----------------"<<this->name()<<"-------------------------------------------"<<endl;
			cout <<"\t\t\t\t"<< this->name() << " received packet seq:" << packets[0].sequence
			     << " from EAST (source:" << packets[2].source_x << "," << packets[2].source_y << ")"
			     << " (dest:" << packets[2].dest_x << "," << packets[2].dest_y << ")"
			     << " @ " << sc_time_stamp() << endl;
			has_packet[2] = true;
		}
		if (in_west && read_port_conditional(in_west, packets[3])) {
			cout <<"\t\t\t\t"<< "-----------------"<<this->name()<<"-------------------------------------------"<<endl;
			cout <<"\t\t\t\t"<< this->name() << " received packet seq:" << packets[0].sequence
			     << " from WEST (source:" << packets[3].source_x << "," << packets[3].source_y << ")"
			     << " (dest:" << packets[3].dest_x << "," << packets[3].dest_y << ")"
			     << " @ " << sc_time_stamp() << endl;
			has_packet[3] = true;
		}
		// Store all received packets
		for (int i = 0; i < 4; i++) {
			if (has_packet[i]) {
				if (!push_to_buffer(i_buffer, packets[i])) {
					cout << "Dropped packet due to full i_buffer: " << packets[i].sequence << endl;
				}
			}
		}

		// Process output buffers with simultaneous routing


		// Process output buffer - NEW VERSION
		if (!o_buffer.empty()) {
			// Make a copy of current packets to process
			std::vector<MeshPacket> to_process;
			to_process.assign(o_buffer.begin(), o_buffer.end());
			o_buffer.clear(); // Clear original buffer

			for (auto& pkt : to_process) {
				route_packet_simultaneous(pkt);
			}
		}

		// Process input buffer
		if (!i_buffer.empty()) {
			MeshPacket pkt = i_buffer.front();
			i_buffer.pop_front();

			if (pkt.dest_x == x_pos && pkt.dest_y == y_pos) {
				push_to_buffer(i_buffer, pkt); // Local delivery
			} else {
				route_packet_simultaneous(pkt);
			}
		}



		if (!i_buffer.empty()) {
			MeshPacket pkt = i_buffer.front();
			if (pkt.dest_x == x_pos && pkt.dest_y == y_pos) {
				// Local delivery - handled by pe_interface_process
			} else {
				route_packet_simultaneous(pkt);
				i_buffer.pop_front();
			}
		}

		wait(SC_ZERO_TIME); // Yield to other processes
	}
}


bool MeshRouter::is_port_available(sc_port<sc_fifo_out_if<MeshPacket>>* port) {
	if (!port || !port->get_interface()) return false;
	sc_fifo_out_if<MeshPacket>* fifo_if = port->operator->();
	return fifo_if->num_free() > 0;
}
