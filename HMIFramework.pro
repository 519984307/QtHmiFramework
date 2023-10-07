QT +=  core gui qml quick sensors multimedia
CONFIG += c++11 qml_debug console

include(Application/Application.pri)
include(HMICommon/HMICommon.pri)
include(HMIEngine/HMIEngine.pri)
include(IPCEngine/IPCEngine.pri)


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS_WARN_ON += \
    -Wno-unused-function \
    -Wunused-parameter

INCLUDEPATH += \
    $$PWD/Application \
    $$PWD/HMICommon \
    $$PWD/HMIEngine \
    $$PWD/IPCEngine

  
HEADERS += \
    config.h
      
SOURCES += \
    main.cpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

