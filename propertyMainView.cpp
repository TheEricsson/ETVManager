#include "propertyMainView.h"
//#include "ui_propertymainview.h"
#include "propertysettings.h"
#include "agendadialog.h"
#include <QSqlTableModel>
#include <QtWidgets>
#include <QtSql>
#include "ordertab.h"
#include "generatorWidget.h"
#include "patterneditor.h"
#include "patterneditorreport.h"
#include "systemsettings.h"
//#include "reportgeneratortab.h"
#include "stringreplacer.h"
#include "decissionlibrarytab.h"
#include "propertylistdialog.h"
#include "qstandarditemmodelpropertyoverview.h"
#include "agendaoptionsdialog.h"
#include <QDebug>
#include "global.h"
#include "protocolDecissionGenerator.h"
#include "ui_propertymainview.h"


propertyMainView::propertyMainView(QWidget *parent, QString &rDbConnectionName, int curEstateId) :
    QWidget(parent),
    ui(new Ui::propertyMainView)
{
  ui->setupUi(this);
  setConnectionName(rDbConnectionName);
  setCurrentEstateId(curEstateId);

  setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

  mItemModelTree = 0;
  mProtocolDecissionGenerator = 0;
  mAgendaWidget = 0;

  openProperty();
}

void propertyMainView::setHeader (const QString &header)
{
  this->ui->label->setText(header);
}

void propertyMainView::setConnectionName (const QString value)
{
  this->mDbConnectionName = value;
}

void propertyMainView::setCurrentEstateId (const int value)
{
  this->mCurrentEstateId = value;
}

propertyMainView::~propertyMainView()
{
  delete ui;

  if (0 != mProtocolDecissionGenerator)
    delete mProtocolDecissionGenerator;

  if (0 != mItemModelTree)
    delete mItemModelTree;

  if (0 != mAgendaWidget)
    delete mAgendaWidget;
}

void propertyMainView::openProperty()
{
  if (0 != mItemModelTree)
  {
    delete mItemModelTree;
    mItemModelTree = 0;
  }

  mItemModelTree = new QStandardItemModelPropertyOverview ();
  if (0 != mItemModelTree)
  {
    if (true == mItemModelTree->populate(mDbConnectionName, mCurrentEstateId))
    {
      ui->treeView->setModel(mItemModelTree);
    }
  }
}

void propertyMainView::on_treeView_doubleClicked(const QModelIndex &index)
{
  showAgendaOptionsDialog ();
}

void propertyMainView::showAgendaOptionsDialog ()
{
  AgendaOptionsDialog dlg;
  if (QDialog::Accepted == dlg.exec())
  {
    AgendaOptionsDialog::returnValue retVal = AgendaOptionsDialog::undefined;
    retVal = (AgendaOptionsDialog::returnValue) dlg.result();

    switch (retVal)
    {
      case AgendaOptionsDialog::editAgenda:
        showAgendaView ();
        break;
      case AgendaOptionsDialog::editProtocolTranscript:
        showProtocolTranscriptEditor ();
        break;
      case AgendaOptionsDialog::generateProtocol:
        showProtocolGenerator ();
        break;
      case AgendaOptionsDialog::generateDocuments:
        showDocumentGenerator ();
        break;
      default:
        break;
    };
  }
}

void propertyMainView::showAgendaView ()
{
  int selectedYear = ui->treeView->selectionModel()->selectedRows(0).value(0).data().toInt();
  int selectedAgendaNum = ui->treeView->selectionModel()->selectedRows(1).value(0).data().toInt();

  mAgendaWidget = new AgendaDialog (this, mDbConnectionName, mCurrentEstateId, selectedYear, selectedAgendaNum);
  if (0 != mAgendaWidget)
  {
    connect (mAgendaWidget, SIGNAL (exitWidget()), this, SLOT (killAgendaWidget()));
    mAgendaWidget->show();
  }
}

void propertyMainView::showNewAgendaMenu()
{
    //todo
}

void propertyMainView::showProtocolTranscriptEditor ()
{
    //todo
}

void propertyMainView::showProtocolGenerator ()
{
  int selectedYear = ui->treeView->selectionModel()->selectedRows(0).value(0).data().toInt();
  int selectedAgendaNum = ui->treeView->selectionModel()->selectedRows(1).value(0).data().toInt();

  mProtocolDecissionGenerator = new ProtocolDecissionGenerator (this, mDbConnectionName, mCurrentEstateId, selectedYear, selectedAgendaNum);
  if (0 != mProtocolDecissionGenerator)
  {
    connect (mProtocolDecissionGenerator, SIGNAL (exitView()), this, SLOT (killProtocolGeneratorView ()));
    mProtocolDecissionGenerator->show ();
  }
}

void propertyMainView::killProtocolGeneratorView ()
{
  if (0 != mProtocolDecissionGenerator)
  {
    delete mProtocolDecissionGenerator;
    mProtocolDecissionGenerator = 0;
  }
}

void propertyMainView::killAgendaWidget()
{
  if (0 != mAgendaWidget)
  {
    delete mAgendaWidget;
    mAgendaWidget = 0;
  }
}

void propertyMainView::showDocumentGenerator()
{
    qDebug () <<"todo: implement propertyMainView::showDocumentGenerator";
}

void propertyMainView::on_exitButton_clicked()
{
  emit exitPropertyView ();
}

void propertyMainView::on_newAgendaButton_clicked()
{
    showNewAgendaMenu();
    qDebug ()<<"hello";
}

void propertyMainView::on_editButton_clicked()
{
  showAgendaOptionsDialog ();
}
