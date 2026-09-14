#ifndef QSQLQUERYMODELAGENDAVIEW_H
#define QSQLQUERYMODELAGENDAVIEW_H

#include "QSqlQueryModelImpl.h"

class QSqlQueryModelAgendaView : public QSqlQueryModelImpl
{
  Q_OBJECT
public:
  explicit QSqlQueryModelAgendaView(QObject *parent = 0);
  bool updateData ();
  bool removeRow (int aItemId);
  bool moveRowUp (int aItemId);
  bool moveRowDown (int aItemId);

public slots:

private:
  bool reorganizeIds ();

};

#endif // QSQLQUERYMODELAGENDAVIEW_H
