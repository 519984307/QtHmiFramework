#ifndef CQMLROOTCONTAINER_H
#define CQMLROOTCONTAINER_H

#include <QQuickPaintedItem>
#include <QPainter>

class CQmlRootContainer : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged FINAL)
public:
    CQmlRootContainer(QQuickItem *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);

    // QQuickPaintedItem interface
public:
    virtual void paint(QPainter *painter) override;

    QString color() const;
    void setColor(const QString &newColor);

signals:

    void titleChanged();
    void colorChanged();

private:
    QRect   m_rect;

    // qml properties
    QString m_title{"[Screen]Nothing"};
    QString m_color;
};

#endif // CQMLROOTCONTAINER_H
