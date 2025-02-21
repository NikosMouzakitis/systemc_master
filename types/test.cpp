#include "systemc.h"


int sc_main(int argc, char *argv[])
{

	sc_bit enable1;
	sc_bit read_en1;

	enable1 = '1';
	cout << "value of enable1: " << enable1 << endl;
	read_en1 = enable1;
	cout << "value of read_en1: " << read_en1 << endl;


	sc_logic read_en,pad, enable;
	sc_bit no_x_z;

	pad = 'z';
	cout << "pad: " << pad << endl;

	enable='0';
	cout << "enable: " << enable << endl;
	read_en = ~enable;	
	cout << "read_en: " << read_en << endl;

	if(pad == '1')
	{
		cout << "pad is 1" <<  endl;
	} else {

		cout << "pad is not 1" << endl;
	}

	no_x_z = enable;
	cout << "no_x_z: " << no_x_z << endl;
	no_x_z = pad;
	cout << "no_x_z: " << no_x_z << endl;

	pad = sc_logic('x');
	cout << "pad: " << pad  << endl;

	no_x_z = pad;
	cout << "no_x_z: " << no_x_z << endl;


	return 1;
}
