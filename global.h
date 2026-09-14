#ifndef Global_H
#define Global_H

#include <QtSql>
#include "global.h"

#define INVALID -99999
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

enum voteType
{
  eHead = 0,
  eVoice = 1
};

enum settingsType
{
  eDbConnectionName = 0
};

class Global
{
public:
    static Global *getInstance();
    //void setGlobal (QSqlGlobal* pDb);
    //QSqlGlobal* getGlobal ();

    //does not really belong here (to lazy to move this somewhere else and it does its job)
    int getCurrentPropertyId ();
    void setCurrentPropertyId (int aId);
    void setCurrentEtvNumber (int aNumber);
    int getCurrentEtvNumber ();
    int getCurrentYear ();
    void setCurrentYear (int aYear);
    //const QString getTextPattern (eTextPattern aId);
    //bool dbIsOk ();
    //void execQuery (QSqlQuery* query);

protected:
    //QSqlGlobal* mDb;

private:
    Global(void);
    ~Global(void);

    int mPropertyId;
    int mYear;
    int mEtvNumber;
};

#endif // Global_H
