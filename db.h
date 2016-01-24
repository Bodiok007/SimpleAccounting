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
    QSortFilterProxyModel *getAllSales();
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
    QSortFilterProxyModel *m_pProxyModelSales;
    QSortFilterProxyModel *m_pProxyModelServices;
    QSqlQueryModel *m_pModelSales;
    QSqlQueryModel *m_pModelServices;
};

#endif // DB_H
