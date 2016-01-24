#include "addsale.h"

AddSale::AddSale(QWidget *parent)
    : QGroupBox(parent)
{
    m_pGridLayout = new QGridLayout;

    createLabels();

    createEditLines();

    createAddButton();

    setLayout(m_pGridLayout);

    setAttribute(Qt::WA_ShowModal);
}

void AddSale::initializeComponents()
{

}

void AddSale::createLabels()
{
    QLabel *lb1 = new QLabel("Назва товару");
    QLabel *lb2 = new QLabel("Категорія");
    QLabel *lb3 = new QLabel("Кількість");
    //QLabel *lb3 = new QLabel("Дата продажі");
    QLabel *lb4 = new QLabel("Вартість одиниці");

    m_pGridLayout->addWidget(lb1, 0, 0);
    m_pGridLayout->addWidget(lb2, 0, 1);
    m_pGridLayout->addWidget(lb3, 0, 2);
    m_pGridLayout->addWidget(lb4, 0, 3);

}

void AddSale::createEditLines()
{
    m_pNameProduct = new QLineEdit;
    //m_pNameProduct->resize(25, 25);
    m_pCategoryProduct = new QLineEdit;
    m_pCountProduct = new QLineEdit;
    m_pPriceProduct = new QLineEdit;

    m_pGridLayout->addWidget(m_pNameProduct, 1, 0);
    m_pGridLayout->addWidget(m_pCategoryProduct, 1, 1);
    m_pGridLayout->addWidget(m_pCountProduct, 1, 2);
    m_pGridLayout->addWidget(m_pPriceProduct, 1, 3);
}

void AddSale::createAddButton()
{
    m_pAddSale = new QPushButton;
    m_pAddSale->resize(15, 25);
    m_pAddSale->setText("Додати");

    m_pGridLayout->addWidget(m_pAddSale, 2, 3);

}

