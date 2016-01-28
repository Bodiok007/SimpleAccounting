#ifndef ADDSALE_H
#define ADDSALE_H

#include <QtWidgets>

class AddSale : public QGroupBox
{
    Q_OBJECT
public:
    AddSale(QWidget *parent);

signals:

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

    QString m_employeeName;

    void createLabels();
    void createFields();
    void createAddButton();
};

#endif // ADDSALE_H
