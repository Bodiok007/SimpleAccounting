#include "loginform.h"
#include "ui_loginform.h"
#include "db.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    connect(getLoginButton(),
            SIGNAL(clicked(bool)),
            SLOT(pressLoginButton())
           );

    // save parameters
    connect(ui->buttonSaveSettings,
            SIGNAL(clicked(bool)),
            SLOT(saveSettings())
           );

    // reconnect to DB with new parameter
    connect(this,
            SIGNAL(changeSettings()),
            DB::instance(),
            SLOT(connectToDB())
           );

    setSettingsDB();

    ui->toolBox->setCurrentIndex(0);
}


QPushButton *LoginForm::getLoginButton()
{
    return ui->buttonEnter;
}


void LoginForm::pressLoginButton()
{
    QString login = ui->lineLogin->text().replace(" ", "");
    QString password = ui->linePassword->text().replace(" ", "");

    if (login == "" || password == "") {
        message("Заповніть, будь ласка, поля логіна та пароля!");
        return;
    }

    QString userName = "";
    if ((userName = DB::instance()->logIn(login, password)) == NULL) {
        message("Користувач не знайдений! "
                "Перевірте, будь ласка, логін та пароль!");
        return;
    }

    emit logged(userName);

    this->hide();
    ui->linePassword->setText("");
}


void LoginForm::message(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}


void LoginForm::setSettingsDB()
{
    DBSettings *settings = DB::instance()->getSettings();
    ui->lineNameDB->setText(settings->getDatabaseName());
    ui->lineNameUserDB->setText(settings->getUserName());
    ui->linePasswordUserDB->setText(settings->getPassword());
    ui->lineHostDB->setText(settings->getHostName());
}


void LoginForm::saveSettings()
{
    DB::instance()->getSettings()->writeSettings(
                                        ui->lineNameDB->text(),
                                        ui->lineNameUserDB->text(),
                                        ui->linePasswordUserDB->text(),
                                        ui->lineHostDB->text()
                                        );
    emit changeSettings();
    DB::instance()->connectToDB();
}


LoginForm::~LoginForm()
{
    delete ui;
}

