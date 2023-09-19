#ifndef CVIEW_H
#define CVIEW_H

#include <QObject>
#include <QQuickItem>
#include <QCoreApplication>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QTimer>
#include <QHash>
#include "CommonStructs.h"
#include "CommonDefine.h"
#include "Logger/LoggerDefines.h"

class CView: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(uint8_t countDown READ countDown NOTIFY countDownChanged FINAL)
public:
    explicit CView(QQuickItem *parent = nullptr);
    ~CView();

    void show()
    {
        CPP_LOG_DEBUG("[%s][%s]", c_strType(), path())
        this->setProperty("visible", true);
        emit signalVisible();
    }
    void hide()
    {
        CPP_LOG_DEBUG("[%s][%s]", c_strType(), path())
        this->setProperty("visible", false);
        emit signalInvisible();
    }

    CView *initialize(const S_VIEW_INFORMATION *, QQuickItem*);

    uint32_t id() const;
    uint32_t duration() const;
    E_VIEW_TYPE type() const;
    const QString strType() const;
    const char* c_strType() const;
    const char *path() const;


    virtual CView *customizeProperties() { return this; };

    // QQuickPaintedItem interface
public:
    virtual void paint(QPainter *painter) override;

    QString title() const;
    void setTitle(const QString &newTitle);

    QString color() const;
    void setColor(const QString &newColor);

    uint8_t countDown() const;

private:
    void initConnections();
    void readProperties();

protected:
    QHash<QString, QVariant>     m_properties;

signals:
    void titleChanged();
    void colorChanged();

    void signalVisible();
    void signalInvisible();
    void signalVisibleTimeout();

    void countDownChanged();

public slots:
    void onSignalVisible();
    void onSignalInvisible();
    void onTimeout();

protected:
    QString                  m_str_type;

private:
    void startTimer();
    void stopTimer();

private:
    QRectF                   m_rect;
    QTimer                  *m_timer = nullptr;
    uint32_t                 m_count_down{0};

    // view info
    uint32_t                 m_id{0};
    uint32_t                 m_duration{E_DURATION::NONE};
    E_VIEW_TYPE              m_type{E_VIEW_TYPE::NONE_TYPE};
    const char*              m_path;

    // Qml properties
    QString m_title;
    QString m_color;
};


#endif // CVIEW_H
