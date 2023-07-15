#ifndef CVIEWMANAGER_H
#define CVIEWMANAGER_H

#include <QObject>
#include <QTimer>
#include <QStack>
#include "CPopupObject.h"
#include "Common.h"

class CViewManager : public QObject
{
    Q_OBJECT
public:
    explicit CViewManager(QObject *parent = nullptr);
    ~CViewManager();
    const S_VIEW_INFORMATION *currentView() const;
    void popExit();
    void pushEnter(const S_VIEW_INFORMATION*);



private:
    QStack<CPopupObject*>                               m_popupObjs{};
    QStack<const S_VIEW_INFORMATION*>                   m_stack;
};

#endif // CVIEWMANAGER_H
