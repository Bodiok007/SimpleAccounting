#include "mainwindow.h"
#include "addsaleform.h"
#include <QApplication>

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

    return a.exec();
}
