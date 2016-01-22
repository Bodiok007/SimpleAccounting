#include "servicestableview.h"

ServicesTableView::ServicesTableView(QWidget *parent)
    : QTableView(parent)
{
    initializeContextMenu();
}


bool ServicesTableView::initializeContextMenu()
{
    m_pContextMenu = new QMenu(this);

    QAction *addSales = m_pContextMenu->addAction("Додати");
    addSales->setObjectName("addService");

    QAction *addService = m_pContextMenu->addAction("Редагувати");
    addService->setObjectName("editService");

    connect(m_pContextMenu,
            SIGNAL(triggered(QAction*)),
            SLOT(slotActivatedContextMenu(QAction*))
           );

    return true;
}


void ServicesTableView::contextMenuEvent(QContextMenuEvent *pe)
{
    m_pContextMenu->exec(pe->globalPos());
}

// do action from context menu
void ServicesTableView::slotActivatedContextMenu(QAction *pAction)
{
    if (pAction->objectName() == "addService") {
        qDebug() << "Додати сервіс";
    }
    else if (pAction->objectName() == "editService") {
        qDebug() << "Редагувати сервіс";
    }

}
