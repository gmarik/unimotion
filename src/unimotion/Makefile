SDK:=$(shell ls /Developer/SDKs | sort -r | head -n 1)
CFLAGS=-Wall -Os -g -isysroot /Developer/SDKs/$(SDK) -arch i386 -fconstant-cfstrings
LFLAGS=-Wl,-syslibroot,/Developer/SDKs/$(SDK) -arch i386 -framework IOKit -framework CoreFoundation
TARGET=libUniMotion.dylib

all: ../Frameworks/$(TARGET) ../bin/$(TARGET)
clean:
	rm -f *.o ../Frameworks/$(TARGET) ../bin/$(TARGET)

../Frameworks/$(TARGET): unimotion.o 
	mkdir -p ../Frameworks
	$(CC) $(LFLAGS) -headerpad_max_install_names -dynamiclib -install_name @executable_path/$@ -o $@ $^

../bin/$(TARGET): unimotion.o
	mkdir -p ../bin
	$(CC) $(LFLAGS) -headerpad_max_install_names -dynamiclib -install_name @executable_path/$(TARGET) -o $@ $^

unimotion.o: unimotion.c unimotion.h

