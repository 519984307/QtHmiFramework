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
    CPP_LOG_INFO("[Entry]")

    {
        m_id        = info->id;
        m_type      = info->type;
        m_duration  = info->duration;
        m_path      = info->path;
    }


    if(m_type > E_VIEW_TYPE::SCREEN_TYPE && m_timer != nullptr)
    {
        if(m_duration > 0)
        {
            m_timer->setSingleShot(true);
            m_timer->start(m_duration * ONE_SEC);
        }
    }

    this->setParentItem(parent);
    this->readProperties();
    this->customizeProperties();

    CPP_LOG_INFO("[Exit]")
    return this;
}

void CView::readProperties()
{
    CPP_LOG_INFO("[Entry]")
    m_properties["x"]           = this->property("x").toReal();
    m_properties["y"]           = this->property("y").toReal();
    m_properties["z"]           = this->property("z").toReal();
    m_properties["width"]       = this->property("width").toReal();
    m_properties["height"]      = this->property("height").toReal();
    m_properties["anchors"]     = this->property("anchors");
    CPP_LOG_INFO("[Exit]")
}

void CView::initConnections()
{
    connect(this, &CView::signalVisible, [this]() {this->show();});
    connect(this, &CView::signalInvisible, [this]() {this->hide();});

    if(m_timer != nullptr)
    {
        connect(m_timer, &QTimer::timeout, this, &CView::signalInvisible, Qt::DirectConnection);
    }
}

uint32_t CView::id() const
{
    return m_id;
}

E_DURATION CView::duration() const
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
