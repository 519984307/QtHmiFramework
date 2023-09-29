@echo off 

SET BUILD=.\build\
SET QTDIR=D:\Programs\Qt\6.5.1\
SET mingw64=mingw_64\bin\

SET kit=%mingw64%

SET TOOLCHAINDIR=%QTDIR%%kit%
SET QMAKE=%TOOLCHAINDIR%qmake.exe
SET QTDEPLOY=%TOOLCHAINDIR%windeployqt.exe
SET MAKE=D:/Programs/Qt/Tools/mingw1120_64/bin/mingw32-make.exe 
SET PROFILE=..\HMIFramework.pro
SET SPEC=win32-g++
SET MODE=debug
SET EXTRA=%MODE% qml_debug
SET APP=\HMIFramework.exe
SET BINDIR=%BUILD%%MODE%
SET APPPATH=%BINDIR%%APP%

echo Select a mode. (build/deploy/run)
set /p flag=

IF /i "%flag%" == "clean"  goto CLEAN_APP
IF /i "%flag%" == "build"  goto BUILD_APP
IF /i "%flag%" == "deploy"  goto DEPLOY_APP
IF /i "%flag%" == "run" goto RUN_APP

:CLEAN_APP
rm -rf %BUILD%
goto EXIT

:BUILD_APP
if NOT exist %BUILD% mkdir %BUILD%
cd %BUILD%
%QMAKE% %PROFILE% -spec %SPEC% "CONFIG+=%EXTRA%" && %MAKE% -j5
goto EXIT


:DEPLOY_APP
cd %BINDIR%
%QTDEPLOY% .
goto EXIT

:RUN_APP
echo %APPPATH%
goto EXIT


:EXIT
pause