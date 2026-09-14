#ifndef QSTANDARDITEMMODELPROPERTYOVERVIEW_H
#define QSTANDARDITEMMODELPROPERTYOVERVIEW_H

#include <QStandardItemModel>
#include <QSqlDatabase>

class QStandardItemModelPropertyOverview : public QStandardItemModel
{
  public:
    QStandardItemModelPropertyOverview();
    ~QStandardItemModelPropertyOverview();
    void setQuery(const QSqlQuery &query);
    bool populate (QString &dbConnName, int propertyId);
    //void setPropertyId (int propertyId);
  private:
    bool runSqlQuery (QSqlQuery &query);
};

#endif // QSTANDARDITEMMODELPROPERTYOVERVIEW_H
