#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QDebug>

#include <QtMath>
#include<QHostAddress>
#include<QNetworkInterface>
#include<QNetworkProxy>
#include<QMessageBox>


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

  qRegisterMetaType<QVector<Show_Info>>("QVector<Show_Info>");
  qRegisterMetaType<QVector<QVector<double>>>("QVector<QVector<double>>");

  for(int i = 0;i < lineNumber;i++)
    {
      series[i] = nullptr;
    }

  initUI();

  initSlot();

  startSocket();

  startTimer();

  startThread();

}

MainWidget::~MainWidget()
{
  delete ui;
  for(int i = 0;i < lineNumber;i++)
    {
      delete series[i];
      series[i] = nullptr;
    }
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

  resize(700,620);
  checkIdWidget = new CheckIdWidget();

  initChart();
}

void MainWidget::initChart()
{
  //网格化
  showGrid();
  for(int i = 0;i < lineNumber;i++)
    {
      series[i] = new QLineSeries;
      connect(series[i], SIGNAL(hovered(QPointF, bool)),this, SLOT(tipSlot(QPointF,bool)));

      chart->addSeries(series[i]);
    }
  chart->createDefaultAxes();
  chart->axisY()->setRange(beginX, overX);
  chart->axisX()->setRange(beginY, overY);

  chart->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
  chart->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));

  chart->axisX()->setTitleText("");
  chart->axisX()->setTitleText("north--->");

  //显示网格
  chart->axisX()->setGridLineVisible(s_Flag);
  chart->axisY()->setGridLineVisible(s_Flag);


  chart->axisX()->setLabelsColor(QColor("#ffffff"));
  chart->axisY()->setLabelsColor(QColor("#ffffff"));

  chart->axisX()->setTitleBrush(QBrush(QColor("#ffffff")));

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
  connect(checkIdWidget,SIGNAL(mySignalClose()),this,SLOT(startRequestCurData()));

  connect(checkIdWidget,SIGNAL(mySignalPoints(const QVector<QVector<double> >&)),this,SLOT(showPoints(const QVector<QVector<double> >&)));
}


void MainWidget::showCurPoint(const QVector<Show_Info> &data)
{
  for(int i = 0;i < data.size() && i < lineNumber;i++)
    {
      QVector<QPointF> onlyPoint;
      onlyPoint.append(QPointF(data[i].x,data[i].y));

      series[i]->replace(onlyPoint);
      series[i]->setPointsVisible(true);
    }
  emit mySignalCurData(data);
}

void MainWidget::showPoints(const QVector<QVector<double> > &points)
{
  QVector<QPointF> allPoints;

  for(int i = 0; i < points.size();i++)
  {
    allPoints.append(QPointF(points[i][0],points[i][1]));
    series[0]->replace(allPoints);
    series[0]->setPointsVisible(true);
  }
}

void MainWidget::timerSlot()
{
  if (QObject::sender() == timer) {
      //      updateData();
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
  if (tip == 0)
    tip = new Callout(chart);

  if (isHovering) {
      tip->setText(QString("X: %1 \nY: %2").arg(position.x()).arg(position.y()));
      tip->setAnchor(position);
      tip->setZValue(11);
      tip->updateGeometry();
      tip->show();
    } else {
      tip->hide();
    }
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
  m_Timer.stop();

  checkIdWidget->show();

}

void MainWidget::startRequestCurData()
{
  m_Timer.start();
}


void MainWidget::onConnected()
{
  qDebug()<<"Connected to server";
  m_reconnectTimer.stop();

}

void MainWidget::onDisconnected()
{
  qDebug()<<"Disconnect from server";

  m_socket->connectToHost(QHostAddress(ip),port);
  m_reconnectTimer.start();
}

void MainWidget::reconnect()
{
  qDebug()<<"Reconnecting...";
  //ip和端口号
  m_socket->connectToHost(QHostAddress(ip),port);
}




void MainWidget::showGrid()
{
  // 创建并添加自定义水平网格线
  hLineSeries = new QLineSeries;
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

    }
  chart->addSeries(hLineSeries);
  // 创建并添加自定义垂直网格线
  vLineSeries = new QLineSeries;
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

    }
  chart->addSeries(vLineSeries);
  // 设置网格线的样式和颜色
  QPen gridPen(Qt::DotLine);

  gridPen.setColor(Qt::white);
  hLineSeries->setPen(gridPen);
  vLineSeries->setPen(gridPen);
}

