CXXFLAGS := -Wall -Wnon-virtual-dtor -g
CPPFLAGS := -I include
LDFLAGS := -L.


unit_tests := unit-tests/test \
              unit-tests/numeric-tests/int-overflow \
              unit-tests/numeric-tests/int-underflow \
              unit-tests/numeric-tests/int-invalid

libs := libgetopt.a libunit-test.a

unit-tests/test_SRCS := unit-tests/test.cc
unit-tests/test_LIBS := getopt unit-test
unit-tests/test_CPPFLAGS := $(CPPFLAGS) -I libunit-test

unit-tests/numeric-tests/int-overflow_SRCS := unit-tests/numeric-tests/int_overflow.cc
unit-tests/numeric-tests/int-overflow_LIBS := getopt unit-test
unit-tests/numeric-tests/int-overflow_CPPFLAGS := $(CPPFLAGS) -I libunit-test

unit-tests/numeric-tests/int-underflow_SRCS := unit-tests/numeric-tests/int_underflow.cc
unit-tests/numeric-tests/int-underflow_LIBS := getopt unit-test
unit-tests/numeric-tests/int-underflow_CPPFLAGS := $(CPPFLAGS) -I libunit-test

unit-tests/numeric-tests/int-invalid_SRCS := unit-tests/numeric-tests/int_invalid.cc
unit-tests/numeric-tests/int-invalid_LIBS := getopt unit-test
unit-tests/numeric-tests/int-invalid_CPPFLAGS := $(CPPFLAGS) -I libunit-test

libunit-test_SRCS := $(wildcard libunit-test/*.cc)
libgetopt_SRCS := $(wildcard src/*.cc)


# generates the depends file paths given a list of paths

# 1 = list of file paths
define create_depends
$(foreach path,$(1),$(dir $(path)).$(basename $(notdir $(path))).d)
endef

srcs := $(libgetopt_SRCS) $(libunit-test_SRCS) $(foreach test,$(unit_tests),$($(test)_SRCS))

# get all the depends files that exist.  Whatever ones don't exist
# will be created when their object files are created
depends := $(wildcard $(call create_depends,$(srcs)))


# generates the rule for a given target

# 1 = target
define create_target

ifneq ($($(1)_CPPFLAGS),)
$(1): CPPFLAGS := $($(1)_CPPFLAGS)
endif

$(1): Makefile $($(1)_SRCS:.cc=.o) $($(1)_LIBS:%=lib%.a)
	$(CXX) $(LDFLAGS) $$(filter %.o,$$^) $($(1)_LIBS:%=lib%.a) -o $$@
endef


all: libgetopt.a libunit-test.a unit-tests


%.o: %.cc
	@$(CXX) $(CPPFLAGS) -M -E -MM -MD -MT $@ $< -o $(call create_depends,$@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


# make the object files depend on the Makefile
$(foreach obj,$(srcs:.cc=.o),$(eval $(obj): Makefile))

# create the rules for the unit tests
$(foreach test,$(unit_tests),$(eval $(call create_target,$(test))))

# only include the depends files if the target is not a clean target
ifeq ($(filter clean%,$(MAKECMDGOALS)),)
include $(depends)
endif


libgetopt.a: Makefile $(libgetopt_SRCS:.cc=.o)
	$(AR) rcs $@ $(filter %.o,$^)

libunit-test.a: Makefile $(libunit-test_SRCS:.cc=.o) libgetopt.a
	$(AR) rcs $@ $(filter %.o,$^)

unit-tests: $(unit_tests)

clean:
	rm -f libgetopt.a $(unit_tests) libunit-test.a
	rm -f $(srcs:.cc=.o) $(call create_depends,$(srcs))
	rm -f Makefile~ src/*~ include/*~ unit-tests/*~ libunit-test/*~ *~
