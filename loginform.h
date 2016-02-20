#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QtWidgets>


namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

    QPushButton *getLoginButton();
    void message(QString text);

    void setSettingsDB();

public slots:
    void pressLoginButton();
    void saveSettings();

signals:
    void logged(QString userName);
    void changeSettings();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
