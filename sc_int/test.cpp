#include "systemc.h"


int sc_main(int argc, char *argv[])
{

	sc_int <4> a;


	a = 0;
	
	for(int i = 0; i < 20; i++)
	{
		cout << "a: "<< a << endl;
		a++;
	}
	

	sc_bigint<128> large;

	large = 1000 << 1;

	cout  << "large is: "<< large << endl;

	return 0;
}
