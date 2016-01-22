#include "salestableview.h"

SalesTableView::SalesTableView(QWidget *parent)
    : QTableView(parent)
{
    initializeContextMenu();
}


bool SalesTableView::initializeContextMenu()
{
    m_contextMenu = new QMenu(this);

    QAction *addSales = m_contextMenu->addAction("Додати");
    addSales->setObjectName("addSales");

    QAction *addService = m_contextMenu->addAction("Редагувати");
    addService->setObjectName("editSales");

    connect(m_contextMenu,
            SIGNAL(triggered(QAction*)),
            SLOT(slotActivatedContextMenu(QAction*))
           );

    return true;
}


// show context menu in mouse position
void SalesTableView::contextMenuEvent(QContextMenuEvent *pe)
{
    m_contextMenu->exec(pe->globalPos());
}


// do action from context menu
void SalesTableView::slotActivatedContextMenu(QAction *pAction)
{
    if (pAction->objectName() == "addSales") {
        qDebug() << "Додати продажу";
    }
    else if (pAction->objectName() == "editSales") {
        qDebug() << "Редагувати поле";
    }

}


SalesTableView::~SalesTableView()
{
}


