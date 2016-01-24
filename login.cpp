#include "login.h"

LoginWgt::LoginWgt(QWidget *parent)
    : QGroupBox(parent)
{
    QLineEdit *login = new QLineEdit;
    QLabel *labelLogin = new QLabel("Логін:");
    labelLogin->setBuddy(login);

    QLineEdit *password = new QLineEdit;
    QLabel *labelPassword = new QLabel("Пароль:");
    labelPassword->setBuddy(password);

    QVBoxLayout *layOut = new QVBoxLayout;
    layOut->addWidget(labelLogin);
    layOut->addWidget(login);
    layOut->addWidget(labelPassword);
    layOut->addWidget(password);

    setLayout(layOut);
}

void LoginWgt::createFields()
{

}

