CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -lm -O0
TARGET = svc
TRANSFORM_TARGET = transform
OBJ = $(TARGET).c $(ODIR)/$(TRANSFORM_TARGET).o

ODIR = out
TDIR = test
CUTEST_DIR = $(TDIR)/CuTest

CUTEST = $(CUTEST_DIR)/CuTest
ALL_TESTS = $(TDIR)/AllTests
TESTS_TARGET = AllTests

# Target
$(TARGET).out: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

$(TARGET).exe: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

$(ODIR)/%.o: %.c
	$(CC) -c $^ $(CFLAGS) -o $@

test:
	$(CC) $(ALL_TESTS).c $(CUTEST).c $(TDIR)/TransformTests.c $(ODIR)/$(TRANSFORM_TARGET).o -o $(TESTS_TARGET).out

clean:
	$(RM) $(ODIR)/*.o *.exe *.out

.PHONY: clean test
