CC = gcc
ODIR = out
MATH_TARGET = math
THRESHOLD_TARGET = threshold
THRESHOLDMAIN_TARGET = thresholdmain
CFLAGS = -ansi -pedantic -Wall -Wextra -O0

$(THRESHOLDMAIN_TARGET).out: $(THRESHOLDMAIN_TARGET).c $(ODIR)/$(MATH_TARGET).o $(ODIR)/$(THRESHOLD_TARGET).o
	$(CC) $^ $(CFLAGS) -o $@

$(ODIR)/%.o: %.c
	$(CC) -c $^ $(CFLAGS) -o $@
