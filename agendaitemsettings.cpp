#include "agendaitemsettings.h"
#include "ui_agendaitemsettings.h"
#include <QSql>
#include <QMessageBox>
#include "QSqlQueryModelImpl.h"
#include "stringreplacer.h"
#include <QSqlQuery>
#include <global.h>

AgendaItemSettings::AgendaItemSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AgendaItemSettings)
{
    ui->setupUi(this);

    //prevent dialog from blocking application
    this->setWindowModality(Qt::NonModal);
    m_model = 0;
}

AgendaItemSettings::~AgendaItemSettings()
{
    delete ui;

  if (0 != m_model)
    delete m_model;
}

int AgendaItemSettings::getItemType ()
{
  if (ui->mitBeschlussoption->isChecked())
    return 0;
  if (ui->ohneBeschlussoption->isChecked())
    return 2;

  return 2;
}

void AgendaItemSettings::setItemType (int aType)
{
  if (0 == aType)
    ui->mitBeschlussoption->setChecked(true);
  else if (2 == aType)
    ui->ohneBeschlussoption->setChecked(true);
}

void AgendaItemSettings::update ()
{
  refreshAgendaItem ();
  updateTextPatterns ();
}

void AgendaItemSettings::refreshAgendaItem ()
{
  //verfuegbare Vorlagen aus Datenbank holen
  QSqlQuery query (QSqlDatabase::database(mDbConnectionName));
  query.prepare("SELECT top_header, top_descr, top_vorschlag, top_vorschlag2, top_vorschlag3, beschlussArt FROM Tagesordnungspunkte WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr AND top_id = :topid");

  query.bindValue(":id", this->mPropertyId);
  query.bindValue(":year", this->mYear);
  query.bindValue(":etvnr", this->mAgendaNum);
  query.bindValue(":topid", this->mAgendaItemId);
  query.exec();

  if (query.next())
  {
    this->setHeader(query.value(0).toString());
    this->setDescription(query.value(1).toString());
    this->setSuggestion(query.value(2).toString());
    this->setSuggestion2(query.value(3).toString());
    this->setSuggestion3(query.value(4).toString());
    this->setItemType(query.value(5).toInt());
  }
}

void AgendaItemSettings::updateTextPatterns ()
{
  //verfuegbare Vorlagen aus Datenbank holen
  QSqlQuery query (QSqlDatabase::database(mDbConnectionName));
  query.prepare("SELECT bezeichnung, id from AgendaPatterns ORDER BY bezeichnung ASC");
  query.exec();

  m_model = new QSqlQueryModelImpl ();
  m_model->setQuery(query);
  //Comboxbox mit Daten fuellen
  ui->patterns->setModel(m_model);
}

QString AgendaItemSettings::getHeader ()
{
  return ui->header->toHtml();
}

QString AgendaItemSettings::getDescription ()
{
  if ("" == ui->description->toHtml())
    return "";

  return ui->description->toHtml();
}

QString AgendaItemSettings::getSuggestion ()
{
  if ("" == ui->suggestion->toHtml())
    return "";

  return ui->suggestion->toHtml();
}

QString AgendaItemSettings::getSuggestion2 ()
{
  if ("" == ui->suggestion2->toHtml())
    return "";

  return ui->suggestion2->toHtml();
}

QString AgendaItemSettings::getSuggestion3 ()
{
  if ("" == ui->suggestion3->toHtml())
    return "";

  return ui->suggestion3->toHtml();
}

void AgendaItemSettings::setHeader (QString rValue)
{
    ui->header->setText(rValue);
}

void AgendaItemSettings::setDescription (QString rValue)
{
    ui->description->setText(rValue);
}

void AgendaItemSettings::setSuggestion (QString rValue)
{
    ui->suggestion->setText(rValue);
}

void AgendaItemSettings::setSuggestion2 (QString rValue)
{
    ui->suggestion2->setText(rValue);
}

void AgendaItemSettings::setSuggestion3 (QString rValue)
{
    ui->suggestion3->setText(rValue);
}

void AgendaItemSettings::on_insertPattern_clicked()
{
  //check model pointer
  if (0 != ui->patterns->model())
  {
    //get id
    QModelIndex index = ui->patterns->model()->index(ui->patterns->currentIndex(), 1);
    int patternId = index.data ().toInt();

    //get values
    //Liegenschaften aus Datenbank holen
    QSqlQuery query (QSqlDatabase::database(mDbConnectionName));
    query.prepare("SELECT ueberschrift, beschreibung, beschlussvorschlag, beschlussvorschlag2, beschlussvorschlag3, beschlussArt from AgendaPatterns WHERE id=:patternId");
    query.bindValue(":patternId", patternId);
    query.exec();

    if (query.next())
    {
      //header
      setHeader (replaceWildcards(query.value(0).toString()));

      //descr
      setDescription (replaceWildcards(query.value(1).toString()));

      //proposal
      setSuggestion (replaceWildcards(query.value(2).toString()));

      //proposal2
      setSuggestion2 (replaceWildcards(query.value(3).toString()));

      //proposal3
      setSuggestion3 (replaceWildcards(query.value(4).toString()));

      //set checkboxes
      int beschlussArt = query.value(5).toInt ();
      if (0 == beschlussArt || 1 == beschlussArt)
        ui->mitBeschlussoption->setChecked(true);
      else
        ui->ohneBeschlussoption->setChecked(true);
    }
  }
}

