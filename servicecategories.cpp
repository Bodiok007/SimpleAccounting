#include "servicecategories.h"
#include "DB/db.h"



/******************************************************************************
 * Class: ServiceCategoriesDestroyer
 * Purpose: automatically destroy class ServiceCategories
 * after end of the program
 ******************************************************************************/



//------------------------------------------------------------------------------
// Initialize the member for destroy
//------------------------------------------------------------------------------
void ServiceCategoriesDestroyer::initialize(ServiceCategories *serviceCategories)
{
    m_pInstance = serviceCategories;
}


//------------------------------------------------------------------------------
// DESTRUCTOR
// Destroys member 'm_pInstance' that refers to instance
// of class 'ServiceCategories' after end of the program
//------------------------------------------------------------------------------
ServiceCategoriesDestroyer::~ServiceCategoriesDestroyer()
{
    delete m_pInstance;
}



/******************************************************************************
 * Class: ServiceCategories
 * Purpose: provides the opportunity to receive service categories
 * Feature: returns single instance of the class
 ******************************************************************************/



//------------------------------------------------------------------------------
// CONSTRUCTOR
//------------------------------------------------------------------------------
ServiceCategories::ServiceCategories()
{
    bool statusOk = getServiceCategoriesFromDB();
    if (!statusOk) {
        message("Неможливо отримати категорії послуг!");
    }
}


//------------------------------------------------------------------------------
// Returns single instance of current class
//------------------------------------------------------------------------------
ServiceCategories *ServiceCategories::instance()
{
    if (!m_pInstance) {
        m_pInstance = new ServiceCategories();
        m_destroyer.initialize(m_pInstance);
    }

    return m_pInstance;
}


//------------------------------------------------------------------------------
// Create a query to get all data from 'servicecategories' table
//------------------------------------------------------------------------------
bool ServiceCategories::getServiceCategoriesFromDB()
{
    QString query = "SELECT servicecategories.serviceCategoryName, "
                        "servicecategories.serviceCategoryID "
                    "FROM servicecategories";
    bool statusOk = DB::instance()->query(query);

    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        return false;
    }

    setServiceCategories();

    return true;
}


//------------------------------------------------------------------------------
// Set selected data from 'servicecategories' table
// to map 'm_serviceCategiriesData',
// where the keys - name of categories, values - id of categories
//------------------------------------------------------------------------------
void ServiceCategories::setServiceCategories()
{
    QSqlQuery *serviceCategoriesData = DB::instance()->getData();

    while (serviceCategoriesData->next()) {
        QString categoryName = serviceCategoriesData->value(0).toString();
        QString categoryID = serviceCategoriesData->value(1).toString();
        m_serviceCategiriesData[categoryName] = categoryID;
    }
}


//------------------------------------------------------------------------------
// Return service categories contains in map 'm_serviceCategiriesData'
//------------------------------------------------------------------------------
QMap<QString, QString> *ServiceCategories::getCategories()
{
    return &m_serviceCategiriesData;
}


//------------------------------------------------------------------------------
// Create a message window
//------------------------------------------------------------------------------
void ServiceCategories::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


//------------------------------------------------------------------------------
// DESTRUCTOR
// Destroys the object and frees any allocated resources
//------------------------------------------------------------------------------
ServiceCategories::~ServiceCategories()
{
}

ServiceCategories *ServiceCategories::m_pInstance = NULL;
ServiceCategoriesDestroyer ServiceCategories::m_destroyer;

