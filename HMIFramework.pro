QT +=  core gui qml quick
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS_WARN_ON += \
    -Wno-unused-function \
    -Wunused-parameter

SOURCES += \
        CNgin.cpp \
        Common/CallBackManager/CCallbackManager.cpp \
        Common/ObserverManager/CObserverManager.cpp \
        Utils/Logger/CLogger.cpp \
        Utils/Memory/LFUCache/CLFUCache.cpp \
        Utils/Memory/LRUCache/CLRUCache.cpp \
        View/ViewStates.cpp \
        ViewManager/CComponent.cpp \
        ViewManager/CViewManager.cpp \
        main.cpp

HEADERS += \
    $$PWD/CNgin.h \
    $$PWD/Common/Common.h \
    $$PWD/Common/CommonDefine.h \
    $$PWD/Common/CommonEnums.h \
    $$PWD/Common/CommonStructs.h \
    $$PWD/QmlTypes/QmlTypes.h \
    $$PWD/Utils/Utils.h \
    $$PWD/Utils/Memory/LFUCache/CLFUCache.h \
    $$PWD/Utils/Memory/LRUCache/CLRUCache.h \
    $$PWD/View/CViewEnums.h \
    $$PWD/View/ViewStates.h \
    $$PWD/View/ViewData.h \
    $$PWD/View/ViewDefines.h \
    $$PWD/ViewManager/CViewManager.h \
    Common/CallBackManager/CCallbackManager.h \
    Common/ObserverManager/CObserverManager.h \
    Utils/Logger/CLogger.h \
    Utils/Logger/LoggerDefines.h \
    ViewManager/CComponent.h \
    ViewManager/ViewManagerDefines.h

INCLUDEPATH += \
    $$PWD/QmlTypes \
    $$PWD/ViewManager \
    $$PWD/View/States \
    $$PWD/View \
    $$PWD/Common \
    $$PWD/Utils \
    $$PWD

RESOURCES += \
    $$PWD/Resources/QML/qml_resources.qrc \
    $$PWD/Resources/Images/image_resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
