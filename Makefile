#
# Root Makefile to build the library, tests and benchmarks
#

.PHONY: all release debug clean recompile

all: release

release:
	$(MAKE) -C lib BUILD_TYPE=RELEASE
	$(MAKE) -C test BUILD_TYPE=RELEASE
	$(MAKE) -C benchmark BUILD_TYPE=RELEASE

debug:
	$(MAKE) -C lib BUILD_TYPE=DEBUG
	$(MAKE) -C test BUILD_TYPE=DEBUG
	$(MAKE) -C benchmark BUILD_TYPE=DEBUG

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C test clean
	$(MAKE) -C benchmark clean

recompile: clean all

