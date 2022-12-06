#include "window/MainWindow.h"

#include <FramelessWidgetsHelper>
#include <QApplication>

FRAMELESSHELPER_USE_NAMESPACE

int main(int argc, char *argv[]) {
    FramelessHelper::Widgets::initialize();
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    const int exec = a.exec();
    FramelessHelper::Widgets::uninitialize();
    return exec;
}
