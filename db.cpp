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

    m_pQuery = new QSqlQuery;

    getSaleCategoriesFromDB();
    getServiceCategoriesFromDB();
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
    m_pQuery->prepare(
                "SELECT employeeName FROM employees "
                "WHERE employeeLogin = ? "
                "AND employeePassword = ?"
                );
    m_pQuery->addBindValue(login);
    m_pQuery->addBindValue(password);
    m_pQuery->exec();

    if (m_pQuery->size() <= 0) {
        return NULL;
    }

    m_pQuery->next();
    QString userName = m_pQuery->value(0).toString();

    return userName;
}


QMap<QString, uint> *DB::getSaleCategories()
{
    return &m_saleCategories;
}


QStringList DB::getListSaleCategories()
{
    QStringList categories;

    QMapIterator<QString, uint> i(m_saleCategories);
    while (i.hasNext()) {
        i.next();
        categories << i.key();
    }

    return categories;
}

QStringList DB::getListServiceCategories()
{
    QStringList categories;

    QMapIterator<QString, uint> i(m_serviceCategories);
    while (i.hasNext()) {
        i.next();
        categories << i.key();
    }

    return categories;
}

QString DB::getSaleCategoryNameByID(uint categoryID)
{
    return m_saleCategories.key(categoryID);
}

QString DB::getServiceCategoryNameByID(uint categoryID)
{
    return m_serviceCategories.key(categoryID);
}

QStringList DB::getSaleProductsDataByID(uint productID)
{
    m_pQuery->prepare(
                "SELECT productName, productCost "
                "FROM products "
                "WHERE productID = ? "
                );
    m_pQuery->addBindValue(productID);


    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastQuery();
        qDebug() << m_pQuery->lastError();
        //return QStringList t;
    }

    m_pQuery->next();

    QStringList productsData;
    productsData << m_pQuery->value(0).toString()
                 << m_pQuery->value(1).toString();

    return productsData;
}

QStringList DB::getServiceCustomerDataByID(uint customerID)
{
    m_pQuery->prepare(
                "SELECT customerName, customerPhone "
                "FROM customers "
                "WHERE customerID = ? "
                );
    m_pQuery->addBindValue(customerID);

    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastQuery();
        qDebug() << m_pQuery->lastError();
    }

    m_pQuery->next();

    QStringList custmersData;
    custmersData << m_pQuery->value(0).toString()
                 << m_pQuery->value(1).toString();

    return custmersData;
}

QMap<QString, QString> &DB::getCurrentSaleData(uint saleID)
{
    getCurrentSaleDataFromDB(saleID);
    return m_currentSaleData;
}

QMap<QString, QString> &DB::getCurrentServiceData(uint serviceID)
{
    getCurrentServiceDataFromDB(serviceID);
    return m_currentServiceData;
}

void DB::addSale(QString productName,
                 QString categoryName,
                 QString employeeName,
                 double productCount,
                 double productCost)
{
    uint productID = addProduct(productName, productCost);
    if (productID == NULL) {
        qDebug() << m_pQuery->lastQuery();
        return;
    }

    double saleSum = productCount * productCost;

    uint employeeID = getCurrentEmployeeID(employeeName);
    if (employeeID == NULL) {
        qDebug() << m_pQuery->lastQuery();
        return;
    }

    m_pQuery->prepare(
                "INSERT INTO sales "
                    "(employeeID, "
                    "productCategoryID, "
                    "productID, "
                    "productCount, "
                    "saleDate, "
                    "saleSum) "
                "VALUES (?, ?, ?, ?, ?, ?) "
                );
    m_pQuery->addBindValue(employeeID);
    m_pQuery->addBindValue(m_saleCategories[categoryName]);
    m_pQuery->addBindValue(productID);
    m_pQuery->addBindValue(productCount);
    m_pQuery->addBindValue(getCurrentDate());
    m_pQuery->addBindValue(saleSum);


    if (!m_pQuery->exec()) {
        qDebug() << productCount << " "
                 << productCost << " "
                 << m_saleCategories[productName];
        qDebug() << m_pQuery->lastError();
        qDebug() << m_pQuery->lastQuery();
    }

    emit updateSalesData();

}


void DB::addService(QString customerName,
                    QString customerPhone,
                    QString employeeName,
                    QString categoryName,
                    QString orderDescription,
                    double serviceSum)
{
    uint customerID = addCustomer(customerName, customerPhone);
    if (customerID == NULL) {
        qDebug() << m_pQuery->lastQuery();
        return;
    }

    uint employeeID = getCurrentEmployeeID(employeeName);
    if (employeeID == NULL) {
        qDebug() << m_pQuery->lastQuery();
        return;
    }

    m_pQuery->prepare(
                "INSERT INTO provideservices "
                    "(serviceCategoryID, "
                    "employeeID, "
                    "customerID, "
                    "orderDescription, "
                    "orderServiceDate, "
                    "executionServiceDate, "
                    "serviceSum) "
                "VALUES (?, ?, ?, ?, ?, ?, ?) "
                );
    m_pQuery->addBindValue(m_serviceCategories[categoryName]);
    m_pQuery->addBindValue(employeeID);
    m_pQuery->addBindValue(customerID);
    m_pQuery->addBindValue(orderDescription);
    m_pQuery->addBindValue(getCurrentDate());
    m_pQuery->addBindValue("");
    m_pQuery->addBindValue(serviceSum);

    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastError();
        qDebug() << m_pQuery->lastQuery();
        return;
    }

    emit updateServicesData();
}

