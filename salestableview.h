#ifndef BASETABLEVIEW_H
#define BASETABLEVIEW_H

#include <QtWidgets>
#include "salesmodel.h"

class SalesTableView : public QTableView
{
    Q_OBJECT
public:
    SalesTableView(QWidget *parent);
    ~SalesTableView();

    uint getCurrentSaleID();

signals:
    void addSale();
    void editSale(uint saleID);

public slots:
    void slotActivatedContextMenu(QAction *pAction);
    void setSalesModel();

protected:
    virtual void contextMenuEvent(QContextMenuEvent *pe);
    bool initializeContextMenu();

private:
    QMenu *m_contextMenu;
    SalesModel *m_pSalesModel;
};

#endif // BASETABLEVIEW_H
