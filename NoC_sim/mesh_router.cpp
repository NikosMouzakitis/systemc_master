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
bool MeshRouter::write_port_conditional(sc_port<sc_fifo_out_if<MeshPacket>>* port, 
                                      const MeshPacket& packet) {
    if (!port || !port->get_interface()) return false;
    if ((*port)->num_free() > 0) {
        (*port)->write(packet);
        cout << this->name() << " forwarded via " << port->name() 
             << " @ " << sc_time_stamp() << endl;
        return true;
    }
    return false;
}


void MeshRouter::pe_interface_process() {
    while (true) {
        // Handle incoming packets from PE
        if (in_pe->num_available() > 0) {
            MeshPacket pkt = in_pe->read();
            cout << this->name() << " received from PE @ " << sc_time_stamp() << endl;
            o_buffer.push(pkt);
            o_buffer_event.notify();
        }

        // Handle outgoing packets to PE
        if (!i_buffer.empty() && out_pe->num_free() > 0) {
            MeshPacket& pkt = i_buffer.front();
            if (pkt.dest_x == x_pos && pkt.dest_y == y_pos) {
                out_pe->write(pkt);
                i_buffer.pop();
                cout << this->name() << " DELIVERED to PE @ " << sc_time_stamp() << endl;
            }
        }
        wait(10, SC_NS);
    }
}
void MeshRouter::router_process() {
    while (true) {
        bool processed = false;
        MeshPacket packet;

        // Check all input ports
        #define CHECK_PORT(port, dir) \
            if (port && (*port)->num_available() > 0) { \
                packet = (*port)->read(); \
                cout << this->name() << " received from " #dir " @ " << sc_time_stamp() << endl; \
                i_buffer.push(packet); \
                processed = true; \
            }

        CHECK_PORT(in_north, NORTH)
        CHECK_PORT(in_south, SOUTH)
        CHECK_PORT(in_east, EAST)
        CHECK_PORT(in_west, WEST)

        // Process buffers
        if (!o_buffer.empty()) {
            route_packet(o_buffer.front());
            o_buffer.pop();
            processed = true;
        } 
        else if (!i_buffer.empty()) {
            MeshPacket pkt = i_buffer.front();
            if (pkt.dest_x == x_pos && pkt.dest_y == y_pos) {
                // For local delivery, let pe_interface_process handle it
                processed = true;
            } else {
                route_packet(pkt);
                i_buffer.pop();
                processed = true;
            }
        }

        // Time management
        if (processed) {
            wait(SC_ZERO_TIME);
        } else {
            wait(10, SC_NS);
        }
    }
}

void MeshRouter::route_packet(const MeshPacket& packet) {
    MeshPacket routed = packet;
    update_packet_hop(routed);

    cout << this->name() << " ROUTING to (" << packet.dest_x 
         << "," << packet.dest_y << ") @ " << sc_time_stamp() << endl;

    if (packet.dest_x == x_pos && packet.dest_y == y_pos) {
        // Local delivery
        i_buffer.push(routed);
        return;
    }

    if (packet.dest_x != x_pos) { // X-dimension first
        if (packet.dest_x > x_pos && out_east) {
            if (!write_port_conditional(out_east, routed)) {
                o_buffer.push(routed);
            }
        } 
        else if (out_west) {
            if (!write_port_conditional(out_west, routed)) {
                o_buffer.push(routed);
            }
        }
    } 
    else { // Y-dimension
        if (packet.dest_y > y_pos && out_north) {
            if (!write_port_conditional(out_north, routed)) {
                o_buffer.push(routed);
            }
        } 
        else if (out_south) {
            if (!write_port_conditional(out_south, routed)) {
                o_buffer.push(routed);
            }
        }
    }
}

void MeshRouter::update_packet_hop(MeshPacket& packet) {
	packet.timestamp = sc_time_stamp().to_default_time_units();
}
