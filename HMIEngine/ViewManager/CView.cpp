#include "CView.h"
#include "Utils.h"

CView::CView(QQuickItem *parent):QQuickPaintedItem{parent}
{
    m_timer = new QTimer(this);

    setAcceptTouchEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);

    initConnections();
}

CView::~CView()
{
    safeRelease(m_timer);
}

CView * CView::initialize(const S_VIEW_INFORMATION *info, QQuickItem *parent)
{
    CPP_LOG_DEBUG("[%s][Entry]", c_strType())

    {
        m_id        = info->id;
        m_type      = info->type;
        m_duration  = info->duration;
        m_path      = info->path;
    }

    m_count_down = m_duration;

    m_timer->setSingleShot(false);
    m_timer->setInterval(ONE_SEC);

    this->setVisible(false);
    this->setParentItem(parent);
    this->readProperties();
    this->customizeProperties();

    CPP_LOG_DEBUG("[%s][Exit]", c_strType())

    return this;
}

void CView::readProperties()
{
    CPP_LOG_DEBUG("[%s][Entry]", c_strType())
    m_properties["x"]           = this->property("x").toReal();
    m_properties["y"]           = this->property("y").toReal();
    m_properties["z"]           = this->property("z").toReal();
    m_properties["width"]       = this->property("width").toReal();
    m_properties["height"]      = this->property("height").toReal();
    m_properties["anchors"]     = this->property("anchors");
    CPP_LOG_DEBUG("[%s][Exit]", c_strType())
}

void CView::onSignalVisible()
{
    startTimer();
}

void CView::onSignalInvisible()
{
    stopTimer();
}

void CView::onTimeout()
{
    --m_count_down;
    if(m_count_down < 1)
    {
        m_count_down = m_duration;
        stopTimer();

        this->hide();
    }

    emit countDownChanged();
}

void CView::startTimer()
{
    if(m_type > E_VIEW_TYPE::SCREEN_TYPE && !m_timer->isActive())
    {
        if(m_duration > 0)
        {
            m_timer->start();
        }
    }
}

void CView::stopTimer()
{
    if(m_type > E_VIEW_TYPE::SCREEN_TYPE && m_timer->isActive())
    {
        m_timer->stop();
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
    QRectF rect = boundingRect();
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawRect(rect);
    painter->fillRect(rect, QColor(m_color));
    painter->restore();
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

uint8_t CView::countDown() const
{
    return m_count_down;
}
