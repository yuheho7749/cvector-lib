VERSION = 1
SUBVERSION = 0
EXTRA = rc2

CC = gcc
# CC = clang		 # Typically has a better optimizer than gcc

BUILD_FLAGS = -Wall -O2
# BUILD_FLAGS = -Wall -O2 -DXVECTOR_LIB

# Build with no "guardrails" (not recommended for COLD_GUARDRAILS)
# BUILD_FLAGS = -Wall -O2 -DHOT_GUARDRAILS_OFF -DCOLD_GUARDRAILS_OFF

# xvector (not ready yet): Consider building with SIMD vectorization (SSE, AVX, etc)
# BUILD_FLAGS = -Wall -O2 -mavx2
# BUILD_FLAGS = -Wall -O2 -march=native
# BUILD_FLAGS = -Wall -O2 -mavx2 -DXVECTOR_LIB

LINK_FLAGS = -Iinclude -Llib -lvector

.PHONY: all lib test spotcheck clean

all: lib

test: spotcheck

spotcheck: lib
	$(CC) test/spotcheck.c $(LINK_FLAGS) -o test/spotcheck

lib:
	$(CC) $(BUILD_FLAGS) -c src/vector.c -Iinclude -o build/vector.o
	ar rcs lib/libvector.a build/vector.o

clean:
	rm -f build/*.o test/spotcheck lib/libvector.a
