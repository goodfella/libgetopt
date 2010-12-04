CXXFLAGS := -Wall -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -fno-rtti -g
CPPFLAGS := -I include
LDFLAGS := -L.
UNIT_TEST_LIBS := unit-test getopt


# generates the depends file paths given a list of paths

# 1 = list of file paths
define create_depends
$(foreach path,$(1),$(dir $(path)).$(basename $(notdir $(path))).d)
endef


# generates the rule for a given target

# 1 = target
# 2 = sources
# 3 = libs
define create_target

$(1): Makefile $(2:.cc=.o) $(3:%=lib%.a)
	$(CXX) $(LDFLAGS) $$(filter %.o,$$^) $$(LIBS:%=lib%.a) -o $$@
endef


# generates the rule for a unit test given its target name and source

# 1 = unit test target name
# 2 = unit test source paths
define create_unit_test_rule
$(1): SRCS := $(2)
$(1): LIBS := $(UNIT_TEST_LIBS)
$(1): CPPFLAGS := $(CPPFLAGS) -I libunit-test

$(call create_target,$(1),$(2),$(UNIT_TEST_LIBS))

endef


# converts a source file name to a binary name

# 1 = source file path or name
define create_bin_name
$(basename $(subst _,-,$(1)))
endef


# Get all unit test sources.
unit_test_srcs := $(wildcard unit-tests/*/*.cc)
unit_tests := $(foreach src,$(unit_test_srcs),$(call create_bin_name,$(src)))

# Create rules for all unit tests
$(eval $(foreach src,$(unit_test_srcs),$(call create_unit_test_rule,$(call create_bin_name,$(src)),$(src))))

libs := libgetopt.a libunit-test.a

libunit-test_SRCS := $(wildcard libunit-test/*.cc)
libgetopt_SRCS := $(wildcard src/*.cc)


srcs := $(libgetopt_SRCS) $(libunit-test_SRCS) $(unit_test_srcs)

# get all the depends files that exist.  Whatever ones don't exist
# will be created when their object files are created
depends := $(wildcard $(call create_depends,$(srcs)))

# only include the depends files if the target is not a clean target
ifeq ($(filter clean%,$(MAKECMDGOALS)),)
include $(depends)
endif


# custom object file implicit rule that generates its dependency file
%.o: %.cc
	@$(CXX) $(CPPFLAGS) -M -E -MM -MD -MT $@ $< -o $(call create_depends,$@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@


# make the object files depend on the Makefile
$(foreach obj,$(srcs:.cc=.o),$(eval $(obj): Makefile))


libgetopt.a: Makefile $(libgetopt_SRCS:.cc=.o)
	$(AR) rcs $@ $(filter %.o,$^)

all: libgetopt.a libunit-test.a unit-tests


libunit-test.a: Makefile $(libunit-test_SRCS:.cc=.o) libgetopt.a
	$(AR) rcs $@ $(filter %.o,$^)

unit-tests: $(unit_tests)

clean:
	rm -f libgetopt.a $(unit_tests) libunit-test.a
	rm -f $(srcs:.cc=.o) $(call create_depends,$(srcs))
	rm -f Makefile~ src/*~ include/*~ unit-tests/*~ libunit-test/*~ *~
