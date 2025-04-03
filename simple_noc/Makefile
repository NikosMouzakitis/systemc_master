CXX = g++
SYSTEMC_HOME =/home/nicko/work/systemc-2.2.0/build/
OCCN_HOME = /home/nicko/work/occn_3

CXXFLAGS = -I$(SYSTEMC_HOME)/include -I$(OCCN_HOME)/include -std=c++11 -fPIC
LDFLAGS = -L$(SYSTEMC_HOME)/lib-linux64 -L$(OCCN_HOME)/lib-linux64 -no-pie -fpermissive
#LDLIBS = -Wl,--start-group -lsystemc -loccn -lpthread -Wl,--end-group
#LDLIBS = -lsystemc -loccn -lpthread -lsystemc
LDLIBS = -Wl,--start-group -lsystemc -loccn -lpthread -Wl,--end-group \
         -Wl,--exclude-libs=StatGuiNewFile.o -Wl,--exclude-libs=StatDurationLib.o
CXXFLAGS += -DOCCN_NO_GUI_STATS -DOCCN_NO_GUI -DOCCN_NO_STATS -DNO_STAT_GUI -DNO_STAT_FILE  # Add this to disable GUI stats

all: noc_simulation

noc_simulation: main.cpp router.h ni.h noc_common.h
	$(CXX) $(CXXFLAGS) main.cpp $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -f noc_simulation *.o
