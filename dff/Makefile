all:
	g++ -I/home/nicko/implementations/systemc-2.3.3/include tb_main.cpp main.cpp  -L/home/nicko/implementations/systemc-2.3.3/lib-linux64  -lsystemc  -fpermissive

view:
	gtkwave dff_waveform.vcd

clean:
	rm a.out  dff_waveform.vcd 

