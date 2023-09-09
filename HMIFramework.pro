QT +=  core gui qml quick sensors
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS_WARN_ON += \
    -Wno-unused-function \
    -Wunused-parameter

SOURCES += \
        $$PWD/AnimationManager/AAnimation.cpp \
        $$PWD/CNgin.cpp \
        $$PWD/Utils/Logger/CLogger.cpp \
        $$PWD/Utils/Memory/LFUCache/CLFUCache.cpp \
        $$PWD/Utils/Memory/LRUCache/CLRUCache.cpp \
        $$PWD/View/ViewStates.cpp \
        $$PWD/ViewManager/AView.cpp \
        $$PWD/ViewManager/AViewManager.cpp \
        $$PWD/ViewManager/Notify/CNotify.cpp \
        $$PWD/ViewManager/Toast/CToast.cpp \
        $$PWD/ViewManager/Popup/CPopup.cpp \
        $$PWD/ViewManager/Popup/CPopupManager.cpp \
        $$PWD/ViewManager/Screen/CScreen.cpp \
        $$PWD/ViewManager/Screen/CScreenManager.cpp \
        $$PWD/ViewManager/Screen/CScreenTransitions.cpp \
        $$PWD/AnimationManager/ATransition.cpp \
        $$PWD/main.cpp \
        ViewManager/Notify/CNotifyManager.cpp \
        ViewManager/Toast/CToastManager.cpp

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
    $$PWD/Utils/Logger/CLogger.h \
    $$PWD/Utils/Logger/LoggerDefines.h \
    $$PWD/ViewManager/AView.h \
    $$PWD/ViewManager/AViewManager.h \
    $$PWD/AnimationManager/AAnimation.h \
    $$PWD/AnimationManager/ATransition.h \
    $$PWD/ViewManager/Notify/CNotify.h \
    $$PWD/ViewManager/Toast/CToast.h \
    $$PWD/ViewManager/Popup/CPopup.h \
    $$PWD/ViewManager/Popup/CPopupManager.h \
    $$PWD/ViewManager/Screen/CScreen.h \
    $$PWD/ViewManager/Screen/CScreenManager.h \
    $$PWD/ViewManager/Screen/CScreenTransitions.h \
    ViewManager/Notify/CNotifyManager.h \
    ViewManager/Toast/CToastManager.h

INCLUDEPATH += \
    $$PWD/View \
    $$PWD/QmlTypes \
    $$PWD/ViewManager \
    $$PWD/AnimationManager \
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
