#include "QSqlQueryModelImpl.h"
#include <QTextDocument>
#include <QSqlError>
#include <QMessageBox>

#define INVALID -1

QSqlQueryModelImpl::QSqlQueryModelImpl(QObject *parent)
{
  mDbConnectionName = "";
  mPropertyId = INVALID;
  mYear = INVALID;
  mAgendaNum = INVALID;
}

QSqlQueryModelImpl::~QSqlQueryModelImpl()
{

}

void QSqlQueryModelImpl::setDbConnectionName (QString &dbName)
{
  mDbConnectionName = dbName;
}

void QSqlQueryModelImpl::setPropertyId (int propId)
{
  mPropertyId = propId;
}

void QSqlQueryModelImpl::setYear (int year)
{
  mYear = year;
}

void QSqlQueryModelImpl::setAgendaNum (int agendaNum)
{
  mAgendaNum = agendaNum;
}

bool QSqlQueryModelImpl::runSqlQuery (QSqlQuery &query)
{
  bool retVal = false;

  retVal = query.exec();

  //handle sql error
  if (false == retVal)
  {
    QSqlError error;
    error = query.lastError();

    QString errMsg ("");
    errMsg.append("Fehlerausgabe Datenbank:\n");
    errMsg.append(error.databaseText());
    errMsg.append("\nFehlerausgabe Datenbanktreiber:\n");
    errMsg.append(error.driverText());

    QMessageBox msgBox;
    msgBox.setText("Schwerwiegender Fehler beim Ausführen eines Datenbankbefehls");
    msgBox.setInformativeText(errMsg);
    int ret = msgBox.exec();
  }
  return retVal;
}

bool QSqlQueryModelImpl::moveRowUp (int aSourceRow)
{

}

bool QSqlQueryModelImpl::moveRowDown (int aSourceRow)
{

}

QVariant QSqlQueryModelImpl::data(const QModelIndex &index, int role) const
{
  //remove html syntax from database entry
  //return as plain string
  // - just for tableview purpose

  QVariant value = QSqlQueryModel::data(index, role);

  if (value.isValid() && role == Qt::DisplayRole)
  {
    QTextDocument doc;
    doc.setHtml(value.toString());

    return doc.toPlainText();
  }
  return value;
}
