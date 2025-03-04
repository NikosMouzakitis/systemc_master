#include "systemc.h"
#include "tlm.h"

SC_MODULE(test)
{
	sc_in_clk clock;
	int val = 3;

	void func(void)
	{
		while(true) {
			cout << val << " ready" <<  endl;
			val--;
			wait();
			cout << val <<" set" <<  endl;
			val--;
			wait();
			cout << val << " go" << endl;
			val--;
			wait();
			val=3;
		}
	}
	SC_CTOR(test)
	{
		SC_THREAD(func);
		sensitive << clock.pos();
	}

};

int sc_main(int argc, char *argv[])
{
	sc_clock clk("clk", 10, SC_NS); // 10 ns period clock
	test t("test");

	t.clock(clk);

	sc_start(sc_time(100,SC_NS));

	return 0;
}
