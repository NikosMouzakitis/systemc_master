#include "noc_common.h"

enum { LOCAL, NORTH, EAST, SOUTH, WEST };

SC_MODULE(Router) {
    sc_export<occn::SlaveIf<Packet, Packet>> slave_export;
    sc_port<occn::MasterIf<Packet, Packet>> ports[5];
    int x, y;

    void route_packet() {
        while (true) {
            Packet pkt;
            pkt.sdu_size = sizeof(Packet);
            
            if (slave_export->wait_read_authorization() == OCCN_OK) {
                slave_export->read_pdu(&pkt);
                slave_export->end_of_reading();

                int dest_x = pkt.dest_id % NOC_WIDTH;
                int dest_y = pkt.dest_id / NOC_WIDTH;
                int out_port = (dest_x > x) ? EAST : 
                             (dest_x < x) ? WEST :
                             (dest_y > y) ? NORTH : 
                             (dest_y < y) ? SOUTH : LOCAL;

                if (ports[out_port]->wait_write_authorization() == OCCN_OK) {
                    ports[out_port]->write_pdu(pkt);
                    ports[out_port]->end_of_writing();
                }
            }
            wait(10, SC_NS);
        }
    }

    SC_HAS_PROCESS(Router);
    Router(sc_module_name name, int x, int y) : 
        sc_module(name), x(x), y(y) 
    {
        SC_THREAD(route_packet);
    }
};
