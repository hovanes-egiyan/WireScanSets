#CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

CXXFLAGS = 	-c -g -fPIC -Wall -O2 -std=c++11 -Wall -fmessage-length=0  $(INCLUDE_DIR)
LDFLAGS =	-g -shared -Wall -m64 

ROOT_INCLUDE += $(shell root-config --incdir)
ROOT_LIBS += $(shell root-config --libs)

INCLUDE_DIR += -I/home/hovanes/GlueX/MCB/src -I/usr/include/jsoncpp -I$(ROOT_INCLUDE)

OBJS =	ScanResults.o ScanSet.o

LIBS += $(ROOT_LIBS)  -ljsoncpp 

TARGET =	WireScanSets


$(TARGET):	$(OBJS) $(TARGET).o 
	$(CXX) -o $(TARGET) $(TARGET).o $(OBJS) $(LIBS)
	
testErrors:	$(OBJS) testErrors.o
	$(CXX) -o testErrors testErrors.o $(OBJS) $(LIBS)

all:	$(TARGET) testErrors


clean:
	rm -f $(OBJS) $(TARGET) $(TESTS) testErrors.o WireScanSets.o
