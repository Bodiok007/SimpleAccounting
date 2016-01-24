#ifndef LOGIN_H
#define LOGIN_H

#include <QtWidgets>

class LoginWgt : public QGroupBox
{
    Q_OBJECT
public:
    LoginWgt(QWidget *parent);
    void createFields();

signals:

public slots:

private:
    //QLineEdit *login;
    //QLineEdit *password;
};

#endif // LOGIN_H
