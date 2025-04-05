/*
 * Mouzakitis N. 2025.
 */


#ifndef MESH_ROUTER_H
#define MESH_ROUTER_H

#include <systemc.h>
#include <queue>
#include "mesh_packet.h"
#include <set>

#define ACTIVITY_ALPHA 0.3
#define SC_ALLOW_DEPRECATED_IEEE_API 1
SC_MODULE(MeshRouter) {
	friend class ThermalModel; //allow thermal access.
	// Router parameters
	const uint32_t x_pos;
	const uint32_t y_pos;
	const uint32_t mesh_size;
	const uint32_t buffer_depth;
	uint32_t dropped_pkts=0;
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

	std::deque<MeshPacket> i_buffer;  // For packets from other routers
	std::deque<MeshPacket> o_buffer;  // For packets from local PE or to be forwarded
	std::set<uint32_t> in_flight_packets; //track packets being routed.
	// Public getter for dropped_pkts
	uint32_t get_dropped_packets() const {
		return dropped_pkts;
	}
	
	double activity_factor=0.0;
       	double get_activity_factor() const { 
            return 1.02*activity_factor; // Normalize to 0-1
        }

private:
	//thermal related
	sc_time last_update = SC_ZERO_TIME;
	uint32_t packet_count=0;
	const double MAX_PACKET_RATE = 1e6; // 1 million packets/sec = full activity

	void count_packet() {
		if (packet_count == 0) {
			last_update = sc_time_stamp(); // Initialize on first packet
		}
		packet_count++;
	}
	
	void update_activity() {
		sc_time now = sc_time_stamp();

		if (last_update != SC_ZERO_TIME) {
			double elapsed_sec = (now - last_update).to_seconds();
		
			if (elapsed_sec > 0) {
				double current_rate = packet_count / elapsed_sec;
				// Normalize and smooth
				activity_factor = 0.3 * (current_rate/MAX_PACKET_RATE) + 0.7 * activity_factor;
				activity_factor = std::clamp(activity_factor, 0.0, 1.0);
			}
		}
	
		cout << this->name() << " activity: " << activity_factor << " pkts=" << packet_count << "\n";
		packet_count = 0;
		last_update = now;
	}

        
       
	sc_event i_buffer_event, o_buffer_event, clear_event;
	bool * port_already_tx; //0-N 1-E 2-S 3-W
	bool push_to_buffer(std::deque<MeshPacket>& buffer, const MeshPacket& packet);
	void pe_interface_process();
	void route_packet(const MeshPacket& packet);
	bool write_port_conditional(sc_port<sc_fifo_out_if<MeshPacket>>* port, const MeshPacket& packet);
	bool read_port_conditional(sc_port<sc_fifo_in_if<MeshPacket>>* port, MeshPacket& packet);
	void router_process(void);
	//if port is available to transmit a packet.
	bool is_port_available(sc_port<sc_fifo_out_if<MeshPacket>>* port);
	void route_packet_simultaneous(const MeshPacket& packet);
	bool try_simultaneous_tx(const MeshPacket& pkt, bool x_routed);
	void refresh_tx_tracking(void);
	void init_tx_tracking(void);
	void clear_ports(void);
};

#endif
