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

all: $(TARGETS)

%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGETS): $(OBJECTS)
	echo "hello"

.PRECIOUS: $(OBJECTS)

.PHONY: clean all

clean:
	rm -rf $(OBJECTS) $(TARGETS)
