#include "qsqlquerymodelprotocolgeneratorview.h"

QSqlQueryModelProtocolGeneratorView::QSqlQueryModelProtocolGeneratorView(QObject *parent) :
  QSqlQueryModelImpl(parent)
{

}

bool QSqlQueryModelProtocolGeneratorView::updateData ()
{
  QString request ("SELECT top_id, header, protokoll_id FROM Beschluesse WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr ORDER BY protokoll_id ASC");
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));
  query.prepare(request);
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.exec();

  bool result = runSqlQuery(query);

  this->setQuery(query);
  this->setHeaderData(0, Qt::Horizontal, tr("Tagesordnungspunkt Nummer"));
  this->setHeaderData(1, Qt::Horizontal, tr("Beschlussüberschrift"));
  this->setHeaderData(2, Qt::Horizontal, tr("Protokollreihenfolge"));

  return result;
}

bool QSqlQueryModelProtocolGeneratorView::moveRowUp(int aSourceRow)
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));

  //set the id of the top before to -999
  query.prepare("UPDATE Beschluesse SET protokoll_id = -999 WHERE obj_id = :id AND wi_jahr = :year AND protokoll_id = :protokoll_id AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":protokoll_id", (aSourceRow - 1));
  bool retVal = runSqlQuery(query);

  //set the chosen top to the correct id
  query.prepare("UPDATE Beschluesse SET protokoll_id = :protokoll_id_new WHERE obj_id = :id AND wi_jahr = :year AND protokoll_id =:protokoll_id AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":protokoll_id", aSourceRow);
  query.bindValue(":protokoll_id_new", aSourceRow - 1);
  retVal = runSqlQuery(query);

  //set the '-999' topid to the correct topid
  query.prepare("UPDATE Beschluesse SET protokoll_id = :protokoll_id WHERE obj_id = :id AND wi_jahr = :year AND protokoll_id = -999 AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":protokoll_id", aSourceRow);

  retVal = runSqlQuery(query);

  updateData();
}

bool QSqlQueryModelProtocolGeneratorView::moveRowDown(int aSourceRow)
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));

  //set the id of the top before to -999
  query.prepare("UPDATE Beschluesse SET protokoll_id = -999 WHERE obj_id = :id AND wi_jahr = :year AND protokoll_id = :protokoll_id AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":protokoll_id", (aSourceRow + 1));
  bool retVal = runSqlQuery(query);

  //set the chosen top to the correct id
  query.prepare("UPDATE Beschluesse SET protokoll_id = :protokoll_id_new WHERE obj_id = :id AND wi_jahr = :year AND protokoll_id =:protokoll_id AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":protokoll_id", aSourceRow);
  query.bindValue(":protokoll_id_new", aSourceRow + 1);
  retVal = runSqlQuery(query);

  //set the '-999' topid to the correct topid
  query.prepare("UPDATE Beschluesse SET protokoll_id = :protokoll_id WHERE obj_id = :id AND wi_jahr = :year AND protokoll_id = -999 AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":protokoll_id", aSourceRow);
  retVal = runSqlQuery(query);

  updateData();

  return retVal;
}

bool QSqlQueryModelProtocolGeneratorView::deleteEntry (int aRow)
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));

  query.prepare("DELETE FROM Beschluesse WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr AND top_id = aRow");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  query.bindValue(":top_id", aRow);
  bool retVal = runSqlQuery(query);

  updateData();

  return retVal;
}

bool QSqlQueryModelProtocolGeneratorView::deleteEntries ()
{
  QSqlQuery query (QSqlDatabase::database(this->getDbConnectionName()));

  query.prepare("DELETE FROM Beschluesse WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr");
  query.bindValue(":id", this->getPropertyId());
  query.bindValue(":year", this->getYear());
  query.bindValue(":etvnr", this->getAgendaNum());
  bool retVal = runSqlQuery(query);

  updateData();

  return retVal;
}