bool DB::saveEditSale(uint saleID,
                     QString productCategoryName,
                     uint productID,
                     QString productName,
                     QString saleDate,
                     int productCount,
                     double productCost)
{
    bool ok = updateProduct(productID, productName, productCost);
    if (!ok) {
        qDebug() << "Can`t update product";
    }

    m_pQuery->prepare(
                "UPDATE sales SET "
                    "productCategoryID = ?, "
                    "productCount = ?, "
                    "saleDate = ?, "
                    "saleSum = ? "
                "WHERE saleID = ? "
                );
    m_pQuery->addBindValue(m_saleCategories[productCategoryName]);
    m_pQuery->addBindValue(productCount);
    m_pQuery->addBindValue(saleDate);
    m_pQuery->addBindValue(productCount * productCost);
    m_pQuery->addBindValue(saleID);

    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastError();
        qDebug() << "Can`t save edit data";
        return false;
    }

    emit updateSalesData();

    return true;
}

bool DB::saveEditService(uint serviceID,
                         QString serviceCategoryName,
                         uint customerID,
                         QString customerName,
                         QString customerPhone,
                         QString orderDescription,
                         QString orderServiceDate,
                         QString executionServiceDate,
                         double serviceSum)
{
    bool ok = updateCustomer(customerID, customerName, customerPhone);
    if (!ok) {
        qDebug() << "Can`t update customer";
    }

    m_pQuery->prepare(
                "UPDATE provideServices SET "
                    "serviceCategoryID = ?, "
                    "orderDescription = ?, "
                    "orderServiceDate = ?, "
                    "executionServiceDate = ?, "
                    "serviceSum = ? "
                "WHERE provideServicesID = ? "
                );
    m_pQuery->addBindValue(m_serviceCategories[serviceCategoryName]);
    m_pQuery->addBindValue(orderDescription);
    m_pQuery->addBindValue(orderServiceDate);
    m_pQuery->addBindValue(executionServiceDate);
    m_pQuery->addBindValue(serviceSum);
    m_pQuery->addBindValue(serviceID);

    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastError();
        qDebug() << m_pQuery->lastQuery();
        qDebug() << "Can`t save edit data";
        return false;
    }

    emit updateServicesData();

    return true;
}


uint DB::addProduct(QString productName,
                            double productCost)
{
    m_pQuery->prepare(
                "INSERT INTO products (productName, productCost) "
                "VALUES (?, ?) "
                );
    m_pQuery->addBindValue(productName);
    m_pQuery->addBindValue(productCost);

    if (m_pQuery->exec()) {
        return m_pQuery->lastInsertId().toUInt();
    }

    qDebug() << m_pQuery->lastQuery();

    return NULL;
}


uint DB::addCustomer(QString customerName,
                             QString customerPhone)
{
    m_pQuery->prepare(
                "INSERT INTO customers (customerName, customerPhone) "
                "VALUES (?, ?) "
                );
    m_pQuery->addBindValue(customerName);
    m_pQuery->addBindValue(customerPhone);

    if (m_pQuery->exec()) {
        return m_pQuery->lastInsertId().toUInt();
    }

    qDebug() << m_pQuery->lastQuery();

    return NULL;
}


bool DB::updateProduct(uint productID,
                       QString productName,
                       double productCost)
{
    m_pQuery->prepare(
                    "UPDATE products SET "
                        "productName = ?, "
                        "productCost = ? "
                    "WHERE productID = ? "
                    );
    m_pQuery->addBindValue(productName);
    m_pQuery->addBindValue(productCost);
    m_pQuery->addBindValue(productID);

    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastQuery();
        qDebug() << m_pQuery->lastError();
        return false;
    }

    return true;
}


bool DB::updateCustomer(uint customerID,
                        QString customerName,
                        QString customerPhone)
{
    m_pQuery->prepare(
                    "UPDATE customers SET "
                        "customerName = ?, "
                        "customerPhone = ? "
                    "WHERE customerID = ? "
                    );
    m_pQuery->addBindValue(customerName);
    m_pQuery->addBindValue(customerPhone);
    m_pQuery->addBindValue(customerID);

    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastQuery();
        qDebug() << m_pQuery->lastError();
        return false;
    }

    return true;
}


QString DB::getCurrentDate()
{
    QDate dateToday = QDate::currentDate();
    return dateToday.toString("dd.MM.yyyy");
}


