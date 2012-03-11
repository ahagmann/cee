rm -rf build
mkdir build
cp C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtGui4.dll build
cp C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtCore4.dll build
cp C:\MinGW\bin\libstdc++-6.dll build
cp C:\MinGW\bin\libgcc_s_dw2-1.dll build
cp C:\MinGW\bin\mingwm10.dll build
cd ..\..\cee-core
qmake CONFIG+=release
make
cp release\libcee-core.a .
cd ..\app
qmake CONFIG+=release
make
cp release\cee.exe ..\deployment\windows\build
make distclean
cd ..\cee-core
make distclean
cd ..\deployment\windows
