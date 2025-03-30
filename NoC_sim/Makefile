all:
	g++ -I/home/nicko/implementations/systemc-2.3.3/include main.cpp mesh_router.cpp -L/home/nicko/implementations/systemc-2.3.3/lib-linux64  -lsystemc  -fpermissive 

run: 
	./a.out | grep LATENC > noc_log.txt
analysis:
	python3 analysis.py
extended: 
	python3 analysis2.py
clean:
	rm a.out  noc_log.txt noc_dashboard.html path_statistics.csv noc_analysis.csv noc_analysis_results.csv
