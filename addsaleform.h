#ifndef ADDSALEFORM_H
#define ADDSALEFORM_H

#include <QWidget>

namespace Ui {
class AddSaleForm;
}

class AddSaleForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddSaleForm(QWidget *parent = 0);
    ~AddSaleForm();

    void setEmployeeName(QString emloyeeName);

public slots:
    //void addSale();

private:
    Ui::AddSaleForm *ui;
};

#endif // ADDSALEFORM_H
