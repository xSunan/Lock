CC=gcc
CFLAGS=-g

all : libspin.so libcounter.so liblist.so libhash.so

spin.o : spin.c
	$(CC) $(CFLAGS) -c -fpic spin.c

libspin.so : spin.o
	$(CC) $(CFLAGS) -shared -o $@ $<

counter.o : counter.c
	$(CC) $(CFLAGS) -c -fpic counter.c

libcounter.so : counter.o
	$(CC) $(CFLAGS) -shared -o $@ $<

list.o : list.c
	$(CC) $(CFLAGS) -c -fpic list.c

liblist.so : list.o
	$(CC) $(CFLAGS) -shared -o $@ $<

hash.o : hash.c
	$(CC) $(CFLAGS) -c -fpic hash.c

libhash.so : hash.o
	$(CC) $(CFLAGS) -shared -o $@ $<

#test : test.o libmem.so
#	$(CC) $(CFLAGS) $< -o $@ -lmem -L.


clean :
	rm -rf *.o test *.so
