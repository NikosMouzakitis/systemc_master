#include "systemc.h"

int array[32][5];  // 32 rows, 5 columns used for the testing.

SC_MODULE(adder)
{
	sc_in <sc_bit> a;
	sc_in <sc_bit> b;
	sc_in <sc_bit> cin;
	sc_out <sc_bit> sum;
	sc_out <sc_bit> cout;
	

	//functionality
	void func()
	{
		sum = a ^ b ^ cin;
		cout = (a & b) | (b & cin) | (a & cin);
	}

	SC_CTOR(adder)
	{
		SC_METHOD(func);
		sensitive << a << b << cin;
	}
};




void input_vals() {

    // Generate binary values
    for (int i = 0; i < 32; i++) {  // Loop through numbers 0 to 31
        for (int j = 4; j >= 0; j--) {  // Extract each bit from MSB to LSB
            array[i][j] = (i >> (4 - j)) & 1;  // Extract bit using bitwise shift
        }
    }

    // Print the array to verify
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 5; j++) {
            std::cout << array[i][j];
        }
        std::cout << std::endl;
    }
}


int sc_main(int argc, char * argv[])
{
	adder ad0("adder 0 "), ad1("adder 1");

	sc_signal <sc_bit> a0;
	sc_signal <sc_bit> b0;
	sc_signal <sc_bit> cin0;
	sc_signal <sc_bit> sum0;
	sc_signal <sc_bit> cout0;

	sc_signal <sc_bit> a1;
	sc_signal <sc_bit> b1;
	sc_signal <sc_bit> cin1;
	sc_signal <sc_bit> sum1;
	sc_signal <sc_bit> cout1;
	
	ad0.a(a0);
	ad0.b(b0);
	ad0.cin(cin0);
	ad0.sum(sum0);
	ad0.cout(cout0);

	ad1.a(a1);
	ad1.b(b1);
	ad1.cin(cout0);
	ad1.sum(sum1);
	ad1.cout(cout1);

	
	//start simulation
	//simulation start	
	sc_trace_file *tf = sc_create_vcd_trace_file("waveform");

	sc_trace(tf,a0,"a0");
	sc_trace(tf,a1,"a1");
	sc_trace(tf,b0,"b0");
	sc_trace(tf,b1,"b1");
	sc_trace(tf,cin0,"cin0");
	
	sc_trace(tf,sum0,"SUM0");
	sc_trace(tf,sum1,"SUM1");
	sc_trace(tf,cout1,"COUT");
	
	//create the test variables
	input_vals();		
	sc_start();
	
	for (int i = 0; i < 32; i++) {
            // Assign values to signals
            a0.write(sc_bit(array[i][0]));
            a1.write(sc_bit(array[i][1]));
            b0.write(sc_bit(array[i][2]));
            b1.write(sc_bit(array[i][3]));
            cin0.write(sc_bit(array[i][4]));

            // Print assigned values
            cout << "@" << sc_time_stamp() << " Assigned: ";
            cout << a0.read() << a1.read() << b0.read() << b1.read() << cin0.read() << endl;

            sc_start(sc_time(5, SC_NS));  // Wait for 5ns before assigning next values
        }

	return 0;
}
