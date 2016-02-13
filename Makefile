CC = g++

CPPTHREAD = $(wildcard *thread*.cc)
CPPNORMAL = $(filter-out $(wildcard *thread*.cc), $(wildcard *.cc))
CPPFILES = $(CPPNORMAL) $(CPPTHREAD)

TARGETSTHREAD = $(patsubst %.cc,%,$(CPPTHREAD))
TARGETSNORMAL = $(patsubst %.cc,%,$(CPPNORMAL))
TARGETS = $(TARGETSNORMAL) $(TARGETSTHREAD)

.PRECIOUS: $(OFILES)

all: $(TARGETSTHREAD) $(TARGETSNORMAL)

$(TARGETSTHREAD): $(CPPTHREAD)
	$(CC) -pthread -Wall -O0 -std=c++11 -o $@ $@.cc

$(TARGETSNORMAL): $(CPPNORMAL)
	$(CC) -Wall -O0 -std=c++11 -o $@ $@.cc

.PHONY: clean

clean:
	rm -rf $(OFILES) $(TARGETS)
