

all: disk
	
core:
	cd ../../cee-core; qmake -r -spec macx-g++ CONFIG+=release
	cd ../../cee-core; make
	cd ../../cee-core; make clean

gui-app: core
	cd ../../app; qmake -r -spec macx-g++ CONFIG+=release DEFINES+=GUI_ONLY
	cd ../../app; make
	mkdir -p build
	cp -r ../../app/cee.app build
	cd ../../app; make distclean

cli-app: core
	cd ../../app; qmake -r -spec macx-g++ CONFIG+=release CONFIG-=app_bundle
	cd ../../app; make
	mkdir -p build
	cp ../../app/cee build
	cd ../../app; make distclean

disk: gui-app cli-app
	hdiutil create /tmp/tmp.dmg -ov -volname "cee" -fs HFS+ -srcfolder "build"
	hdiutil convert /tmp/tmp.dmg -format UDZO -o cee.dmg

parser:
	cd ../../cee-core; make -f MakefileParser

clean:
	-cd ../../cee-core; make distclean
	rm -rf build

distclean: clean
	rm cee.dmg

