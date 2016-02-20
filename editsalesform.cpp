#include "editsalesform.h"
#include "ui_editsalesform.h"
#include "DB/db.h"
#include "salecategories.h"


//------------------------------------------------------------------------------
// CONSTRUCTOR
//------------------------------------------------------------------------------
EditSalesForm::EditSalesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditSalesForm)
{
    ui->setupUi(this);

	m_pDoubleValidator = new QDoubleValidator;
	ui->lineProductCost->setValidator(m_pDoubleValidator);
	m_pIntValidator = new QIntValidator;
	ui->lineProductCount->setValidator(m_pIntValidator);

    setAttribute(Qt::WA_ShowModal);

    connect(ui->buttonSaveEditSale,
            SIGNAL(clicked(bool)),
            SLOT(saveEditData())
           );
    m_pSaleCategories = SaleCategories::instance()->getCategories();
}


EditSalesForm::~EditSalesForm()
{
    delete ui;
	delete m_pDoubleValidator;
	delete m_pIntValidator;
}


//------------------------------------------------------------------------------
// Add data from DB to form
// 'saleID' get from selected field in 'SalesTableView'
//------------------------------------------------------------------------------
void EditSalesForm::addDataToForm(uint saleID)
{
    clearEditForm();
    show();
    m_saleID = saleID;

    getSaleTableData(m_saleID);

    addSaleDateToForm();

    // add list categories and set current one
    addCategoriesToForm();

    // add product name, cost and count
    addProductToForm(m_saleTableData["productID"]);
}


void EditSalesForm::saveEditData()
{
    qDebug() << "edit button sale ok";
    /*DB::instance()->saveEditSale(m_saleID,
                                 ui->comboSaleCategory->currentText(),
                                 m_generalData["productID"].toUInt(),
                                 ui->lineProductName->text(),
                                 ui->calendarSale->selectedDate().toString("dd.MM.yyyy"),
                                 ui->lineProductCount->text().toInt(),
                                 ui->lineProductCost->text().toDouble()
                                );*/
    bool ok = updateProduct();
    if (!ok) {
        message("Неможливо змінити дані про продукт");
        hide();
        return;
    }

    double saleSum = ui->lineProductCost->text().toDouble() * ui->lineProductCount->text().toDouble();

    QString query = "UPDATE sales SET "
                        "saleCategoryID = ?, "
                        "productCount = ?, "
                        "saleDate = ?, "
                        "saleSum = ? "
                    "WHERE saleID = ? ";
    QStringList arguments;
    arguments << m_pSaleCategories->value(ui->comboSaleCategory->currentText())
              << ui->lineProductCount->text()
              << ui->calendarSale->selectedDate().toString("dd.MM.yyyy")
              << QString::number(saleSum)
              << QString::number(m_saleID);

    bool statusOk = DB::instance()->query(query, arguments);

    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        qDebug() << "Can`t save edit sale data";
        hide();
        return;
    }

    emit updateSalesData();

    hide();
}


bool EditSalesForm::updateProduct()
{
    QString query = "UPDATE products SET "
                        "productName = ?, "
                        "productCost = ? "
                    "WHERE productID = ? ";
    QStringList arguments;
    arguments << ui->lineProductName->text()
              << ui->lineProductCost->text()
              << m_saleTableData["productID"];

    bool statusOk = DB::instance()->query(query, arguments);

    if (!statusOk) {
        qDebug() << "Can`t update product!";
        qDebug() << DB::instance()->lastError();
        return false;
    }

    return true;
}


bool EditSalesForm::getSaleTableData(uint serviceID)
{
    QString query = "SELECT productID, "
                        "saleCategoryID, "
                        "productCount, "
                        "saleDate "
                    "FROM sales "
                    "WHERE saleID = ?";
    QStringList arguments(QString::number(serviceID));

    bool statusOk = DB::instance()->query(query, arguments);

    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        return false;
    }

    setSaleTableData();

    return true;
}

void EditSalesForm::setSaleTableData()
{
    QStringList fieldNames;
    fieldNames << "productID"
               << "saleCategoryID"
               << "productCount"
               << "saleDate";

    QSqlQuery *saleData = DB::instance()->getData();

    saleData->next();

    for (int currentField = 0;
         currentField < fieldNames.size();
         ++currentField) {

        m_saleTableData[fieldNames.at(currentField)]
                = saleData->value(currentField).toString();
    }
}




QStringList EditSalesForm::getListCategories()
{
    QStringList categories;

    QMapIterator<QString, QString> i(*m_pSaleCategories);
    while (i.hasNext()) {
        i.next();
        categories << i.key();
    }

    return categories;
}


//------------------------------------------------------------------------------
// Create a message window
//------------------------------------------------------------------------------
void EditSalesForm::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


//------------------------------------------------------------------------------
// Clear fields on form
//------------------------------------------------------------------------------
void EditSalesForm::clearEditForm()
{
    ui->comboSaleCategory->clear();
}


//------------------------------------------------------------------------------
// Add list categories to form and set current one
//------------------------------------------------------------------------------
void EditSalesForm::addCategoriesToForm()
{
    QString currentCategory = m_pSaleCategories->key(m_saleTableData["saleCategoryID"]);
    ui->comboSaleCategory->addItems(getListCategories());
    ui->comboSaleCategory->setCurrentText(currentCategory);
}


//------------------------------------------------------------------------------
// Add sale date to form
//------------------------------------------------------------------------------
void EditSalesForm::addSaleDateToForm()
{
    QDate saleData = QDate::fromString(m_saleTableData["saleDate"], "dd.MM.yyyy");
    ui->calendarSale->setSelectedDate(saleData);
}


//------------------------------------------------------------------------------
// Set selected data from 'sales' table to map 'm_saleTableData'
// where the keys - name of fields
//------------------------------------------------------------------------------
QMap<QString, QString> *EditSalesForm::getProductTableData(QString productID)
{
    QString query = "SELECT productName, productCost "
                    "FROM products "
                    "WHERE productID = ? ";
    QStringList arguments(productID);

    bool statusOk = DB::instance()->query(query, arguments);

    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        return NULL;
    }

    QSqlQuery *productDataFromTabel = DB::instance()->getData();
    productDataFromTabel->next();

    QMap<QString, QString> *productData = new QMap<QString, QString>;
    (*productData)["productName"] = productDataFromTabel->value(0).toString();
    (*productData)["productCost"] = productDataFromTabel->value(1).toString();

    return productData;
}


//------------------------------------------------------------------------------
// Add data about current saled product to form
//------------------------------------------------------------------------------
void EditSalesForm::addProductToForm(QString productID)
{
    QMap<QString, QString> *productData = getProductTableData(productID);

    if (!productData) {
        return;
    }

    addProductNameToForm((*productData)["productName"]);
    addProductCostToForm((*productData)["productCost"]);
    addProductCountToForm();

    delete productData;
}


//------------------------------------------------------------------------------
// Add product name to form
//------------------------------------------------------------------------------
void EditSalesForm::addProductNameToForm(QString productName)
{
    ui->lineProductName->setText(productName);
}


//------------------------------------------------------------------------------
// Add product cost to form
//------------------------------------------------------------------------------
void EditSalesForm::addProductCostToForm(QString productCost)
{
    ui->lineProductCost->setText(productCost);
}


//------------------------------------------------------------------------------
// Add count saled product to form
//------------------------------------------------------------------------------
void EditSalesForm::addProductCountToForm()
{
    ui->lineProductCount->setText(m_saleTableData["productCount"]);
}

