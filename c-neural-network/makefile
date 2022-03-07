CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -lm -O0
TARGET = neuralNetwork
MATRIXMATH_TARGET = matrixmath
MATRIXLIB_TARGET = matrixlib
MATRIXMEMLIB_TARGET = matrixmemlib

$(TARGET).out: $(TARGET).c $(MATRIXMEMLIB_TARGET).o $(MATRIXMATH_TARGET).o $(MATRIXLIB_TARGET).o
	$(CC) $^ $(CFLAGS) -o $@

$(TARGET).exe: $(TARGET).c $(MATRIXMEMLIB_TARGET).o $(MATRIXMATH_TARGET).o $(MATRIXLIB_TARGET).o
	$(CC) $^ $(CFLAGS) -o $@

%.o: %.c
	$(CC) -c $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o *.exe *.out