#ifndef AGENDAWIZARD_H
#define AGENDAWIZARD_H

#include <QString>
#include <QStringList>

class AgendaWizard
{
  public:
    AgendaWizard (QString &rDbConnectionName, int estateId, int agendaYear, int agendaNum);
    ~AgendaWizard();

    bool hasItems ();
    void process ();

  private:
    bool getAgendaItems ();
    bool getSavedDecissions ();

    QString mDbConnName;
    int mEstateId;
    int mAgendaYear;
    int mAgendaNum;
    bool mHasSavedDecissions;

    std::vector<QStringList> mStringListAgendaItems;
    std::vector<QStringList> mStringListSavedDecissions;
};

#endif // AGENDAWIZARD_H
