#include "db.h"



/******************************************************************************
 * Class: DBDestroyer
 * Purpose: automatically destroys class DB after end of the program
 ******************************************************************************/



//------------------------------------------------------------------------------
// Initialize the member for destroy
//------------------------------------------------------------------------------
void DBDestroyer::initialize(DB *db)
{
    m_pInstance = db;
}


//------------------------------------------------------------------------------
// DESTRUCTOR
// Destroys member 'm_pInstance' that refers to instance
// of class 'DB' after end of the program
//------------------------------------------------------------------------------
DBDestroyer::~DBDestroyer()
{
   delete m_pInstance;
}



/******************************************************************************
 * Class: DB
 * Purpose: provides the opportunity to work with database
 * Feature: returns single instance of the class
 ******************************************************************************/



//------------------------------------------------------------------------------
// CONSTRUCTOR
//------------------------------------------------------------------------------
DB::DB(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase("QMYSQL");
    m_pSettings = new DBSettings;

    connectToDB();

    m_pQuery = new QSqlQuery;
}


//------------------------------------------------------------------------------
// Сonnected to a database of transferred parameters
//------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------
// Сonnected to a database with standard parameters
//------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------
// Returns configuration database
//------------------------------------------------------------------------------
DBSettings *DB::getSettings()
{
    return m_pSettings;
}


//------------------------------------------------------------------------------
// Returns user name with 'login' and 'password'
// else returns 'NULL'
//------------------------------------------------------------------------------
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


//------------------------------------------------------------------------------
// Returns single instance of current class
//------------------------------------------------------------------------------
DB *DB::instance()
{
    if (!m_pInstance) {
        m_pInstance = new DB();
        m_destroyer.initialize(m_pInstance);
    }

    return m_pInstance;
}


//------------------------------------------------------------------------------
// Creates query to database and set rusults in 'model'
//------------------------------------------------------------------------------
bool DB::query(QString &query,
               QStringList &arguments,
               QSqlQueryModel *model)
{
    // set current type object query and current model
    if (model->objectName() == "salesModel") {
        m_typeObjectsQuery = qSqlQueryModelForSales;
        m_pModelSales = model;
    } else if (model->objectName() == "servicesModel") {
        m_typeObjectsQuery = qSqlQueryModelForServices;
        m_pModelServices = model;
    }

    bool status = false;

    if (arguments.size() <= 0) {
        status = queryWithoutParameters(query, model);
    } else {
        status = queryWithParameters(query, arguments, model);
    }

    return status;
}


bool DB::queryWithoutParameters(QString &query, QSqlQueryModel *model)
{
    model->setQuery(query);
    return model->lastError().isValid();
}


bool DB::queryWithParameters(QString &query,
                             QStringList &arguments,
                             QSqlQueryModel *model)
{
    return false;
}


//------------------------------------------------------------------------------
// Creates query to database
//------------------------------------------------------------------------------
bool DB::query(QString &query, QStringList &arguments)
{
    m_typeObjectsQuery = qSqlQuery;

    bool status = false;

    if (arguments.size() <= 0) {
        status = queryWithoutParameters(query);
    } else {
        status = queryWithParameters(query, arguments);
    }

    return status;
}


//------------------------------------------------------------------------------
// Creates query to database without parameters
//------------------------------------------------------------------------------
bool DB::query(QString &query)
{
    m_typeObjectsQuery = qSqlQuery;

    bool statusOk = queryWithoutParameters(query);

    if(!statusOk) {
        return false;
    }

    return true;
}


bool DB::queryWithoutParameters(QString &query)
{
    m_pQuery->exec(query);

    if (m_pQuery->size() <= 0) {
        qDebug() << m_pQuery->lastQuery();
        return false;
    }

    return true;
}


bool DB::queryWithParameters(QString &query, QStringList &arguments)
{
    m_pQuery->prepare(query);
    foreach (QString arg, arguments) {
        m_pQuery->addBindValue(arg);
    }

    if (!m_pQuery->exec()) {
        return false;
    }

    return true;
}


//------------------------------------------------------------------------------
// Returns last error database
//------------------------------------------------------------------------------
QSqlError DB::lastError() const
{
    switch (m_typeObjectsQuery) {
        case qSqlQueryModelForSales:
            return m_pModelSales->lastError();
            break;
        case qSqlQueryModelForServices:
            return m_pModelServices->lastError();
            break;
        case qSqlQuery:
            return m_pQuery->lastError();
            break;
        default:
            return NULL;
            break;
    }
}


//------------------------------------------------------------------------------
// Returns last insert id
//------------------------------------------------------------------------------
QVariant DB::lastInsertId() const
{
    return m_pQuery->lastInsertId();
}


//------------------------------------------------------------------------------
// Returns selected data from qury
//------------------------------------------------------------------------------
QSqlQuery *DB::getData() const
{
    return m_pQuery;
}


//------------------------------------------------------------------------------
// DESTRUCTOR
//------------------------------------------------------------------------------
DB::~DB()
{
    delete m_pSettings;
}

//-----------------------------------------------------------------------------
DB *DB::m_pInstance;
DBDestroyer DB::m_destroyer;
