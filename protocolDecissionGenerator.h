#ifndef PROTOCOLDECISSIONGENERATOR_H
#define PROTOCOLDECISSIONGENERATOR_H

#include <QWidget>
#include <QModelIndex>

class QSqlQueryModelProtocolGeneratorView;
class AgendaWizard;

namespace Ui {
  class protocolDecissionGenerator;
}

class ProtocolDecissionGenerator : public QWidget
{
  Q_OBJECT

public:
  explicit ProtocolDecissionGenerator(QWidget *parent, QString &rDbConnectionName, int curEstateId, int agendaYear, int agendaNum);
  ~ProtocolDecissionGenerator();

signals:
  void exitView ();

private slots:
  void on_startAgendaWizard_clicked();
  void on_moveEntryUp_clicked();
  void on_moveEntryDown_clicked();
  void on_addChangeRules_clicked();
  void on_addChangePresence_clicked();
  void on_buttonBox_accepted();
  void on_deleteAllEntries_clicked();
  void on_tableView_doubleClicked (const QModelIndex &index);

private:
  void initTableView();
  void updateTableView ();
  void changeDecissionItem (int aId);
  Ui::protocolDecissionGenerator *ui;
  QSqlQueryModelProtocolGeneratorView* mView;
  QString mDbConnectionName;
  int mEstateId;
  int mAgendaYear;
  int mAgendaNum;

  AgendaWizard* mAgendaWizard;
};

#endif // PROTOCOLDECISSIONGENERATOR_H
