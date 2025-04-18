/*
 * main.cpp
 */

#include <QApplication>
#include "mainwindow.h"

/*just to tes*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
