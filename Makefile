CC = gcc
CFLAGS = -g
CFILES = indexer.c format.c inverted-list.c output.c main.c
HFILES = indexer.h format.h inverted-list.h output.h



main:
	$(CC) $(CFLAGS) -o index $(CFILES) 

archive: main
	ar -r libsl.a $(HFILES)

clean:
	rm -rf *.o
