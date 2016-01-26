#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "db.h"
#include "ui_addsaleform.h"

#include "dbsettings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pAddSaleForm = new AddSale(0);

    connect(ui->addSaleButton,
            SIGNAL(clicked(bool)),
            SLOT(showAddSaleForm())
           );

    m_pLoginForm = new LoginForm(0);
    m_pLoginForm->show();

    //this->hide();

    ui->tableSales->setModel(DB::instance()->getAllSales());
    ui->tableSales->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableServices->setModel(DB::instance()->getAllServices());
    ui->tableServices->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 35px; }");

    ui->toolBar->addAction(QPixmap(":/logOut.png"), "Вихід", this, SLOT(logOut()) );

    connect(m_pLoginForm, SIGNAL(logged(QString)), SLOT(logIn(QString)) );
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pAddSaleForm;
    delete m_pLoginForm;
}

Ui::MainWindow *MainWindow::getForm()
{
    return ui;
}

void MainWindow::exit()
{
    this->hide();
    m_pLoginForm->show();
}

void MainWindow::showAddSaleForm()
{
    m_pAddSaleForm->show();
}

void MainWindow::logOut()
{
    this->hide();
    m_pLoginForm->show();
}

void MainWindow::logIn(QString userName)
{
    this->show();
    qDebug() << "userLogged!" + userName;
}
