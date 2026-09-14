#include "agendatab.h"
#include "ui_agendatab.h"
#include "propertyMainView.h"
#include <QtSql>
#include <QString>
#include "agendasettings.h"
#include <string>
#include "agendaitemsettings.h"
#include "qsqlquerymodelagendaview.h"
#include <QMenu>
#include "global.h"

AgendaTab::AgendaTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AgendaTab)
{
  ui->setupUi(this);
  mQueryModelAgendaView = 0;

  ui->tableAgenda->horizontalHeader()->setStretchLastSection(true);

  initAgendaTable();
}

AgendaTab::~AgendaTab()
{
  if (0 != mQueryModelAgendaView)
      delete mQueryModelAgendaView;

  delete ui;
}

void AgendaTab::refreshOnSelected ()
{
  if (!this->isEnabled())
  {
    QMessageBox::information(this, "Fehler", "Alle Einstellungen deaktiviert.\nLegen Sie zunächst ein Wirtschaftsjahr und eine Eigentümerversammlung an");
    return;
  }

  ui->tableAgenda->setColumnWidth(0, 40);
  updateAgendaTable();
}

void AgendaTab::setParameter (settingsType aParameter, QString aSetting)
{
  switch (aParameter)
  {
    case eDbConnectionName:
      mUser = aSetting;
      break;
  }
}

void AgendaTab::initAgendaTable ()
{
  if (0 == mQueryModelAgendaView)
  {
    mQueryModelAgendaView = new QSqlQueryModelAgendaView ();
    ui->tableAgenda->setModel(mQueryModelAgendaView);
    ui->tableAgenda->horizontalHeader()->resizeSection(0, 50);
    ui->tableAgenda->show();
  }
}

void AgendaTab::updateAgendaTable()
{
  if (0 != mQueryModelAgendaView)
  {
    mQueryModelAgendaView->setDbConnectionName(mUser);
    mQueryModelAgendaView->setPropertyId(Global::getInstance()->getCurrentPropertyId());
    mQueryModelAgendaView->setYear(Global::getInstance()->getCurrentYear());
    mQueryModelAgendaView->setAgendaNum(Global::getInstance()->getCurrentEtvNumber());
    mQueryModelAgendaView->updateData ();
  }
}

void AgendaTab::changeAgendaItemSettings (int aTopId)
{
  AgendaItemSettings itemSettings (this);
  itemSettings.setdialogMode(AgendaItemDialogMode::update);
  itemSettings.setDbConnectionName(mUser);
  itemSettings.setPropertyId(Global::getInstance()->getCurrentPropertyId());
  itemSettings.setYear(Global::getInstance()->getCurrentYear());
  itemSettings.setAgendaNum(Global::getInstance()->getCurrentEtvNumber());
  itemSettings.setAgendaItemId(aTopId);

  itemSettings.update();
  itemSettings.show();

  if (itemSettings.exec() != QDialog::Rejected)
    updateAgendaTable();
}

void AgendaTab::on_tableAgenda_doubleClicked(const QModelIndex &index)
{
  if (ui->tableAgenda->selectionModel()->selectedRows().count() == 1)
  {
    int top_id = ui->tableAgenda->model()->index(index.row(),0).data().toInt();
    changeAgendaItemSettings(top_id);
  }
}

void AgendaTab::on_addEntry_clicked()
{
  AgendaItemSettings itemSettings (this);
  itemSettings.setdialogMode(AgendaItemDialogMode::insert);
  itemSettings.setDbConnectionName(mUser);
  itemSettings.setPropertyId(Global::getInstance()->getCurrentPropertyId());
  itemSettings.setYear(Global::getInstance()->getCurrentYear());
  itemSettings.setAgendaNum(Global::getInstance()->getCurrentEtvNumber());

  //set next id for new entry
  if (0 != ui->tableAgenda->model())
    itemSettings.setAgendaItemId(ui->tableAgenda->model()->rowCount() + 1);

  itemSettings.update();
  itemSettings.show();

  if (itemSettings.exec() != QDialog::Rejected)
    updateAgendaTable();
}

void AgendaTab::on_editEntry_clicked()
{
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

void AgendaTab::on_deleteEntry_clicked()
{
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

void AgendaTab::on_moveAgendaItemUp_clicked()
{
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

void AgendaTab::on_moveAgendaItemDown_clicked()
{
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
