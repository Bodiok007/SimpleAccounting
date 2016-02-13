#include "salesmodel.h"
#include "db.h"

//------------------------------------------------------------------------------
// CONSTRUCTOR
//------------------------------------------------------------------------------
SalesModel::SalesModel(QObject *parent) : QObject(parent)
{
    m_pSalesModel = new QSqlQueryModel(this);
}


//------------------------------------------------------------------------------
// Get model with the data from DB
//------------------------------------------------------------------------------
QSqlQueryModel *SalesModel::getModel()
{
    m_pSalesModel->setQuery(
                "SELECT sales.saleID, "
                    "products.productName, "
                    "salecategories.saleCategoryName, "
                    "employees.employeeName, "
                    "sales.productCount, "
                    "sales.saleDate, "
                    "products.productCost, "
                    "sales.saleSum "
                "FROM sales "

                "LEFT JOIN products "
                "ON products.productID "
                    "= sales.productID "

                "LEFT JOIN salecategories "
                "ON salecategories.saleCategoryID "
                    "= sales.saleCategoryID "

                "LEFT JOIN employees "
                "ON employees.employeeID "
                    "= sales.employeeID;"
                );

    if (m_pSalesModel->lastError().isValid()) {
        qDebug() << "Can`t get sale model " << m_pSalesModel->lastError();
    }

    setHeaderModelSales();


    return m_pSalesModel;
}


//------------------------------------------------------------------------------
// Set headers in the sales model
//------------------------------------------------------------------------------
void SalesModel::setHeaderModelSales()
{
    if(!m_pSalesModel) {
        qDebug() << "Sales model empty! Can`t create header model sales!";
        return;
    }

    QStringList lst;
    lst << "ID"
        << "Товар"
        << "Категорія"
        << "Продавець"
        << "Кількість"
        << "Дата продажі"
        << "Вартість одиниці, грн"
        << "Загальна сума, грн";

    int numHeaderColumn = lst.size();

    for (int currentHeaderColumn = 0;
         currentHeaderColumn < numHeaderColumn;
         ++currentHeaderColumn) {

       m_pSalesModel->setHeaderData(currentHeaderColumn
                                   , Qt::Horizontal
                                   , lst.at(currentHeaderColumn));
    }
}


//------------------------------------------------------------------------------
// DESTRUCTOR
//------------------------------------------------------------------------------
SalesModel::~SalesModel()
{
    delete m_pSalesModel;
}

