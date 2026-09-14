#include "presencechangedialog.h"
#include "ui_presencechangedialog.h"

presenceChangeDialog::presenceChangeDialog(QWidget *parent, QString &rDbConnectionName, int curEstateId, int curYear, int curAgendaNum) :
  QDialog(parent),
  ui(new Ui::presenceChangeDialog)
{
  ui->setupUi(this);

  setDbConnectionName(rDbConnectionName);
  setPropertyId(curEstateId);
  setYear(curYear);
  setAgendaNum(curAgendaNum);

  mDbConnectionName = "";
  mPropertyId = 0;
  mYear = 0;
  mAgendaNum = 0;
}

presenceChangeDialog::~presenceChangeDialog()
{
  delete ui;
}
