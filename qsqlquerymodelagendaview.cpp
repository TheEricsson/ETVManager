#include "qsqlquerymodelagendaview.h"
#include <QSqlQuery>
#include "global.h"

QSqlQueryModelAgendaView::QSqlQueryModelAgendaView(QObject *parent) :
  QSqlQueryModelImpl(parent)
{

}

bool QSqlQueryModelAgendaView::updateData ()
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));
  query.prepare("SELECT top_id, top_header FROM Tagesordnungspunkte WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());

  bool result = runSqlQuery(query);
  this->setQuery(query);
  this->setHeaderData(0, Qt::Horizontal, tr("TOP"));
  this->setHeaderData(1, Qt::Horizontal, tr("Bezeichnung"));

  return result;
}

bool QSqlQueryModelAgendaView::removeRow (int aItemId)
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));
  query.prepare("DELETE FROM Tagesordnungspunkte WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr AND top_id = :topid");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":topid", aItemId);

  bool retVal = runSqlQuery(query);
  updateData();

  if (true == retVal)
    reorganizeIds();

  return retVal;
}

bool QSqlQueryModelAgendaView::moveRowUp (int aItemId)
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));

  //set the id of the top before to -999
  query.prepare("UPDATE Tagesordnungspunkte SET top_id = -999 WHERE obj_id = :id AND wi_jahr = :year AND top_id = :topid AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":topid", (aItemId - 1));
  bool retVal = runSqlQuery(query);

  //set the chosen top to the correct id
  query.prepare("UPDATE Tagesordnungspunkte SET top_id = :topid_new WHERE obj_id = :id AND wi_jahr = :year AND top_id =:topid AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":topid", aItemId);
  query.bindValue(":topid_new", aItemId-1);
  retVal = runSqlQuery(query);

  //set the '-999' topid to the correct topid
  query.prepare("UPDATE Tagesordnungspunkte SET top_id = :topid WHERE obj_id = :id AND wi_jahr = :year AND top_id = -999 AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":topid", aItemId);

  retVal = runSqlQuery(query);

  updateData();
}

bool QSqlQueryModelAgendaView::moveRowDown (int aItemId)
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));

  //set the id of the top before to -999
  query.prepare("UPDATE Tagesordnungspunkte SET top_id = -999 WHERE obj_id = :id AND wi_jahr = :year AND top_id = :topid AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":topid", (aItemId + 1));
  bool retVal = runSqlQuery(query);

  //set the chosen top to the correct id
  query.prepare("UPDATE Tagesordnungspunkte SET top_id = :topid_new WHERE obj_id = :id AND wi_jahr = :year AND top_id =:topid AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":topid", aItemId);
  query.bindValue(":topid_new", aItemId + 1);
  retVal = runSqlQuery(query);

  //set the '-999' topid to the correct topid
  query.prepare("UPDATE Tagesordnungspunkte SET top_id = :topid WHERE obj_id = :id AND wi_jahr = :year AND top_id = -999 AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":topid", aItemId);
  retVal = runSqlQuery(query);

  updateData();

  return retVal;
}

bool QSqlQueryModelAgendaView::reorganizeIds ()
{
  int count = this->rowCount();

  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));
  QSqlRecord record;

  int topId = 0;

  //update top ids
  for (int i = 0; i < count; i++)
  {
    topId++;
    record = this->record(i);
    query.prepare("UPDATE Tagesordnungspunkte SET top_id = :newid WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr AND top_id = :oldid");
    query.bindValue(":id", this->getPropertyId());
    query.bindValue(":year", this->getYear());
    query.bindValue(":etvnr", this->getAgendaNum());
    query.bindValue(":oldid", record.value(0).toInt());
    query.bindValue(":newid", topId);
    runSqlQuery(query);
  }
}
