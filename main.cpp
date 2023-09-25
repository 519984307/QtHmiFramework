#include <QGuiApplication>
#include <thread>
#include "CNgin.h"
#include "ViewData.h"
#include "CController.h"
#include "CModels.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);


    CController ctrl;
    CModels model;

    CNgin::instance()->initialize(app, __MAIN_WINDOW_WIDTH__, __MAIN_WINDOW_HEIGHT__, CViewEnums::E_SCREEN_A_EVT_SHOW);
    CNgin::instance()->registerViews(ALL_INFOR, SIZE_OF_ARRAY(ALL_INFOR));
    CNgin::instance()->registerEvents(ALL_EVENTS, SIZE_OF_ARRAY(ALL_EVENTS));
    CNgin::instance()->setCtxProperty("QmlCtrl", QVariant::fromValue(&ctrl));
    CNgin::instance()->setCtxProperty("QmlModel", QVariant::fromValue(&model));
    CNgin::instance()->completed();

    return app.exec();
}