void MainWidget::startSocket()
{
  m_socket = new QTcpSocket(this);

  //去掉代理
  m_socket->setProxy(QNetworkProxy::NoProxy);

  //ip和端口号
  m_socket->connectToHost(QHostAddress(ip),port);

  try{
    if(m_socket->waitForConnected())
      {
        qDebug() << "connect success";

      }else{
        qDebug() << "connect filed";
      }
  }

  catch(std::exception &ex)
  {

    return ;
  }

  connect(m_socket,&QTcpSocket::connected,this,&MainWidget::onConnected);

  connect(m_socket,&QTcpSocket::disconnected,this,&MainWidget::onDisconnected);

}

QString MainWidget::getMyIpString()
{
  QString ip_address;
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses(); // 获取所有ip
  for (int i = 0; i < ipAddressesList.size(); ++i)
    {

      QHostAddress ipAddr = ipAddressesList.at(i);
      if ((ipAddr.protocol() == QAbstractSocket::IPv4Protocol))// 筛选出ipv4
        {

          if (!ipAddr.toString().startsWith("169"))// 过滤掉网卡，路由器等的ip
            {
              ip_address = ipAddr.toString();
              break;
            }
        }
    }
  if (ip_address.isEmpty())
    ip_address = QHostAddress(QHostAddress::LocalHost).toString();
  return ip_address;
}

void MainWidget::sendData(const QByteArray &msg)
{
  try{

    if(m_socket->state() == QAbstractSocket::UnconnectedState)
      {
        m_socket->connectToHost(QHostAddress(ip),port);
      }

    if(m_socket->state() == QAbstractSocket::ConnectedState)
      {
        m_socket->write(msg);
        qDebug()<<"send:"<<msg;
        m_socket->flush();
      }

  }
  catch(std::exception &ex)
  {
    return ;
  }
}

void MainWidget::requestCurData()
{
  QByteArray data =  resCurData();

  sendData(data);
}

void MainWidget::startTimer()
{

  timer->setInterval(2000);
  timer->start();

  m_reconnectTimer.setSingleShot(true);

  m_reconnectTimer.setInterval(10000);

  connect(&m_reconnectTimer,&QTimer::timeout,this,&MainWidget::reconnect);

  //每隔1s请求一次
  m_Timer.setInterval(updatetime);

  //开启定时器
  m_Timer.start();

  //监听定时器发送的信号
  connect(&m_Timer,&QTimer::timeout,[=](){

      //请求当前移动信息
      requestCurData();

    });
}

void MainWidget::startThread()
{
  inWork = new InWork;

  inWork->moveToThread(&threadOne);

  inWork->setSocket(m_socket);

  outWork = new OutWork;

  outWork->moveToThread(&threadTwo);

  connect(m_socket, &QTcpSocket::readyRead, inWork, &InWork::readMessage);
  connect(&threadTwo,SIGNAL(started()),outWork,SLOT(doWork()));

  connect(outWork,SIGNAL(mySignalCurData(const QVector<Show_Info>&)),this,SLOT(showCurPoint(const QVector<Show_Info>&)));

  connect(this,&MainWidget::destroyed,this,[=](){
      threadOne.quit();
      threadOne.wait();
      threadOne.deleteLater();

      threadTwo.quit();
      threadTwo.wait();
      threadTwo.deleteLater();
    });
  threadOne.start();
  threadTwo.start();
}
