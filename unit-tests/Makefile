# creates the recipe for running a unit test

# 1 = path to unit test
define unit-test-recipe
$1-test:
	@./run-test.sh $1
	@./valgrind-test.sh $1
	@echo

endef

# returns the test targets for a given directory

# 1 = directory name
define directory-tests
$(filter $1/%,$(test_targets))
endef

stripped_unit_tests := $(patsubst unit-tests/%,%,$(unit_tests))
test_targets := $(addsuffix -test,$(stripped_unit_tests))

.PHONY: run-tests $(test_targets)

run-tests: $(test_targets)

$(eval $(foreach unit_test,$(stripped_unit_tests),$(call unit-test-recipe,$(unit_test))))

parameter-name-tests/name-initialization-test: parameter-name-tests/invalid-name-test
parameter-name-tests/name-comparison-test: parameter-name-tests/name-initialization-test

# cmdline parser tests depend on parameter-name-tests passing
$(call directory-tests,cmdline-parser-tests): $(call directory-tests,parameter-name-tests)

# option tests depend on parameter-name-tests passing
$(call directory-tests,option-tests): $(call directory-tests,parameter-name-tests)
option-tests/option-set-arg-test: option-tests/option-initialization-test
option-tests/option-arg-invalid-test: cmdline-parser-tests/option-invalid-arg-test option-tests/option-initialization-test
option-tests/option-arg-valid-test: cmdline-parser-tests/option-valid-arg-test option-tests/option-initialization-test
option-tests/option-arg-list-test option-tests/option-arg-vector-test: option-tests/option-arg-valid-test

# numeric tests depend on option tests passing
$(call directory-tests,numeric-tests): $(call directory-tests,option-tests)

# custom parser tests depend on option tests
$(call directory-tests,custom-parser-tests): $(call directory-tests,option-tests)
