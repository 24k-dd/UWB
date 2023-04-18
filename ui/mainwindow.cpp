#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  qRegisterMetaType<QVector<Show_Info>>("QVector<Show_Info>");


  resize(1510,780);
  //  setStyleSheet("background-color: #5B677A;");
  ui->menubar->setStyleSheet("background-color: #c5dada");

  mainWidget = new MainWidget(this);

  //弹簧
  h_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Minimum);
  v_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding);
  ui->treeWidget_menu->setFixedWidth(240);
  ui->treeWidget_group->setFixedWidth(480);

  ui->treeWidget_group->setColumnWidth(0,180);
  ui->treeWidget_group->setColumnWidth(1,110);
  ui->treeWidget_group->setColumnWidth(2,160);
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

  QWidget *widget = new QWidget(this);

  widget->setLayout(h_layout);

  setCentralWidget(widget);

  //  connect(ui->action_grid,SIGNAL(triggered()),mainWidget,SLOT(showGridSlot()));

  connect(ui->action_pause,SIGNAL(triggered()),mainWidget,SLOT(buttonSlot()));

  connect(ui->action_locusplay,SIGNAL(triggered()),mainWidget,SLOT(locusPlay()));

  connect(ui->action2_0x,SIGNAL(triggered()),mainWidget,SLOT(speedPlay()));

  connect(ui->action1_0x_2,SIGNAL(triggered()),mainWidget,SLOT(speedPlay1()));

  connect(ui->action_id,SIGNAL(triggered()),mainWidget,SLOT(checkId()));

  connect(ui->action_topic1,SIGNAL(triggered()),this,SLOT(showTopicOne()));

  connect(ui->action_topic2,SIGNAL(triggered()),this,SLOT(showTopicTwo()));

  connect(ui->action_topic3,SIGNAL(triggered()),this,SLOT(showTopicThree()));
//  connect(ui->action_topic2,SIGNAL(triggered()),this,SLOT(showTopicThree()));


  connect(mainWidget,SIGNAL(mySignalCurData(const QVector<Show_Info>&)),this,SLOT(showCurPoint(const QVector<Show_Info>&)));

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showCurPoint(const QVector<Show_Info> &data)
{
  QTreeWidgetItem *studentTopItem = ui->treeWidget_group->topLevelItem(2);
  for(int i = 0;i < studentTopItem->childCount();i++)
    {
      QTreeWidgetItem *child = studentTopItem->takeChild(i);
      delete child;
    }

  for(int i = 0;i < data.size();i++)
    {
      QList<QString> allItemName;
      allItemName.append(data[i].id);
      allItemName.append("root");
      allItemName.append(QString::asprintf("(%1,%2)").arg(data[i].x).arg(data[i].y));
      QTreeWidgetItem *childItem = new QTreeWidgetItem(allItemName);
      studentTopItem->addChild(childItem);

    }

}

void MainWindow::showTopicOne()
{
  setStyleSheet("QTreeWidget{background-color: pink;font-size:17px; color: #000000;}"
                "QTreeWidget::item{margin:5px;background: #81ffc4;background-clip: margin;}"
                "QWidget{background-color: #81ffc4;}");

  ui->menubar->setStyleSheet("background-color: #2cf5ff");
  mainWidget->chart->setBackgroundBrush(QBrush(QColor("white")));

  mainWidget->chart->axisX()->setLabelsColor(QColor("#000000"));
  mainWidget->chart->axisY()->setLabelsColor(QColor("#000000"));
  mainWidget->chart->axisY()->setTitleBrush(QBrush(QColor("#000000")));

  QPen pen(Qt::DotLine);
  pen.setColor("#000000");

  mainWidget->hLineSeries->setPen(pen);
  mainWidget->vLineSeries->setPen(pen);

}

void MainWindow::showTopicTwo()
{
  setStyleSheet("QTreeWidget{background-color: pink;font-size:17px; color: #000000;}"
                "QTreeWidget::item{margin:5px;background: #15f4ff;background-clip: margin;}"
                "QWidget{background-color: #15f4ff;}");

  ui->menubar->setStyleSheet("background-color: #55aaff");

  mainWidget->chart->setBackgroundBrush(QBrush(QColor("white")));

  mainWidget->chart->axisX()->setLabelsColor(QColor("#000000"));
  mainWidget->chart->axisY()->setLabelsColor(QColor("#000000"));

  mainWidget->chart->axisY()->setTitleBrush(QBrush(QColor("#000000")));

  QPen pen(Qt::DotLine);
  pen.setColor("#000000");

  mainWidget->hLineSeries->setPen(pen);
  mainWidget->vLineSeries->setPen(pen);

}

void MainWindow::showTopicThree()
{
  setStyleSheet("QTreeWidget{background-color: #5B677A;font-size:17px; color: white;}"
                "QTreeWidget::item{margin:5px;background: #5B677A;background-clip: margin;}"
                "QWidget{background-color: #5B677A;}");

  ui->menubar->setStyleSheet("background-color: #c5dada");

  mainWidget->chart->setBackgroundBrush(QBrush(QColor("white")));

  mainWidget->chart->axisX()->setLabelsColor(QColor("#000000"));
  mainWidget->chart->axisY()->setLabelsColor(QColor("#000000"));

  mainWidget->chart->axisY()->setTitleBrush(QBrush(QColor("#000000")));
//  mainWidget->gridPen->setColor(Qt::black);

  QPen pen(Qt::DotLine);
  pen.setColor("#000000");

  mainWidget->hLineSeries->setPen(pen);
  mainWidget->vLineSeries->setPen(pen);
}
