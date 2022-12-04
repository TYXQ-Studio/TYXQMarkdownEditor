#include "ui/MainWindow.h"

#include <FramelessWidgetsHelper>
#include <QApplication>
#include <iostream>


FRAMELESSHELPER_USE_NAMESPACE

int main(int argc, char *argv[])
{
    std::cout << "??" << std::endl;
    FramelessHelper::Widgets::initialize();
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    const int exec = a.exec();
    FramelessHelper::Widgets::uninitialize();
    return exec;
}
