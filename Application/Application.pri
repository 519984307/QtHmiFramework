HEADERS += \
    $$PWD/Controllers/CController.h \
    $$PWD/Models/CModels.h \
    $$PWD/ViewData/CViewEnums.h \
    $$PWD/ViewData/ViewData.h \
    $$PWD/ViewData/ViewDefines.h \
    $$PWD/ViewData/ViewStates.h

SOURCES += \
    $$PWD/Controllers/CController.cpp \
    $$PWD/Models/CModels.cpp \
    $$PWD/ViewData/ViewStates.cpp

INCLUDEPATH += \
    $$PWD/ViewData \
    $$PWD/Controllers \
    $$PWD/Models


RESOURCES += \
    $$PWD/Resources/QML/qml_resources.qrc \
    $$PWD/Resources/Images/image_resources.qrc
