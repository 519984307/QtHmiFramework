#ifndef CNOTIFY_H
#define CNOTIFY_H

#include <QTimer>
#include "AView.h"

class CNotify : public AView
{
    Q_OBJECT
public:
    CNotify(const S_VIEW_INFORMATION *info, QObject *parent = nullptr);
    ~CNotify();
    // AView interface
public:
    virtual AView *customizeProperties() override;

signals:
    void signalWaittingForTimeout();

private:
    QTimer                  *m_timer = nullptr;
};

#endif // CNOTIFY_H
