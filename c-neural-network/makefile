CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -lm -O0
TARGET = neuralNetwork
MATRIXMATH_TARGET = matrixmath
MATRIXLIB_TARGET = matrixlib
MATRIXMEMLIB_TARGET = matrixmemlib
OBJ = $(TARGET).c $(ODIR)/$(MATRIXMEMLIB_TARGET).o $(ODIR)/$(MATRIXMATH_TARGET).o $(ODIR)/$(MATRIXLIB_TARGET).o

ODIR = out

$(TARGET).out: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

$(TARGET).exe: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

$(ODIR)/%.o: %.c
	$(CC) -c $^ $(CFLAGS) -o $@

.PHONY: clean

clean:
	$(RM) $(ODIR)/*.o *.exe *.out