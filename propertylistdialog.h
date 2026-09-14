#ifndef PROPERTYLISTDIALOG_H
#define PROPERTYLISTDIALOG_H

#include <QDialog>

class QSqlQueryModelPropertyView;

namespace Ui {
  class simpleListDialog;
}

class propertyListDialog : public QDialog
{
  Q_OBJECT

  public:

    explicit propertyListDialog(QWidget *parent = 0);
    void setDbConnectionName (QString &user);
    void updateDialog ();
    int getSelectedPropertyId ();
    QString getSelectedPropertyName () const;
    ~propertyListDialog();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    void initDialog ();
    Ui::simpleListDialog *ui;
    QSqlQueryModelPropertyView *mView;

    QString mUser;
    int mSelectedPropertyId;
    QString mSelectedPropertyName;
};

#endif // PROPERTYLISTDIALOG_H
