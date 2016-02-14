CC = g++
CFLAGS = -Wall -O0 -std=c++11

# headers
HEADERS = $(wildcard *.h)

# objects
OBJECTS = $(patsubst %.cc, %.o, $(wildcard *.cc))

# targets
CPP_THREAD = $(wildcard *thread*.cc)
CPP_NORMAL = $(filter-out $(wildcard *thread*.cc) utils.cc, $(wildcard *.cc))
CPPFILES = $(CPP_NORMAL) $(CPP_THREAD)
TARGETS_THREAD = $(patsubst %.cc,%,$(CPP_THREAD))
TARGETS_NORMAL = $(patsubst %.cc,%,$(CPP_NORMAL))
TARGETS = $(TARGETS_NORMAL) $(TARGETS_THREAD)

default: $(TARGETS_NORMAL) $(TARGETS_THREAD)
all: default

%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGETS_THREAD): % : %.o utils.o utils.h
	$(CC) -pthread $(CFLAGS) utils.o $< -o $@

$(TARGETS_NORMAL): % : %.o utils.o utils.h
	$(CC) $(CFLAGS) utils.o $< -o $@

.PRECIOUS: $(OBJECTS)

.PHONY: clean all

clean:
	rm -rf $(OBJECTS) $(TARGETS)
