test: $(wildcard src/*.cc) $(wildcard src/*.h)
	g++ -g -Wall $(filter %.cc,$^) -o $@

clean:
	rm -f test
	rm -rf src/*~
	rm -f Makefile~
