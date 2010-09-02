test: src/test.cc src/arg_option_base.cc src/option_base.cc src/cmdline_parser.cc $(wildcard src/*.h)
	g++ -g $(filter %.cc,$^) -o $@