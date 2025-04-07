#include <set>
#include <random>
#include <fstream>
#include <iomanip>
#include <map>
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
const int MESH_SIZE = 3;

// Base class for Core and Memory to enable polymorphism
class Device {
public:
    virtual ~Device() = default;  // Virtual destructor for polymorphism
};

struct Core : public Device {
    int core_id;
    Core(int id) : core_id(id) {}
};

struct Memory : public Device {
    int memory_id;
    Memory(int id) : memory_id(id) {}
};

class Mesh {
private:
    // Grid of pointers, each either pointing to a Core or a Memory object
    std::vector<std::vector<Device*>> grid;
    std::vector<Memory*> available_memories; // Keep track of memory objects
    std::map<int, pair<unsigned long, unsigned long>> memory_address_map; // Map for memory address ranges

public:
    // Constructor: Initialize mesh to nullptr
    Mesh() : grid(MESH_SIZE, vector<Device*>(MESH_SIZE, nullptr)) {}

    // Assign a Core to a specific (x, y) position
    void assignCore(int x, int y, int core_id) {
        assert(x >= 0 && x < MESH_SIZE && y >= 0 && y < MESH_SIZE);  // Ensure within bounds
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Core(core_id);
            cout << "Assigned Core " << core_id << " to position (" << x << "," << y << ")\n";
        } else {
            cout << "Error: Cell already occupied!\n";
        }
    }

    // Assign a Memory to a specific (x, y) position
    void assignMemory(int x, int y, int memory_id) {
        assert(x >= 0 && x < MESH_SIZE && y >= 0 && y < MESH_SIZE);  // Ensure within bounds
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Memory(memory_id);
            available_memories.push_back(static_cast<Memory*>(grid[x][y]));  // Track assigned memory
            cout << "Assigned Memory " << memory_id << " to position (" << x << "," << y << ")\n";
        } else {
            cout << "Error: Cell already occupied!\n";
        }
    }

    // Split memory addresses based on available memories
    void splitMemoryAddresses(unsigned long total_memory_size) {
        unsigned long num_memories = available_memories.size();
        cout << "Total memories: " << num_memories << endl;
        cout << "Total memory size: " << hex << total_memory_size << endl;

        if (num_memories == 0) {
            cout << "No memories assigned! Cannot split memory addresses.\n";
            return;
        }

        unsigned long memory_block_size = (total_memory_size) / num_memories;
        cout << "memory block size: " << hex << memory_block_size << endl;
        for (int i = 0; i < num_memories; ++i) {
            unsigned long start_address = i * memory_block_size;
            unsigned long end_address = (i + 1) * memory_block_size - 1;

            memory_address_map[available_memories[i]->memory_id] = {start_address, end_address};
            cout << "i: " << i << " Memory " << std::hex << available_memories[i]->memory_id
                 << " gets address range [" << start_address << ", " << end_address << "]\n";
        }
    }

    // Get memory ID for a given address
    int getMemoryIdByAddress(unsigned long address) {
        for (const auto& entry : memory_address_map) {
            if (address >= entry.second.first && address <= entry.second.second) {
                return entry.first;  // Return memory ID
            }
        }
        cout << "Error: Address " << hex << address << " is out of bounds.\n";
        return -1;  // Return -1 if address is out of bounds
    }

    // Get the (x, y) of a memory by its ID
    pair<int, int> getCoordinatesByMemoryId(int memory_id) {
        for (int i = 0; i < MESH_SIZE; ++i) {
            for (int j = 0; j < MESH_SIZE; ++j) {
                Memory* memory = dynamic_cast<Memory*>(grid[i][j]);
                if (memory && memory->memory_id == memory_id) {
                    return {i, j};  // Return coordinates
                }
            }
        }
        cout << "Error: Memory with ID " << memory_id << " not found.\n";
        return {-1, -1};  // Return (-1, -1) if memory not found
    }

    // Display the contents of the mesh
    void displayMesh() {
        for (int i = 0; i < MESH_SIZE; ++i) {
            for (int j = 0; j < MESH_SIZE; ++j) {
                cout << "(" << i << "," << j << ") ";
                if (grid[i][j] == nullptr) {
                    cout << "Empty\n";
                } else {
                    Core* core = dynamic_cast<Core*>(grid[i][j]);
                    if (core) {
                        cout << "Core " << core->core_id << "\n";
                    } else {
                        Memory* memory = dynamic_cast<Memory*>(grid[i][j]);
                        if (memory) {
                            cout << "Memory " << memory->memory_id << "\n";
                        }
                    }
                }
            }
        }
    }
};

