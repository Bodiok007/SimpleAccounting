#ifndef EDITSERVICESFORM_H
#define EDITSERVICESFORM_H

#include <QtWidgets>

namespace Ui {
class EditServicesForm;
}

class EditServicesForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditServicesForm(QWidget *parent = 0);
    ~EditServicesForm();

public slots:
    void addDataToForm(uint serviceID);
    void saveEditData();

private:
    Ui::EditServicesForm *ui;
    QMap<QString, QString> m_generalData;
    uint m_serviceID;

    void clearEditForm();
};

#endif // EDITSERVICESFORM_H
