#include "CScreenObject.h"


CScreenObject::CScreenObject(const S_VIEW_INFORMATION *view,
                             QQmlApplicationEngine *ngin,
                             QObject *parent): QQmlComponent(ngin, view->path, parent)
{
    m_ngin = ngin;
    m_info = view;
}

CScreenObject::~CScreenObject()
{

}
