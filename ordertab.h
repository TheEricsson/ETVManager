#ifndef ORDERTAB_H
#define ORDERTAB_H

#include <QWidget>
#include <QString>
#include "global.h"

class QSqlDatabase;
class QSqlQueryModelImpl;

namespace Ui {
class OrderTab;
}

class OrderTab : public QWidget
{
    Q_OBJECT

public:
    OrderTab(QWidget *parent = 0);
    void refreshOnSelected ();
    void setParameter (settingsType aParameter, QString aSetting);
    void refresh ();
    virtual ~OrderTab();

signals:
    void selectTab (int);

private slots:
    void on_tableAgenda_doubleClicked(const QModelIndex &index);
    void on_tableReportTemplate_doubleClicked(const QModelIndex &index);
    void on_editButton_clicked();

private:
    //void initReportPattern ();
    void updateAgendaTable ();
    void updateReportTemplateTable ();
    void changeAgendaItemSettings (int aId);
    Ui::OrderTab *ui;
    QSqlQueryModelImpl* mQueryModel;
    QSqlQueryModelImpl* mQueryModelReportTemplate;

    QString mUser;
};

#endif // ORDERTAB_H
