#ifndef SERVICESTABLEVIEW_H
#define SERVICESTABLEVIEW_H

#include <QtWidgets>

class ServicesTableView : public QTableView
{
    Q_OBJECT
public:
    ServicesTableView(QWidget *parent);

signals:
    void addService();
    void editService(uint serviceID);

public slots:
    void slotActivatedContextMenu(QAction *pAction);

protected:
    virtual void contextMenuEvent(QContextMenuEvent *pe);
    bool initializeContextMenu();

private:
    QMenu *m_pContextMenu;

    uint getCurrentServiceID();
};

#endif // SERVICESTABLEVIEW_H
