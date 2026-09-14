#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QtSql>
#include "qsqlconnectiondialog.h"
#include <QString>
#include "global.h"

namespace Ui {
class propertyMainView;
}

QT_FORWARD_DECLARE_CLASS(QSqlError)

class PropertyOverview;
class ConnectionWidget;
class QStandardItemModelPropertyOverview;
class ProtocolDecissionGenerator;
class AgendaDialog;

enum tabSelection
{
    ePropertySelectionTab = 0,
    eAgendaTab = 1,
    eOrderTab = 2,
    eReportGeneratorTab = 3,
    eDecissionLibraryTab = 4,
    eGeneratorTab = 5
};

class propertyMainView : public QWidget
{
    Q_OBJECT

public:
    explicit propertyMainView(QWidget *parent, QString &rDbConnectionName, int curEstateId);
    void setHeader (const QString &header);
    ~propertyMainView();

signals:
    exitPropertyView ();

private slots:
    void on_treeView_doubleClicked(const QModelIndex &index);
    void on_exitButton_clicked();
    void on_newAgendaButton_clicked();
    void on_editButton_clicked();
    void killProtocolGeneratorView ();
    void killAgendaWidget();

private:
    void openProperty();
    bool dbIsOk();
    void setCurrentEstateId (const int value);
    void setConnectionName (QString value);
    void updateMainView();

    void showAgendaOptionsDialog ();
    void showAgendaView ();
    void showNewAgendaMenu();
    void showProtocolTranscriptEditor ();
    void showProtocolGenerator ();
    void showDocumentGenerator ();

    Ui::propertyMainView *ui;
    QSqlDatabase db;

    int mCurrentEstateId;
    PropertyOverview* mPropertyOverview;
    ProtocolDecissionGenerator* mProtocolDecissionGenerator;
    QString mDbConnectionName;
    QStandardItemModelPropertyOverview* mItemModelTree;
    AgendaDialog* mAgendaWidget;
};

#endif // MAINVIEW_H
