#include <QGuiApplication>
#include <QDebug>
#include <thread>
#include "config.h"
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

    App::CController ctrl;
    App::CModels model;

    HmiNgin::CNgin::instance()->initialize(
        app,
        APP_NAME,
        __MAIN_WINDOW_WIDTH__,
        __MAIN_WINDOW_HEIGHT__,
        App::CViewEnums::E_SCREEN_A_EVT_SHOW);
    HmiNgin::CNgin::instance()->registerViews(App::ALL_INFOR, SIZE_OF_ARRAY(App::ALL_INFOR));
    HmiNgin::CNgin::instance()->registerEvents(App::ALL_EVENTS, SIZE_OF_ARRAY(App::ALL_EVENTS));
    HmiNgin::CNgin::instance()->setCtxProperty("QmlCtrl", QVariant::fromValue(&ctrl));
    HmiNgin::CNgin::instance()->setCtxProperty("QmlModel", QVariant::fromValue(&model));
    HmiNgin::CNgin::instance()->completed();

    return app.exec();
}
