#ifndef PROPERTYSETTINGS_H
#define PROPERTYSETTINGS_H

#include <QDialog>
#include "global.h"

namespace Ui {
class PropertySettings;
}

class PropertySettings : public QDialog
{
    Q_OBJECT

public:
    PropertySettings(QWidget *parent = 0);
    void setPropertyName (QString name);
    void setMea(float mea);
    void setVotingRule (const QString rVotingRule);
    void setOwnerQuantity (int ownerQuantity);
    void setpropertyId (long aId);
    void setInvitationDeadline (QString aValue);
    QString getInvitationDeadline ();
    const QString& getAdviserPresident ();
    const QString& getAdviser1 ();
    const QString& getAdviser2 ();

    QString propertyName () const;
    float mea () const;
    QString votingRule () const;
    int ownerQuantity () const;
    virtual ~PropertySettings();

private:
    void accept ();
    Ui::PropertySettings *ui;
};

#endif // PROPERTYSETTINGS_H
