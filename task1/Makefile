CC=g++
CFLAGS=-O2

objects = main.o friend.o page.o

ECTP: $(objects)
	$(CC) $(objects) -o ECTP.exe

main.o: global.hpp json.hpp main.cpp
	$(CC) $(CFLAGS) -c main.cpp
friend.o: global.hpp json.hpp friend.cpp
	$(CC) $(CFLAGS) -c friend.cpp
page.o: global.hpp json.hpp page.cpp
	$(CC) $(CFLAGS) -c page.cpp

.PHONY: clean
clean:
	del ECTP.exe $(objects)