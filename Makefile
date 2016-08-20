CFLAGS = -O3 -Wall -Idep/murmur3

.PHONY: all clean

all: dep cass-wd
cass-wd:
	$(CC) $(CFLAGS) -o cass-wd dep/murmur3/murmur3.c src/cass-wd.c
dep:
	git clone https://github.com/PeterScott/murmur3.git dep/murmur3

clean:
	rm -f cass-wd
	rm -rf dep
