#ifndef ADDSERVICEFORM_H
#define ADDSERVICEFORM_H

#include <QWidget>

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

private:
    Ui::AddServiceForm *ui;
    QString m_employeeName;
};

#endif // ADDSERVICEFORM_H
