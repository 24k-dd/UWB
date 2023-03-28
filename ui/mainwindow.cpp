#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  resize(1430,800);
//  setStyleSheet("background-color: #5B677A;");
  ui->menubar->setStyleSheet("background-color: #c5dada");

  mainWidget = new MainWidget;


  //弹簧
  h_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Minimum);
  v_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding);
  ui->treeWidget_menu->setFixedWidth(200);
  ui->treeWidget_group->setFixedWidth(430);

  ui->treeWidget_group->setColumnWidth(0,140);
  for(int i = 1;i < 4;i++)
    ui->treeWidget_group->setColumnWidth(i,90);

//  ui->treeWidget_group->setStyleSheet("background-color: white;");
//  ui->treeWidget_menu->setStyleSheet("background-color: white;");

  QHBoxLayout *h_layout = new QHBoxLayout;

  h_layout->addWidget(ui->treeWidget_menu);
  h_layout->addItem(h_spacer);
  h_layout->addWidget(mainWidget);
  h_layout->addItem(h_spacer);
  h_layout->addWidget(ui->treeWidget_group);

  setStyleSheet("QTreeWidget{background-color: #5B677A;font-size:17px; color: white;}"
                "QTreeWidget::item{margin:5px;background: #5B677A;background-clip: margin;}"
                "QWidget{background-color: #5B677A;}");





  QWidget *widget = new QWidget;

  widget->setLayout(h_layout);

  setCentralWidget(widget);

//  connect(ui->action_grid,SIGNAL(triggered()),mainWidget,SLOT(showGridSlot()));

  connect(ui->action_pause,SIGNAL(triggered()),mainWidget,SLOT(buttonSlot()));

  connect(ui->action_locusplay,SIGNAL(triggered()),mainWidget,SLOT(locusPlay()));

  connect(ui->action2_0x,SIGNAL(triggered()),mainWidget,SLOT(speedPlay()));

  connect(ui->action1_0x_2,SIGNAL(triggered()),mainWidget,SLOT(speedPlay1()));

  connect(ui->action_id,SIGNAL(triggered()),mainWidget,SLOT(checkId()));

}

MainWindow::~MainWindow()
{
  delete ui;
}
