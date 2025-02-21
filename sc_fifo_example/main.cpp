#include "systemc.h"
using namespace std;

SC_MODULE(Producer)
{
	sc_fifo_out<int> fifo_out;

	SC_CTOR(Producer)
	{
		SC_THREAD(produce);
	}
	void produce() {
		for (int i = 0; i < 10; i++) {
			wait(1,SC_NS);
			fifo_out.write(i);
			std::cout << "producer wrote: " << i << "@ " <<sc_time_stamp() << std::endl;
		}
	}
};

SC_MODULE(Consumer)
{
	sc_fifo_in <int> fifo_in;

	SC_CTOR(Consumer)
	{
		SC_THREAD(consume);
	}
	void consume() {
		for(int i = 0; i < 10; i++) {
			wait(3,SC_NS);
			int data = fifo_in.read();
			std::cout << "consumer read: " << i << "@ " << sc_time_stamp() << std::endl;
		}
	}
};

int sc_main(int argc, char * argv[])
{
	sc_fifo<int> fifo(20); //fifo with depth of 5

	Producer pr("producer");
	Consumer co("consumer");

	pr.fifo_out(fifo);
	co.fifo_in(fifo);
	
	sc_start();

	return 0;
}
