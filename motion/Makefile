SDK:=$(shell ls /Developer/SDKs | sort -r | head -n 1)
CFLAGS=-Wall -Os -g -isysroot /Developer/SDKs/$(SDK) -arch i386 -arch ppc -I../unimotion
LFLAGS=-Wl,-syslibroot,/Developer/SDKs/$(SDK) -arch i386 -arch ppc
TARGET=../bin/motion

all: $(TARGET)
clean:
	rm -f *.o $(TARGET)

$(TARGET): main.o
	$(CC) $(LFLAGS) -o $@ $^ -L../bin  -lUniMotion

main.o: main.c

