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
public:
    explicit CView(QQuickItem *parent = nullptr);
    ~CView();

    void show()
    {
        CPP_LOG_INFO("[%s][%s]", strType().toStdString().c_str(), path())
        this->setProperty("visible", true);
    }
    void hide()
    {
        CPP_LOG_INFO("[%s][%s]", strType().toStdString().c_str(), path())
        this->setProperty("visible", false);
    }

    CView *initialize(const S_VIEW_INFORMATION *, QQuickItem*);

    uint32_t id() const;
    E_DURATION duration() const;
    E_VIEW_TYPE type() const;
    const QString strType() const;
    const char *path() const;


    virtual CView *customizeProperties() { return this; };

    // QQuickPaintedItem interface
public:
    virtual void paint(QPainter *painter) override;

    QString title() const;
    void setTitle(const QString &newTitle);

    QString color() const;
    void setColor(const QString &newColor);

private:
    void initConnections();
    void readProperties();

protected:
    QHash<QString, QVariant>     m_properties;

signals:
    void signalVisible();
    void signalInvisible();

    void titleChanged();

    void colorChanged();

protected:
    QString                  m_str_type;

private:
    QRectF                   m_rect;
    QTimer                  *m_timer = nullptr;

    // view info
    uint32_t                 m_id{0};
    E_DURATION               m_duration{E_DURATION::NONE};
    E_VIEW_TYPE              m_type{E_VIEW_TYPE::NONE_TYPE};
    const char*              m_path;

    // Qml properties
    QString m_title;
    QString m_color;
};


#endif // CVIEW_H
