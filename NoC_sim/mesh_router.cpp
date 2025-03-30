#include "mesh_router.h"

MeshRouter::MeshRouter(sc_module_name name, uint32_t x, uint32_t y,
                       uint32_t mesh_size, uint32_t buf_depth) :
	sc_module(name), x_pos(x), y_pos(y), mesh_size(mesh_size), buffer_depth(buf_depth),
	in_north(nullptr), in_south(nullptr), in_east(nullptr), in_west(nullptr),
	out_north(nullptr), out_south(nullptr), out_east(nullptr), out_west(nullptr)
{
	// Create only needed ports
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

bool MeshRouter::read_port_conditional(sc_port<sc_fifo_in_if<MeshPacket>>* port, MeshPacket& packet) {
    if (!port || !port->get_interface()) return false;
    sc_fifo_in_if<MeshPacket>* fifo_if = port->operator->();
    if (fifo_if->num_available() == 0) return false;
    packet = fifo_if->read();
    return true;
}

bool MeshRouter::write_port_conditional(sc_port<sc_fifo_out_if<MeshPacket>>* port, const MeshPacket& packet) {
    if (!port || !port->get_interface()) return false;
    sc_fifo_out_if<MeshPacket>* fifo_if = port->operator->();
    if (fifo_if->num_free() == 0) return false;
    fifo_if->write(packet);
    return true;
}

void MeshRouter::pe_interface_process() {
    while (true) {
        // Check PE input
        if (in_pe->num_available() > 0) {
            MeshPacket pkt = in_pe->read();
            i_buffer.push(pkt);
            i_buffer_event.notify();
        }

        // Check output to PE
        if (!o_buffer.empty() && out_pe->num_free() > 0) {
            out_pe->write(o_buffer.front());
            o_buffer.pop();
        }
        wait(10, SC_NS);
    }
}

void MeshRouter::router_process() {
	while (true) {
		MeshPacket packet;

		// Check directional ports
		if (in_north && read_port_conditional(in_north, packet)) {
			i_buffer.push(packet);
			i_buffer_event.notify();
		}

		if (in_south && read_port_conditional(in_south, packet)) {
			i_buffer.push(packet);
			i_buffer_event.notify();
		}

		if (in_east && read_port_conditional(in_east, packet)) {
			i_buffer.push(packet);
			i_buffer_event.notify();
		}

		if (in_west && read_port_conditional(in_west, packet)) {
			i_buffer.push(packet);
			i_buffer_event.notify();
		}

		// Process PE input
		if (read_port_conditional(&in_pe, packet)) {
			i_buffer.push(packet);
			i_buffer_event.notify();
		}

		if (!i_buffer.empty()) {
			MeshPacket pkt = i_buffer.front();
			i_buffer.pop();
			route_packet(pkt);
		}
		else {
			wait(i_buffer_event | o_buffer_event);
		}
	}
}

void MeshRouter::route_packet(const MeshPacket& packet) {
	MeshPacket routed_pkt = packet;
	update_packet_hop(routed_pkt);

	if (packet.dest_x == x_pos && packet.dest_y == y_pos) {
		o_buffer.push(routed_pkt);
		o_buffer_event.notify();
	}
	else if (packet.dest_x != x_pos) {
		if (packet.dest_x > x_pos && out_east) {
			if (!write_port_conditional(out_east, routed_pkt)) {
				o_buffer.push(routed_pkt);
			}
		}
		else if (out_west) {
			if (!write_port_conditional(out_west, routed_pkt)) {
				o_buffer.push(routed_pkt);
			}
		}
	}
	else {
		if (packet.dest_y > y_pos && out_north) {
			if (!write_port_conditional(out_north, routed_pkt)) {
				o_buffer.push(routed_pkt);
			}
		}
		else if (out_south) {
			if (!write_port_conditional(out_south, routed_pkt)) {
				o_buffer.push(routed_pkt);
			}
		}
	}
}

void MeshRouter::update_packet_hop(MeshPacket& packet) {
	packet.timestamp = sc_time_stamp().to_default_time_units();
}
