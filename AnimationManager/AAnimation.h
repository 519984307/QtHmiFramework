#ifndef AANIMATION_H
#define AANIMATION_H

#include <QObject>
#include <QByteArray>
#include <QPropertyAnimation>

class AAnimation: public QPropertyAnimation
{
public:

private:
    int                 m_duration{200};
    QObject            *m_target  = nullptr;
    QByteArray          m_property_name;

    // QObject interface
public:
    AAnimation(QObject *target, const QByteArray &propertyName, QObject *parent = nullptr);

    virtual bool event(QEvent *event) override;

    // QAbstractAnimation interface
protected:
    virtual void updateState(State newState, State oldState) override;

    // QVariantAnimation interface
protected:
    virtual void updateCurrentValue(const QVariant &value) override;
};

#endif // AANIMATION_H
