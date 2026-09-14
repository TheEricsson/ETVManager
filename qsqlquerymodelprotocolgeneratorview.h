#ifndef QSQLQUERYMODELPROTOCOLGENERATORVIEW_H
#define QSQLQUERYMODELPROTOCOLGENERATORVIEW_H

#include "QSqlQueryModelImpl.h"

class QSqlQueryModelProtocolGeneratorView : public QSqlQueryModelImpl
{
public:
  explicit QSqlQueryModelProtocolGeneratorView (QObject *parent = 0);
  bool updateData ();
  bool moveRowUp(int aSourceRow);
  bool moveRowDown(int aSourceRow);
  bool deleteEntry (int aRow);
  bool deleteEntries ();
};

#endif // QSQLQUERYMODELPROTOCOLGENERATORVIEW_H
