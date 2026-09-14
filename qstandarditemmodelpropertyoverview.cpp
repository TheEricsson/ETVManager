#include "qstandarditemmodelpropertyoverview.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>

QStandardItemModelPropertyOverview::QStandardItemModelPropertyOverview()
{
}

void QStandardItemModelPropertyOverview::setQuery(const QSqlQuery &query)
{
  QStandardItem *parentItem = this->invisibleRootItem();
  QSqlQuery qry = query;

  QString year ("");
  QString etvNum ("");
  QString etvDate ("");
  QString etvTime ("");

  QList <QStandardItem*> itemList;

  QStandardItem *item = 0;

  while (qry.next())
  {
    //row
    for (int i=0; i<4; i++)
    {
      item = new QStandardItem(qry.value(i).toString());
      if (0 != item)
      {
        itemList.push_back(item);
      }
    }
    parentItem->appendRow(itemList);
    itemList.clear();
  }
}

bool QStandardItemModelPropertyOverview::runSqlQuery (QSqlQuery &query)
{
  bool retVal = false;

  retVal = query.exec();

  //handle sql error
  if (false == retVal)
  {
    QSqlError error;
    error = query.lastError();

    QString errMsg ("");
    errMsg.append("Fehlerausgabe Datenbank:\n");
    errMsg.append(error.databaseText());
    errMsg.append("\nFehlerausgabe Datenbanktreiber:\n");
    errMsg.append(error.driverText());

    QMessageBox msgBox;
    msgBox.setText("Schwerwiegender Fehler beim Ausführen eines Datenbankbefehls");
    msgBox.setInformativeText(errMsg);
    int ret = msgBox.exec();
  }
  return retVal;
}

bool QStandardItemModelPropertyOverview::populate (QString &dbConnName, int propertyId)
{
  QSqlQuery query (QSqlDatabase::database (dbConnName));

  query.prepare("SELECT wi_jahr, etv_nr, etv_datum, etv_uhrzeit FROM Eigentuemerversammlungen WHERE obj_id = :id");
  query.bindValue(":id", propertyId);

  bool result = runSqlQuery(query);

  this->setQuery(query);

  this->setHeaderData(0, Qt::Horizontal, tr("Jahr"));
  this->setHeaderData(1, Qt::Horizontal, tr("ETV lfd. Nummer"));
  this->setHeaderData(2, Qt::Horizontal, tr("Datum"));
  this->setHeaderData(3, Qt::Horizontal, tr("Uhrzeit"));
  this->sort(0, Qt::AscendingOrder);

  return result;
}

QStandardItemModelPropertyOverview::~QStandardItemModelPropertyOverview()
{

}
