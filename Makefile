
CC=gcc
CFLAGS=-g -Wall -std=c99 -lgsl -lgslcblas -lm -Isupport

all: simulations_app

simulations_app:
	$(CC) $(CFLAGS) support/*.c -o runSimulations