uint DB::getCurrentEmployeeID(QString employeeName)
{
    m_pQuery->prepare(
                "SELECT employeeID FROM employees "
                "WHERE employeeName = ? "
                );
    m_pQuery->addBindValue(employeeName);
    m_pQuery->exec();

    if (m_pQuery->size() <= 0) {
        qDebug() << m_pQuery->lastQuery();
        qDebug() << m_pQuery->lastError();
        return NULL;
    }

    m_pQuery->next();
    uint employeeID = m_pQuery->value(0).toUInt();

    return employeeID;
}


bool DB::getSaleCategoriesFromDB()
{
    m_pQuery->exec(
                "SELECT productcategories.productCategoryName, "
                    "productcategories.productCategoryID "
                "FROM productcategories"
                );

    if (m_pQuery->size() <= 0) {
        qDebug() << m_pQuery->lastQuery();
        return NULL;
    }

    while (m_pQuery->next()) {
        QString categoryName = m_pQuery->value(0).toString();
        uint categoryID = m_pQuery->value(1).toUInt();
        m_saleCategories[categoryName] = categoryID;
    }

    return &m_saleCategories;
}


bool DB::getServiceCategoriesFromDB()
{
    m_pQuery->exec(
                "SELECT servicecategories.serviceCategoryName, "
                    "servicecategories.serviceCategoryID "
                "FROM servicecategories"
                );

    if (m_pQuery->size() <= 0) {
        qDebug() << m_pQuery->lastQuery();
        return NULL;
    }

    while (m_pQuery->next()) {
        QString categoryName = m_pQuery->value(0).toString();
        uint categoryID = m_pQuery->value(1).toUInt();
        m_serviceCategories[categoryName] = categoryID;
    }

    return &m_serviceCategories;
}


bool DB::getCurrentSaleDataFromDB(uint saleID)
{
    m_pQuery->prepare(
                "SELECT productID, "
                    "productCategoryID, "
                    "productCount, "
                    "saleDate "
                "FROM sales "
                "WHERE saleID = ?"
                );
    m_pQuery->addBindValue(saleID);

    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastQuery();
        qDebug() << m_pQuery->lastError();
        return false;
    }

    setCurrentSaleDataFromDB();

    return true;
}


void DB::setCurrentSaleDataFromDB()
{
    QStringList fieldNames;
    fieldNames << "productID"
               << "productCategoryID"
               << "productCount"
               << "saleDate";

    m_pQuery->next();

    for (int currentField = 0;
         currentField < fieldNames.size();
         ++currentField) {

        m_currentSaleData[fieldNames.at(currentField)]
                = m_pQuery->value(currentField).toString();
    }
}


bool DB::getCurrentServiceDataFromDB(uint serviceID)
{
    m_pQuery->prepare(
                "SELECT serviceCategoryID, "
                    "customerID, "
                    "orderDescription, "
                    "orderServiceDate, "
                    "executionServiceDate, "
                    "serviceSum "
                "FROM provideservices "
                "WHERE provideServicesID = ?"
                );
    m_pQuery->addBindValue(serviceID);

    if (!m_pQuery->exec()) {
        qDebug() << m_pQuery->lastQuery();
        qDebug() << m_pQuery->lastError();
        return false;
    }

    setCurrentServiceDataFromDB();

    return true;
}


void DB::setCurrentServiceDataFromDB()
{
    QStringList fieldNames;
    fieldNames << "serviceCategoryID"
               << "customerID"
               << "orderDescription"
               << "orderServiceDate"
               << "executionServiceDate"
               << "serviceSum";

    m_pQuery->next();

    for (int currentField = 0;
         currentField < fieldNames.size();
         ++currentField) {

        m_currentServiceData[fieldNames.at(currentField)]
                = m_pQuery->value(currentField).toString();
    }
}


QSortFilterProxyModel *DB::getAllSales()
{
    m_pModelSales->setQuery(
                "SELECT sales.saleID, "
                    "products.productName, "
                    "productcategories.productCategoryName, "
                    "employees.employeeName, "
                    "sales.productCount, "
                    "sales.saleDate, "
                    "products.productCost, "
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

       m_pModelSales->setHeaderData(currentHeaderColumn
                                   , Qt::Horizontal
                                   , lst.at(currentHeaderColumn));
    }

    return true;
}


QSqlQueryModel *DB::getAllServices()
{
    m_pModelServices->setQuery(
                "SELECT provideservices.provideServicesID, "
                    "servicecategories.serviceCategoryName, "
                    "provideservices.orderDescription, "
                    "employees.employeeName, "
                    "customers.customerName, "
                    "customers.customerPhone, "
                    "provideservices.orderServiceDate, "
                    "provideservices.executionServiceDate, "
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
    lst << "ID"
        << "Категорія"
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

       m_pModelServices->setHeaderData(currentHeaderColumn
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
    delete m_pModelSales;
    delete m_pModelServices;
    delete m_pSettings;
    delete m_instance;
}



