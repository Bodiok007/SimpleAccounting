#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_addsaleform.h"
#include "DB/db.h"
#include "servicecategories.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_DeleteOnClose);

    m_pAddSaleForm = new AddSale(0);
    m_pAddServiceForm = new AddServiceForm;

    m_pLoginForm = new LoginForm;
    m_pLoginForm->show();
    connect(m_pLoginForm, SIGNAL(logged(QString)), SLOT(logIn(QString)) );

    m_pEditSaleForm = new EditSalesForm;
    m_pEditServiceForm = new EditServicesForm;

    bindSignalsAndSlotsForSales();
    bindSignalsAndSlotsForServices();

    setModels();

    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 35px; }");
    ui->toolBar->addAction(QPixmap(":/logOut.png"), "Вихід", this, SLOT(logOut()) );   
}


void MainWindow::bindSignalsAndSlotsForSales()
{
    // clicked button 'add sale' - show 'add sale form'
    connect(ui->addSaleButton,
            SIGNAL(clicked(bool)),
            SLOT(showAddSaleForm())
           );

    // clicked in context menu 'add sale' - show 'add sale form'
    connect(ui->tableSales,
            SIGNAL(addSale()),
            SLOT(showAddSaleForm())
           );

    // request from 'add sale form' for update data in 'sales table'
    connect(m_pAddSaleForm,
            SIGNAL(updateSalesData()),
            SLOT(updateSalesModel())
           );

    // clicked in context menu 'edit sale' - show 'edit sale form' with clicked item data
    connect(ui->tableSales,
            SIGNAL(editSale(uint)),
            m_pEditSaleForm,
            SLOT(addDataToForm(uint))
           );

    // request from 'edit sale form' for update data in 'sales table'
    connect(m_pEditSaleForm,
            SIGNAL(updateSalesData()),
            SLOT(updateSalesModel())
           );
}


void MainWindow::bindSignalsAndSlotsForServices()
{
    // clicked button 'add service' - show 'add service form'
    connect(ui->addServiceButton,
            SIGNAL(clicked(bool)),
            SLOT(showAddServiceForm())
           );

    // clicked in context menu 'add service' - show 'add service form'
    connect(ui->tableServices,
            SIGNAL(addService()),
            SLOT(showAddServiceForm())
           );

    // request from 'add service form' for update 'service table'
    connect(m_pAddServiceForm,
            SIGNAL(updateServicesData()),
            SLOT(updateServicesModel())
           );

    // clicked in context menu 'edit service' - show 'edit service form' with clicked item data
    connect(ui->tableServices,
            SIGNAL(editService(uint)),
            m_pEditServiceForm,
            SLOT(addDataToForm(uint))
           );

    // request from 'edit service form' for update data in 'services table'
    connect(m_pEditServiceForm,
            SIGNAL(updateServicesData()),
            SLOT(updateServicesModel())
           );
}


void MainWindow::setModels()
{
    updateSalesModel();
    updateServicesModel();
    ui->tableSales->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableServices->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void MainWindow::updateSalesModel()
{
    ui->tableSales->setSalesModel();
    ui->tableSales->setColumnHidden(0, true);
}

void MainWindow::updateServicesModel()
{
    ui->tableServices->setServicesModel();
    ui->tableServices->setColumnHidden(0, true);
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
    m_pAddSaleForm->setEmployeeName(windowTitle());
    m_pAddSaleForm->show();
}


void MainWindow::showAddServiceForm()
{
    m_pAddServiceForm->setEmployeeName(windowTitle());
    m_pAddServiceForm->show();
}


void MainWindow::showEditSaleForm()
{
    m_pEditSaleForm->show();
}


void MainWindow::showEditServiceForm()
{
    m_pEditServiceForm->show();
}


void MainWindow::logOut()
{
    this->hide();
    m_pLoginForm->show();
}


void MainWindow::logIn(QString userName)
{
    this->setWindowTitle(userName);
    this->show();
    qDebug() << "userLogged!" + userName;
}


MainWindow::~MainWindow()
{
    delete ui;
    delete m_pAddSaleForm;
    delete m_pAddServiceForm;
    delete m_pEditSaleForm;
    delete m_pEditServiceForm;
    delete m_pLoginForm;
}


