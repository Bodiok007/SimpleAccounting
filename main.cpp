#include "mainwindow.h"
#include "addsaleform.h"
#include <QApplication>

#include "loginform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QStyle* pstyle = QStyleFactory::create("Fusion");
    QApplication::setStyle(pstyle);

    return a.exec();
}
