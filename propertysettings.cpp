#include "propertysettings.h"
#include "ui_propertysettings.h"
#include <QtCore>
#include "stringreplacer.h"
#include <QMessageBox>

PropertySettings::PropertySettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PropertySettings)
{
  ui->setupUi(this);

  //prevent dialog from blocking application
  this->setWindowModality(Qt::NonModal);
}

void PropertySettings::setPropertyName (QString name)
{
  ui->propertyName->setText(name);
}
void PropertySettings::setMea(float mea)
{
  ui->mea->setValue((double)mea);
}
void PropertySettings::setVotingRule (const QString rVotingRule)
{
  ui->votingType->setText(rVotingRule);
}
void PropertySettings::setOwnerQuantity (int ownerQuantity)
{
  ui->ownerQuantity->setValue(ownerQuantity);
}

void PropertySettings::setpropertyId (long aId)
{
  QString value = QString::number(aId);
  ui->propertyId->setText(value);
}

void PropertySettings::setInvitationDeadline (QString aWeeks)
{
  ui->deadline->setText(aWeeks);
}

QString PropertySettings::getInvitationDeadline ()
{
  return ui->deadline->toHtml();
}

QString PropertySettings::propertyName () const
{
  return ui->propertyName->text();
}

float PropertySettings::mea () const
{
  return ui->mea->value();
}

QString PropertySettings::votingRule () const
{
  return ui->votingType->toHtml();
}

int PropertySettings::ownerQuantity () const
{
  return ui->ownerQuantity->value();
}

PropertySettings::~PropertySettings()
{
  delete ui;
}

void PropertySettings::accept ()
{
  if ("" == propertyName ())
  {
    QMessageBox::warning(this, "Fehler", "Kein Liegenschaftsnahme angegeben.", QMessageBox::Discard);
  }
  else if (0 == ownerQuantity ())
  {
    QMessageBox::warning(this, "Fehler", "Keine Eigentümeranzahl angegeben.", QMessageBox::Discard);
  }
  else if ("" == votingRule ())
  {
    QMessageBox::warning(this, "Fehler", "Angaben zum Stimmrecht fehlen.", QMessageBox::Discard);
  }
  else if (0 == mea())
  {
    QMessageBox::warning(this, "Fehler", "Keine Miteigentumsanteile eingetragen.", QMessageBox::Discard);
  }
  else if ("" == getInvitationDeadline ())
  {
    QMessageBox::warning(this, "Fehler", "Keine Einladungsfrist angegeben.", QMessageBox::Discard);
  }
  else
  {
    done (QDialog::Accepted);
  }
}
