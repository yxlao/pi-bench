CC = g++


CPPFILES = $(wildcard *.cc)
OFILES = $(patsubst %.cc,%.o,$(CPPFILES))
TARGETS = $(patsubst %.cc,%,$(CPPFILES))

.PRECIOUS: $(OFILES)

all: $(TARGETS)

%: %.cc cycles.h
	$(CC) -Wall -O0 -std=c++11 -o create_process create_process.cc
	$(CC) -Wall -O0 -std=c++11 -o switch_process switch_process.cc
	$(CC) -Wall -O0 -std=c++11 -o test_proc test_proc.cc
	$(CC) -Wall -O0 -std=c++11 -o measurement measurement.cc
	$(CC) -Wall -O0 -std=c++11 -o sys_call sys_call.cc
	$(CC) -pthread -Wall -O0 -std=c++11 -o test_thread_create test_thread_create.cc
	$(CC) -pthread -Wall -O0 -std=c++11 -o test_thread_switch test_thread_switch.cc

.PHONY: clean

clean:
	rm -rf $(OFILES) $(TARGETS)
	rm *.txt

clean_txt:
	rm *.txt
