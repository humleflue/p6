CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wextra -O0
TARGET = main
SVC_TARGET = svc
TRANSFORM_TARGET = transform
KERNELS_TARGET = kernels
MATH_TARGET = math
PREDICTOR_TARGET = predictor
OBJ = $(TARGET).c $(ODIR)/$(SVC_TARGET).o $(ODIR)/$(TRANSFORM_TARGET).o $(ODIR)/$(KERNELS_TARGET).o $(ODIR)/$(MATH_TARGET).o $(ODIR)/$(PREDICTOR_TARGET).o 

ODIR = out
TDIR = test
CUTEST_DIR = $(TDIR)/CuTest

CUTEST = $(CUTEST_DIR)/CuTest
ALL_TESTS = $(TDIR)/AllTests
TESTS_TARGET = AllTests
MATH_TESTS = $(TDIR)/MathTests.c $(ODIR)/$(MATH_TARGET).o
TRANSFORM_TESTS = $(TDIR)/TransformTests.c $(ODIR)/$(TRANSFORM_TARGET).o
PREDICTOR_TESTS = $(TDIR)/PredictorTests.c $(ODIR)/$(PREDICTOR_TARGET).o $(ODIR)/$(KERNELS_TARGET).o
TESTS = $(CC) $(ALL_TESTS).c $(CUTEST).c $(TRANSFORM_TESTS) $(MATH_TESTS) $(PREDICTOR_TESTS)

# Target
$(TARGET).exe: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

$(TARGET).out: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

$(ODIR)/%.o: %.c
	$(CC) -c $^ $(CFLAGS) -o $@


testu:
	$(TESTS) -o $(TESTS_TARGET).out

testw:
	$(TESTS) -o $(TESTS_TARGET).exe

clean:
	$(RM) $(ODIR)/*.o *.exe *.out

.PHONY: clean testw testu
