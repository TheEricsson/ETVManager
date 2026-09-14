#ifndef AGENDADIALOG_H
#define AGENDADIALOG_H

#include <QWidget>

class QSqlQueryModelAgendaView;

namespace Ui {
  class AgendaDialog;
}

class AgendaDialog : public QWidget
{
  Q_OBJECT

public:
  explicit AgendaDialog(QWidget *parent, QString &rDbConnName, int estateId, int agendaYear, int agendaNum);
  void updateAgendaTable();
  ~AgendaDialog();

private slots:
  void on_moveAgendaItemDown_clicked();
  void on_moveAgendaItemUp_clicked();
  void on_editEntry_clicked();
  void on_addEntry_clicked();
  void on_deleteEntry_clicked();
  void on_tableAgenda_doubleClicked(const QModelIndex &index);
  void on_buttonBox_accepted();

signals:
  void exitWidget();

private:
  void initAgendaTable ();
  void changeAgendaItemSettings (int aTopId);
  bool checkForExistingDecissions ();
  bool deleteExistingDecissions();

  Ui::AgendaDialog *ui;
  QSqlQueryModelAgendaView* mQueryModelAgendaView;
  QString mDbConnName;
  int mEstateId;
  int mAgendaYear;
  int mAgendaNum;
};

#endif // AGENDADIALOG_H
