# a very simple install script
#
# needs: qt-core, qt-gui, gnu-readline
#

all: app/cee

app/cee:
	cd cee-core; qmake CONF+=release
	cd cee-core; make
	cd app; qmake CONF+=release
	cd app; make

clean:
	cd cee-core; make distclean
	cd app; make distclean

install: app/cee
	cp app/cee /usr/bin