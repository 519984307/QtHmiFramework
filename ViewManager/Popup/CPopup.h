#ifndef CPOPUP_H
#define CPOPUP_H

#include <QTimer>
#include "AView.h"

class CPopup : public AView
{
    Q_OBJECT
public:
    CPopup(const S_VIEW_INFORMATION *info, QQuickItem *parent = nullptr);
    ~CPopup();

    // AView interface
public:
    virtual AView *customizeProperties() override;
};

#endif // CPOPUP_H
