#ifndef SALEMODEL_H
#define SALEMODEL_H

#include <QtWidgets>
#include <QtSql>

class SalesModel : public QObject
{
    Q_OBJECT
public:
    explicit SalesModel(QObject *parent = 0);
    ~SalesModel();
    QSqlQueryModel *getModel();

signals:

public slots:

private:
    QSqlQueryModel *m_pSalesModel;

    void setHeaderModelSales();
};

#endif // SALEMODEL_H
