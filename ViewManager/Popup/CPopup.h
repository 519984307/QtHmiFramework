#ifndef CPOPUP_H
#define CPOPUP_H

#include <QTimer>
#include "AView.h"

class CPopup : public AView
{
    Q_OBJECT
public:
    CPopup(const S_VIEW_INFORMATION *info, QObject *parent = nullptr);
    ~CPopup();

    // AView interface
public:
    virtual AView *customizeProperties() override;

signals:
    void signalWaittingForTimeout();

private:
    QTimer                  *m_timer = nullptr;

};

#endif // CPOPUP_H
