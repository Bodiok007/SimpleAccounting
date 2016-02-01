#ifndef BASETABLEVIEW_H
#define BASETABLEVIEW_H

#include <QtWidgets>
//#include <QtSql>

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

protected:
    virtual void contextMenuEvent(QContextMenuEvent *pe);
    bool initializeContextMenu();

private:
    QMenu *m_contextMenu;
};

#endif // BASETABLEVIEW_H
