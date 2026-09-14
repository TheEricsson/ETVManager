#include "protocolDecissionGenerator.h"
#include "ui_ProtocolDecissionGenerator.h"
#include "QSqlQueryModelProtocolGeneratorView.h"
#include "agendawizard.h"
#include <QMessageBox>
#include "global.h"
#include "presencechangedialog.h"
#include "decissionitemsettings.h"

ProtocolDecissionGenerator::ProtocolDecissionGenerator(QWidget *parent, QString &rDbConnectionName, int curEstateId, int agendaYear, int agendaNum) :
  QWidget(parent),
  ui(new Ui::protocolDecissionGenerator)
{
  ui->setupUi(this);
  ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Zurück zur Übersicht");

  setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

  mView = 0;
  mAgendaWizard = 0;

  mDbConnectionName = rDbConnectionName;
  mEstateId = curEstateId;
  mAgendaYear = agendaYear;
  mAgendaNum = agendaNum;

  initTableView();
  updateTableView();
}

ProtocolDecissionGenerator::~ProtocolDecissionGenerator()
{
  if (0 != mView)
    delete mView;

  if (0 != mAgendaWizard)
    delete mAgendaWizard;

  delete ui;
}

void ProtocolDecissionGenerator::initTableView ()
{
  if (0 == mView)
  {
    mView = new QSqlQueryModelProtocolGeneratorView ();
    ui->tableView->setModel(mView);
    ui->tableView->show();
  }
}

void ProtocolDecissionGenerator::updateTableView ()
{
  if (0 != mView)
  {
    mView->setDbConnectionName(mDbConnectionName);
    mView->setPropertyId(mEstateId);
    mView->setYear(mAgendaYear);
    mView->setAgendaNum(mAgendaNum);
    mView->updateData ();
  }
}

void ProtocolDecissionGenerator::on_startAgendaWizard_clicked()
{
  mAgendaWizard = new AgendaWizard (mDbConnectionName, mEstateId, mAgendaYear, mAgendaNum);

  if (0 != mAgendaWizard)
  {
    mAgendaWizard->process();
    updateTableView();

    delete mAgendaWizard;
    mAgendaWizard = 0;
  }
}

void ProtocolDecissionGenerator::on_moveEntryUp_clicked()
{
  int selectedRow = ui->tableView->selectionModel()->selection().indexes().value(0).row();
  int protocolId = ui->tableView->model()->index(selectedRow,2).data().toInt();

  if (1 == protocolId)
  {
    QMessageBox lMsgBox (this);
    lMsgBox.setText("Der Beschluss kann nicht weiter nach oben verschoben werden.");
    lMsgBox.setWindowTitle("Fehler");
    lMsgBox.exec();
    ui->tableView->setFocus();
    ui->tableView->selectRow(selectedRow);
  }
  else
  {
    mView->moveRowUp(protocolId);
    ui->tableView->setFocus();
    ui->tableView->selectRow(selectedRow - 1);
  }
}

void ProtocolDecissionGenerator::on_moveEntryDown_clicked()
{
  int selectedRow = ui->tableView->selectionModel()->selection().indexes().value(0).row();
  int protocolId = ui->tableView->model()->index(selectedRow,2).data().toInt();

  int rows = ui->tableView->model()->rowCount();
  if (rows == selectedRow + 1 || rows == protocolId)
  {
    QMessageBox lMsgBox (this);
    lMsgBox.setText("Der Beschluss kann nicht weiter nach unten verschoben werden.");
    lMsgBox.setWindowTitle("Fehler");
    lMsgBox.exec();
    ui->tableView->setFocus();
    ui->tableView->selectRow(selectedRow);
  }
  else
  {
    mView->moveRowDown(protocolId);
    ui->tableView->setFocus();
    ui->tableView->selectRow(selectedRow + 1);
  }
}

void ProtocolDecissionGenerator::on_addChangeRules_clicked()
{

}

void ProtocolDecissionGenerator::on_addChangePresence_clicked()
{
  presenceChangeDialog presenceDlg (this, mDbConnectionName, mEstateId, mAgendaYear, mAgendaNum);
  presenceDlg.update();
  presenceDlg.show();

  if (presenceDlg.exec() != QDialog::Rejected)
    updateTableView();
}

void ProtocolDecissionGenerator::on_buttonBox_accepted()
{
  emit exitView();
}

void ProtocolDecissionGenerator::on_deleteAllEntries_clicked()
{
  int ret = QMessageBox::warning(this, tr("ETVManager"),
                                 tr("Achtung. Bestätigung des Dialogs\n"
                                    "entfernt alle generierten Beschlüsse.\n"
                                    "Fortfahren?"),
                                 QMessageBox::Ok | QMessageBox::Cancel);

  switch (ret)
  {
    case QMessageBox::Ok:
      mView->deleteEntries ();
      // Save was clicked
      break;
    case QMessageBox::Cancel:
      // Cancel was clicked
      break;
    default:
      // should never be reached
      break;
  }
}

void ProtocolDecissionGenerator::on_tableView_doubleClicked (const QModelIndex &index)
{
  if (ui->tableView->selectionModel()->selectedRows().count() == 1)
  {
    int id = ui->tableView->model()->index(index.row(),0).data().toInt();
    changeDecissionItem(id);
  }
}

void ProtocolDecissionGenerator::changeDecissionItem(int id)
{
  DecissionItemSettings decItemSettings (this, mDbConnectionName, mEstateId, mAgendaYear, mAgendaNum, id);

  decItemSettings.update();
  decItemSettings.show();

  if (decItemSettings.exec() != QDialog::Rejected)
  {
    decItemSettings.saveValues ();
    updateTableView();
  }
}
