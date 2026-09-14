#include "agendawizard.h"
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include "wizarddialogbox.h"
#include <QDebug>
#include <QRegularExpression>

AgendaWizard::AgendaWizard (QString &rDbConnectionName, int estateId, int agendaYear, int agendaNum)
{
  mDbConnName = rDbConnectionName;
  mEstateId = estateId;
  mAgendaYear = agendaYear;
  mAgendaNum = agendaNum;
  mHasSavedDecissions = false;

  mStringListAgendaItems.clear();
  mStringListSavedDecissions.clear();

  bool stepOk = getAgendaItems();

  if (stepOk)
  {
    mHasSavedDecissions = getSavedDecissions();
  }
}

AgendaWizard::~AgendaWizard()
{
  mStringListAgendaItems.clear();
  mStringListSavedDecissions.clear();
}

bool AgendaWizard::getAgendaItems ()
{
  mStringListAgendaItems.clear();
  bool hasItems = false;

  QSqlQuery query (QSqlDatabase::database(mDbConnName));

  query.clear();
  query.prepare("SELECT top_id, top_header, top_descr, top_vorschlag, top_vorschlag2, top_vorschlag3, beschlussArt FROM Tagesordnungspunkte WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvNum");
  query.bindValue(":id", mEstateId);
  query.bindValue(":year", mAgendaYear);
  query.bindValue(":etvNum", mAgendaNum);
  query.exec();

  QString sug1 ("");
  QString sug2 ("");
  QString sug3 ("");
  QString header ("");
  QString descr ("");
  QString type ("");
  QString top_id ("");

  QStringList strings;
  strings.clear();

  while (query.next())
  {
    hasItems = true;

    top_id  = query.value(0).toString();
    header  = query.value(1).toString();
    descr   = query.value(2).toString();
    sug1    = query.value(3).toString();
    sug2    = query.value(4).toString();
    sug3    = query.value(5).toString();
    type    = query.value(6).toString();

    strings.insert(0, top_id);
    strings.insert(1, header);

    QString debugStr ("");
    debugStr = header.remove(QRegularExpression("<[^>]*>"));
    qDebug () << "strings.insert(1, header): " << debugStr;

    strings.insert(2, descr);
    strings.insert(3, sug1);
    strings.insert(4, sug2);
    strings.insert(5, sug3);
    strings.insert(6, type);

    mStringListAgendaItems.push_back(strings);
    strings.clear();
  }
  return hasItems;
}

bool AgendaWizard::getSavedDecissions ()
{
  mStringListSavedDecissions.clear();

  QSqlQuery queryOldDecission (QSqlDatabase::database(mDbConnName));
  queryOldDecission.prepare("SELECT *  FROM Beschluesse WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvNum");
  queryOldDecission.bindValue(":id", mEstateId);
  queryOldDecission.bindValue(":year", mAgendaYear);
  queryOldDecission.bindValue(":etvNum", mAgendaNum);

  queryOldDecission.exec();

  bool hasItems = false;

  QStringList strings;
  strings.clear();

  while (queryOldDecission.next())
  {
    hasItems = true;

    QString top_id  = queryOldDecission.value(3).toString();
    QString header  = queryOldDecission.value(5).toString();
    QString descr   = queryOldDecission.value(6).toString();
    QString decission = queryOldDecission.value(7).toString();
    QString decissionPronouncement    = queryOldDecission.value(8).toString();
    QString votesYes  = queryOldDecission.value(9).toString();
    QString votesNo = queryOldDecission.value(10).toString();
    QString votesAbstention = queryOldDecission.value(11).toString();
    QString decissionType = queryOldDecission.value(11).toString();

    strings.insert(0, top_id);
    strings.insert(1, header);
    strings.insert(2, descr);
    strings.insert(3, decission);
    strings.insert(4, decissionPronouncement);
    strings.insert(5, votesYes);
    strings.insert(6, votesNo);
    strings.insert(7, votesAbstention);
    strings.insert(8, decissionType);

    mStringListSavedDecissions.push_back(strings);
    strings.clear();
  }
  return hasItems;
}

bool AgendaWizard::hasItems ()
{
  if (0 != mStringListAgendaItems.size())
    return true;
  else
    return false;
}

