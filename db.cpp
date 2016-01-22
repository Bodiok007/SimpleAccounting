#include "db.h"

DB::DB(QObject *parent) : QObject(parent)
{
    m_db = &QSqlDatabase::addDatabase("QMYSQL");
    connectToDB();
    m_modelSales = new QSqlQueryModel;
    m_modelServices = new QSqlQueryModel;
}


bool DB::connectToDB(QString databaseName,
                 QString userName ,
                 QString password ,
                 QString hostName )
{
    m_db->setDatabaseName(databaseName);
    m_db->setUserName(userName);
    m_db->setHostName(hostName);
    m_db->setPassword(password);

    if (!m_db->open()) {
        qDebug() << "Cannot open database [DB class]:" << m_db->lastError() << databaseName;
        return false;
    }

    return true;
}


QSqlQueryModel *DB::getAllSales()
{
    m_modelSales->setQuery(
                "SELECT products.productName, "
                    "productcategories.productCategoryName, "
                    "employees.employeeName, "
                    "sales.productCount, "
                    "sales.saleData, "
                    "sales.saleSum "
                "FROM sales "

                "LEFT JOIN products "
                "ON products.productID "
                    "= sales.productID "

                "LEFT JOIN productcategories "
                "ON productcategories.productCategoryID "
                    "= sales.productCategoryID "

                "LEFT JOIN employees "
                "ON employees.employeeID "
                    "= sales.employeeID;"
                );

    if (!setHeaderModelSales()) {
        qDebug() << "Can not create header model sales!";
    }

    return m_modelSales;
}


// set header for each column model sales
bool DB::setHeaderModelSales()
{
    if(!m_modelSales) {
        return false;
    }

    QStringList lst;
    lst << "Товар"
        << "Категорія"
        << "Продавець"
        << "Кількість"
        << "Дата продажі"
        << "Вартість, грн";

    int numHeaderColumn = lst.size();

    for (int currentHeaderColumn = 0;
         currentHeaderColumn < numHeaderColumn;
         ++currentHeaderColumn) {

       m_modelSales->setHeaderData(currentHeaderColumn
                                   , Qt::Horizontal
                                   , lst.at(currentHeaderColumn));
    }

    return true;
}


QSqlQueryModel *DB::getAllServices()
{
    m_modelServices->setQuery(
                "SELECT servicecategories.serviceCategoryName, "
                    "provideservices.orderDescription, "
                    "employees.employeeName, "
                    "customers.customerName, "
                    "customers.customerPhone, "
                    "provideservices.orderServiceData, "
                    "provideservices.executionServiceData, "
                    "provideservices.serviceSum "
                "FROM provideservices "

                "LEFT JOIN servicecategories "
                "ON servicecategories.serviceCategoryID "
                    "= provideservices.serviceCategoryID "

                "LEFT JOIN customers "
                "ON customers.customerID "
                    "= provideservices.customerID "

                "LEFT JOIN employees "
                "ON employees.employeeID "
                    "= provideservices.employeeID;"

                );

    if (!setHeaderModelServices()) {
        qDebug() << "Can not create header model services!";
    }

    return m_modelServices;
}

// set header for each column model services
bool DB::setHeaderModelServices()
{
    if(!m_modelServices) {
        return false;
    }

    QStringList lst;
    lst << "Категорія"
        << "Опис"
        << "Працівник"
        << "Замовник"
        << "Телефон"
        << "Дата замовлення"
        << "Дата виконання"
        << "Вартість, грн";

    int numHeaderCeil = lst.count();

    for (int currentHeaderColumn = 0;
         currentHeaderColumn < numHeaderCeil;
         ++currentHeaderColumn) {
       m_modelServices->setHeaderData(currentHeaderColumn
                                   , Qt::Horizontal
                                   , lst.at(currentHeaderColumn));
    }

    return true;
}


DB *DB::instance()
{
    return m_instance ? m_instance : (m_instance = new DB);
}

DB *DB::m_instance;


DB::~DB()
{
    delete m_modelSales;
    delete m_modelServices;
    delete m_db;
    delete m_instance;
}



