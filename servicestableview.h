#ifndef SERVICESTABLEVIEW_H
#define SERVICESTABLEVIEW_H

#include <QtWidgets>
#include "servicesmodel.h"

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
    void setServicesModel();

protected:
    virtual void contextMenuEvent(QContextMenuEvent *pe);
    bool initializeContextMenu();

private:
    QMenu *m_pContextMenu;
    ServicesModel *m_pServicesModel;

    uint getCurrentServiceID();
};

#endif // SERVICESTABLEVIEW_H
