#ifndef SALECATEGORY_H
#define SALECATEGORY_H

#include <QtWidgets>


class SaleCategories;


class SaleCategoriesDestroyer
{
public:
    void initialize(SaleCategories* saleCategories);
    ~SaleCategoriesDestroyer();
private:
    SaleCategories *m_pInstance;
};


class SaleCategories
{
public:
    static SaleCategories *instance();
    QMap<QString, QString> *getCategories();

private:
    static SaleCategories *m_pInstance;
    static SaleCategoriesDestroyer m_destroyer;

    friend class SaleCategoriesDestroyer;

    SaleCategories();
    SaleCategories(const SaleCategories&);
    SaleCategories& operator=(SaleCategories&);
    ~SaleCategories();

    QMap<QString, QString> m_saleCategiriesData;
    bool getSaleCategoriesFromDB();
    void setSaleCategories();
    void message(QString text);
};

#endif // SALECATEGORY_H
