#include "Global.h"

Global::Global()
{
  mPropertyId = INVALID;
  mYear = INVALID;
  mEtvNumber = INVALID;
}

Global::~Global()
{
}

Global* Global::getInstance()
{
  static Global theInstance;
  return &theInstance;
}

int Global::getCurrentPropertyId ()
{
  if (mPropertyId == INVALID)
      qDebug() << "mPropertyId is not valid";

  return mPropertyId;
}

void Global::setCurrentPropertyId (int aId)
{
  mPropertyId = aId;
  qDebug() << "current property id: " << mPropertyId;
}

void Global::setCurrentEtvNumber (int aNumber)
{
  mEtvNumber = aNumber;
  qDebug() << "current etv number: " << mEtvNumber;
}

int Global::getCurrentEtvNumber ()
{
  if (mEtvNumber == INVALID)
      qDebug() << "mEtvNumber is not valid";

  return mEtvNumber;
}

int Global::getCurrentYear ()
{
  if (mYear == INVALID)
      qDebug() << "mYear is not valid";

  return mYear;
}

void Global::setCurrentYear (int aYear)
{
  mYear = aYear;
  qDebug() << "current year: " << mYear;
}
