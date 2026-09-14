#ifndef PATTERNITEMSETTINGS_H
#define PATTERNITEMSETTINGS_H

#include <QDialog>

namespace Ui {
  class PatternItemSettings;
}

class PatternItemSettings : public QDialog
{
  Q_OBJECT

public:
  explicit PatternItemSettings(QWidget *parent = 0);
  ~PatternItemSettings();

  QString getPatternName ();
  QString getHeader ();
  QString getDescription ();
  QString getSuggestion ();
  QString getSuggestion2 ();
  QString getSuggestion3 ();
  int getNumberOfLines ();
  int getType ();

  void setNumberOfLines(int aNumber);
  void refresh ();

  void setPatternName (const QString &rValue);
  void setHeader(QString rValue);
  void setDescription(QString rValue);
  void setSuggestion(QString rValue);
  void setSuggestion2(QString rValue);
  void setSuggestion3(QString rValue);
  void setType (int aType);

private slots:
  void on_insertWildcard_clicked();

private:
  bool eventFilter(QObject *object, QEvent *event);
  Ui::PatternItemSettings *ui;

  enum eFocussedTextView
  {
    eNone,
    eHeader,
    eDescription,
    eSuggestion,
    eSuggestion2,
    eSuggestion3,
  };

  eFocussedTextView mFocussedView;
};

#endif // PATTERNITEMSETTINGS_H
