var BUILD=".\\0_build\\"
var QT_DIR="D:\\Programs\\Qt\\6.5.1\\"
var KIT="mingw_64\\bin\\"
var PATH_TO_QT=`${QT_DIR}${KIT}`
var QMAKE=`${PATH_TO_QT}qmake.exe`
var MAKE="D:\\Programs\\Qt\\Tools\\mingw1120_64\\bin\\mingw32-make.exe"
var PROFILE="D:\\Projects\\O\\QT_Projects\\HMIFramework\\HMIFramework.pro"
var SPEC="win32-g++"
var BUILD_MODE="debug\\"
var EXTRA="debug qml_debug console"
var APP="HMIFramework.exe"
var BIN_DIR=`${BUILD}${BUILD_MODE}`
var PATH_TO_EXECUTABLE=`${BIN_DIR}${APP}`

module.exports = {
    BUILD,
    QT_DIR,
    KIT,
    PATH_TO_QT,
    QMAKE,
    MAKE,
    PROFILE,
    SPEC,
    BUILD_MODE,
    EXTRA,
    APP,
    BIN_DIR,
    PATH_TO_EXECUTABLE
}

