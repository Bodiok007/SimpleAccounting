#ifndef ADDSERVICEFORM_H
#define ADDSERVICEFORM_H

#include <QtWidgets>

namespace Ui {
class AddServiceForm;
}

class AddServiceForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddServiceForm(QWidget *parent = 0);
    ~AddServiceForm();

public slots:
    void addService();
    void setEmployeeName(QString employeeName);

signals:
    void updateServicesData();

private:
    Ui::AddServiceForm *ui;
    QString m_employeeName;
    QMap<QString, QString> *m_pServiceCategories;
	QDoubleValidator *m_pDoubleValidator;

    void message(QString text);

    bool emptyEnterFromUser();

    void setCategories();
    QStringList getListCategories();

    uint getEmployeeID();
    bool addCustomer(QString customerName,
                     QString customerPhone);
    QString getCurrentData();
};

#endif // ADDSERVICEFORM_H
