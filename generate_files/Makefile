CC = g++


CCFILES = $(wildcard *.cc)
OFILES = $(patsubst %.cc,%.o,$(CCFILES))
TARGETS = $(patsubst %.cc,%,$(CCFILES))

.PRECIOUS: $(OFILES)

all: $(TARGETS)

%: %.cpp
	@dos2unix -q $<
	$(CC) -Wall -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OFILES) $(TARGETS)
