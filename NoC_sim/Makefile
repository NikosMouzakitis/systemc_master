all:
	g++ -std=c++17 -I/home/nicko/work/systemc-3.0.1/include main.cpp mesh_router.cpp thermal_model.cpp -L/home/nicko/work/systemc-3.0.1/lib-linux64  -lsystemc  -fpermissive -Wdeprecated-declarations

run: 
	./a.out | grep LATENC > noc_log.txt
analysis:
	python3 analysis.py
extended: 
	python3 analysis2.py
clean:
	rm a.out  noc_log.txt noc_dashboard.html path_statistics.csv noc_analysis.csv noc_analysis_results.csv thermal_data.csv
