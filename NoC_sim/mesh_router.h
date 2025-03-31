#ifndef MESH_ROUTER_H
#define MESH_ROUTER_H

#include <systemc.h>
#include <queue>
#include "mesh_packet.h"

SC_MODULE(MeshRouter) {
	// Router parameters
	const uint32_t x_pos;
	const uint32_t y_pos;
	const uint32_t mesh_size;
	const uint32_t buffer_depth;

	// Conditional ports (use references instead of pointers)
	sc_port<sc_fifo_in_if<MeshPacket>>* in_north=nullptr;
	sc_port<sc_fifo_in_if<MeshPacket>>* in_south=nullptr;
	sc_port<sc_fifo_in_if<MeshPacket>>* in_east=nullptr;
	sc_port<sc_fifo_in_if<MeshPacket>>* in_west=nullptr;
	sc_port<sc_fifo_out_if<MeshPacket>>* out_north=nullptr;
	sc_port<sc_fifo_out_if<MeshPacket>>* out_south=nullptr;
	sc_port<sc_fifo_out_if<MeshPacket>>* out_east=nullptr;
	sc_port<sc_fifo_out_if<MeshPacket>>* out_west=nullptr;

	// PE ports (always present)
	sc_port<sc_fifo_in_if<MeshPacket>> in_pe;
	sc_port<sc_fifo_out_if<MeshPacket>> out_pe;
	SC_HAS_PROCESS(MeshRouter);
	MeshRouter(sc_module_name name, uint32_t x, uint32_t y, uint32_t mesh_size, uint32_t buf_depth = 8);
	~MeshRouter();

	std::queue<MeshPacket> i_buffer;  // For packets from other routers
	std::queue<MeshPacket> o_buffer;  // For packets from local PE or to be forwarded
private:
    sc_event i_buffer_event, o_buffer_event;

    void router_process();
    void pe_interface_process();
    void route_packet(const MeshPacket& packet);
    void update_packet_hop(MeshPacket& packet);
    bool write_port_conditional(sc_port<sc_fifo_out_if<MeshPacket>>* port, const MeshPacket& packet);
    bool MeshRouter::read_port_conditional(sc_port<sc_fifo_in_if<MeshPacket>>* port, MeshPacket& packet);
};

#endif
