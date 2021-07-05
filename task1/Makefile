CC=cl
CFLAGS=/O2 /Qpar /EHsc /nologo /std:c++17

objects = main.obj friend.obj pagea.obj pageb.obj filter.obj

ECTP: $(objects)
	$(CC) $(CFLAGS) /Fe:ECTP.exe $(objects)

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

.PHONY: clean
clean:
	del ECTP.exe $(objects)