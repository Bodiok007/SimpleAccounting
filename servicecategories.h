#ifndef SERVICECATEGORIES_H
#define SERVICECATEGORIES_H

#include <QtWidgets>

class ServiceCategories;


class ServiceCategoriesDestroyer
{
public:
    ~ServiceCategoriesDestroyer();
    void initialize(ServiceCategories* serviceCategories);

private:
    ServiceCategories* m_pInstance;
};


class ServiceCategories
{
public:
    static ServiceCategories *instance();
    QMap<QString, QString> *getCategories();

private:
    static ServiceCategories *m_pInstance;
    static ServiceCategoriesDestroyer m_destroyer;

    friend class ServiceCategoriesDestroyer;

    ServiceCategories();
    ServiceCategories(const ServiceCategories&);
    ServiceCategories& operator=(ServiceCategories&);
    ~ServiceCategories();

    QMap<QString, QString> m_serviceCategiriesData;
    bool getServiceCategoriesFromDB();
    void setServiceCategories();
    void message(QString text);
};

#endif // SERVICECATEGORIES_H
