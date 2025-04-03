#include "systemc.h"

//definitions of the interfaces.
class write_if : virtual public sc_interface {
	public:
		virtual void write(int data) = 0;
};
class read_if : virtual public sc_interface {
	public:
		virtual void read(int &data) = 0;
		virtual int num_available(void) = 0;
};

class fifo_channel : public sc_channel, public write_if, public read_if {
	private:
		int buffer[10];
		int head, tail, count;
		sc_event data_written_event, data_read_event;
	public:
		fifo_channel(sc_module_name name) : sc_channel(name), head(0), tail(0), count(0) {}

		void write(int data) {
			if(count == 10) {
				wait(data_read_event); //blocks here.
			}
			buffer[tail] = data;
			tail = (tail + 1) % 10; //increment the tail
			count++;
			data_written_event.notify(); //notify this event that data has been written on the fifo.
		}

		void read(int &data) {
			if(count == 0) {
				wait(data_written_event); // block on an empty fifo.
			}
			data = buffer[head];
			head = (head+1) % 10;
			count--;
			data_read_event.notify();
		}
		int num_available(void){
			return count;
		}
};

SC_MODULE(Producer)
{
	sc_port<write_if> out;
	void produce() {
		int data = 1;
		while(true) {
			out->write(data);	
			cout << "produced: " << data << " at " << sc_time_stamp() << endl;
			data++;	
			wait(1, SC_NS);
		}
	}
	SC_CTOR(Producer)
	{
		SC_THREAD(produce);
	}
};

SC_MODULE(Consumer)
{
	sc_port<read_if> in;

	void consume() {
		int data;
		while(true)
		{
			in->read(data);
			cout << "consumed: " << data << " at " << sc_time_stamp() << endl;
			wait(5, SC_NS);
		}
	}
	SC_CTOR(Consumer) {
		SC_THREAD(consume);
	}
};

SC_MODULE(Top)
{
	Producer *producer;
	Consumer *consumer;
	fifo_channel *fifo;

	SC_CTOR(Top) {
		producer = new Producer("producer");
		consumer = new Consumer("consumer");
		fifo = new fifo_channel("FIFO");
		producer->out.bind(*fifo);
		consumer->in.bind(*fifo);
	}
	~Top() {
		delete producer;
		delete consumer;
		delete fifo;
	}
};

int sc_main(int argc, char * argv[])
{
	Top top("TOP");
	sc_start(100,SC_NS);
	return 0;
}
