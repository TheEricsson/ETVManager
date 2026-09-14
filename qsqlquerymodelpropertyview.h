#ifndef QSQLQUERYMODELPROPERTYVIEW_H
#define QSQLQUERYMODELPROPERTYVIEW_H

#include "QSqlQueryModelImpl.h"

class QSqlQueryModelPropertyView : public QSqlQueryModelImpl
{
  Q_OBJECT
public:
  explicit QSqlQueryModelPropertyView(QObject *parent = 0);
  bool updateData ();

public slots:

private:
  bool reorganizeIds ();

};

#endif // QSQLQUERYMODELPROPERTYVIEW_H
