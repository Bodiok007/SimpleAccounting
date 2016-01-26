#include "db.h"

DB::DB(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_pSettings = new DBSettings;

    connectToDB();

    m_pModelSales = new QSqlQueryModel;
    m_pProxyModelSales = new QSortFilterProxyModel;

    m_pModelServices = new QSqlQueryModel;
    m_pProxyModelServices = new QSortFilterProxyModel;
}


bool DB::connectToDB(QString databaseName,
                 QString userName,
                 QString password,
                 QString hostName)
{
    m_db.setDatabaseName(databaseName);
    m_db.setUserName(userName);
    m_db.setHostName(hostName);
    m_db.setPassword(password);

    if (!m_db.open()) {
        qDebug() << "Cannot open database [DB class]:" << m_db.lastError()
                 << m_pSettings->getDatabaseName();
        return false;
    }

    return true;
}


bool DB::connectToDB()
{
    m_db.setDatabaseName(m_pSettings->getDatabaseName());
    m_db.setUserName(m_pSettings->getUserName());
    m_db.setHostName(m_pSettings->getHostName());
    m_db.setPassword(m_pSettings->getPassword());

    if (!m_db.open()) {
        qDebug() << "Cannot open database [DB class]:" << m_db.lastError()
                 << m_pSettings->getDatabaseName();
        return false;
    }

    return true;
}


DBSettings *DB::getSettings()
{
    return m_pSettings;
}


QString DB::logIn(QString login, QString password)
{
    QSqlQuery query;
    query.prepare(
                "SELECT employeeName FROM employees "
                "WHERE employeeLogin = ? "
                "AND employeePassword = ?"
                );
    query.addBindValue(login);
    query.addBindValue(password);
    query.exec();

    if (query.size() <= 0) {
        return NULL;
    }

    query.next();
    QString userName = query.value(0).toString();

    return userName;
}


QSortFilterProxyModel *DB::getAllSales()
{
    m_pModelSales->setQuery(
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
        qDebug() << "Can`t create header model sales!";
    }

    m_pProxyModelSales->setSourceModel(m_pModelSales);

    return m_pProxyModelSales;
}


// set header for each column model sales
bool DB::setHeaderModelSales()
{
    if(!m_pModelSales) {
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

       m_pModelSales->setHeaderData(currentHeaderColumn
                                   , Qt::Horizontal
                                   , lst.at(currentHeaderColumn));
    }

    return true;
}


QSqlQueryModel *DB::getAllServices()
{
    m_pModelServices->setQuery(
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
        qDebug() << "Can`t create header model services!";
    }

    return m_pModelServices;
}

// set header for each column model services
bool DB::setHeaderModelServices()
{
    if(!m_pModelServices) {
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
       m_pModelServices->setHeaderData(currentHeaderColumn,
                                       Qt::Horizontal,
                                       lst.at(currentHeaderColumn));
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
    delete m_pModelSales;
    delete m_pModelServices;
    delete m_pSettings;
    delete m_instance;
}



