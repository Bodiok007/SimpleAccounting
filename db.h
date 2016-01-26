#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql>
#include "dbsettings.h"

/*
 * Bug in QT 5.5.0
 * QSqlDatabase::open() always return true
 *
 */

class DB : public QObject
{
    Q_OBJECT
public:
    static DB *instance();

    QSortFilterProxyModel *getAllSales();
    QSqlQueryModel *getAllServices();
    ~DB();

signals:

public slots:
    bool connectToDB(QString databaseName,
                 QString userName,
                 QString password,
                 QString hostName);
    bool connectToDB();

    DBSettings *getSettings();

    QString logIn(QString login, QString password);

private:
    bool setHeaderModelSales();
    bool setHeaderModelServices();

    DBSettings *m_pSettings;

    explicit DB(QObject *parent = 0);
    static DB *m_instance;
    QSqlDatabase m_db;
    QSortFilterProxyModel *m_pProxyModelSales;
    QSortFilterProxyModel *m_pProxyModelServices;
    QSqlQueryModel *m_pModelSales;
    QSqlQueryModel *m_pModelServices;
};

#endif // DB_H
