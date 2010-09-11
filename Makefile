unit-tests/test: $(wildcard src/*.cc) $(wildcard src/*.h) Makefile unit-tests/test.cc
	g++ -I include -g -Wall -Wnon-virtual-dtor -fno-rtti $(filter %.cc,$^) -o $@

clean:
	rm -f test
	rm -rf src/*~ include/*~ unit-tests/*~
	rm -f Makefile~
