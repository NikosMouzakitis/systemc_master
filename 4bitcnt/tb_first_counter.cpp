#include "systemc.h"
#include "first_counter.cpp" // Include the counter module

int sc_main(int argc, char* argv[]) {
    // Declare signals
    sc_clock clk("clk", 10, SC_NS); // 10 ns period clock
    sc_signal<sc_bit> reset;
    sc_signal<sc_bit> enable;
    sc_signal<sc_uint<4>> counter_out;

    // Instantiate the counter module
    first_counter fc("fc");
    fc.clock(clk);
    fc.reset(reset);
    fc.enable(enable);
    fc.counter_out(counter_out);

    // Open a trace file for waveform viewing
    sc_trace_file *tf = sc_create_vcd_trace_file("counter_waveform");
    sc_trace(tf, clk, "clk");
    sc_trace(tf, reset, "reset");
    sc_trace(tf, enable, "enable");
    sc_trace(tf, counter_out, "counter_out");

    // Initialize signals
    reset = sc_bit(0);
    enable = sc_bit(0);

    // Start the simulation
    sc_start(10, SC_NS); // Run for 10 ns

    // Apply reset
    reset = sc_bit(1);
    sc_start(10, SC_NS); // Run for 10 ns
    reset = sc_bit(0);

    // Enable the counter
    enable = sc_bit(1);
    sc_start(400, SC_NS); // Run for 100 ns

    // Disable the counter
    enable = sc_bit(0);
    sc_start(20, SC_NS); // Run for 20 ns

    // Close the trace file
    sc_close_vcd_trace_file(tf);

    cout << "Testbench finished!" << endl;

    return 0;
}
