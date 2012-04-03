CC = gcc
CCOPTS = -O3 -Wall -g -Iinclude

CPP = g++
CPPOPTS = -O3 -Wall -g -Iinclude

all: qless

job.o: include/job.h include/qless.h src/job.cpp
	$(CPP) $(CPPOPTS) -o job.o -c src/job.cpp

client.o: include/client.h include/qless.h src/client.cpp
	$(CPP) $(CPPOPTS) -o client.o -c src/client.cpp

queue.o: include/queue.h include/qless.h src/queue.cpp
	$(CPP) $(CPPOPTS) -o queue.o -c src/queue.cpp

qless.o: include/qless.h src/qless.cpp
	$(CPP) $(CPPOPTS) -o qless.o -c src/qless.cpp

qless: client.o queue.o qless.o job.o
	$(CPP) $(CPPOPTS) -o qless src/driver.cpp job.o client.o queue.o qless.o -lhiredis

clean:
	rm -rdf *.o qless