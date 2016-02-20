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

signals:
    void updateServicesData();

private:
    Ui::EditServicesForm *ui;
    QMap<QString, QString> m_serviceTableData;
    uint m_serviceID;
    QMap<QString, QString> *m_pServiceCategories;
	QDoubleValidator *m_pDoubleValidator;

    void message(QString text);
    void clearEditForm();


    bool getServiceTableData(uint serviceID);
    void setServiceTableData();
    QMap<QString, QString> *getCustomerTableData(QString customerID);

    QStringList getListCategories();

    void addServiceCustomerDataToForm(uint customerID);
    void addServiceDescriptionToForm();
    void addServiceCostToForm();
    void addCustomerToForm(QString customerID);
    void addCustomerNameToForm(QString customerName);
    void addCustomerPhoneToForm(QString customerPhone);
    void addOrderDateToForm();
    void addExecutionDateToForm();
    void addCategoriesToForm();

    bool updateCustomer();
};

#endif // EDITSERVICESFORM_H
