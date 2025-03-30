#ifndef MESH_PACKET_H
#define MESH_PACKET_H

#include <systemc.h>
#include <iostream>
#include <iomanip>

// Packet Types definitions
enum MeshPacketType {
    DATA_PACKET,
    CONTROL_PACKET,
    MEMORY_REQUEST,
    MEMORY_RESPONSE,
    TASK_PACKET
};

struct MeshPacket {
    // Header
    uint32_t source_x;
    uint32_t source_y;
    uint32_t dest_x;
    uint32_t dest_y;
    uint32_t sequence;
    MeshPacketType type;
    uint32_t timestamp;
    uint8_t priority;
    uint16_t checksum;
    
    // Payload
    union {
        struct {
            uint32_t address;
            uint32_t data[13];
        } memory_op;
        
        struct {
            uint32_t task_id;
            uint32_t parameters[13];
        } task;
        
        uint8_t raw[56];
    } payload;
};

// Add as non-member function outside the struct
inline std::ostream& operator<<(std::ostream& os, const MeshPacket& pkt) {
    os << "Packet[" << pkt.sequence << "] "
       << "Type:" << pkt.type << " "
       << "From:(" << pkt.source_x << "," << pkt.source_y << ") "
       << "To:(" << pkt.dest_x << "," << pkt.dest_y << ")";
    return os;
}

#endif // MESH_PACKET_H
