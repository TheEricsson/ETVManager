#ifndef QSqlQueryModelImpl_H
#define QSqlQueryModelImpl_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class QSqlQueryModelImpl : public QSqlQueryModel
{
  public:
    QSqlQueryModelImpl (QObject *parent = 0);
    virtual ~QSqlQueryModelImpl();
    QVariant data(const QModelIndex &index, int role) const;
    void setDbConnectionName (QString &dbName);
    void setPropertyId (int propId);
    void setYear (int year);
    void setAgendaNum (int agendaNum);
    bool runSqlQuery (QSqlQuery &query);
    virtual bool moveRowUp (int aSourceRow);
    virtual bool moveRowDown (int aSourceRow);

    QString getDbConnectionName () {return mDbConnectionName;};
    int getPropertyId () {return mPropertyId;};
    int getYear () {return mYear;};
    int getAgendaNum () {return mAgendaNum;};

  private:
    QString mDbConnectionName;
    int mPropertyId;
    int mYear;
    int mAgendaNum;
};

#endif // QSqlQueryModelImpl_H
