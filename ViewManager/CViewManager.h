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
    void addView(const S_VIEW_INFORMATION*);
    void addEvents(const S_VIEW_EVENT*);
    void pushViewByEvt(uchar&);
    void popLastView();


private:
    QStack<const S_VIEW_INFORMATION*>                   m_stack;
    QList<const S_VIEW_INFORMATION*>                    m_views{};
    QList<const S_VIEW_EVENT*>                          m_events{};
    QList<CPopupObject*>                                m_popupObjs{};
};

#endif // CVIEWMANAGER_H
