#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql>

class DB : public QObject
{
    Q_OBJECT
public:
    static DB *instance();
    bool connectToDB(QString databaseName = "accounting",
                 QString userName = "root",
                 QString password = "",
                 QString hostName = "localhost");
    QSqlQueryModel *getAllSales();
    QSqlQueryModel *getAllServices();
    ~DB();

signals:

public slots:

private:
    bool setHeaderModelSales();
    bool setHeaderModelServices();

    explicit DB(QObject *parent = 0);
    static DB *m_instance;
    QSqlDatabase *m_db;
    QSqlQueryModel *m_modelSales;
    QSqlQueryModel *m_modelServices;
};

#endif // DB_H
