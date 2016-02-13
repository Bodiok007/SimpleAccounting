#include "editservicesform.h"
#include "ui_editservicesform.h"
#include "db.h"
#include "servicecategories.h"


//------------------------------------------------------------------------------
// CONSTRUCTOR
//------------------------------------------------------------------------------
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

    m_pServiceCategories = ServiceCategories::instance()->getCategories();
}


//------------------------------------------------------------------------------
// Create a message window
//------------------------------------------------------------------------------
void EditServicesForm::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


//------------------------------------------------------------------------------
// Clear fields on form
//------------------------------------------------------------------------------
void EditServicesForm::clearEditForm()
{
    ui->comboServiceCategory->clear();
}


//------------------------------------------------------------------------------
// Save customer name and phone from form to DB
//------------------------------------------------------------------------------
bool EditServicesForm::updateCustomer()
{
    QString query = "UPDATE customers SET "
                        "customerName = ?, "
                        "customerPhone = ? "
                    "WHERE customerID = ? ";
    QStringList arguments;
    arguments << ui->lineCustomer->text()
              << ui->linePhone->text()
              << m_serviceTableData["customerID"];

    bool statusOk = DB::instance()->query(query, arguments);

    if (!statusOk) {
        qDebug() << "Can`t update customer!";
        qDebug() << DB::instance()->lastError();
        return false;
    }

    return true;
}


//------------------------------------------------------------------------------
// Add data from DB to form
// 'serviceID' get from selected field in 'ServicesTableView'
//------------------------------------------------------------------------------
void EditServicesForm::addDataToForm(uint serviceID)
{
    clearEditForm();
    show();
    m_serviceID = serviceID;

    getServiceTableData(serviceID);

    addServiceDescriptionToForm();
    addServiceCostToForm();

    // add customer name and phone
    addCustomerToForm(m_serviceTableData["customerID"]);

    addOrderDateToForm();
    addExecutionDateToForm();

    // add list categories and set current one
    addCategoriesToForm();
}


//------------------------------------------------------------------------------
// Save data from form to DB
//------------------------------------------------------------------------------
void EditServicesForm::saveEditData()
{
    bool ok = updateCustomer();
    if (!ok) {
        message("Неможливо змінити дані про замовника");
    }

    QString query = "UPDATE provideServices SET "
                        "serviceCategoryID = ?, "
                        "orderDescription = ?, "
                        "orderServiceDate = ?, "
                        "executionServiceDate = ?, "
                        "serviceSum = ? "
                    "WHERE provideServicesID = ? ";
    QStringList arguments;
    arguments << m_pServiceCategories->value(ui->comboServiceCategory->currentText())
              << ui->plainDescription->toPlainText()
              << ui->calendarOrderService->selectedDate().toString("dd.MM.yyyy")
              << ui->calendarExecutionService->selectedDate().toString("dd.MM.yyyy")
              << ui->lineSum->text()
              << QString::number(m_serviceID);

    bool statusOk = DB::instance()->query(query, arguments);

    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        qDebug() << "Can`t save edit service data";
        hide();
        return;
    }

    emit updateServicesData();

    hide();
}


//------------------------------------------------------------------------------
// Create a query to get data from 'services' table with current 'serviceID'
//------------------------------------------------------------------------------
bool EditServicesForm::getServiceTableData(uint serviceID)
{
    QString query = "SELECT serviceCategoryID, "
                        "customerID, "
                        "orderDescription, "
                        "orderServiceDate, "
                        "executionServiceDate, "
                        "serviceSum "
                    "FROM provideservices "
                    "WHERE provideServicesID = ?";
    QStringList arguments(QString::number(serviceID));

    bool statusOk = DB::instance()->query(query, arguments);

    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        return false;
    }

    setServiceTableData();

    return true;
}


//------------------------------------------------------------------------------
// Set selected data from 'services' table to map 'm_serviceTableData'
// where the keys - name of fields
//------------------------------------------------------------------------------
void EditServicesForm::setServiceTableData()
{
    QStringList fieldNames;
    fieldNames << "serviceCategoryID"
               << "customerID"
               << "orderDescription"
               << "orderServiceDate"
               << "executionServiceDate"
               << "serviceSum";

    QSqlQuery *serviceData = DB::instance()->getData();

    serviceData->next();

    for (int currentField = 0;
         currentField < fieldNames.size();
         ++currentField) {

        m_serviceTableData[fieldNames.at(currentField)]
                = serviceData->value(currentField).toString();
    }
}


