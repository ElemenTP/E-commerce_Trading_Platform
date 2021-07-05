CC=cl
CFLAGS=/O2 /Qpar /EHsc /nologo /std:c++17

objects = main.obj friend.obj pagea.obj pageb.obj filter.obj cell.obj client.obj

client: $(objects)
	$(CC) $(CFLAGS) /Fe:client.exe $(objects)

server: network.hpp server.cpp
	$(CC) $(CFLAGS) /Fe:server.exe server.cpp

main.obj: global.hpp json.hpp main.cpp
	$(CC) $(CFLAGS) /c main.cpp
friend.obj: global.hpp json.hpp friend.cpp
	$(CC) $(CFLAGS) /c friend.cpp
pagea.obj: global.hpp json.hpp pagea.cpp
	$(CC) $(CFLAGS) /c pagea.cpp
pageb.obj: global.hpp json.hpp pageb.cpp
	$(CC) $(CFLAGS) /c pageb.cpp
filter.obj: global.hpp json.hpp filter.cpp
	$(CC) $(CFLAGS) /c filter.cpp
cell.obj: global.hpp json.hpp cell.cpp
	$(CC) $(CFLAGS) /c cell.cpp
client.obj: global.hpp json.hpp client.cpp network.hpp
	$(CC) $(CFLAGS) /c client.cpp

.PHONY: clean
clean:
	del client.exe $(objects) server.exe server.obj