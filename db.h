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
    QMap<QString, uint> *getSaleCategories();

    QStringList getListSaleCategories();
    QStringList getListServiceCategories();

    QString getSaleCategoryNameByID(uint categoryID);
    QString getServiceCategoryNameByID(uint categoryID);
    QStringList getSaleProductsDataByID(uint productID);
    QStringList getServiceCustomerDataByID(uint customerID);

    QMap<QString, QString> &getCurrentSaleData(uint saleID);
    QMap<QString, QString> &getCurrentServiceData(uint serviceID);


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

    bool saveEditSale(uint saleID,
                      QString productCategoryName,
                      uint productID,
                      QString productName,
                      QString saleDate,
                      int productCount,
                      double productCost);

    bool saveEditService(uint serviceID,
                         QString serviceCategoryName,
                         uint customerID,
                         QString customerName,
                         QString customerPhone,
                         QString orderDescription,
                         QString orderServiceDate,
                         QString executionServiceDate,
                         double serviceSum
                        );

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

    bool getCurrentSaleDataFromDB(uint saleID);
    void setCurrentSaleDataFromDB();
    bool getCurrentServiceDataFromDB(uint serviceID);
    void setCurrentServiceDataFromDB();

    uint addProduct(QString productName,
                    double productCost);
    uint addCustomer(QString customerName,
                     QString customerPhone);

    bool updateProduct(uint productID,
                       QString productName,
                       double productCost);
    bool updateCustomer(uint customerID,
                        QString customerName,
                        QString customerPhone);

    QString getCurrentDate();
    uint getCurrentEmployeeID(QString employeeName);

    DBSettings *m_pSettings;
    QSqlQuery *m_pQuery;

    explicit DB(QObject *parent = 0);
    static DB *m_instance;
    QSqlDatabase m_db;
    QSortFilterProxyModel *m_pProxyModelSales;
    QSortFilterProxyModel *m_pProxyModelServices;
    QSqlQueryModel *m_pModelSales;
    QSqlQueryModel *m_pModelServices;

    QMap<QString, uint> m_saleCategories;
    QMap<QString, uint> m_serviceCategories;

    QMap<QString, QString> m_currentSaleData;
    QMap<QString, QString> m_currentServiceData;
};

#endif // DB_H
