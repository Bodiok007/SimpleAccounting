#include "servicesmodel.h"


//------------------------------------------------------------------------------
// CONSTRUCTOR
//------------------------------------------------------------------------------
ServicesModel::ServicesModel(QWidget *parent) : QObject(parent)
{
    m_pServicesModel = new QSqlQueryModel(this);
}


//------------------------------------------------------------------------------
// Get model with the data from DB
//------------------------------------------------------------------------------
QSqlQueryModel *ServicesModel::getModel()
{
    m_pServicesModel->setQuery(
                "SELECT provideservices.provideServicesID, "
                    "servicecategories.serviceCategoryName, "
                    "provideservices.orderDescription, "
                    "employees.employeeName, "
                    "customers.customerName, "
                    "customers.customerPhone, "
                    "provideservices.orderServiceDate, "
                    "provideservices.executionServiceDate, "
                    "provideservices.serviceSum "
                "FROM provideservices "

                "LEFT JOIN servicecategories "
                "ON servicecategories.serviceCategoryID "
                    "= provideservices.serviceCategoryID "

                "LEFT JOIN customers "
                "ON customers.customerID "
                    "= provideservices.customerID "

                "LEFT JOIN employees "
                "ON employees.employeeID "
                    "= provideservices.employeeID;"

                );

    if (!setHeaderModelServices()) {
        qDebug() << "Can`t create header model services!";
    }

    return m_pServicesModel;
}


//------------------------------------------------------------------------------
// Set headers in the services model
//------------------------------------------------------------------------------
bool ServicesModel::setHeaderModelServices()
{
    if(!m_pServicesModel) {
        return false;
    }

    QStringList headers;
    headers << "ID"
            << "Категорія"
            << "Опис"
            << "Працівник"
            << "Замовник"
            << "Телефон"
            << "Дата замовлення"
            << "Дата виконання"
            << "Вартість, грн";

    int numHeaderCeil = headers.count();

    for (int currentHeaderColumn = 0;
         currentHeaderColumn < numHeaderCeil;
         ++currentHeaderColumn) {

       m_pServicesModel->setHeaderData(currentHeaderColumn
                                       , Qt::Horizontal
                                       , headers.at(currentHeaderColumn));
    }

    return true;
}


//------------------------------------------------------------------------------
// DESTRUCTOR
//------------------------------------------------------------------------------
ServicesModel::~ServicesModel()
{
    delete m_pServicesModel;
}
