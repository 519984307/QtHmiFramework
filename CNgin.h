#ifndef CNGIN_H
#define CNGIN_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QGuiApplication>
#include <QTimer>
#include <vector>
#include "CViewManager.h"

class CNgin : public QObject
{
    Q_OBJECT
public:
    static CNgin* instance();

    void initialize(QGuiApplication&, uint32_t, uint32_t, uchar);
    void completed();
    void setCtxProperty(QString, QVariant);
    void registerViews(const S_VIEW_INFORMATION*, uint32_t);
    void registerEvents(const S_VIEW_EVENT*, uint32_t);
    Q_INVOKABLE void sendEvent(uchar);
    Q_INVOKABLE void previousView();
public slots:
    void onClosePopup();
    void onPopupTimeout();

signals:
    void initCompleted();

private:
    explicit CNgin(QObject *parent = nullptr);
    ~CNgin();

    void loadView();
    void loadQML(QString, const QString&);

private:
    static CNgin                           *s_instance;
    QQmlApplicationEngine                  *m_qmlNgin           = nullptr;
    QQmlContext                            *m_qmlCtx            = nullptr;
    QObject                                *m_rootObject        = nullptr;
    QTimer                                 *m_popupTimer        = nullptr;
    CViewManager                           *m_viewManager       = nullptr;
};

#endif // CNGIN_H
