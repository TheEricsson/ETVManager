#ifndef AGENDAITEMSETTINGS_H
#define AGENDAITEMSETTINGS_H

#include <QDialog>

namespace Ui {
class AgendaItemSettings;
}

class QSqlQueryModelImpl;

namespace AgendaItemDialogMode {
  enum type {
    update,
    insert,
  };
}

class AgendaItemSettings : public QDialog
{
    Q_OBJECT

public:
    explicit AgendaItemSettings(QWidget *parent = 0);
    ~AgendaItemSettings();

    void setDbConnectionName(QString &connName) {mDbConnectionName = connName;};
    void setPropertyId(int aPropertyId) {mPropertyId = aPropertyId;};
    void setYear(int aYear) {mYear = aYear;};
    void setAgendaNum(int aAgendaNum) {mAgendaNum = aAgendaNum;};
    void setAgendaItemId(int aAgendaItemId) {mAgendaItemId = aAgendaItemId;};
    void setdialogMode(AgendaItemDialogMode::type aType) {mType = aType;};

    QString getHeader ();
    QString getDescription ();
    QString getSuggestion ();
    QString getSuggestion2 ();
    QString getSuggestion3 ();
    int getItemType ();

    void update ();
    void setHeader (QString rValue);
    void setDescription (QString rValue);
    void setSuggestion (QString rValue);
    void setSuggestion2 (QString rValue);
    void setSuggestion3 (QString rValue);
    void setItemType (int aType);

private slots:
    void on_insertPattern_clicked();
    void on_buttonBox_accepted();

private:
    void updateTextPatterns ();
    void refreshAgendaItem ();

    QString replaceWildcards (QString in);
    Ui::AgendaItemSettings *ui;
    QSqlQueryModelImpl* m_model;

    QString mDbConnectionName;
    int mPropertyId;
    int mYear;
    int mAgendaNum;
    int mAgendaItemId;
    AgendaItemDialogMode::type mType;

};

#endif // AGENDAITEMSETTINGS_H
