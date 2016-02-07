#include "addserviceform.h"
#include "ui_addserviceform.h"
#include "db.h"

AddServiceForm::AddServiceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddServiceForm)
{
    ui->setupUi(this);
    ui->lineServiceSum->setValidator(new QDoubleValidator);

    setAttribute(Qt::WA_ShowModal);

    ui->comboServiceCategory->addItems(DB::instance()->getListServiceCategories());

    connect(ui->addServiceButton,
            SIGNAL(clicked(bool)),
            SLOT(addService()));
}

AddServiceForm::~AddServiceForm()
{
    delete ui;
}

void AddServiceForm::addService()
{
    qDebug() << "addServiceOK!";
    DB::instance()->addService(ui->lineCustomerName->text(),
                               ui->lineCustomerPhone->text(),
                               m_employeeName,
                               ui->comboServiceCategory->currentText(),
                               ui->lineServiceDescription->toPlainText(),
                               ui->lineServiceSum->text().toDouble());
    ui->lineCustomerName->clear();
    ui->lineCustomerPhone->clear();
    ui->lineServiceDescription->clear();
    ui->lineServiceSum->clear();

    hide();
}

void AddServiceForm::setEmployeeName(QString employeeName)
{
    m_employeeName = employeeName;
}
