#include "editsalesform.h"
#include "ui_editsalesform.h"
#include "db.h"

EditSalesForm::EditSalesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditSalesForm)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_ShowModal);

    connect(ui->buttonSaveEditSale,
            SIGNAL(clicked(bool)),
            SLOT(saveEditData())
           );
}

EditSalesForm::~EditSalesForm()
{
    delete ui;
}

void EditSalesForm::addDataToForm(uint saleID)
{
    clearEditForm();
    m_saleID = saleID;

    m_generalData = DB::instance()->getCurrentSaleData(saleID);
    qDebug() << m_generalData["saleDate"];

    QDate saleData = QDate::fromString(m_generalData["saleDate"], "dd.MM.yyyy");
    ui->calendarSale->setSelectedDate(saleData);

    QString currentCategory = DB::instance()->getSaleCategoryNameByID(m_generalData["productCategoryID"].toUInt());
    ui->comboSaleCategory->addItems(DB::instance()->getListSaleCategories());
    ui->comboSaleCategory->setCurrentText(currentCategory);

    QStringList productsData = DB::instance()->getSaleProductsDataByID(m_generalData["productID"].toUInt());
    ui->lineProductName->setText(productsData.at(0));
    ui->lineProductCost->setText(productsData.at(1));
    ui->lineProductCount->setText(m_generalData["productCount"]);
}

void EditSalesForm::saveEditData()
{
    qDebug() << "edit button sale ok";
    DB::instance()->saveEditSale(m_saleID,
                                 ui->comboSaleCategory->currentText(),
                                 m_generalData["productID"].toUInt(),
                                 ui->lineProductName->text(),
                                 ui->calendarSale->selectedDate().toString("dd.MM.yyyy"),
                                 ui->lineProductCount->text().toInt(),
                                 ui->lineProductCost->text().toDouble()
                                );
    hide();
}

void EditSalesForm::clearEditForm()
{
     ui->comboSaleCategory->clear();
     //ui->lineProductCost->clear();
     //ui->lineProductCount->clear();
     //ui->lineProductName->clear();
}
