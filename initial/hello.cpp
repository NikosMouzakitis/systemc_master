#include "systemc.h"


SC_MODULE(hello)
{
	SC_CTOR(hello)
	{
		//empty constructor
	}
	
	void sayHello(void)
	{
		cout << "hi\n";
	}

};

int sc_main(int argc, char *argv[]) {

	hello h("HELLO");

	h.sayHello();
	return 0;
}
