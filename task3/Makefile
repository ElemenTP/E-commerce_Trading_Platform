CC=g++
CFLAGS=-O2
LDFLAGS = -lwsock32

objects = main.o friend.o pagea.o pageb.o filter.o cell.o client.o

client: $(objects)
	$(CC) $(objects) -o client.exe $(LDFLAGS)

server: network.hpp server.cpp
	$(CC) server.cpp -o server.exe $(LDFLAGS)

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
cell.o: global.hpp json.hpp cell.cpp
	$(CC) $(CFLAGS) -c cell.cpp
client.o: global.hpp json.hpp client.cpp network.hpp
	$(CC) $(CFLAGS) -c client.cpp

.PHONY: clean
clean:
	del client.exe $(objects) server.exe