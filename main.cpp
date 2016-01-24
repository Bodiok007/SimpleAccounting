#include "mainwindow.h"
#include "addsaleform.h"
#include <QApplication>

#include "loginform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AddSaleForm addSaleForm;
    //addSaleForm.show();
    /*QObject::connect(w.getForm()->sddSaleButton,
            SIGNAL(clicked(bool)),
            addSaleForm,
            SLOT(show())
           );*/
    w.show();

    //LoginForm lf;
    //lf.show();

    QStyle* pstyle = QStyleFactory::create("Fusion");
    QApplication::setStyle(pstyle);

    return a.exec();
}