void AgendaWizard::process ()
{
  mStringListSavedDecissions.front();
  mStringListAgendaItems.front();

  QStringList stringList;

  QString sug1 ("");
  QString sug2 ("");
  QString sug3 ("");
  QString header ("");
  QString descr ("");
  QString type ("");

  QString savedSuggestion("");
  QString votePreview("");
  QString votesYes ("");
  QString votesNo ("");
  QString votesAbstention ("");

  int top_id = -1;
  int abortWizard = QDialog::Accepted;


  for(std::vector<int>::size_type i = 0; i != mStringListAgendaItems.size() && abortWizard != QDialog::Rejected; i++)
  {
    //get decission
    stringList = mStringListAgendaItems[i];

    top_id  = stringList.value(0).toInt();
    header  = stringList.value(1);
    descr   = stringList.value(2);
    sug1    = stringList.value(3);
    sug2    = stringList.value(4);
    sug3    = stringList.value(5);
    type    = stringList.value(6);

    if (mHasSavedDecissions)
    {
      bool foundRecord = false;

      for(std::vector<int>::size_type i = 0; i != mStringListSavedDecissions.size() && foundRecord == false; i++)
      {
        stringList.clear();
        stringList = mStringListSavedDecissions[i];

        //find record
        if (top_id == stringList.value(0).toInt())
        {
          savedSuggestion = stringList.value(3);
          votePreview = stringList.value(4);
          votesYes = stringList.value(5);
          votesNo = stringList.value(6);
          votesAbstention = stringList.value(7);
          //end loop
          foundRecord = true;
        }
      }
    }

    WizardDialogBox dialog (0, header.toStdString().c_str(), eComplexDialog);

    if ("" != sug1)
      dialog.setSuggestion1(sug1);

    if ("" != sug2)
      dialog.setSuggestion2(sug2);

    if ("" != sug3)
      dialog.setSuggestion3(sug3);

    //set old Values ->
    if (mHasSavedDecissions)
    {
      dialog.setSavedSuggestion(savedSuggestion);
      dialog.setVotePreview (votePreview);

      dialog.setVotingsYes (votesYes.toFloat());
      dialog.setVotingsNo (votesNo.toFloat());
      dialog.setVotingsConcordant (votesAbstention.toFloat());
    }

    abortWizard = dialog.exec();

    if (QDialog::Accepted == abortWizard && -1 != top_id)
    {
      QSqlQuery query3 (QSqlDatabase::database(mDbConnName));

      //get cover page
      query3.prepare("SELECT top_id FROM Beschluesse WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvNum AND top_id = :top_id");
      query3.bindValue(":id", mEstateId);
      query3.bindValue(":year", mAgendaYear);
      query3.bindValue(":etvNum", mAgendaNum);
      query3.bindValue(":top_id", top_id);
      query3.exec();

      bool resultFound = false;
      //record found -> update query
      if (query3.next())
      {
        resultFound = true;

        //set values
        query3.prepare("UPDATE Beschluesse SET beschlussformulierung = :formulierung, header = :headerText, descr = :description, abstimmergebnis = :ergebnis, stimmenJa = :ja, stimmenNein = :nein, stimmenEnthaltung = :enthaltung, beschlusssammlungVermerke = :vermerke, beschlussArt =:type WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvNum AND top_id = :top_id");
      }

      //no record found -> insert query
      if (!resultFound)
      {
        query3.prepare("INSERT INTO Beschluesse (obj_id, wi_jahr, etv_nr, top_id, beschlussformulierung, header, descr, abstimmergebnis, stimmenJa, stimmenNein, stimmenEnthaltung, protokoll_id, beschlusssammlungVermerke, beschlussArt) VALUES (:id, :year, :etvNum, :top_id, :formulierung, :headerText, :description, :ergebnis, :ja, :nein, :enthaltung, :protokollid, :vermerke, :type)");
      }

      query3.bindValue(":id", mEstateId);
      query3.bindValue(":year", mAgendaYear);
      query3.bindValue(":etvNum", mAgendaNum);
      query3.bindValue(":top_id", top_id);
      query3.bindValue(":protokollid", top_id);
      query3.bindValue(":headerText", header);
      query3.bindValue(":description", descr);
      query3.bindValue(":formulierung", dialog.getResult());
      query3.bindValue(":ergebnis", dialog.getVoteText());
      query3.bindValue(":ja", dialog.getVotingsYes());
      query3.bindValue(":nein", dialog.getVotingsNo());
      query3.bindValue(":enthaltung", dialog.getVotingsConcordant());
      query3.bindValue(":vermerke", dialog.getVoteText());
      query3.bindValue(":type", type);
      query3.exec ();
    }
  }
}
