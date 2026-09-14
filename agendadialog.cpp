#include "agendadialog.h"
#include "ui_agendadialog.h"
#include "QSqlQueryModelAgendaView.h"
#include "AgendaItemSettings.h"
#include <QMessageBox>

AgendaDialog::AgendaDialog(QWidget *parent, QString &rDbConnName, int estateId, int agendaYear, int agendaNum) :
  QWidget(parent),
  ui(new Ui::AgendaDialog)
{
  ui->setupUi(this);
  ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Zurück zur Übersicht");
  mQueryModelAgendaView = 0;
  mDbConnName = rDbConnName;
  mEstateId = estateId;
  mAgendaYear = agendaYear;
  mAgendaNum = agendaNum;

  initAgendaTable();
  updateAgendaTable();
}

AgendaDialog::~AgendaDialog()
{
  if (0 != mQueryModelAgendaView)
      delete mQueryModelAgendaView;

  delete ui;
}

void AgendaDialog::initAgendaTable ()
{
  if (0 == mQueryModelAgendaView)
  {
    mQueryModelAgendaView = new QSqlQueryModelAgendaView ();
    ui->tableAgenda->setModel(mQueryModelAgendaView);
    ui->tableAgenda->horizontalHeader()->resizeSection(0, 50);
    ui->tableAgenda->show();
  }
}

void AgendaDialog::updateAgendaTable()
{
  if (0 != mQueryModelAgendaView)
  {
    mQueryModelAgendaView->setDbConnectionName(mDbConnName);
    mQueryModelAgendaView->setPropertyId(mEstateId);
    mQueryModelAgendaView->setYear(mAgendaYear);
    mQueryModelAgendaView->setAgendaNum(mAgendaNum);
    mQueryModelAgendaView->updateData ();
  }
}

void AgendaDialog::changeAgendaItemSettings (int aTopId)
{
  if (checkForExistingDecissions())
  {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Achtung", "Es wurde bereits eine Protokollabschrift generiert.\n"
                                                              "Generierte Beschlüsse werden gelöscht, Neuerstellung erforderlich.\n"
                                                              "Fortfahren?", QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
    {
      return;
    }
    else
    {
      deleteExistingDecissions ();
    }
  }

  AgendaItemSettings itemSettings (this);
  itemSettings.setWindowModality(Qt::WindowModal);
  itemSettings.setdialogMode(AgendaItemDialogMode::update);
  itemSettings.setDbConnectionName(mDbConnName);
  itemSettings.setPropertyId(mEstateId);
  itemSettings.setYear(mAgendaYear);
  itemSettings.setAgendaNum(mAgendaNum);
  itemSettings.setAgendaItemId(aTopId);

  itemSettings.update();
  itemSettings.show();

  if (itemSettings.exec() != QDialog::Rejected)
  {
    updateAgendaTable();
  }
}

bool AgendaDialog::checkForExistingDecissions()
{
  QSqlQuery query (QSqlDatabase::database(mDbConnName));
  query.prepare("SELECT top_id FROM Beschluesse WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr");
  query.bindValue(":id", mEstateId);
  query.bindValue(":year", mAgendaYear);
  query.bindValue(":etvnr", mAgendaNum);

  bool result = query.exec();

  if (query.next())
  {
    return true;
  }
  else
    return false;
}

bool AgendaDialog::deleteExistingDecissions()
{
  QSqlQuery query (QSqlDatabase::database(mDbConnName));

  query.prepare("DELETE FROM Beschluesse WHERE obj_id = :id AND wi_jahr = :year AND etv_nr = :etvnr");
  query.bindValue(":id", mEstateId);
  query.bindValue(":year", mAgendaYear);
  query.bindValue(":etvnr", mAgendaNum);

  return query.exec();
}

void AgendaDialog::on_tableAgenda_doubleClicked(const QModelIndex &index)
{
  if (ui->tableAgenda->selectionModel()->selectedRows().count() == 1)
  {
    int top_id = ui->tableAgenda->model()->index(index.row(),0).data().toInt();
    changeAgendaItemSettings(top_id);
  }
}

void AgendaDialog::on_addEntry_clicked()
{
  if (checkForExistingDecissions())
  {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Achtung", "Es wurde bereits eine Protokollabschrift generiert.\n"
                                                              "Generierte Beschlüsse werden gelöscht, Neuerstellung erforderlich.\n"
                                                              "Fortfahren?", QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
    {
      return;
    }
    else
    {
      deleteExistingDecissions ();
    }
  }

  AgendaItemSettings itemSettings (this);
  itemSettings.setdialogMode(AgendaItemDialogMode::insert);
  itemSettings.setDbConnectionName(mDbConnName);
  itemSettings.setPropertyId(mEstateId);
  itemSettings.setYear(mAgendaYear);
  itemSettings.setAgendaNum(mAgendaNum);

  //set next id for new entry
  if (0 != ui->tableAgenda->model())
    itemSettings.setAgendaItemId(ui->tableAgenda->model()->rowCount() + 1);

  itemSettings.update();
  itemSettings.show();

  if (itemSettings.exec() != QDialog::Rejected)
  {
    updateAgendaTable();
  }
}

