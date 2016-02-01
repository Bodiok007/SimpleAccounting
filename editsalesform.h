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

private:
    Ui::EditSalesForm *ui;
    QMap<QString, QString> m_generalData;
    uint m_saleID;

    void clearEditForm();
};

#endif // EDITSALESFORM_H
