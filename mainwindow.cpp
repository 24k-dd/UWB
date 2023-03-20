#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  mainWidget = new MainWidget;

  setCentralWidget(mainWidget);

  connect(ui->action_grid,SIGNAL(triggered()),mainWidget,SLOT(showGrid()));

  connect(ui->action_pause,SIGNAL(triggered()),mainWidget,SLOT(buttonSlot()));

  connect(ui->action_locusplay,SIGNAL(triggered()),mainWidget,SLOT(locusPlay()));

}

MainWindow::~MainWindow()
{
  delete ui;
}
