#ifndef GeneratorWidget_H
#define GeneratorWidget_H

#include <QWidget>
#include <QString>
#include "global.h"

class QTextTableFormat;

namespace Ui {
class GeneratorWidget;
}

class GeneratorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GeneratorWidget(QWidget *parent = 0);
    ~GeneratorWidget();
    void refreshOnSelected ();
    void setParameter (settingsType aParameter, QString aSetting);

private slots:
  void on_doOdt_clicked();
  void on_doPdf_clicked();

private:
    void setTableFormat (QTextTableFormat* pTableFormat);
    QString generateProcurationAsPdf (const QString &rFilePath);
    QString generateAgendaAsPdf (const QString &rFilePath);
    QString generateAgendaAsOdt (const QString &rFilePath);
    QString generateReportTemplateAsPdf (const QString &rFilePath);
    QString generateReportTranscriptAsPdf (const QString &rFilePath);
    QString generateDecissionLibraryAsPdf (const QString &rFilePath);
    //helpers
    QString replaceCoverPageTagsByUnderscore (QString in);
    Ui::GeneratorWidget *ui;

    QString mUser;
};

#endif // GeneratorWidget_H
