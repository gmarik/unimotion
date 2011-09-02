SDK:=$(shell ls /Developer/SDKs | sort -r | head -n 1)
CFLAGS=-Wall -Os -g -isysroot /Developer/SDKs/$(SDK) -arch i386 -arch ppc -I../unimotion -fconstant-cfstrings
LFLAGS=-Wl,-syslibroot,/Developer/SDKs/$(SDK) -arch i386 -arch ppc -framework CoreFoundation
TARGET=../bin/calibrate

all: $(TARGET)
clean:
	rm -f *.o $(TARGET)

$(TARGET): main.o
	$(CC) $(LFLAGS) -o $@ $^ -L../bin  -lUniMotion

main.o: main.c

