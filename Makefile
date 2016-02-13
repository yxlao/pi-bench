CC = g++


CPPFILES = $(wildcard *.cc)
OFILES = $(patsubst %.cc,%.o,$(CPPFILES))
TARGETS = $(patsubst %.cc,%,$(CPPFILES))

.PRECIOUS: $(OFILES)

all: a b c d e f g

a: c4_create_proc.cc utils.h
	$(CC) -Wall -O0 -std=c++11 -o c4_create_proc c4_create_proc.cc

b: c6_switch_proc.cc utils.h
	$(CC) -Wall -O0 -std=c++11 -o c6_switch_proc c6_switch_proc.cc

c: c2_proc_call.cc utils.h
	$(CC) -Wall -O0 -std=c++11 -o c2_proc_call c2_proc_call.cc

d: c1_measurement.cc utils.h
	$(CC) -Wall -O0 -std=c++11 -o c1_measurement c1_measurement.cc

e: c3_sys_call.cc utils.h
	$(CC) -Wall -O0 -std=c++11 -o c3_sys_call c3_sys_call.cc

f: c5_create_thread.cc utils.h
	$(CC) -pthread -Wall -O0 -std=c++11 -o c5_create_thread c5_create_thread.cc

g: c7_switch_thread.cc utils.h
	$(CC) -pthread -Wall -O0 -std=c++11 -o c7_switch_thread c7_switch_thread.cc

.PHONY: clean

clean:
	rm -rf $(OFILES) $(TARGETS)
	rm *.txt

clean_txt:
	rm *.txt
