QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        CNgin.cpp \
        ViewManager/CPopupObject.cpp \
        ViewManager/CViewManager.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    CNgin.h \
    Common/Common.h \
    Common/CommonDefine.h \
    Common/CommonEnums.h \
    Common/CommonStructs.h \
    Utils/Utils.h \
    View/CViewEnums.h \
    View/States/POPUP_X_STATE.h \
    View/States/POPUP_Y_STATE.h \
    View/States/POPUP_Z_STATE.h \
    View/States/SCREEN_A_STATE.h \
    View/States/SCREEN_B_STATE.h \
    View/States/SCREEN_C_STATE.h \
    View/States/ViewStates.h \
    View/ViewData.h \
    View/ViewDefines.h \
    ViewManager/CPopupObject.h \
    ViewManager/CViewManager.h

INCLUDEPATH += \
    $$PWD/ViewManager \
    $$PWD/View/States \
    $$PWD/View \
    $$PWD/Common \
    $$PWD/Utils \
    $$PWD/
