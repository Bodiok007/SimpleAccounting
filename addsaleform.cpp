#include "addsaleform.h"
#include "ui_addsaleform.h"

AddSaleForm::AddSaleForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSaleForm)
{
    ui->setupUi(this);
}

AddSaleForm::~AddSaleForm()
{
    delete ui;
}

void AddSaleForm::setEmployeeName(QString emloyeeName)
{
    ui->groupBox->setEmployeeName(emloyeeName);
}
