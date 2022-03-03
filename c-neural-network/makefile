CC = gcc
CFLAGS = -pedantic -Wall -Wextra -lm -O0
TARGET = neuralNetwork
MATRIXMEMLIB_TARGET = matrixmemlib

$(TARGET).out: $(TARGET).c $(MATRIXMEMLIB_TARGET).o
	$(CC) $^ $(CFLAGS) -o $@

$(TARGET).exe: $(TARGET).c $(MATRIXMEMLIB_TARGET).o
	$(CC) $^ $(CFLAGS) -o $@

$(MATRIXMEMLIB_TARGET).o: $(MATRIXMEMLIB_TARGET).c
	$(CC) -c $^ $(CFLAGS) -o $@

clean:
	$(RM) *.o *.exe *.out