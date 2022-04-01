
CC=gcc
CFLAGS=-g -Wall -std=c99 -lgsl -lgslcblas -lm

all: simulations_app

simulations_app: support/samlib.o support/stats.o support/side.o sim.o
	$(CC) $(CFLAGS) sim.o -o runSimulation
	$(MAKE) clean

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm *.o