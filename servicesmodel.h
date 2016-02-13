#ifndef SERVICESMODEL_H
#define SERVICESMODEL_H

#include <QtWidgets>
#include <QtSql>

class ServicesModel : public QObject
{
    Q_OBJECT
public:
    explicit ServicesModel(QWidget *parent = 0);
    ~ServicesModel();
    QSqlQueryModel *getModel();

signals:

public slots:

private:
    QSqlQueryModel *m_pServicesModel;

    bool setHeaderModelServices();
};

#endif // SERVICESMODEL_H