void AgendaDialog::on_editEntry_clicked()
{
  if (checkForExistingDecissions())
  {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Achtung", "Es wurde bereits eine Protokollabschrift generiert.\n"
                                                              "Generierte Beschlüsse werden gelöscht, Neuerstellung erforderlich.\n"
                                                              "Fortfahren?", QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
    {
      return;
    }
    else
    {
      deleteExistingDecissions ();
    }
  }

  //check if selection in tableview is valid
  if (ui->tableAgenda->selectionModel()->selectedRows().count() == 1)
  {
    int selectedRow = ui->tableAgenda->selectionModel()->selection().indexes().value(0).row();
    int top_id = ui->tableAgenda->model()->index(selectedRow,0).data().toInt();

    changeAgendaItemSettings(top_id);
  }
  else if (ui->tableAgenda->selectionModel()->selection().indexes().count() == 0)
    QMessageBox::information(this, "Fehler", "Bitte eine Zeile auswählen.");
}

void AgendaDialog::on_deleteEntry_clicked()
{
  if (checkForExistingDecissions())
  {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Achtung", "Es wurde bereits eine Protokollabschrift generiert.\n"
                                                              "Generierte Beschlüsse werden gelöscht, Neuerstellung erforderlich.\n"
                                                              "Fortfahren?", QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
    {
      return;
    }
    else
    {
      deleteExistingDecissions ();
    }
  }

  if (ui->tableAgenda->selectionModel()->selectedRows().count() == 1)
  {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Achtung", "Tagesordnungspunkt wirklich löschen?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
      int selectedRow = ui->tableAgenda->selectionModel()->selection().indexes().value(0).row();
      int top_id = ui->tableAgenda->model()->index(selectedRow,0).data().toInt();

      mQueryModelAgendaView->removeRow(top_id);

      updateAgendaTable();
      ui->tableAgenda->setFocus();

      //set focussed item
      int newRowSelection = 0;
      if (ui->tableAgenda->model()->rowCount() > selectedRow)
        newRowSelection = selectedRow;
      else
        newRowSelection = ui->tableAgenda->model()->rowCount();

      ui->tableAgenda->selectRow(newRowSelection);
    }
  }
  else
  QMessageBox::information(this, "Fehler", "Es wurde kein Eintrag zum Löschen ausgewählt.");
}

void AgendaDialog::on_moveAgendaItemUp_clicked()
{
  if (checkForExistingDecissions())
  {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Achtung", "Es wurde bereits eine Protokollabschrift generiert.\n"
                                                              "Generierte Beschlüsse werden gelöscht, Neuerstellung erforderlich.\n"
                                                              "Fortfahren?", QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
    {
      return;
    }
    else
    {
      deleteExistingDecissions ();
    }
  }

  int selectedRow = ui->tableAgenda->selectionModel()->selection().indexes().value(0).row();
  int top_id = ui->tableAgenda->model()->index(selectedRow,0).data().toInt();

  if (1 == top_id)
  {
    QMessageBox::information(this, "Fehler", "Tagesordnungspunkt kann nicht nach oben verschoben werden.");
  }
  else
  {
    mQueryModelAgendaView->moveRowUp(top_id);
    ui->tableAgenda->setFocus();
    ui->tableAgenda->selectRow(top_id - 2);
  }
}

void AgendaDialog::on_moveAgendaItemDown_clicked()
{
  if (checkForExistingDecissions())
  {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Achtung", "Es wurde bereits eine Protokollabschrift generiert.\n"
                                                              "Generierte Beschlüsse werden gelöscht, Neuerstellung erforderlich.\n"
                                                              "Fortfahren?", QMessageBox::Yes|QMessageBox::No);
    if (reply != QMessageBox::Yes)
    {
      return;
    }
    else
    {
      deleteExistingDecissions ();
    }
  }

  int selectedRow = ui->tableAgenda->selectionModel()->selection().indexes().value(0).row();
  int top_id = ui->tableAgenda->model()->index(selectedRow,0).data().toInt();

  int rows = ui->tableAgenda->model()->rowCount();
  if (rows == selectedRow + 1 || rows == top_id)
  {
    QMessageBox::information(this, "Fehler", "Tagesordnungspunkt kann nicht nach unten verschoben werden.");
  }
  else
  {
    mQueryModelAgendaView->moveRowDown(top_id);
    ui->tableAgenda->setFocus();
    ui->tableAgenda->selectRow(top_id);
  }
}

void AgendaDialog::on_buttonBox_accepted()
{
  emit exitWidget();
}
