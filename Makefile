#CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

CXXFLAGS = 	-c -g -fPIC -Wall -O2 -std=c++11 -Wall -fmessage-length=0  $(INCLUDE_DIR)
LDFLAGS =	-g -shared -Wall -m64 

ROOT_INCLUDE += $(shell $(ROOTSYS)/bin/root-config --incdir)
ROOT_LIBS += $(shell $(ROOTSYS)/bin/root-config --libs)

INCLUDE_DIR += -I/usr/include/jsoncpp -I/usr/include/boost -I$(ROOT_INCLUDE) 

OBJS =	ScanResultJSON.o  ScanResult.o ScanJSON.o Scan.o ScanSet.o ScanSetJSON.o FileNameFinder.o BoundaryFunctionOfEmittance.o DerivativeFunctionOfEpsilon.o 

LIBS += $(ROOT_LIBS)  -ljsoncpp -lboost_program_options

TARGET =	WireScanSets


$(TARGET):	$(OBJS) $(TARGET).o 
	$(CXX) -o $(TARGET) $(TARGET).o $(OBJS) $(LIBS)
	
testErrors:	$(OBJS) testErrors.o
	$(CXX) -o testErrors testErrors.o $(OBJS) $(LIBS)
	
readScanJSON : $(OBJS) readScanJSON.o 
	$(CXX) -o readScanJSON readScanJSON.o $(OBJS) $(LIBS)

readScanArrayJSON : $(OBJS) readScanArrayJSON.o 
	$(CXX) -o readScanArrayJSON readScanArrayJSON.o $(OBJS) $(LIBS)
	

all:	$(TARGET) testErrors


clean:
	rm -f $(OBJS) $(TARGET) $(TESTS) testErrors.o readScanJSON readScanArrayJSON readScanJSON.o readScanArrayJSON.o WireScanSets.o
