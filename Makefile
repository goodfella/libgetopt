CXXFLAGS := -Wall -Wnon-virtual-dtor -g
CPPFLAGS := -I include
LDFLAGS := -L .

unit_tests := unit-tests/test

all: libgetopt.a unit-tests

libgetopt.a: Makefile $(patsubst %.cc,%.o,$(wildcard src/*.cc)) \
             $(wildcard src/*.h)
	$(AR) rcs $@ $(filter %.o,$^)

unit-tests: $(unit_tests)

unit-tests/test:  Makefile $(patsubst %.cc,%.o,unit-tests/test.cc) libgetopt.a
	$(CXX) $(LDFLAGS) $(filter %.o,$^) -lgetopt -o $@

clean:
	rm -f libgetopt.a $(unit_tests)
	rm -rf src/*.o unit-tests/*.o
	rm -f Makefile~ src/*~ include/*~ unit-tests/*~ *~
