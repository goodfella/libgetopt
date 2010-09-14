CXXFLAGS := -Wall -Wnon-virtual-dtor -g
CPPFLAGS := -I include
LDFLAGS := -L.


unit_tests := unit-tests/test
libs := libgetopt.a

unit-tests/test_SRCS := unit-tests/test.cc
unit-tests/test_LIBS := getopt

libgetopt_SRCS := $(wildcard src/*.cc)

srcs := $(libgetopt_SRCS) $(foreach test,$(unit_tests),$($(test)_SRCS))

# 1 = target
define create_target
$(1): Makefile $($(1)_SRCS:.cc=.o) $($(1)_LIBS:%=lib%.a)
	$(CXX) $(LDFLAGS) $$(filter %.o,$$^) $($(1)_LIBS:%=lib%.a) -o $$@
endef


# depend files require a source file
%.d: %.cc
	@$(CXX) $(CPPFLAGS) -M -E -MM -MD -MT $(<:.cc=.o) -MT $(<:.cc=.d) $(<) -o $(<:.cc=.d)

all: libgetopt.a unit-tests

$(foreach test,$(unit_tests),$(eval $(call create_target,$(test))))

# only include the depends file if the target is not clean
ifeq ($(filter clean%,$(MAKECMDGOALS)),)
-include $(srcs:.cc=.d)
endif


libgetopt.a: Makefile $(libgetopt_SRCS:.cc=.o)
	$(AR) rcs $@ $(filter %.o,$^)

unit-tests: $(unit_tests)

clean:
	rm -f libgetopt.a $(unit_tests)
	rm -rf src/*.o unit-tests/*.o $(srcs:.cc=.d)
	rm -f Makefile~ src/*~ include/*~ unit-tests/*~ *~
