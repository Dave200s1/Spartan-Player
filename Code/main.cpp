#include "mainwindow.h"
#include <QMainWindow>
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setMinimumHeight(500);
    w.setMinimumWidth(700);
    w.show();
    return a.exec();
}
