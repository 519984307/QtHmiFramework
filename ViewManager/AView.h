#ifndef AVIEW_H
#define AVIEW_H

#include <QObject>
#include <QQuickItem>
#include <QCoreApplication>
#include <QTimer>
#include <QHash>
#include "CommonStructs.h"
#include "CommonDefine.h"
#include "Logger/LoggerDefines.h"
#include "CQmlRootContainer.h"

class AView: public CQmlRootContainer
{
    Q_OBJECT
public:
    explicit AView(const S_VIEW_INFORMATION *info, QQuickItem *parent = nullptr);
    ~AView();

    inline void show()
    {
        CPP_LOG_INFO("[Entry]")
        this->setProperty("visible", true);
        emit signalVisible();
        CPP_LOG_INFO("[Exit]")
    }
    inline void hide()
    {
        CPP_LOG_INFO("[Entry]")
        this->setProperty("visible", false);
        emit signalInvisible();
        CPP_LOG_INFO("[Exit]")
    }

    const S_VIEW_INFORMATION *info() const
    {
        return m_info;
    }

    void setInfo(const S_VIEW_INFORMATION *newInfo);

    AView *initialize(QQuickItem*);


    virtual AView *customizeProperties() { return this; };


private:
    void initConnections();
    void readProperties();

    // QObject interface
public:
    virtual bool event(QEvent *event) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;


protected:
    const S_VIEW_INFORMATION    *m_info         = nullptr;
    QHash<QString, QVariant>     m_properties;

signals:
        void signalVisible();
    void signalInvisible();
    void signalWaittingForTimeout();

private:
    QTimer                  *m_timer = nullptr;

};


#endif // AVIEW_H
