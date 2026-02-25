CC = gcc
CFLAGS = -Wall

all: SJF RR

SJF: SJF.c
	$(CC) $(CFLAGS) SJF.c -o SJF

RR: RR.c
	$(CC) $(CFLAGS) RR.c -o RR

clean:
	rm -f SJF RR
