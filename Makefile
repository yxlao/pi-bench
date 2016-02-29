CC = g++
CFLAGS = -Wall -O0 -std=c++11

# thread
CPPS_THREAD = $(wildcard *thread*.cc)
OBJS_THREAD = $(patsubst %.cc,%.o,$(CPPS_THREAD))
BINS_THREAD = $(patsubst %.cc,%,$(CPPS_THREAD))

# network
CPPS_NETWORK = $(wildcard *network*.cc)
OBJS_NETWORK = $(patsubst %.cc,%.o,$(CPPS_NETWORK))
BINS_NETWORK = $(patsubst %.cc,%,$(CPPS_NETWORK))

# normal
CPPS_NORMAL = $(filter-out $(CPPS_THREAD) $(CPPS_NETWORK) utils.cc utils_tcp.cc, $(wildcard *.cc))
OBJS_NORMAL = $(patsubst %.cc,%.o,$(CPPS_NORMAL))
BINS_NORMAL = $(patsubst %.cc,%,$(CPPS_NORMAL))

# global info
OBJS = $(patsubst %.cc,%.o,$(wildcard *.cc))
BINS = $(BINS_THREAD) $(BINS_NETWORK) $(BINS_NORMAL)

default: $(BINS)
all: default

# utilities
utils.o: utils.cc utils.h
	@echo ">>> utils"
	@echo "compiling $@ from $<"
	$(CC) $(CFLAGS) -c $< -o $@

utils_tcp.o: utils_tcp.cc utils.h utils_tcp.h
	@echo ">>> utils_tcp"
	@echo "compiling $@ from $<"
	$(CC) $(CFLAGS) -c $< -o $@

# binaries
$(BINS_NORMAL): % : %.o utils.o
	@echo ">>> BINS_NORMAL"
	@echo "linking $@ from $<"
	$(CC) $(CFLAGS) utils.o $< -o $@

$(BINS_THREAD): % : %.o utils.o
	@echo ">>> BINS_THREAD"
	@echo "linking $@ from $<"
	$(CC) -pthread $(CFLAGS) utils.o $< -o $@

$(BINS_NETWORK): % : %.o utils.o utils_tcp.o
	@echo ">>> BINS_NETWORK"
	@echo "linking $@ from $<"
	$(CC) $(CFLAGS) utils.o utils_tcp.o $< -o $@

# object files
$(OBJS_NORMAL) $(OBJS_THREAD): %.o : %.cc utils.h
	@echo ">>> OBJS_NORMAL OBJS_THREAD"
	@echo "compiling $@ from $<"
	@dos2unix -q $<
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_NETWORK): %.o : %.cc utils.h utils_tcp.h
	@echo ">>> OBJS_NETWORK"
	@echo "compiling $@ from $<"
	@dos2unix -q $<
	$(CC) $(CFLAGS) -c $< -o $@

# misc
module:
	sudo insmod raspbian-ccr/enable-ccr.ko

temp:
	sudo /opt/vc/bin/vcgencmd measure_temp

.PRECIOUS: $(OBJS)

.PHONY: clean all temp module

clean:
	rm -rf *.o $(BINS)
