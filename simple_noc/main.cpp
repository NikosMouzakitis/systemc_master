#include "noc_common.h"
#include "router.h"
#include "ni.h"

SC_MODULE(Top) {
    sc_clock clock;
    Router* routers[NOC_WIDTH][NOC_HEIGHT];
    NetworkInterface* nis[NOC_WIDTH][NOC_HEIGHT];
    occn::PPBaseChannel<Packet, Packet>* ni_channels[NOC_WIDTH][NOC_HEIGHT];  // Channels between NIs and routers

    SC_CTOR(Top) : clock("clock", 10, SC_NS) {
        // Create channels first
        for (int y = 0; y < NOC_HEIGHT; y++) {
            for (int x = 0; x < NOC_WIDTH; x++) {
                ni_channels[x][y] = new occn::PPBaseChannel<Packet, Packet>(
                    sc_gen_unique_name("ni_channel"));
            }
        }

        // Create routers and NIs
        for (int y = 0; y < NOC_HEIGHT; y++) {
            for (int x = 0; x < NOC_WIDTH; x++) {
                uint32_t id = x + y * NOC_WIDTH;
                
                routers[x][y] = new Router(sc_gen_unique_name("router"), x, y);
                nis[x][y] = new NetworkInterface(sc_gen_unique_name("ni"), id);

                // Connect NI to router through channel
                nis[x][y]->master_port(*ni_channels[x][y]);
                routers[x][y]->slave_export(*ni_channels[x][y]);

                // Connect clock
                nis[x][y]->clock(clock);

                // Create and connect router-to-router channels
                // (Implementation would go here)
            }
        }
    }
};

int sc_main(int argc, char* argv[]) {
    Top top("top");
    sc_start(1000, SC_NS);
    return 0;
}
