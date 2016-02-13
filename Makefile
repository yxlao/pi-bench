CC = g++
CFLAGS = -Wall -O0 -std=c++11

# headers
HEADERS = $(wildcard *.h)

# objects
OBJECTS = $(patsubst %.cc, %.o, $(wildcard *.cc))

# targets
CPPTHREAD = $(wildcard *thread*.cc)
CPPNORMAL = $(filter-out $(wildcard *thread*.cc) utils.cc, $(wildcard *.cc))
CPPFILES = $(CPPNORMAL) $(CPPTHREAD)
TARGETSTHREAD = $(patsubst %.cc,%,$(CPPTHREAD))
TARGETSNORMAL = $(patsubst %.cc,%,$(CPPNORMAL))
TARGETS = $(TARGETSNORMAL) $(TARGETSTHREAD)

all: $(TARGETSNORMAL) $(TARGETSTHREAD)

%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGETSTHREAD): % : %.o utils.o utils.h
	$(CC) -pthread $(CFLAGS) $< -o $@

$(TARGETSNORMAL): % : %.o utils.o utils.h
	$(CC) $(CFLAGS) $< -o $@

.PRECIOUS: $(OBJECTS)

.PHONY: clean all

clean:
	rm -rf $(OBJECTS) $(TARGETS)
