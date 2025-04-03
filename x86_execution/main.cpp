#include <systemc>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace sc_core;

SC_MODULE(InstructionParser) {
    std::vector<uint64_t> addresses;
    std::vector<std::string> instructions;

    void parse_instructions() {
        std::ifstream file("instructions.txt");
        if (!file) {
            std::cerr << "Error: Could not open instructions.txt\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            uint64_t address;
            std::string instr;

            if (iss >> std::hex >> address) {
                std::getline(iss, instr); // Read the rest as instruction
                addresses.push_back(address);
                instructions.push_back(instr);
            }
        }
        file.close();
    }

    void simulate_execution() {
	std::cout << "instructions to be executed in simulation" << std::endl;
        for (size_t i = 0; i < addresses.size(); ++i) {
            std::cout << std::hex << addresses[i] << ": " << instructions[i] << std::endl;
            wait(1, SC_NS); // Simulate 1ns delay per instruction
        }
    }

    SC_CTOR(InstructionParser) {
        SC_THREAD(parse_instructions);
        SC_THREAD(simulate_execution);
    }
};

int sc_main(int argc, char* argv[]) {
    InstructionParser parser("Parser");
    sc_start();
    return 0;
}

