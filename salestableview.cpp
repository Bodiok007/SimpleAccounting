#include "salestableview.h"

SalesTableView::SalesTableView(QWidget *parent)
    : QTableView(parent)
{
    initializeContextMenu();
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
}


bool SalesTableView::initializeContextMenu()
{
    m_contextMenu = new QMenu(this);

    QAction *addSales = m_contextMenu->addAction("Додати");
    addSales->setObjectName("addSale");

    QAction *addService = m_contextMenu->addAction("Редагувати");
    addService->setObjectName("editSale");

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
    if (pAction->objectName() == "addSale") {
        emit addSale();
    }
    else if (pAction->objectName() == "editSale") {
        emit editSale(getCurrentSaleID());
    }

}


uint SalesTableView::getCurrentSaleID()
{
    int currentRow = selectionModel()->currentIndex().row();

    // 0 is hide column with ID
    QModelIndex currentIndex = model()->index(currentRow, 0);
    uint currentSaleID = model()->data(currentIndex).toUInt();

    return currentSaleID;
}


SalesTableView::~SalesTableView()
{
}






