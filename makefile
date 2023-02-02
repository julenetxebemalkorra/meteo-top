CC = g++
CFLAGS = -Wall
LDFLAGS =
LIBS = -lcurl -ljsoncpp

INCLUDES = open_meteo.h

SOURCES := open_meteo.cpp main.cpp 
OBJS := $(SOURCES:.cpp =.o)

meteo-top : $(OBJS)
	$(CC) $(CFLAGS) -o meteo-top.exe $(OBJS) $(LDFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
clean:
	rm *.o temp
