#ifndef CVIEWMANAGER_H
#define CVIEWMANAGER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QTimer>
#include <QStack>
#include <QQuickItem>
#include "CommonStructs.h"

class CViewManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(uint8_t depth READ depth NOTIFY depthChanged)
public:
    explicit CViewManager(QQmlApplicationEngine *ngin, QObject *parent = nullptr);
    ~CViewManager();
    const S_VIEW_INFORMATION *currentView() const;
    uint8_t depth() const;
    void pushEnter(const S_VIEW_INFORMATION*);
    void popExit();

signals:
    void depthChanged();

private:
    QQmlApplicationEngine                              *m_ngin = nullptr;
    QStack<const S_VIEW_INFORMATION*>                   m_stack;
    QHash<uint32_t, bool>                               m_stack_history;
    uint8_t                                             m_depth{0};
};

#endif // CVIEWMANAGER_H
