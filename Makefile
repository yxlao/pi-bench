CC = g++


CPPFILES = $(wildcard *.cc)
OFILES = $(patsubst %.cc,%.o,$(CPPFILES))
TARGETS = $(patsubst %.cc,%,$(CPPFILES))

.PRECIOUS: $(OFILES)

all: a b c d e f g

a: create_process.cc cycles.h
	$(CC) -Wall -O0 -std=c++11 -o create_process create_process.cc

b: switch_process.cc cycles.h
	$(CC) -Wall -O0 -std=c++11 -o switch_process switch_process.cc

c: test_proc.cc cycles.h
	$(CC) -Wall -O0 -std=c++11 -o test_proc test_proc.cc

d: measurement.cc cycles.h
	$(CC) -Wall -O0 -std=c++11 -o measurement measurement.cc

e: sys_call.cc cycles.h
	$(CC) -Wall -O0 -std=c++11 -o sys_call sys_call.cc

f: test_thread_create.cc cycles.h
	$(CC) -pthread -Wall -O0 -std=c++11 -o test_thread_create test_thread_create.cc

g: test_thread_switch.cc cycles.h
	$(CC) -pthread -Wall -O0 -std=c++11 -o test_thread_switch test_thread_switch.cc

.PHONY: clean

clean:
	rm -rf $(OFILES) $(TARGETS)
	rm *.txt

clean_txt:
	rm *.txt
