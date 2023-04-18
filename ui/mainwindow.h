#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSpacerItem>
#include<QAction>

#include<QToolButton>
#include<QGroupBox>
#include<QToolBox>
#include<QHBoxLayout>

#include"mainwidget.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void showCurPoint(const QVector<Show_Info> &data);

  void showTopicOne();

  void showTopicTwo();
  void showTopicThree();

private:
  Ui::MainWindow *ui;

  MainWidget *mainWidget;

  QSpacerItem *h_spacer;
  QSpacerItem *v_spacer;



};

#endif // MAINWINDOW_H
