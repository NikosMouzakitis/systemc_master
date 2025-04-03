#ifndef NOC_COMMON_H
#define NOC_COMMON_H
#define NO_STAT_GUI
#define NO_STAT_FILE
#define OCCN_NO_GUI
#define OCCN_NO_STATS

#include <systemc.h>
#include <stdint.h>
#include <occn.h>
#include <iostream>
#include <sstream>
#include <string>

// Helper function to format sc_time as string
inline std::string sc_time_to_string(const sc_core::sc_time& t) {
    std::ostringstream oss;
    oss << t.to_default_time_units() << " ns";
    return oss.str();
}
struct Packet {
    uint32_t src_id;
    uint32_t dest_id;
    uint32_t payload;
    sc_time timestamp;
    uint32_t sdu_size;
    
    std::string to_string() const {
        std::ostringstream oss;
        oss << "Packet[src=" << src_id 
            << ", dest=" << dest_id
            << ", payload=" << payload
            << ", time=" << timestamp.to_default_time_units() << "ns"
            << ", size=" << sdu_size << "]";
        return oss.str();
    }

    friend void sc_trace(sc_trace_file* tf, const Packet& p, const std::string& name) {
        sc_trace(tf, p.src_id, name + ".src_id");
        sc_trace(tf, p.dest_id, name + ".dest_id");
        sc_trace(tf, p.payload, name + ".payload");
    }

    bool operator==(const Packet& other) const {
        return src_id == other.src_id &&
               dest_id == other.dest_id &&
               payload == other.payload &&
               timestamp == other.timestamp &&
               sdu_size == other.sdu_size;
    }
};

const int NOC_WIDTH = 2;
const int NOC_HEIGHT = 2;
const int OCCN_OK = 0;

#endif
