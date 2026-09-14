#include "decissionitemsettings.h"
#include "ui_decissionitemsettings.h"
#include <QSqlQuery>

DecissionItemSettings::DecissionItemSettings(QWidget *parent, QString &rDbConnectionName, int estateId, int agendaYear, int agendaNum, int decissionId) :
  QDialog(parent),
  ui(new Ui::DecissionItemSettings)
{
  ui->setupUi(this);

  mDbConnectionName = rDbConnectionName;
  mEstateId = estateId;
  mAgendaYear = agendaYear;
  mAgendaNum = agendaNum;
  mDecissionId = decissionId;

  //prevent dialog from blocking application
  this->setWindowModality(Qt::NonModal);

  this->update();
}

DecissionItemSettings::~DecissionItemSettings()
{
  delete ui;
}

void DecissionItemSettings::setHeader (const QString aValue)
{
  ui->header->setText(aValue);
}

void DecissionItemSettings::setDescription (const QString aValue)
{
  ui->description->setText(aValue);
}

void DecissionItemSettings::setDecissionText (const QString aValue)
{
  ui->decissionText->setText(aValue);
}

void DecissionItemSettings::setDecissionProclamation (const QString aValue)
{
  ui->decissionProclamation->setText(aValue);
}

void DecissionItemSettings::setYesVotes (float aValue)
{
  ui->yes->setValue(aValue);
}

void DecissionItemSettings::setNoVotes (float aValue)
{
  ui->no->setValue(aValue);
}

void DecissionItemSettings::setAbsentionVotes (float aValue)
{
  ui->abstention->setValue(aValue);
}

void DecissionItemSettings::setType (int aType)
{
  if (0 == aType)
    ui->mitBeschlussoption->setChecked(true);
  else if (1 == aType)
    ui->schriftlicherBeschluss->setChecked(true);
  else if (2 == aType)
    ui->ohneBeschlussoption->setChecked(true);
}

void DecissionItemSettings::update ()
{
  QSqlQuery query (QSqlDatabase::database(mDbConnectionName));
  query.prepare("SELECT * FROM Beschluesse WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr AND top_id = :topid");
  query.bindValue(":id", mEstateId);
  query.bindValue(":year", mAgendaYear);
  query.bindValue(":etvnr", mAgendaNum);
  query.bindValue(":topid", mDecissionId);
  query.exec();

  if (query.next())
  {
    this->setHeader                    (query.value(5).toString());
    this->setDescription               (query.value(6).toString());
    this->setDecissionText             (query.value(7).toString());
    this->setDecissionProclamation     (query.value(8).toString());
    this->setYesVotes                  (query.value(9).toFloat());
    this->setNoVotes                   (query.value(10).toFloat());
    this->setAbsentionVotes            (query.value(11).toFloat());
    this->setType                      (query.value(12).toInt());
  }
}

void DecissionItemSettings::saveValues()
{
  QSqlQuery query (QSqlDatabase::database(mDbConnectionName));

  //set values
  query.prepare("UPDATE Beschluesse SET header =:newHeader, descr =:newDescr, beschlussformulierung =:newBeschlussformulierung, abstimmergebnis =:newAbstimmergebnis, beschlusssammlungVermerke = :vermerke, stimmenJa =:ja, stimmenNein =:nein, stimmenEnthaltung =:enthaltung WHERE obj_id = :id AND wi_jahr = :year AND top_id = :topid AND etv_nr = :etvnum");
  query.bindValue(":id", mEstateId);
  query.bindValue(":year", mAgendaYear);
  query.bindValue(":etvnum", mAgendaNum);
  query.bindValue(":topid", mDecissionId);
  query.bindValue(":newHeader", this->getHeader());
  query.bindValue(":newDescr", this->getDescription());
  query.bindValue(":newBeschlussformulierung", this->getDecissionText());
  query.bindValue(":newAbstimmergebnis", this->getDecissionProclamation());
  query.bindValue(":ja", this->getYesVotes());
  query.bindValue(":nein", this->getNoVotes());
  query.bindValue(":enthaltung", this->getAbsentionVotes());
  query.bindValue(":vermerke", this->getDecissionProclamation());
  //query.bindValue(":type", this->getType());

  query.exec();

  //also save changes of agenda item (header/description)
  query.clear();
  //update item
  query.prepare("UPDATE Tagesordnungspunkte SET top_header =:header, top_descr =:descr WHERE obj_id = :id AND wi_jahr = :year AND top_id = :topid AND etv_nr = :etvnum");
  query.bindValue(":id", mEstateId);
  query.bindValue(":year", mAgendaYear);
  query.bindValue(":etvnum", mAgendaNum);
  query.bindValue(":header", this->getHeader());
  query.bindValue(":descr", this->getDescription());
  query.bindValue(":topid", mDecissionId);
  //query.bindValue(":itemType", this->getItemType());
  query.exec();
}

int DecissionItemSettings::getType(void)
{
  if (ui->mitBeschlussoption->isChecked())
    return 0;
  else if (ui->schriftlicherBeschluss->isChecked())
    return 1;
  else if (ui->ohneBeschlussoption->isChecked ())
    return 2;

  return 0;
}

const QString DecissionItemSettings::getHeader (void)
{
  return ui->header->toHtml();
}

const QString DecissionItemSettings::getDescription (void)
{
  return ui->description->toHtml();
}

const QString DecissionItemSettings::getDecissionText (void)
{
  return ui->decissionText->toHtml();
}

const QString DecissionItemSettings::getDecissionProclamation (void)
{
  return ui->decissionProclamation->toHtml();
}

float DecissionItemSettings::getYesVotes (void)
{
  return ui->yes->value();
}

float DecissionItemSettings::getNoVotes (void)
{
  return ui->no->value();
}

float DecissionItemSettings::getAbsentionVotes (void)
{
  return ui->abstention->value();
}
