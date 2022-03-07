CC = gcc
CFLAGS = -pedantic -Wall -Wextra -lm -O0
TARGET = neuralNetwork
MATRIXMATH_TARGET = matrixmath
MATRIXLIB_TARGET = matrixlib
MATRIXMEMLIB_TARGET = matrixmemlib

$(TARGET).out: $(TARGET).c $(MATRIXMEMLIB_TARGET).o $(MATRIXMATH_TARGET).o $(MATRIXLIB_TARGET).o
	$(CC) $^ $(CFLAGS) -o $@

$(TARGET).exe: $(TARGET).c $(MATRIXMEMLIB_TARGET).o $(MATRIXMATH_TARGET).o $(MATRIXLIB_TARGET).o
	$(CC) $^ $(CFLAGS) -o $@

$(MATRIXMEMLIB_TARGET).o: $(MATRIXMEMLIB_TARGET).c
	$(CC) -c $^ $(CFLAGS) -o $@

$(MATRIXMATH_TARGET).o: $(MATRIXMATH_TARGET).c
	$(CC) -c $^ $(CFLAGS) -o $@

$(MATRIXLIB_TARGET).o: $(MATRIXLIB_TARGET).c
	$(CC) -c $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o *.exe *.out