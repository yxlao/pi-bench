CC = g++


CPPFILES = $(wildcard *.cc)
OFILES = $(patsubst %.cc,%.o,$(CPPFILES))
TARGETS = $(patsubst %.cc,%,$(CPPFILES))

.PRECIOUS: $(OFILES)

all: $(TARGETS)

%: %.cc
	$(CC) -Wall -O0 -std=c++11 -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OFILES) $(TARGETS)