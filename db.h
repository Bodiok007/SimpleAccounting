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
    QMap<QString, unsigned int> *getSaleCategories();

    QStringList getListSaleCategories();
    QStringList getListServiceCategories();

    void addSale(QString productName,
                 QString categoryName,
                 QString employeeName,
                 double productCount,
                 double productCost);

    void addService(QString customerName,
                    QString customerPhone,
                    QString employeeName,
                    QString categoryName,
                    QString orderDescription,
                    double serviceSum);

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
    bool setHeaderModelSales();
    bool setHeaderModelServices();

    bool getSaleCategoriesFromDB();
    bool getServiceCategoriesFromDB();

    unsigned int addProduct(QString productName,
                            double productCost);
    unsigned int addCustomer(QString customerName,
                             QString customerPhone);

    QString getCurrentDate();
    unsigned int getCurrentEmployeeID(QString employeeName);

    DBSettings *m_pSettings;
    QSqlQuery *m_pQuery;

    explicit DB(QObject *parent = 0);
    static DB *m_instance;
    QSqlDatabase m_db;
    QSortFilterProxyModel *m_pProxyModelSales;
    QSortFilterProxyModel *m_pProxyModelServices;
    QSqlQueryModel *m_pModelSales;
    QSqlQueryModel *m_pModelServices;

    QMap<QString, unsigned int> m_saleCategories;
    QMap<QString, unsigned int> m_serviceCategories;
};

#endif // DB_H
