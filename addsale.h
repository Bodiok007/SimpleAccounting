#ifndef ADDSALE_H
#define ADDSALE_H

#include <QtWidgets>

class AddSale : public QGroupBox
{
public:
    AddSale(QWidget *parent);

signals:

public slots:

private:
    QLineEdit *m_pNameProduct;
    QLineEdit *m_pCategoryProduct;
    QLineEdit *m_pCountProduct;
    QLineEdit *m_pPriceProduct;
    QPushButton *m_pAddSale;
    QGridLayout *m_pGridLayout;

    void initializeComponents();
    void createLabels();
    void createEditLines();
    void createAddButton();
};

#endif // ADDSALE_H
