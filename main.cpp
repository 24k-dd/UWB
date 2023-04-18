//#include "mainwidget.h"
//#include"mainwindow.h"
#include"checkidwidget.h"
#include <QApplication>
#include<loginwidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    LoginWidget w;
//    CheckIdWidget w;
    w.show();

    return a.exec();
}
