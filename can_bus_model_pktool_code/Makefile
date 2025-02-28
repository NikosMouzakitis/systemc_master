
# source files, header folders, building options
SRCS:= main.cpp

# support libraries, paths and options
include Makefile-local

# ==============================================================================

# compiler options:
#    -I* options
#    -D* options
#    -g -O3 -O2 ... optimization options
#    -W* options
#    -f* options
#    other compiler options 
IFLAGS:=
IFLAGS+= -I$(PKTOOL_PATH)/include
IFLAGS+= -I$(SYSTEMC_PATH)/include
IFLAGS+= -I.
DFLAGS:=
DFLAGS+=
OPT_FLAGS:=
OPT_FLAGS+= $(OPT_DEBUG)
WFLAGS:= 
WFLAGS+= -Wall
WFLAGS+= -Wno-pmf-conversions
WFLAGS+= -Wno-deprecated
FFLAGS:=
#FFLAGS+= -fno-volatile
FFLAGS+= -fno-stack-check 
CFLAGS:=

# linker options
#    -L* options
#    -l* options
#    other linker options
LDLIBS:=
LDPATH:=
LDLIBS+= -lpktool
LDPATH+= -L$(PKTOOL_PATH)/lib
LDLIBS+= -lsystemc
LDPATH+= -L$(SYSTEMC_PATH)/lib-$(SYSTEMC_TARGET_ARCH)

# collecting flag for compiling and linking
CFLAGS+= $(OPT_FLAGS) $(IFLAGS) $(DFLAGS) $(WFLAGS) $(FFLAGS)
LFLAGS+= $(LDPATH) $(LDLIBS)

# ==============================================================================

TARGET:= a.out

default: $(TARGET)

%.d : %.cpp
	@echo; echo depending $< ... ;
	@$(CXX) $(CFLAGS) -MM -MF $@ -MQ $(<:%.cpp=%.o) -MQ $@ $< ;
%.o: %.cpp
	@echo; echo compiling $< ... ;
	$(CXX) $(CFLAGS) -o $@ -c $< ;

$(TARGET): $(SRCS:%.cpp=%.o)
	@echo; echo creating/updating $@ ... ;
	$(LINK) -o $@ $+ $(LFLAGS) ;

clean:
	rm a.out waveform.vcd main.o
view:
	gtkwave waveform.vcd
#-include $(SRCS:%.cpp=%.d)
