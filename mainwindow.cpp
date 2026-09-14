#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QPixmap>
#include "propertylistdialog.h"
#include "patterneditor.h"
#include "patterneditorreport.h"
#include "systemsettings.h"
#include "propertyMainView.h"
#include "propertysettings.h"
#include "QMessageBox"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  mDbConnectionName = "";
  mPropertyWindow = 0;

  ui->openProperty->setIcon(QIcon(":/resources/icons/open_property.png"));
  ui->systemSettings->setIcon(QIcon(":/resources/icons/settings.png"));
  ui->exitApplication->setIcon(QIcon(":/resources/icons/exit.png"));
  ui->newProperty->setIcon(QIcon(":/resources/icons/add_property.png"));
  ui->deleteProperty->setIcon(QIcon(":/resources/icons/delete_property.png"));
  ui->editPatterns->setIcon(QIcon(":/resources/icons/edit_patterns.png"));

  ui->openProperty->setIconSize(QSize(80,80));
  ui->systemSettings->setIconSize(QSize(80,80));
  ui->exitApplication->setIconSize(QSize(80,80));
  ui->newProperty->setIconSize(QSize(80,80));
  ui->deleteProperty->setIconSize(QSize(80,80));
  ui->editPatterns->setIconSize(QSize(80,80));

  ui->openProperty->setToolTip(QString("Bestandspflege"));
  ui->systemSettings->setToolTip(QString("Programmeinstellungen"));
  ui->exitApplication->setToolTip(QString("Programm beenden"));
  ui->newProperty->setToolTip(QString("Hinzufügen einer Liegenschaft"));
  ui->deleteProperty->setToolTip(QString("Löschen von Liegenschaften"));
  ui->editPatterns->setToolTip(QString("Vorlagen verwalten"));
}

void MainWindow::setDbConnectionName (QString rDbConnectionName)
{
  mDbConnectionName = rDbConnectionName;
}


MainWindow::~MainWindow()
{
  delete ui;

  if (0!= mPropertyWindow)
    delete mPropertyWindow;
}

void MainWindow::patternSettings ()
{
  PatternEditor editor (this);
  editor.setUser(mDbConnectionName);
  editor.updatePatternTable();
  editor.exec();
}

void MainWindow::reportSettings ()
{
  patternEditorReport editor (this);
  editor.setUser(mDbConnectionName);
  editor.updatePatternTable();
  editor.exec();
}

void MainWindow::systemSettings ()
{
  SystemSettings settings (this);
  settings.exec();
}

void MainWindow::openProperty()
{
  propertyListDialog dialog (this);
  dialog.setWindowTitle(QString("Liegenschaft öffnen"));
  dialog.setDbConnectionName(mDbConnectionName);
  dialog.updateDialog();

  if (QDialog::Accepted == dialog.exec())
  {
    int curEstateId = dialog.getSelectedPropertyId ();
    QString estateName = dialog.getSelectedPropertyName();

    if (curEstateId != INVALID)
    {
      mPropertyWindow = new propertyMainView (this, mDbConnectionName, curEstateId);
      mPropertyWindow->setHeader (estateName);

      if (0 != mPropertyWindow)
      {
        connect (mPropertyWindow, SIGNAL (exitPropertyView()), this, SLOT (killPropertyView ()));
        mPropertyWindow->show();
      }
    }
  }
}

void MainWindow::addProperty ()
{

}

void MainWindow::on_systemSettings_clicked()
{
  systemSettings();
}

void MainWindow::on_openProperty_clicked()
{
  this->openProperty();
}

void MainWindow::on_exitApplication_clicked()
{
  QApplication::exit();
}

void MainWindow::killPropertyView ()
{
  if (0 != mPropertyWindow)
  {
    mPropertyWindow->hide();
    delete mPropertyWindow;
    mPropertyWindow = 0;
  }
}

void MainWindow::on_editPatterns_clicked()
{
    this->patternSettings ();
}

void MainWindow::on_newProperty_clicked()
{
  PropertySettings dialog (this);
  dialog.setWindowTitle(QString("Liegenschaft hinzufügen"));

  if (QDialog::Accepted == dialog.exec())
  {
    //add property

    //get highest id
    int max_id = 0;
    QString request ("SELECT obj_id FROM Objekt ORDER BY obj_id DESC");
    QSqlQuery query (QSqlDatabase::database(mDbConnectionName));
    query.prepare(request);
    query.exec();

    if (query.next())
    {
      max_id = query.value(0).toInt();
      qDebug () << "max_id: " << max_id;

      if (0 != max_id)
      {
        QString propertyName = dialog.propertyName();
        QString invitationDeadline = dialog.getInvitationDeadline();
        int ownerQuantity = dialog.ownerQuantity();
        QString votingRule = dialog.votingRule();
        float mea = dialog.mea();
        int nextId = ++max_id;

        query.prepare("INSERT INTO Objekt (obj_id, obj_name, obj_mea, obj_stimmrecht, obj_anz_et, obj_inv_deadline) VALUES (:obj_id, :obj_name, :obj_mea, :obj_stimmrecht, :obj_anz_et, :obj_inv_deadline)");
        query.bindValue(":obj_id", nextId);
        query.bindValue(":obj_name", propertyName);
        query.bindValue(":obj_mea", mea);
        query.bindValue(":obj_stimmrecht", votingRule);
        query.bindValue(":obj_anz_et", ownerQuantity);
        query.bindValue(":obj_inv_deadline", invitationDeadline);
        query.exec();
      }
    }
  }
}
