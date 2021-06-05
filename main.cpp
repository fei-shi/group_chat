#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login b;
    b.show();
    return a.exec();
}
