CC=clang

BUILD_FLAGS=-O3 -Wall
LINK_FLAGS=-Iinclude -Llib -lvector

.PHONY: all lib test clean

all: lib

lib:
	$(CC) $(BUILD_FLAGS) -c src/vector.c -Iinclude -o build/vector.o
	ar rcs lib/libvector.a build/vector.o

test:
	$(CC) test/test.c $(LINK_FLAGS) -o test/test

clean:
	rm -f build/*.o test/test lib/libvector.a
