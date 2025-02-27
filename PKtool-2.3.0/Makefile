
# system settings
include Makefile-system

# source files, header folders, building options
include Makefile-prj

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
IFLAGS+= -I./src/
IFLAGS+= -I$(SYSTEMC_PATH)/include
IFLAGS+= -I$(TLM_PATH)/include/tlm
DFLAGS+=
OPT_FLAGS+= $(OPT_DEBUG)
WFLAGS+= 


# linker options
#    -L* options
#    -l* options
#    other linker options
LDLIBS+= -lsystemc
LDPATH+= -L$(SYSTEMC_PATH)/lib-$(SYSTEMC_TARGET_ARCH)

# colleting flag for compiling and linking
CFLAGS+= $(OPT_FLAGS) $(IFLAGS) $(DFLAGS) $(WFLAGS) $(FFLAGS)
LFLAGS+= $(LDPATH) $(LDLIBS)
# ==============================================================================

#raccolta variabili per i targets
TARGET_PATH:=$(PKTOOL_PATH)
TARGET:=./lib/libpktool.a

include Makefile-targets

# -include $(SRCS:%.cpp=%.d)
# -include $(SRCS:./src/%.cpp=$(OBJ_PATH)/%.d)

