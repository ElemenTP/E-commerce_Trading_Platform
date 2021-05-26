CC=g++
CFLAGS=-O2

objects = main.o friend.o pagea.o pageb.o filter.o

ECTP: $(objects)
	$(CC) $(objects) -o ECTP.exe

main.o: global.hpp json.hpp main.cpp
	$(CC) $(CFLAGS) -c main.cpp
friend.o: global.hpp json.hpp friend.cpp
	$(CC) $(CFLAGS) -c friend.cpp
pagea.o: global.hpp json.hpp pagea.cpp
	$(CC) $(CFLAGS) -c pagea.cpp
pageb.o: global.hpp json.hpp pageb.cpp
	$(CC) $(CFLAGS) -c pageb.cpp
filter.o: global.hpp json.hpp filter.cpp
	$(CC) $(CFLAGS) -c filter.cpp

.PHONY: clean
clean:
	del ECTP.exe $(objects)