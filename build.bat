@echo off 

SET BUILD=.\build
SET QtDir=D:\Programs\Qt\6.5.1\
SET mingw64=mingw_64\bin

SET kit=%mingw64%

SET ToolChainDir=%QtDir%%kit%
SET QMAKE=%ToolChainDir%qmake.exe
SET MAKE=D:/Programs/Qt/Tools/mingw1120_64/bin/mingw32-make.exe 
SET PROFILE=.\XFramework.pro
SET SPEC=win32-g++
SET CONFIG=debug qml_debug

if NOT exist %BUILD% (
  mkdir %BUILD%
)

%QMAKE% %PROFILE% -spec %SPEC% "CONFIG+=%CONFIG%" && %MAKE% qmake_all
