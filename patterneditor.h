#ifndef PATTERNEDITOR_H
#define PATTERNEDITOR_H

#include <QDialog>

class QSqlQueryModelImpl;

namespace Ui {
  class PatternEditor;
}

class PatternEditor : public QDialog
{
  Q_OBJECT

public:
  explicit PatternEditor(QWidget *parent = 0);
  ~PatternEditor();
  void updatePatternTable ();
  void setUser (QString user);

private slots:
  void on_editEntry_clicked();
  void on_tablePatterns_doubleClicked(const QModelIndex &index);
  void on_addEntry_clicked();
  void on_deleteEntry_clicked();

private:
  void changePatternItemSettings (int aId);
  Ui::PatternEditor *ui;
  QSqlQueryModelImpl* mQueryModel;
  QString mUser;
};

#endif // PATTERNEDITOR_H
