#include "systemc.h"
using namespace std;

int ar[32][5]; //used to keep all the test vectors

void input_vals() {

    // Generate binary values
    for (int i = 0; i < 32; i++) {  // Loop through numbers 0 to 31
        for (int j = 4; j >= 0; j--) {  // Extract each bit from MSB to LSB
            ar[i][j] = (i >> (4 - j)) & 1;  // Extract bit using bitwise shift
        }
    }

    // Print the array to verify
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << ar[i][j];
        }
        std::cout << std::endl;
    }
}



SC_MODULE(adder)
{
    sc_in <bool> a, b, cin;
    sc_out <bool> sum, cout;

    // Functionality
    void func()
    {
        sum.write((a.read() ^ b.read() ^ cin.read()));
        cout.write(((a.read() & b.read()) | (b.read() & cin.read()) | (a.read() & cin.read())));
	std::cout << "sum: " << sum << "cout: " << cout << std::endl;
    }

    SC_CTOR(adder)
    {
	std::cout << "Creating a 1-bit adder" << endl;
        SC_METHOD(func);
        sensitive << a << b << cin;
    }
};

SC_MODULE(adder_2bits)
{
    sc_in <bool> a0, a1, b0, b1, cin;
    sc_out <bool> sum0, sum1, carry_out;

    // Instantiate two 1-bit adders
    adder ad0, ad1;

    sc_signal <bool> cout_conn;

    SC_CTOR(adder_2bits) : ad0("adder0"),ad1("adder1")
    {
    
        // Connect the first adder
        ad0.a(a0);
        ad0.b(b0);
        ad0.cin(cin);
        ad0.sum(sum0);
        ad0.cout(cout_conn);

        // Connect the second adder
        ad1.a(a1);
        ad1.b(b1);
        ad1.cin(cout_conn);
        ad1.sum(sum1);
        ad1.cout(carry_out);

	std::cout << "Created a 2-bit adder module" << endl;
    }
};

int sc_main(int argc, char *argv[])
{
    // Instantiate the 2-bit adder
    adder_2bits add("adder_2bit");

    // Declare signals
    sc_signal <bool> a0, a1, b0, b1, cin;
    sc_signal <bool> sum0, sum1, carry_out;

    // Connect signals to the 2-bit adder
    add.a0(a0);
    add.a1(a1);
    add.b0(b0);
    add.b1(b1);
    add.cin(cin);
    add.sum0(sum0);
    add.sum1(sum1);
    add.carry_out(carry_out);

    // Create a trace file
    sc_trace_file *tf = sc_create_vcd_trace_file("waveform");

    // Trace signals
    sc_trace(tf, a0, "a0");
    sc_trace(tf, a1, "a1");
    sc_trace(tf, b0, "b0");
    sc_trace(tf, b1, "b1");
    sc_trace(tf, cin, "cin");
    sc_trace(tf, sum0, "sum0");
    sc_trace(tf, sum1, "sum1");
    sc_trace(tf, carry_out, "carry_out");
   

    input_vals();

    // Initialize signals
    a0.write((false));
    a1.write((false));
    b0.write((false));
    b1.write((false));
    cin.write((false));

    // Start simulation
    sc_start(10, SC_NS); // Run for 1 ns to initialize

    for (int i = 0; i < 32; i++) {
            // Assign values to signals
            a0.write((bool)(ar[i][0]));
            a1.write((bool)(ar[i][1]));
            b0.write((bool)(ar[i][2]));
            b1.write((bool)(ar[i][3]));
            cin.write((bool)(ar[i][4]));

            // Print assigned values
            cout << "@" << sc_time_stamp() << " Assigned: ";
            cout << a0.read() << a1.read() << b0.read() << b1.read() << cin.read() << endl;

            sc_start(sc_time(5, SC_NS));  // Wait for 5ns before assigning next values
   }

   // Close the trace file
    sc_close_vcd_trace_file(tf);

    std::cout << "Simulation finished." << endl;

    return 0;
}
