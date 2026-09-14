#ifndef AGENDATAB_H
#define AGENDATAB_H

#include <QWidget>
#include "global.h"

class QSqlDatabase;
class QSqlQueryModelAgendaView;

namespace Ui {
class AgendaTab;
}

class AgendaTab : public QWidget
{
    Q_OBJECT

public:
    AgendaTab(QWidget *parent = 0);
    void refreshOnSelected ();
    void refresh ();
    void setParameter (settingsType aParameter, QString aSetting);
    virtual ~AgendaTab();

signals:
    void exitView ();

private slots:
    void on_tableAgenda_doubleClicked(const QModelIndex &index);
    void on_addEntry_clicked();
    void on_editEntry_clicked();
    void on_deleteEntry_clicked();
    void on_moveAgendaItemUp_clicked();
    void on_moveAgendaItemDown_clicked();

private:
    void initAgendaTable ();
    void updateAgendaTable ();
    void changeAgendaItemSettings (int aTopId);
    Ui::AgendaTab *ui;
    QSqlQueryModelAgendaView* mQueryModelAgendaView;
    QString mUser;
};

#endif // AGENDATAB_H
