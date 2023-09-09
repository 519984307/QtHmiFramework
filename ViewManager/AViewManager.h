#ifndef AVIEWMANAGER_H
#define AVIEWMANAGER_H

#include <QObject>
#include <QStack>
#include <functional>
#include "AView.h"

class AViewManager: public QObject
{
    Q_OBJECT
public:
    explicit AViewManager(QObject *parent = nullptr);
    virtual ~AViewManager(){};
    virtual void pushEnter(const S_VIEW_INFORMATION* view) = 0;
    virtual void popExit() = 0;

    AView *last_view() const;


signals:
    void signalPushEnter(AView*);

protected:
    template<class AT>
    int indexOfViewByID(QList<AT*> &views, const uint32_t &id)
    {
        int index = -1;
        for(AT *e: views)
        {
            index++;
            if(e->info()->id == id)
            {
                break;
            }
        }
        return index;
    }
    AView                          *m_last_view = nullptr;
};


#endif // AVIEWMANAGER_H
