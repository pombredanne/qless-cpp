CC = gcc
CCOPTS = -O3 -Wall -g -Iinclude
CPP = g++
CPPOPTS = -O3 -Wall -g -Iinclude

LD = ld
LDOPTS = 

all: qless

job.o: include/job.h include/util.h src/job.cpp
	$(CPP) $(CPPOPTS) -o job.o -c src/job.cpp

client.o: include/client.h include/util.h src/client.cpp
	$(CPP) $(CPPOPTS) -o client.o -c src/client.cpp

queue.o: include/queue.h include/util.h src/queue.cpp
	$(CPP) $(CPPOPTS) -o queue.o -c src/queue.cpp

util.o: include/util.h src/util.cpp
	$(CPP) $(CPPOPTS) -o util.o -c src/util.cpp

qless: client.o queue.o util.o job.o
	$(CPP) $(CPPOPTS) -o qless src/driver.cpp client.o queue.o util.o job.o -lhiredis

clean:
	rm -rdf *.o qless