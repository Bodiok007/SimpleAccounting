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

class DB;

class DBDestroyer
{
private:
    DB* m_pInstance;
public:
    ~DBDestroyer();
    void initialize(DB* db);
};


enum TypeObjectsQuery { qSqlQueryModelForSales, qSqlQueryModelForServices, qSqlQuery };


class DB : public QObject
{
    Q_OBJECT
public:
    static DB *instance();

    bool query(QString &query,
               QStringList &arguments,
               QSqlQueryModel *model);

    bool query(QString &query,
               QStringList &arguments);

    bool query(QString &query);

    QSqlError lastError() const;
    QVariant lastInsertId() const;
    QSqlQuery *getData() const;

    ~DB();

signals:
    void updateSalesData();
    void updateServicesData();

public slots:
    bool connectToDB(QString databaseName,
                     QString userName,
                     QString password,
                     QString hostName);
    bool connectToDB();

    DBSettings *getSettings();

    QString logIn(QString login, QString password);

private:
    explicit DB(QObject *parent = 0);

    static DB *m_pInstance;
    static DBDestroyer m_destroyer;

    friend class DBDestroyer;

    QSqlDatabase m_db;
    DBSettings *m_pSettings;
    QSqlQuery *m_pQuery;

    QSqlQueryModel *m_pModelSales;
    QSqlQueryModel *m_pModelServices;

    TypeObjectsQuery m_typeObjectsQuery;

    bool queryWithoutParameters(QString &query,
                                QSqlQueryModel *model);

    bool queryWithParameters(QString &query,
                             QStringList &arguments,
                             QSqlQueryModel *model);

    bool queryWithoutParameters(QString &query);

    bool queryWithParameters(QString &query,
                             QStringList &arguments);
};

#endif // DB_H