QString AgendaItemSettings::replaceWildcards (QString in)
{
  //check if the string contains any wildcards at all
  if (in.contains ("%"))
  {
      //not too smart to do a database query here, but for now ok:
      //Global::getInstance()->getDatabase()->open();
      QSqlQuery query (QSqlDatabase::database(mDbConnectionName));

      //get years
      query.prepare("SELECT * FROM Eigentuemerversammlungen WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvNum");
      query.bindValue(":id", mPropertyId);
      query.bindValue(":year", mYear);
      query.bindValue(":etvNum", mAgendaNum);
      query.exec();

      QString etvNum;
      QString etvDate;
      QString etvTime;
      QString etvLoc;

      if (query.next())
      {
          etvNum = query.value(2).toString();
          etvDate = query.value(3).toString();
          etvTime = query.value(4).toString();
          etvLoc = query.value(5).toString();
      }

      if (in.contains("%VergangenesWirtschaftsjahr%"))
      {
          int lastYear = mYear - 1;
          in.replace(QString("%VergangenesWirtschaftsjahr%"), QString::number (lastYear));
      }

      if (in.contains("%Wirtschaftsjahr%"))
      {
          int year = mYear;
          in.replace(QString("%Wirtschaftsjahr%"), QString::number (year));
      }

      if (in.contains("%DatumHeute%"))
      {
          QDate curDate = QDate::currentDate();
          in.replace(QString("%DatumHeute%"), curDate.toString("dddd, dd.MM.yyyy"));
      }

      if (in.contains("%NächstesWirtschaftsjahr%"))
      {
          int year = mYear + 1;
          in.replace(QString("%NächstesWirtschaftsjahr%"), QString::number(year));
      }

      if (in.contains("%ETVNummer%"))
      {
          in.replace(QString("%ETVNummer%"), etvNum);
      }

      if (in.contains("%ETVDatum%"))
      {
          in.replace(QString("%ETVDatum%"), etvDate);
      }

      if (in.contains("%ETVUhrzeit%"))
      {
          in.replace(QString("%ETVUhrzeit%"), etvTime);
      }

      if (in.contains("%DatumNachAnfechtungsfrist%"))
      {
          QDate date = QDate::fromString(etvDate,"dd.MM.yyyy");
          date = date.addMonths(1);
          in.replace(QString("%DatumNachAnfechtungsfrist%"), date.toString("dd.MM.yyyy"));
      }

      if (in.contains("%ZahlungslaufNachAnfechtungsfrist%"))
      {
          QDate date = QDate::fromString(etvDate,"dd.MM.yyyy");
          date = date.addMonths(1);

          if (date.day() >= 3)
            date = date.addMonths(1);

          in.replace(QString("%ZahlungslaufNachAnfechtungsfrist%"), date.toString("MMMM yyyy"));
      }

      in.replace ("%BeiratVorsitz%", StringReplacer::getInstance()->getReplacementString("%BeiratVorsitz%"));
      in.replace ("%BeiratMitglied1%", StringReplacer::getInstance()->getReplacementString("%BeiratMitglied1%"));
      in.replace ("%BeiratMitglied2%", StringReplacer::getInstance()->getReplacementString("%BeiratMitglied2%"));
      in.replace(QString("%BeiratVorsitz%"), "-");
      in.replace(QString("%BeiratMitglied1%"), "-");
      in.replace(QString("%BeiratMitglied2%"), "-");
  }
  return in;
}

void AgendaItemSettings::on_buttonBox_accepted()
{
  QSqlQuery query (QSqlDatabase::database(mDbConnectionName));

  if (mType == AgendaItemDialogMode::update)
  {
    //update item
    query.prepare("UPDATE Tagesordnungspunkte SET top_header =:header, top_descr =:descr, top_vorschlag =:suggestion, top_vorschlag2 =:suggestion2, top_vorschlag3 =:suggestion3, beschlussArt =:itemType WHERE obj_id = :id AND wi_jahr = :year AND top_id = :topid AND etv_nr = :etvnum");
    query.bindValue(":id", mPropertyId);
    query.bindValue(":year", mYear);
    query.bindValue(":etvnum", mAgendaNum);
    query.bindValue(":header", this->getHeader());
    query.bindValue(":descr", this->getDescription());
    query.bindValue(":suggestion", this->getSuggestion());
    query.bindValue(":suggestion2", this->getSuggestion2());
    query.bindValue(":suggestion3", this->getSuggestion3());
    query.bindValue(":topid", mAgendaItemId);
    query.bindValue(":itemType", this->getItemType());
    query.exec();
  }
  else if (mType == AgendaItemDialogMode::insert)
  {
    //insert item
    query.prepare("INSERT INTO Tagesordnungspunkte (obj_id, wi_jahr, top_id, etv_nr, top_header, top_descr, top_vorschlag, top_vorschlag2, top_vorschlag3, beschlussArt) VALUES (:id, :year, :topid, :etvnum, :header, :descr, :suggestion, :suggestion2, :suggestion3, :itemType)");
    query.bindValue(":id", mPropertyId);
    query.bindValue(":year", mYear);
    query.bindValue(":etvnum", mAgendaNum);
    query.bindValue(":header", this->getHeader());
    query.bindValue(":descr", this->getDescription());
    query.bindValue(":suggestion", this->getSuggestion());
    query.bindValue(":suggestion2", this->getSuggestion2());
    query.bindValue(":suggestion3", this->getSuggestion3());
    query.bindValue(":itemType", this->getItemType());
    query.bindValue(":topid", mAgendaItemId);
    query.exec();
  }
  return;
}
