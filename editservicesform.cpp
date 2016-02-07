#include "editservicesform.h"
#include "ui_editservicesform.h"
#include "db.h"

EditServicesForm::EditServicesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditServicesForm)
{
    ui->setupUi(this);
    ui->lineSum->setValidator(new QDoubleValidator);

    setAttribute(Qt::WA_ShowModal);

    connect(ui->buttonSaveEditService,
            SIGNAL(clicked(bool)),
            SLOT(saveEditData())
           );
}

EditServicesForm::~EditServicesForm()
{
    delete ui;
}

void EditServicesForm::addDataToForm(uint serviceID)
{
    clearEditForm();
    m_serviceID = serviceID;

    m_generalData = DB::instance()->getCurrentServiceData(serviceID);

    ui->plainDescription->setPlainText(m_generalData["orderDescription"]);
    ui->lineSum->setText(m_generalData["serviceSum"]);

    // set customer name and phone
    QStringList customerData = DB::instance()->getServiceCustomerDataByID(m_generalData["customerID"].toUInt());
    ui->lineCustomer->setText(customerData.at(0));
    ui->linePhone->setText(customerData.at(1));

    // add order date
    QDate orderServiceDate = QDate::fromString(m_generalData["orderServiceDate"], "dd.MM.yyyy");
    ui->calendarOrderService->setSelectedDate(orderServiceDate);

    // add execution date
    QDate executionServiceDate = QDate::fromString(m_generalData["executionServiceDate"], "dd.MM.yyyy");
    ui->calendarExecutionService->setSelectedDate(executionServiceDate);

    // add list categories and set current one
    QString currentCategory = DB::instance()->getServiceCategoryNameByID(m_generalData["serviceCategoryID"].toUInt());
    ui->comboServiceCategory->addItems(DB::instance()->getListServiceCategories());
    ui->comboServiceCategory->setCurrentText(currentCategory);
}

void EditServicesForm::saveEditData()
{
    qDebug() << "edit button sale ok";

    DB::instance()->saveEditService(m_serviceID,
                                    ui->comboServiceCategory->currentText(),
                                    m_generalData["customerID"].toUInt(),
                                    ui->lineCustomer->text(),
                                    ui->linePhone->text(),
                                    ui->plainDescription->toPlainText(),
                                    ui->calendarOrderService->selectedDate().toString("dd.MM.yyyy"),
                                    ui->calendarExecutionService->selectedDate().toString("dd.MM.yyyy"),
                                    ui->lineSum->text().toDouble());
    hide();
}

void EditServicesForm::clearEditForm()
{
    ui->comboServiceCategory->clear();
}
