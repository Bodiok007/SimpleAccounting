#include "salecategories.h"
#include <QtSql>
#include "DB/db.h"



/******************************************************************************
 * Class: SaleCategoriesDestroyer
 * Purpose: automatically destroys class SaleCategories after end of the program
 ******************************************************************************/



//------------------------------------------------------------------------------
// Initialize the member for destroy
//------------------------------------------------------------------------------
void SaleCategoriesDestroyer::initialize(SaleCategories *saleCategories)
{
    m_pInstance = saleCategories;
}


//------------------------------------------------------------------------------
// DESTRUCTOR
// Destroys member 'm_pInstance' that refers to instance
// of class 'SaleCategories' after end of the program
//------------------------------------------------------------------------------
SaleCategoriesDestroyer::~SaleCategoriesDestroyer()
{
    delete m_pInstance;
}



/******************************************************************************
 * Class: SaleCategories
 * Purpose: provides the opportunity to receive sale categories
 * Feature: returns single instance of the class
 ******************************************************************************/



//------------------------------------------------------------------------------
// CONSTRUCTOR
//------------------------------------------------------------------------------
SaleCategories::SaleCategories()
{
    bool statusOk = getSaleCategoriesFromDB();
    if (!statusOk) {
        message("Неможливо отримати категорії послуг!");
    }
}


//------------------------------------------------------------------------------
// Returns single instance of current class
//------------------------------------------------------------------------------
SaleCategories *SaleCategories::instance()
{
    if (!m_pInstance) {
        m_pInstance = new SaleCategories;
        m_destroyer.initialize(m_pInstance);
    }

    return m_pInstance;
}


//------------------------------------------------------------------------------
// Create a query to get all data from 'salecategories' table
//------------------------------------------------------------------------------
bool SaleCategories::getSaleCategoriesFromDB()
{
    QString query = "SELECT salecategories.saleCategoryName, "
                        "salecategories.saleCategoryID "
                    "FROM salecategories";
    bool statusOk = DB::instance()->query(query);

    if (!statusOk) {
        qDebug() << DB::instance()->lastError();
        return false;
    }

    setSaleCategories();

    return true;
}


//------------------------------------------------------------------------------
// Set selected data from 'salecategories' table
// to map 'm_saleCategiriesData',
// where the keys - name of categories, values - id of categories
//------------------------------------------------------------------------------
void SaleCategories::setSaleCategories()
{
    QSqlQuery *saleCategoriesData = DB::instance()->getData();

    while (saleCategoriesData->next()) {
        QString categoryName = saleCategoriesData->value(0).toString();
        QString categoryID = saleCategoriesData->value(1).toString();
        m_saleCategiriesData[categoryName] = categoryID;
    }
}


//------------------------------------------------------------------------------
// Return service categories contains in map 'm_saleCategiriesData'
//------------------------------------------------------------------------------
QMap<QString, QString> *SaleCategories::getCategories()
{
    return &m_saleCategiriesData;
}


//------------------------------------------------------------------------------
// Create a message window
//------------------------------------------------------------------------------
void SaleCategories::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


//------------------------------------------------------------------------------
// DESTRUCTOR
//------------------------------------------------------------------------------
SaleCategories::~SaleCategories()
{
}

//------------------------------------------------------------------------------
SaleCategories *SaleCategories::m_pInstance = NULL;
SaleCategoriesDestroyer SaleCategories::m_destroyer;
