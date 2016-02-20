#include "addserviceform.h"
#include "ui_addserviceform.h"
#include "DB/db.h"
#include "servicecategories.h"


AddServiceForm::AddServiceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddServiceForm)
{
    ui->setupUi(this);

	m_pDoubleValidator = new QDoubleValidator;
	ui->lineServiceSum->setValidator(m_pDoubleValidator);

    setAttribute(Qt::WA_ShowModal);

    connect(ui->addServiceButton,
            SIGNAL(clicked(bool)),
            SLOT(addService()));

    m_pServiceCategories = ServiceCategories::instance()->getCategories();
    setCategories();
}


AddServiceForm::~AddServiceForm()
{
    delete ui;
	delete m_pDoubleValidator;
}


bool AddServiceForm::emptyEnterFromUser()
{
    if (ui->lineCustomerName->text() != ""
          && ui->lineCustomerPhone->text() != "") {

        return false;
    }

    return true;
}


void AddServiceForm::addService()
{
    if (emptyEnterFromUser()) {
        message("Заповніть, будь ласка, поля імені і телефону замовника!");
        return;
    }
    uint employeeID = getEmployeeID();
    if (employeeID == 0) {
        message("Помилка під час отримання даних про працівнака! "
                "Операція додавання послуги відмінена!");
        return;
    }

    if (!addCustomer(ui->lineCustomerName->text(),
                     ui->lineCustomerPhone->text())) {
        return;
    }
    QString customerID = DB::instance()->lastInsertId().toString();

    QString query = "INSERT INTO provideservices "
                        "(serviceCategoryID, "
                        "employeeID, "
                        "customerID, "
                        "orderDescription, "
                        "orderServiceDate, "
                        "executionServiceDate, "
                        "serviceSum) "
                    "VALUES (?, ?, ?, ?, ?, ?, ?) ";
    QStringList arguments;
    arguments << m_pServiceCategories->value(ui->comboServiceCategory->currentText())
              << QString::number(employeeID)
              << customerID
              << ui->lineServiceDescription->toPlainText()
              << getCurrentData()
              << ""
              << ui->lineServiceSum->text();

    bool statusOk = DB::instance()->query(query, arguments);
    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        message("Не вдалося додати послугу!");
    }

    emit updateServicesData();

    hide();
}


bool AddServiceForm::addCustomer(QString customerName,
                                 QString customerPhone)
{
    QString query = "INSERT INTO customers (customerName, customerPhone) "
                    "VALUES (?, ?) ";
    QStringList arguments;
    arguments << customerName
              << customerPhone;

    bool statusOk = DB::instance()->query(query, arguments);
    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        message("Помилка при додаванні замовника!");
        return false;
    }

    return true;
}


QString AddServiceForm::getCurrentData()
{
    QDate dateToday = QDate::currentDate();
    return dateToday.toString("dd.MM.yyyy");
}


void AddServiceForm::setEmployeeName(QString employeeName)
{
    m_employeeName = employeeName;
}


void AddServiceForm::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


void AddServiceForm::setCategories()
{
    ui->comboServiceCategory->addItems(getListCategories());
}


QStringList AddServiceForm::getListCategories()
{
    QStringList categories;

    QMapIterator<QString, QString> i(*m_pServiceCategories);
    while (i.hasNext()) {
        i.next();
        categories << i.key();
    }

    return categories;
}


uint AddServiceForm::getEmployeeID()
{
    QStringList arguments(m_employeeName);
    QString query = "SELECT employeeID FROM employees "
                    "WHERE employeeName = ? ";

    bool statusOk = DB::instance()->query(query, arguments);
    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        message("Помилка отримання ідентифікатора користувача!");
        return NULL;
    }

    QSqlQuery *data = DB::instance()->getData();
    data->next();
    uint employeeID = data->value(0).toUInt();

    return employeeID;
}
