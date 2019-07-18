CC       = gcc
CFLAGS   = -DNDEBUG -O3 -Wall
CXX      = g++
CXXFLAGS = -DNDEBUG -O3 -Wall

ifdef CONNECT_TYPE
CFLAGS   += -DCONNECT_TYPE_$(CONNECT_TYPE)
CXXFLAGS += -DCONNECT_TYPE_$(CONNECT_TYPE)
endif

ifdef TINKERBOARD
GPIOSRC = gpiotinker.cpp
GPIOLIB =  -lwiringPi
else
GPIOSRC = gpiobus.cpp
GPIOLIB =
endif
GPIOOBJ = $(GPIOSRC:%.cpp=%.o)

RASCSI = rascsi
RASCTL = rasctl
RASDUMP = rasdump

BIN_ALL = $(RASCSI) $(RASCTL) $(RASDUMP)

SRC_RASCSI = \
	rascsi.cpp \
	scsi.cpp \
	disk.cpp \
	ctapdriver.cpp \
	cfilesystem.cpp \
	filepath.cpp \
	fileio.cpp \
	$(GPIOSRC)

SRC_RASCTL = \
	rasctl.cpp

SRC_RASDUMP = \
	rasdump.cpp \
	scsi.cpp \
	filepath.cpp \
	fileio.cpp \
	$(GPIOSRC)

OBJ_RASCSI := $(SRC_RASCSI:%.cpp=%.o)
OBJ_RASCTL := $(SRC_RASCTL:%.cpp=%.o)
OBJ_RASDUMP := $(SRC_RASDUMP:%.cpp=%.o)
OBJ_ALL := $(OBJ_RASCSI) $(OBJ_RASCTL) $(OBJ_RASDUMP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ALL: $(BIN_ALL)

$(RASCSI): $(OBJ_RASCSI)
	$(CXX) -o $@ $(OBJ_RASCSI) -lpthread $(GPIOLIB)

$(RASCTL): $(OBJ_RASCTL)
	$(CXX) -o $@ $(OBJ_RASCTL)

$(RASDUMP): $(OBJ_RASDUMP)
	$(CXX) -o $@ $(OBJ_RASDUMP) $(GPIOLIB)

clean:
	rm -f *.o $(BIN_ALL)

$(GPIOOBJ) : $(GPIOSRC) gpiobus.h
