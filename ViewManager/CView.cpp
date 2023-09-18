#include "CView.h"
#include "Utils.h"

CView::CView(QQuickItem *parent):QQuickPaintedItem{parent}
{
    m_timer = new QTimer(this);

    setAcceptTouchEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);

    setVisible(false);

    initConnections();
}

CView::~CView()
{
    safeRelease(m_timer);
}

CView * CView::initialize(const S_VIEW_INFORMATION *info, QQuickItem *parent)
{
    CPP_LOG_DEBUG("[Entry]")

    {
        m_id        = info->id;
        m_type      = info->type;
        m_duration  = info->duration * ONE_SEC;
        m_path      = info->path;
    }


    m_timer->setSingleShot(true);

    this->setParentItem(parent);
    this->readProperties();
    this->customizeProperties();

    CPP_LOG_DEBUG("[Exit]")
    return this;
}

void CView::readProperties()
{
    CPP_LOG_DEBUG("[Entry]")
    m_properties["x"]           = this->property("x").toReal();
    m_properties["y"]           = this->property("y").toReal();
    m_properties["z"]           = this->property("z").toReal();
    m_properties["width"]       = this->property("width").toReal();
    m_properties["height"]      = this->property("height").toReal();
    m_properties["anchors"]     = this->property("anchors");
    CPP_LOG_DEBUG("[Exit]")
}

void CView::onSignalVisible()
{
    startTimer();
}

void CView::onSignalInvisible()
{
}

void CView::onTimeout()
{
    this->hide();
    emit signalVisibleTimeout();

}

void CView::startTimer()
{
    if(m_type > E_VIEW_TYPE::SCREEN_TYPE && m_timer != nullptr)
    {
        if(m_duration > 0)
        {
            m_timer->start(m_duration);
        }
    }
}

void CView::stopTimer()
{
    if(m_type > E_VIEW_TYPE::SCREEN_TYPE && m_timer != nullptr)
    {
        if(m_timer->isActive())
        {
            m_timer->stop();
        }
    }
}

void CView::initConnections()
{
    if(m_timer != nullptr)
    {
        connect(m_timer, &QTimer::timeout, this, &CView::onTimeout, Qt::DirectConnection);
    }

    connect(this, &CView::signalVisible, this, &CView::onSignalVisible, Qt::DirectConnection);
    connect(this, &CView::signalInvisible, this, &CView::onSignalInvisible, Qt::DirectConnection);

}

uint32_t CView::id() const
{
    return m_id;
}

uint32_t CView::duration() const
{
    return m_duration;
}

E_VIEW_TYPE CView::type() const
{
    return m_type;
}

const QString CView::strType() const
{
    return m_str_type;
}

const char *CView::c_strType() const
{
    std::string str = m_str_type.toStdString();
    const char* c_str = str.c_str();
    return c_str;
}

const char *CView::path() const
{
    return m_path;
}

void CView::paint(QPainter *painter)
{
    m_rect.setRect(0, 0, this->width(), this->height());
    painter->drawRect(m_rect);
    painter->fillRect(m_rect, QColor(m_color));
}

QString CView::title() const
{
    return m_title;
}

void CView::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

QString CView::color() const
{
    return m_color;
}

void CView::setColor(const QString &newColor)
{
    if (m_color == newColor)
        return;
    m_color = newColor;
    emit colorChanged();
}
