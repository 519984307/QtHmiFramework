#ifndef CPOPUP_H
#define CPOPUP_H

#include <QTimer>
#include "AView.h"

class CPopup : public AView
{
public:
    CPopup(const S_VIEW_INFORMATION *info, QObject *parent = nullptr);
    ~CPopup();

    // AView interface
public:
    virtual AView *customizeProperties() override;

private:
    QTimer                  *m_timer = nullptr;

    // QObject interface
public:
    virtual bool event(QEvent *event) override;
};

#endif // CPOPUP_H
