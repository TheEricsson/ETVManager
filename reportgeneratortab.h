#ifndef REPORTGENERATORTAB_H
#define REPORTGENERATORTAB_H

#include <QWidget>
#include <QPair>
#include <QList>
#include <QString>
#include <QStringList>
#include "wizarddialogbox.h"
#include "global.h"

class QSqlQueryModelImpl;

namespace Ui {
  class ReportGeneratorTab;
}

class ReportGeneratorTab : public QWidget
{
  Q_OBJECT

public:
  explicit ReportGeneratorTab(QWidget *parent = 0);
  void refreshOnSelected ();
  void setParameter (settingsType aParameter, QString aSetting);
  ~ReportGeneratorTab();

private slots:
  void on_startWizard_clicked();
  void on_startAgendaWizard_clicked();
  void on_tableAgenda_doubleClicked(const QModelIndex &index);
  void on_tableReportTemplate_doubleClicked(const QModelIndex &index);
  void on_addEntry_clicked();
  void on_editEntry_clicked();
  void on_moveAgendaItemUp_clicked();
  void on_moveAgendaItemDown_clicked();
  void on_deleteEntry_clicked();
  void on_addDecission_clicked();

private:
  void startCoverpageWizard ();
  void startAgendaWizardTest ();
  void startAgendaWizard ();
  bool getSavedDecissions (std::vector<QStringList> &stringList);
  bool getAgendaItems (std::vector<QStringList> &stringList);
  bool getCoverpageItems (QStringList &stringList);
  void updateAgendaTable ();
  void updateReportTemplateTable ();
  void changeAgendaItemSettings (int aId);
  int processWizardDialog (QString aDialogText, QString aWildcard, eDlgType aType = eSimpleDialog, bool aMultipleChoice = false, QStringList aList = QStringList(""));

  Ui::ReportGeneratorTab *ui;
  bool mMarkerVersammlungsleiterFktSet;
  bool mMarkerProtokollfuehrerFktSet;
  QSqlQueryModelImpl* mQueryModel;
  QSqlQueryModelImpl* mQueryModelReportTemplate;
  std::vector<QStringList> mStringListVector;
  QString mUser;
};

#endif // REPORTGENERATORTAB_H
