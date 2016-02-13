#ifndef EDITSALESFORM_H
#define EDITSALESFORM_H

#include <QtWidgets>

namespace Ui {
class EditSalesForm;
}

class EditSalesForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditSalesForm(QWidget *parent = 0);
    ~EditSalesForm();

public slots:
    void addDataToForm(uint saleID);
    void saveEditData();

signals:
    void updateSalesData();

private:
    Ui::EditSalesForm *ui;
    uint m_saleID;
    QMap<QString, QString> *m_pSaleCategories;
    QMap<QString, QString> m_saleTableData;

    bool getSaleTableData(uint serviceID);
    void setSaleTableData();
    QMap<QString, QString> *getProductTableData(QString productID);

    QStringList getListCategories();

    void message(QString text);
    void clearEditForm();

    void addCategoriesToForm();
    void addSaleDateToForm();
    void addProductToForm(QString productID);
    void addProductNameToForm(QString productName);
    void addProductCostToForm(QString productCost);
    void addProductCountToForm();

    bool updateProduct();
};

#endif // EDITSALESFORM_H