//------------------------------------------------------------------------------
// Add data from 'customer' table with current 'customerID' to form
//------------------------------------------------------------------------------
void EditServicesForm::addCustomerToForm(QString customerID)
{
    QMap<QString, QString> *customerData = getCustomerTableData(customerID);

    if (!customerData) {
        return;
    }

    addCustomerNameToForm((*customerData)["customerName"]);
    addCustomerPhoneToForm((*customerData)["customerPhone"]);

    delete customerData;
}


//------------------------------------------------------------------------------
// Get data from 'customer' table with current 'customerID'
// return data contains in map, where the keys - name of fields
//------------------------------------------------------------------------------
QMap<QString, QString> *EditServicesForm::getCustomerTableData(QString customerID)
{
    QString query = "SELECT customerName, customerPhone "
                    "FROM customers "
                    "WHERE customerID = ? ";
    QStringList arguments(customerID);

    bool statusOk = DB::instance()->query(query, arguments);

    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        return NULL;
    }

    QSqlQuery *customerDataFromTabel = DB::instance()->getData();
    customerDataFromTabel->next();

    QMap<QString, QString> *custmerData = new QMap<QString, QString>;
    (*custmerData)["customerName"] = customerDataFromTabel->value(0).toString();
    (*custmerData)["customerPhone"] = customerDataFromTabel->value(1).toString();

    return custmerData;
}


//------------------------------------------------------------------------------
// Return name of categories in StringList container
//------------------------------------------------------------------------------
QStringList EditServicesForm::getListCategories()
{
    QStringList categories;

    QMapIterator<QString, QString> i(*m_pServiceCategories);
    while (i.hasNext()) {
        i.next();
        categories << i.key();
    }

    return categories;
}


//------------------------------------------------------------------------------
// Add customer name to form
//------------------------------------------------------------------------------
void EditServicesForm::addCustomerNameToForm(QString customerName)
{
    ui->lineCustomer->setText(customerName);
}


//------------------------------------------------------------------------------
// Add customer phone to form
//------------------------------------------------------------------------------
void EditServicesForm::addCustomerPhoneToForm(QString customerPhone)
{
    ui->linePhone->setText(customerPhone);
}


//------------------------------------------------------------------------------
// Add service order date to form
//------------------------------------------------------------------------------
void EditServicesForm::addOrderDateToForm()
{
    QDate orderServiceDate = QDate::fromString(m_serviceTableData["orderServiceDate"], "dd.MM.yyyy");
    ui->calendarOrderService->setSelectedDate(orderServiceDate);
}


//------------------------------------------------------------------------------
// Add service execution date to form
//------------------------------------------------------------------------------
void EditServicesForm::addExecutionDateToForm()
{
    QDate executionServiceDate = QDate::fromString(m_serviceTableData["executionServiceDate"], "dd.MM.yyyy");
    ui->calendarExecutionService->setSelectedDate(executionServiceDate);
}


//------------------------------------------------------------------------------
// Add list categories to form and set current one
//------------------------------------------------------------------------------
void EditServicesForm::addCategoriesToForm()
{
    QString currentCategory = m_pServiceCategories->key(m_serviceTableData["serviceCategoryID"]);
    ui->comboServiceCategory->addItems(getListCategories());
    ui->comboServiceCategory->setCurrentText(currentCategory);
}


//------------------------------------------------------------------------------
// Add service description to form
//------------------------------------------------------------------------------
void EditServicesForm::addServiceDescriptionToForm()
{
    ui->plainDescription->setPlainText(m_serviceTableData["orderDescription"]);
}


//------------------------------------------------------------------------------
// Add service cost to form
//------------------------------------------------------------------------------
void EditServicesForm::addServiceCostToForm()
{
    ui->lineSum->setText(m_serviceTableData["serviceSum"]);
}


//------------------------------------------------------------------------------
// DESTRUCTOR
// Destroys the object and frees any allocated resources
//------------------------------------------------------------------------------
EditServicesForm::~EditServicesForm()
{
    delete ui;
}

