#ifndef ADDSALE_H
#define ADDSALE_H

#include <QtWidgets>

class AddSale : public QGroupBox
{
    Q_OBJECT
public:
    AddSale(QWidget *parent = 0);
	~AddSale();

signals:
    void updateSalesData();

public slots:
    void addSale();
    void setEmployeeName(QString employeeName);

private:
    QLineEdit *m_pNameProduct;
    QComboBox *m_pCategoryProduct;
    QLineEdit *m_pCountProduct;
    QLineEdit *m_pPriceProduct;
    QPushButton *m_pAddSale;
    QGridLayout *m_pGridLayout;

	QIcon *m_pIcon;

	QIntValidator *m_pIntValidator;

    QString m_employeeName;

    QMap<QString, QString> *m_pSaleCategories;
    QStringList getListCategories();

    void createLabels();
    void createFields();
    void createAddButton();
    void clearFields();

    void message(QString text);

    bool emptyEnterFromUser();
    bool addProduct();
    uint getEmployeeID();
    QString getCurrentData();
};

#endif // ADDSALE_H
