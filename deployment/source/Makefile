VERSION := $(shell grep VERSION_STRING ../../cee-core/version.h | cut -d'"' -f 2)

all: source

source:
	mkdir -p build
	cp -r ../../cee-core build
	cp -r ../../app	build
	-cd build/cee-core; make distclean; rm *.user
	-cd build/app; make distclean; rm *.user
	cp scripts/Makefile build
	tar -pczf cee-$(VERSION)-src.tar.gz build

clean:
	rm -rf build

distclean: clean
	rm cee*.tar.gz
