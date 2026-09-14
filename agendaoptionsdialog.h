#ifndef AGENDAOPTIONSDIALOG_H
#define AGENDAOPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
  class AgendaOptionsDialog;
}

class AgendaOptionsDialog : public QDialog
{
  Q_OBJECT

public:
  enum returnValue
  {
    editAgenda,
    abortDialog,
    editProtocolTranscript,
    generateProtocolCover,
    generateProtocol,
    generateDocuments,
    undefined
  };

  explicit AgendaOptionsDialog(QWidget *parent = 0);
  ~AgendaOptionsDialog();
  int result () const;

signals:
  void buttonClicked(int aRetVal);

private slots:
  void on_editAgenda_clicked();
  void on_abortDialog_clicked();
  void on_generateProtocol_clicked();
  void on_generateDocuments_clicked();
  void on_editProtocolTranscript_clicked();

private:
  Ui::AgendaOptionsDialog *ui;
  returnValue mRetVal;
};

#endif // AGENDAOPTIONSDIALOG_H
