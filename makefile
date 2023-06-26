CC=gcc
dp=route-records.h
CFLAGS=-Wall

flight.exe : main.o route-records.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o : %.c $(dp)
	$(CC) -c -o $@ $<

clean :
	rm *.o *.exe