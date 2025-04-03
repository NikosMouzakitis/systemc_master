#include "noc_common.h"

SC_MODULE(NetworkInterface) {
    sc_port<occn::MasterIf<Packet, Packet>> master_port;
    sc_in<bool> clock;
    uint32_t id;

    void traffic_generator() {
        while (true) {
            wait();
            Packet pkt;
            pkt.src_id = id;
            pkt.dest_id = rand() % (NOC_WIDTH * NOC_HEIGHT);
            pkt.payload = rand();
            pkt.timestamp = sc_time_stamp();
            pkt.sdu_size = sizeof(Packet);

            if (master_port->wait_write_authorization() == OCCN_OK) {
                master_port->write_pdu(pkt);
                master_port->end_of_writing();
                std::cout << "NI " << id << " sent " << pkt.to_string() << std::endl;
            }
        }
    }

    SC_HAS_PROCESS(NetworkInterface);
    NetworkInterface(sc_module_name name, uint32_t id) : 
        sc_module(name), id(id) 
    {
        SC_THREAD(traffic_generator);
        sensitive << clock.pos();
    }
};
