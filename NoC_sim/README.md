SystemC Network-on-Chip (NoC) Analysis


* contents of noc\_log.txt
```
./a.out | grep LATENCY > noc_log.txt
```


Some visualization from running tests with 
```
#define PE_ROUTER_DELAY		2
#define ROUTER_ROUTER_DELAY	5
const int MESH_SIZE = 5;
#define ROUTER_BUFFER_SIZE	4 //affects the dropped packets observation
#define TRAFFIC_INJECTION_RATE 50 
#define SIMULATION_TIME	 100000
#define PE_ROUTER_FIFO_SIZE 4
#define ROUTER_ROUTER_FIFO_SIZE 4
```

![img](https://github.com/NikosMouzakitis/systemc_master/blob/main/NoC_sim/chart_5x5.png)



Overview
This SystemC implementation models a 2x2 mesh Network-on-Chip (NoC) with routers and processing elements (PEs). The system demonstrates packet-based communication between PEs through a mesh network of routers.

Main Components
1. MeshPacket
The fundamental data unit being transmitted through the network.

Key Fields:

Header: Contains routing information (source/destination coordinates), sequence number, packet type, timestamp

Payload: Union of different payload types (memory operations, tasks, or raw data)

Functions: Overloaded << operator for printing packet information

2. ProcessingElement (PE)
Represents a computational node in the NoC.

Interfaces:

in_port: Input FIFO port for receiving packets

out_port: Output FIFO port for sending packets

Key Functionality:

Generates test packets (only PE_0_0 in this example)

Receives and prints incoming packets

Maintains its position in the mesh (x_pos, y_pos)

3. MeshRouter
The routing node that forwards packets between PEs and other routers.

Interfaces:

Directional ports (conditional, based on position in mesh):

in_north/out_north

in_south/out_south

in_east/out_east

in_west/out_west

PE ports (always present):

in_pe (from PE to router)

out_pe (from router to PE)

Key Functionality:

Implements XY routing algorithm (dimension-order routing)

Maintains input and output buffers

Updates packet timestamps (hop count)

Conditionally creates ports based on router position

Channel Connections
1. PE-Router Connections
Each PE is connected to its local router via two FIFO channels:

PE.out_port → Router.in_pe (4-slot FIFO)

Router.out_pe → PE.in_port (4-slot FIFO)

2. Router-Router Connections
North-South:

Router[x][y].out_north → Router[x][y+1].in_south (4-slot FIFO)

Router[x][y+1].out_south → Router[x][y].in_north (4-slot FIFO)

East-West:

Router[x][y].out_east → Router[x+1][y].in_west (4-slot FIFO)

Router[x+1][y].out_west → Router[x][y].in_east (4-slot FIFO)

System Architecture

```
       PE_0_0        PE_1_0
        |             |
Router_0_0 ----- Router_1_0
   |                  |
   |                  |
Router_0_1 ----- Router_1_1
   |                  |
PE_0_1        PE_1_1
```

Packet Flow Example
PE_0_0 creates a packet destined for PE_1_1

Packet flows:

PE_0_0 → Router_0_0 (via PE.out_port → Router.in_pe)

Router_0_0 routes east to Router_1_0 (X dimension first)

Router_1_0 routes south to Router_1_1 (then Y dimension)

Router_1_1 delivers to PE_1_1 (via Router.out_pe → PE.in_port)

Key Observations
Conditional Port Creation: Routers only create ports for directions that exist in the mesh (edge routers don't create ports pointing outside the mesh)

XY Routing: Packets are routed first in the X dimension, then in the Y dimension

Buffering: Both routers and FIFO channels provide buffering

Routers have input and output buffers

All FIFO channels have 4-slot capacity

Verification: The code includes extensive port binding verification to ensure correct connections

Simulation: The testbench runs for 200ns with PE_0_0 generating a single test packet
