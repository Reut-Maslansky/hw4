.PHONY: all clean
all: frequency

frequency: frequency.c
	gcc -Wall -o frequency frequency.c

clean:
	rm -f *.so *.a *.o frequency
