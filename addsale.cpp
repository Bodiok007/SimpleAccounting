#include "addsale.h"
#include "DB/db.h"
#include "salecategories.h"

AddSale::AddSale(QWidget *parent)
    : QGroupBox(parent)
{
    m_pSaleCategories = SaleCategories::instance()->getCategories();

    m_pGridLayout = new QGridLayout;

	m_pIntValidator = new QIntValidator;

    createLabels();
    createFields();
    createAddButton();

    setLayout(m_pGridLayout);

    setAttribute(Qt::WA_ShowModal);
    setWindowTitle("Додавання продажі");

	m_pIcon = new QIcon(":/logo.png");

    connect(m_pAddSale,
            SIGNAL(clicked(bool)),
            this,
            SLOT(addSale())
           );

}


void AddSale::createLabels()
{
    QLabel *lb1 = new QLabel("Назва товару");
    QLabel *lb2 = new QLabel("Категорія");
    QLabel *lb3 = new QLabel("Кількість");
    QLabel *lb4 = new QLabel("Вартість одиниці");

    m_pGridLayout->addWidget(lb1, 0, 0);
    m_pGridLayout->addWidget(lb2, 0, 1);
    m_pGridLayout->addWidget(lb3, 0, 2);
    m_pGridLayout->addWidget(lb4, 0, 3);

}


void AddSale::createFields()
{
    m_pNameProduct = new QLineEdit;
    m_pCategoryProduct = new QComboBox;
    m_pCategoryProduct->addItems(getListCategories());
    m_pCountProduct = new QLineEdit;
	m_pCountProduct->setValidator(m_pIntValidator);
    m_pPriceProduct = new QLineEdit;
	m_pPriceProduct->setValidator(m_pIntValidator);

    m_pGridLayout->addWidget(m_pNameProduct, 1, 0);
    m_pGridLayout->addWidget(m_pCategoryProduct, 1, 1);
    m_pGridLayout->addWidget(m_pCountProduct, 1, 2);
    m_pGridLayout->addWidget(m_pPriceProduct, 1, 3);
}


void AddSale::createAddButton()
{
    m_pAddSale = new QPushButton;
    m_pAddSale->resize(15, 25);
    m_pAddSale->setText("Додати");

    m_pGridLayout->addWidget(m_pAddSale, 2, 3);
}


void AddSale::clearFields()
{
    m_pCountProduct->clear();
    m_pNameProduct->clear();
    m_pPriceProduct->clear();
}


void AddSale::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


bool AddSale::addProduct()
{
    QString query = "INSERT INTO products (productName, productCost) "
                    "VALUES (?, ?) ";
    QStringList arguments;
    arguments << m_pNameProduct->text()
              << m_pPriceProduct->text();

    bool statusOk = DB::instance()->query(query, arguments);
    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        message("Помилка при додаванні товару!");
        return false;
    }

    return true;
}


uint AddSale::getEmployeeID()
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


QString AddSale::getCurrentData()
{
    QDate dateToday = QDate::currentDate();
    return dateToday.toString("dd.MM.yyyy");
}


bool AddSale::emptyEnterFromUser()
{
    if (m_pNameProduct->text() != ""
          && m_pPriceProduct->text() != ""
          && m_pCountProduct->text() != ""){

        return false;
    }

    return true;
}


void AddSale::addSale()
{
    if (emptyEnterFromUser()) {
        message("Заповніть, будь ласка, всі поля!");
        return;
    }

    if (!addProduct()) {
        return;
    }
    uint productID = DB::instance()->lastInsertId().toUInt();

    uint employeeID = getEmployeeID();
    if (employeeID == 0) {
        return;
    }

    QString saleCategoryID = (*m_pSaleCategories)[m_pCategoryProduct->currentText()];

    double saleSum = m_pPriceProduct->text().toDouble() * m_pCountProduct->text().toDouble();

    QString query(
              "INSERT INTO sales "
                  "(employeeID, "
                  "saleCategoryID, "
                  "productID, "
                  "productCount, "
                  "saleDate, "
                  "saleSum) "
              "VALUES (?, ?, ?, ?, ?, ?) "
              );
    QStringList arguments;
    arguments << QString::number(employeeID)
              << saleCategoryID
              << QString::number(productID)
              << m_pCountProduct->text()
              << getCurrentData()
              << QString::number(saleSum);

    bool statusOk = DB::instance()->query(query, arguments);
    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        message("Помилка додавання продажі!");
    }

    emit updateSalesData();

    clearFields();

    hide();
}


void AddSale::setEmployeeName(QString employeeName)
{
    m_employeeName = employeeName;
}


QStringList AddSale::getListCategories()
{
    QStringList categories;

    QMapIterator<QString, QString> i(*m_pSaleCategories);
    while (i.hasNext()) {
        i.next();
        categories << i.key();
    }

    return categories;
}


AddSale::~AddSale()
{
	delete m_pIntValidator;
	delete m_pIcon;
}
