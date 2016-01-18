#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql>

class DB : public QObject
{
    Q_OBJECT
public:
    static DB *instance();
    bool connect(QString databaseName = "accounting",
                 QString userName = "root",
                 QString password = "",
                 QString hostName = "localhost");


signals:

public slots:

private:
    explicit DB(QObject *parent = 0);
    static DB *m_instance;
    QSqlDatabase *m_db;
    QSqlQueryModel *m_modelSales;
    QSqlQueryModel *m_modelServices;
};

#endif // DB_H
