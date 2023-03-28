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

  resize(700,600);

  initChart();
}

void MainWidget::initChart()
{
  //网格化
  showGrid();

  series = new QLineSeries;

//  series->setUseOpenGL(true);
  chart->addSeries(series);

  chart->createDefaultAxes();
  chart->axisY()->setRange(beginX, overX);
  chart->axisX()->setRange(beginY, overY);

  chart->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
  chart->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));

  chart->axisX()->setTitleText("");
  chart->axisY()->setTitleText("north--->");

  //显示网格
  chart->axisX()->setGridLineVisible(s_Flag);
  chart->axisY()->setGridLineVisible(s_Flag);


  chart->axisX()->setLabelsColor(QColor("#ffffff"));
  chart->axisY()->setLabelsColor(QColor("#ffffff"));

  chart->axisY()->setTitleBrush(QBrush(QColor("#ffffff")));

  /* hide legend */
  chart->legend()->hide();

  chart->setBackgroundBrush(QBrush(QColor("#242424")));

  chartView = new ChartView(chart);

  chartView->setRenderHint(QPainter::Antialiasing);

  ui->mainHorLayout->addWidget(chartView);
}

void MainWidget::initSlot()
{
  connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
  connect(series, SIGNAL(hovered(QPointF, bool)),this, SLOT(tipSlot(QPointF,bool)));
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
  //轨迹播放
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

      data.append(QPointF(i+size, 2));
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

  if (!isStopping) {
      timer->stop();
    } else {
      timer->start();
    }

  isStopping = !isStopping;

}

void MainWidget::tipSlot(QPointF position, bool isHovering)
{
  qDebug()<<"-----------";
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

void MainWidget::showGridSlot()
{
  gridFlag = !gridFlag;
  s_Flag = !s_Flag;
}

void MainWidget::locusPlay()
{
  locusPlayFlag = !locusPlayFlag;

}

void MainWidget::speedPlay()
{
  timer->setInterval(1000);
}

void MainWidget::speedPlay1()
{
  timer->setInterval(2000);
}

void MainWidget::checkId()
{
  if(!s_Flag)
    {
      QWidget *widget = new QWidget();
      widget->setWindowTitle("查询id");
      QLineEdit *lineEdit = new QLineEdit;
      lineEdit->resize(80,60);
      QPushButton *checkBtn = new QPushButton;
      checkBtn->setText("查询");

      QHBoxLayout *h_layout = new QHBoxLayout;
      h_layout->addWidget(lineEdit);
      h_layout->addWidget(checkBtn);
      widget->setLayout(h_layout);
      widget->show();
      connect(widget,SIGNAL(close()),this,SLOT(showGridSlot()));
      s_Flag = !s_Flag;
    }
}

void MainWidget::showGrid()
{
  // 创建并添加自定义水平网格线
  QLineSeries *hLineSeries = new QLineSeries;
  for (int i = 0; i <= rangeSize; i++) {

      QPointF p1(0, i);
      QPointF p2(rangeSize, i);
      if(i%2 == 0)
        {
          hLineSeries->append(p1);
          hLineSeries->append(p2);
        }else{
          hLineSeries->append(p2);
          hLineSeries->append(p1);
        }
      chart->addSeries(hLineSeries);
    }

  // 创建并添加自定义垂直网格线
  QLineSeries *vLineSeries = new QLineSeries;
  for (int i = 0; i <= rangeSize; i++) {

      QPointF p1(i, 0);
      QPointF p2(i,rangeSize);
      if(i%2 == 0)
        {
          vLineSeries->append(p1);
          vLineSeries->append(p2);
        }else{
          vLineSeries->append(p2);
          vLineSeries->append(p1);
        }
      chart->addSeries(vLineSeries);
    }
  // 设置网格线的样式和颜色
  QPen gridPen(Qt::DotLine);
  gridPen.setColor(Qt::white);
  hLineSeries->setPen(gridPen);
  vLineSeries->setPen(gridPen);
}
