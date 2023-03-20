#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtMath>


MainWidget::MainWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MainWidget),
  chart(new QChart),
  tip(0),
  timer(new QTimer),
  count(0),
  isStopping(false)
{
  ui->setupUi(this);

  initUI();

  timer->setInterval(2000);
  timer->start();

  initSlot();


}

MainWidget::~MainWidget()
{
  delete ui;
}

void MainWidget::wheelEvent(QWheelEvent *event)
{
  if (event->delta() > 0) {
      chart->zoom(1.1);
    } else {
      chart->zoom(10.0/11);
    }

  QWidget::wheelEvent(event);
}

void MainWidget::initUI()
{
  ui->comboBox->addItem("TCP");
  ui->comboBox->addItem("UDP");

  auto ports = QSerialPortInfo::availablePorts();
  for (auto port : ports) {
      ui->comboBox->addItem(port.portName());
    }

  initChart();
}

void MainWidget::initChart()
{
//  chart->setTitle("不同类别");

//  chart->setMargins(QMargins(10, 10, 10, 10));

  series = new QLineSeries;

//  series1 = new QLineSeries;
//  series1->setName("类别2");

  chart->addSeries(series);
//  chart->addSeries(series1);


  //    series->setUseOpenGL(true);

  chart->createDefaultAxes();
  chart->axisY()->setRange(beginX, overX);
  chart->axisX()->setRange(beginY, overY);

  chart->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
  chart->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
  chart->axisX()->setTitleText("");
  chart->axisY()->setTitleText("north--->");

  //显示网格
  chart->axisX()->setGridLineVisible(gridFlag);
  chart->axisY()->setGridLineVisible(gridFlag);

  /* hide legend */
  chart->legend()->hide();

  chartView = new ChartView(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  ui->mainHorLayout->addWidget(chartView);
}

void MainWidget::initSlot()
{
  connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
  connect(ui->stopBtn, SIGNAL(clicked(bool)), this, SLOT(buttonSlot()));
  connect(series, SIGNAL(hovered(QPointF, bool)), this, SLOT(tipSlot(QPointF,bool)));
}

void MainWidget::updateData()
{
  int i;
  QVector<QPointF> oldData= series->pointsVector();
  QVector<QPointF> data;

  if (oldData.size() < rangeSize) {
      data = series->pointsVector();
    } else {
      /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加1个数据，所以为1，使用时根据实际情况修改
         */
      for (i = 1; i < oldData.size(); ++i) {
          data.append(QPointF(i , oldData.at(i).y()));
        }

    }
  if(locusPlayFlag)
    {
      data.clear();
      locusPlayFlag = !locusPlayFlag;
    }

  qint64 size = data.size();
  /* 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
  for(i = 0; i < 1; ++i){
      //      //      生成随机数
      //                    srand((unsigned)time(NULL));
      //                    int posX = rand() % rangeSize;

      //                    int posY = rand() % rangeSize;
      //                    data1.append(QPointF(posX,posY));

      data.append(QPointF(i+size, 2));
      //        data.append(QPointF(i + size, 10 * sin(M_PI * count * 4 / 180)));
    }



  series->replace(data);
  series->setPointsVisible(true);

  count++;

}

void MainWidget::timerSlot()
{
  if (QObject::sender() == timer) {
      updateData();
    }
}

void MainWidget::buttonSlot()
{
  if (QObject::sender() == ui->stopBtn) {
      if (!isStopping) {
          timer->stop();
        } else {
          timer->start();
        }

      isStopping = !isStopping;
    }
}

void MainWidget::tipSlot(QPointF position, bool isHovering)
{
  if (tip == 0)
    tip = new Callout(chart);

  if (isHovering) {
      tip->setText(QString("id: 10001 \nX: %1 \nY: %2 \n类别:A").arg(position.x()).arg(position.y()));
      tip->setAnchor(position);
      tip->setZValue(11);
      tip->updateGeometry();
      tip->show();
    } else {
      tip->hide();
    }
}

void MainWidget::showGrid()
{
  gridFlag = !gridFlag;
  chart->axisX()->setGridLineVisible(gridFlag);
  chart->axisY()->setGridLineVisible(gridFlag);
}

void MainWidget::locusPlay()
{
  locusPlayFlag = !locusPlayFlag;
}

