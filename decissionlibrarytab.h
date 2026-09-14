#ifndef DECISSIONLIBRARYTAB_H
#define DECISSIONLIBRARYTAB_H

#include <QWidget>
#include <QString>
#include "global.h"

class QSqlDatabase;
class QSqlQueryModelImpl;

namespace Ui {
  class DecissionLibraryTab;
}

class DecissionLibraryTab : public QWidget
{
  Q_OBJECT

public:
  explicit DecissionLibraryTab(QWidget *parent = 0);
  void refreshOnSelected ();
  void setParameter (settingsType aParameter, QString aSetting);
  ~DecissionLibraryTab();

private slots:
  void on_tableAgenda_doubleClicked(const QModelIndex &index);
  void on_editEntry_clicked();

private:
  void updateAgendaTable ();
  void changeAgendaItemSettings (int aId);
  Ui::DecissionLibraryTab *ui;
  QSqlQueryModelImpl* mQueryModel;
  QSqlQueryModelImpl* mQueryModelReportTemplate;
  QString mUser;
};

#endif // DECISSIONLIBRARYTAB_H
