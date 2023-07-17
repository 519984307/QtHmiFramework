#ifndef CQMLSTACKVIEW_H
#define CQMLSTACKVIEW_H

#include <QQuickItem>

class CQmlStackView : public QQuickItem
{
    Q_OBJECT
public:
    explicit CQmlStackView(QQuickItem *parent = nullptr);
    ~CQmlStackView();

signals:

};

#endif // CQMLSTACKVIEW_H
