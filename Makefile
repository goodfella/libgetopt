# directory where the cmake build system is installed
CMAKE_BUILD_DIR ?= build-dir

# cmake generates a makefile so use that as the target
CMAKE_TARGET := $(CMAKE_BUILD_DIR)/Makefile


# generates the command that's used in a cmake-* target

# 1 = the cmake target to invoke
define cmake_build
@$(MAKE) --no-print-directory -C $(CMAKE_BUILD_DIR) $(1)
endef

.PHONY: all clean-all clean-emacs

all: cmake-all

$(CMAKE_TARGET):
	mkdir -p $(@D)
	cd $(@D); cmake ..

cmake-test: cmake-all
	$(call cmake_build,test)

cmake-getopt: $(CMAKE_TARGET)
	$(call cmake_build,getopt)

cmake-unit-test: $(CMAKE_TARGET)
	$(call cmake_build,unit-test)

cmake-clean:
	$(call cmake_build,clean)

cmake-all: $(CMAKE_TARGET)
	$(call cmake_build,all)

clean-emacs:
	find -name '*~' -exec rm \{\} \;

clean-all:
	test -z "$(CMAKE_BUILD_DIR)" || rm -rf $(CMAKE_BUILD_DIR)
