all:
	g++ -I/home/nicko/implementations/systemc-2.3.3/include tb_first_counter.cpp first_counter.cpp  -L/home/nicko/implementations/systemc-2.3.3/lib-linux64  -lsystemc  -fpermissive

view:
	gtkwave counter_waveform.vcd

clean:
	rm a.out  counter_waveform.vcd 

