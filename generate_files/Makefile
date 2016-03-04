CC = g++


CPPFILES = $(wildcard *.cpp)
OFILES = $(patsubst %.cpp,%.o,$(CPPFILES))
TARGETS = $(patsubst %.cpp,%,$(CPPFILES))

.PRECIOUS: $(OFILES)

all: $(TARGETS)

%: %.cpp
	@dos2unix -q $<
	$(CC) -Wall -o $@ $<

.PHONY: clean

clean:
	rm -rf $(OFILES) $(TARGETS)
