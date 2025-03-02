#include "systemc.h"
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace tlm;
using namespace tlm_utils;

// TestModule1: Initiator
SC_MODULE(TestModule1) {
    simple_initiator_socket<TestModule1> initiator_socket;

    SC_CTOR(TestModule1) : initiator_socket("initiator_socket") {
        SC_THREAD(run);
    }

    void run() {
        for (int i = 0; i < 5; i++) {
            // Create a payload
            tlm_generic_payload payload;
            sc_time delay = SC_ZERO_TIME;
            unsigned int data = i;

            // Set up the payload
            payload.set_command(TLM_WRITE_COMMAND);
            payload.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
            payload.set_data_length(sizeof(data));

            // Send the payload
            cout << "TestModule1: Sending data = " << data << " at time " << sc_time_stamp() << endl;
            initiator_socket->b_transport(payload, delay);

            // Wait for a response
            wait(1, SC_NS);
        }
    }
};

// TestModule2: Target
SC_MODULE(TestModule2) {
    simple_target_socket<TestModule2> target_socket;

    SC_CTOR(TestModule2) : target_socket("target_socket") {
        target_socket.register_b_transport(this, &TestModule2::b_transport);
    }

    void b_transport(tlm_generic_payload& payload, sc_time& delay) {
        // Read the data
        unsigned int data = *reinterpret_cast<unsigned int*>(payload.get_data_ptr());
        cout << "TestModule2: Received data = " << data << " at time " << sc_time_stamp() << endl;

        // Simulate processing delay
        wait(1, SC_NS);

        // Respond with modified data
        data += 1;
        payload.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
        cout << "TestModule2: Sending back data = " << data << " at time " << sc_time_stamp() << endl;
    }
};

// Top Module
SC_MODULE(Top) {
    TestModule1 test_module1;
    TestModule2 test_module2;

    SC_CTOR(Top) : test_module1("test_module1"), test_module2("test_module2") {
        // Connect the initiator socket of TestModule1 to the target socket of TestModule2
        test_module1.initiator_socket.bind(test_module2.target_socket);
    }
};

int sc_main(int argc, char* argv[]) {
    Top top("top");
    sc_start(10, SC_NS);  // Run the simulation for 10 ns
    return 0;
}
