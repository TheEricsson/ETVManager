#include "agendaoptionsdialog.h"
#include "ui_agendaoptionsdialog.h"

AgendaOptionsDialog::AgendaOptionsDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AgendaOptionsDialog)
{
  ui->setupUi(this);
  mRetVal = AgendaOptionsDialog::undefined;
}

AgendaOptionsDialog::~AgendaOptionsDialog()
{
  delete ui;
}

int AgendaOptionsDialog::result () const
{
  return (int)mRetVal;
}

void AgendaOptionsDialog::on_editAgenda_clicked()
{
  mRetVal = AgendaOptionsDialog::editAgenda;
  this->accept();
}

void AgendaOptionsDialog::on_abortDialog_clicked()
{
  mRetVal = AgendaOptionsDialog::abortDialog;
  this->reject();
}

void AgendaOptionsDialog::on_generateProtocol_clicked()
{
  mRetVal = AgendaOptionsDialog::generateProtocol;
  this->accept();
}

void AgendaOptionsDialog::on_generateDocuments_clicked()
{
  mRetVal = AgendaOptionsDialog::generateDocuments;
  this->accept();
}

void AgendaOptionsDialog::on_editProtocolTranscript_clicked()
{
  mRetVal = AgendaOptionsDialog::editProtocolTranscript;
  this->accept();
}
