CC = g++
CFLAGS = -Wall
LDFLAGS =
LIBS = -lcurl -ljsoncpp

SOURCES := main.cpp 
OBJS := $(SOURCES:.cpp =.o)

meteo-top : $(OBJS)
	$(CC) $(CFLAGS) -o meteo-top.exe $(OBJS) $(LDFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<
clean:
	rm *.o temp
