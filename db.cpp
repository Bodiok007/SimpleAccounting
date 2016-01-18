#include "db.h"

DB::DB(QObject *parent) : QObject(parent)
{
    connect();
}

bool DB::connect(QString databaseName,
                 QString userName ,
                 QString password ,
                 QString hostName )
{
    m_db->setDatabaseName(databaseName);
    m_db->setUserName(userName);
    m_db->setHostName(hostName);
    m_db->setPassword(password);
    if (!m_db->open()) {
        qDebug() << "Cannot open database [DB class]:" << m_db->lastError();
        return false;
    }
    return true;
}

DB *DB::instance()
{
    return m_instance ? m_instance : (m_instance = new DB);
}

DB *DB::m_instance;



