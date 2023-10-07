RESOURCES += \
    $$PWD/Resources/root_resource.qrc


SOURCES += \
    $$PWD/CNgin.cpp \
    $$PWD/Managers/View/AViewManager.cpp \
    $$PWD/Utils/Logger/CLogger.cpp \
    $$PWD/Utils/Memory/LFUCache/CLFUCache.cpp \
    $$PWD/Utils/Memory/LRUCache/CLRUCache.cpp \
    $$PWD/Managers/Animation/CAnimationManager.cpp \
    $$PWD/Managers/Animation/NumberAnimation/CNumberAnimation.cpp \
    $$PWD/Managers/Event/CEventManager.cpp \
    $$PWD/Managers/View/CCacheManager.cpp \
    $$PWD/Managers/View/CFreqTable.cpp \
    $$PWD/Managers/View/CView.cpp \
    $$PWD/Managers/View/Notify/CNotify.cpp \
    $$PWD/Managers/View/Notify/CNotifyManager.cpp \
    $$PWD/Managers/View/Popup/CPopup.cpp \
    $$PWD/Managers/View/Popup/CPopupManager.cpp \
    $$PWD/Managers/View/Screen/CScreen.cpp \
    $$PWD/Managers/View/Screen/CScreenManager.cpp \
    $$PWD/Managers/View/Toast/CToast.cpp \
    $$PWD/Managers/View/Toast/CToastManager.cpp \

HEADERS += \
    $$PWD/CNgin.h \
    $$PWD/Utils/Utils.h \
    $$PWD/Utils/Memory/LFUCache/CLFUCache.h \
    $$PWD/Utils/Memory/LRUCache/CLRUCache.h \
    $$PWD/Utils/Logger/CLogger.h \
    $$PWD/Utils/Logger/LoggerDefines.h \
    $$PWD/Managers/Animation/CAnimationManager.h \
    $$PWD/Managers/Animation/NumberAnimation/CNumberAnimation.h \
    $$PWD/Managers/Animation/IAnimation.h \
    $$PWD/Managers/Sound/ISound.h \
    $$PWD/Managers/Event/EventEnums.h \
    $$PWD/Managers/Event/EventDefines.h \
    $$PWD/Managers/Event/EventStructs.h \
    $$PWD/Managers/Event/CEventManager.h \
    $$PWD/Managers/View/AViewManager.h \
    $$PWD/Managers/View/CCacheManager.h \
    $$PWD/Managers/View/CFreqTable.h \
    $$PWD/Managers/View/CView.h \
    $$PWD/Managers/View/Notify/CNotify.h \
    $$PWD/Managers/View/Notify/CNotifyManager.h \
    $$PWD/Managers/View/Popup/CPopup.h \
    $$PWD/Managers/View/Popup/CPopupManager.h \
    $$PWD/Managers/View/Screen/CScreen.h \
    $$PWD/Managers/View/Screen/CScreenManager.h \
    $$PWD/Managers/View/Toast/CToast.h \
    $$PWD/Managers/View/Toast/CToastManager.h

INCLUDEPATH += \
    $$PWD/QmlTypes \
    $$PWD/Managers \
    $$PWD/Managers/View \
    $$PWD/Managers/Event \
    $$PWD/Managers/Sound \
    $$PWD/Managers/Animation \
    $$PWD/Utils


