#include "QSqlQueryModelPropertyView.h"
#include "QSqlQueryModelImpl.h"
#include <QSqlQuery>
#include "global.h"

QSqlQueryModelPropertyView::QSqlQueryModelPropertyView(QObject *parent) :
  QSqlQueryModelImpl(parent)
{

}

bool QSqlQueryModelPropertyView::updateData ()
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));
  query.prepare("SELECT obj_name, obj_id FROM Objekt ORDER BY obj_name ASC");

  bool result = runSqlQuery(query);
  this->setQuery(query);
  this->setHeaderData(0, Qt::Horizontal, tr("Objekt"));
  this->setHeaderData(1, Qt::Horizontal, tr("ID"));

  return result;
}
