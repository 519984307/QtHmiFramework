QT +=  core gui qml quick sensors
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS_WARN_ON += \
    -Wno-unused-function \
    -Wunused-parameter

SOURCES += \
        CNgin.cpp \
        Utils/Logger/CLogger.cpp \
        Utils/Memory/LFUCache/CLFUCache.cpp \
        Utils/Memory/LRUCache/CLRUCache.cpp \
        View/ViewStates.cpp \
        ViewManager/CView.cpp \
        ViewManager/CViewManager.cpp \
        ViewManager/Notify/CNotify.cpp \
        ViewManager/Notify/CNotifyManager.cpp \
        ViewManager/Popup/CPopup.cpp \
        ViewManager/Popup/CPopupManager.cpp \
        ViewManager/Screen/CScreen.cpp \
        ViewManager/Screen/CScreenManager.cpp \
        ViewManager/Toast/CToast.cpp \
        ViewManager/Toast/CToastManager.cpp \
        main.cpp

HEADERS += \
    CNgin.h \
    Common/Common.h \
    Common/CommonDefine.h \
    Common/CommonEnums.h \
    Common/CommonStructs.h \
    Utils/Utils.h \
    Utils/Memory/LFUCache/CLFUCache.h \
    Utils/Memory/LRUCache/CLRUCache.h \
    View/CViewEnums.h \
    View/ViewStates.h \
    View/ViewData.h \
    View/ViewDefines.h \
    Utils/Logger/CLogger.h \
    Utils/Logger/LoggerDefines.h \
    ViewManager/CView.h \
    ViewManager/CViewManager.h \
    ViewManager/Notify/CNotify.h \
    ViewManager/Notify/CNotifyManager.h \
    ViewManager/Popup/CPopup.h \
    ViewManager/Popup/CPopupManager.h \
    ViewManager/Screen/CScreen.h \
    ViewManager/Screen/CScreenManager.h \
    ViewManager/Toast/CToast.h \
    ViewManager/Toast/CToastManager.h

INCLUDEPATH += \
    View \
    QmlTypes \
    ViewManager \
    Common \
    Utils

RESOURCES += \
    Resources/QML/qml_resources.qrc \
    Resources/Images/image_resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml
