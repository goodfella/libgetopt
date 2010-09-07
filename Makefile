test: $(wildcard src/*.cc) $(wildcard src/*.h) Makefile
	g++ -g -Wall -Wnon-virtual-dtor -fno-rtti $(filter %.cc,$^) -o $@

clean:
	rm -f test
	rm -rf src/*~
	rm -f Makefile~
