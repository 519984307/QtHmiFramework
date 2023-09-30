@echo off 

SET BUILD=.\build\
SET QTDIR=D:\Programs\Qt\6.5.1\
SET mingw64=mingw_64\bin\

SET kit=%mingw64%

SET PATH_TO_QT=%QTDIR%%kit%
SET QMAKE=%PATH_TO_QT%qmake.exe
SET MAKE=D:\Programs\Qt\Tools\mingw1120_64\bin\mingw32-make.exe 
SET PROFILE=D:\Projects\O\QT_Projects\HMIFramework\HMIFramework.pro
SET SPEC=win32-g++
SET MODE=debug\
SET EXTRA=debug qml_debug shared
SET APP=HMIFramework.exe
SET BINDIR=%BUILD%%MODE%
SET PATH_TO_EXECUTABLE=%BINDIR%%APP%

echo Select a mode. ([1]run qmake/[2]clean/[3]build/[4]deploy/[5]run)
set /p flag=

IF /i "%flag%" == "run qmake"   goto RUN_QMAKE
IF /i "%flag%" == "clean"       goto CLEAN_APP
IF /i "%flag%" == "build"       goto BUILD_APP
IF /i "%flag%" == "rebuild"     goto REBUILD_APP
IF /i "%flag%" == "deploy"      goto DEPLOY_APP
IF /i "%flag%" == "run"         goto RUN_APP

goto EXIT


:RUN_QMAKE
cd %BUILD%
%QMAKE% ..
cd ..
goto EXIT

:CLEAN_APP
cd %BUILD%
%MAKE% clean -j16
cd ..
goto EXIT

:BUILD_APP
if NOT exist %BUILD% mkdir %BUILD%
cd %BUILD%
%QMAKE% %PROFILE% -spec %SPEC% "CONFIG+=%EXTRA%" && %MAKE% -j16
cd ../
goto EXIT

:REBUILD_APP
@REM cd %BUILD%
@REM %QMAKE% %PROFILE% -spec %SPEC% "CONFIG+=%EXTRA%" && %MAKE% -j16
@REM cd ../
goto EXIT


:DEPLOY_APP
if NOT exist "%PATH_TO_EXECUTABLE%" goto EXIT
%PATH_TO_QT%\windeployqt.exe "%PATH_TO_EXECUTABLE%"
goto EXIT

:RUN_APP
if NOT exist "%PATH_TO_EXECUTABLE%" goto EXIT
echo "START %PATH_TO_EXECUTABLE%"
start %PATH_TO_EXECUTABLE%
goto EXIT


:EXIT
pause