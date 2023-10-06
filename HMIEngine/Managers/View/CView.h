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

BEGIN_NAMESPACE(HmiNgin)
class CView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit CView(QQuickItem *parent = nullptr);
    ~CView();

    void show();
    void hide();

    void initialize(const S_VIEW_INFORMATION *, QQuickItem *);

    uint32_t id() const;
    uint32_t duration() const;
    E_VIEW_TYPE type() const;
    const QString strType() const;
    const char *c_strType() const;
    const char *path() const;

    virtual void customizeProperties(){};
    virtual void completed(){};

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
    QHash<QString, QVariant> m_properties;

protected:
    QString m_str_type;
    QTimer m_timer;

private:
    // view info
    uint32_t m_id{0};
    uint32_t m_duration{E_DURATION::NONE};
    E_VIEW_TYPE m_type{E_VIEW_TYPE::NONE_TYPE};
    const char *m_path;

    // Qml properties
    QString m_title;
    QString m_color;

signals:
    void titleChanged();
    void colorChanged();

    void signalVisible();
    void signalInvisible();

public slots:
    void onSignalVisible();
    void onSignalInvisible();
};

END_NAMESPACE

#endif // CVIEW_H
