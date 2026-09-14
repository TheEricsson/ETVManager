#ifndef PRESENCECHANGEDIALOG_H
#define PRESENCECHANGEDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
  class presenceChangeDialog;
}

class presenceChangeDialog : public QDialog
{
  Q_OBJECT

public:
  explicit presenceChangeDialog(QWidget *parent, QString &rDbConnectionName, int curEstateId, int curYear, int curAgendaNum);

  ~presenceChangeDialog();

private:
  Ui::presenceChangeDialog *ui;

  void setDbConnectionName(QString &connName) {mDbConnectionName = connName;};
  void setPropertyId(int aPropertyId) {mPropertyId = aPropertyId;};
  void setYear(int aYear) {mYear = aYear;};
  void setAgendaNum(int aAgendaNum) {mAgendaNum = aAgendaNum;};

  QString mDbConnectionName;
  int mPropertyId;
  int mYear;
  int mAgendaNum;

};

#endif // PRESENCECHANGEDIALOG_H
