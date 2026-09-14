#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class propertyMainView;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QWidget
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  void setDbConnectionName (QString rDbConnectionName);
  ~MainWindow();

public slots:
  void patternSettings ();
  void reportSettings ();
  void systemSettings ();
  void openProperty();
  void addProperty ();

private slots:
  void on_systemSettings_clicked();
  void on_openProperty_clicked();
  void on_exitApplication_clicked();
  void killPropertyView ();
  void on_editPatterns_clicked();
  void on_newProperty_clicked();

private:
  Ui::MainWindow *ui;
  QString mDbConnectionName;
  propertyMainView *mPropertyWindow;
};

#endif // MAINWINDOW_H
