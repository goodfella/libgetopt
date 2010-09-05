test: $(wildcard src/*.cc) $(wildcard src/*.h)
	g++ -g $(filter %.cc,$^) -o $@

clean:
	rm -f test
	rm -rf src/*~
	rm -f Makefile~
