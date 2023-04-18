#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include<QTime>
#include<QValueAxis>
#include<QLineEdit>
#include<QPushButton>
#include<QDateEdit>
#include<QLabel>
#include "chartview.h"
#include "callout.h"
#include "model/model.h"

#include"api/inwork.h"
#include"api/outwork.h"
#include"checkidwidget.h"



QT_CHARTS_USE_NAMESPACE

namespace Ui {
  class MainWidget;
}

class MainWidget : public QWidget
{
  Q_OBJECT

public:
  explicit MainWidget(QWidget *parent = 0);
  ~MainWidget();


  void showGrid();

  void startSocket();

  QString getMyIpString();

  void sendData(const QByteArray& msg);

  void requestCurData();

  void startTimer();

  void startThread();

signals:
  mySignalCurData(const QVector<Show_Info>&);

private:
  void wheelEvent(QWheelEvent *event);

  void initUI();
  void initChart();
  void initSlot();

  Ui::MainWidget *ui;

  ChartView *chartView = nullptr;

  Callout *tip = nullptr;
  QLineSeries *series[lineNumber];

  QTimer *timer = nullptr;

  quint16 count;

  bool isStopping;

  bool  gridFlag = true;

  bool locusPlayFlag = false;

  bool s_Flag = false;

private slots:
  void timerSlot();
  void buttonSlot();
  void tipSlot(QPointF position, bool isHovering);

  void showCurPoint(const QVector<Show_Info> &data);

  void showPoints(const QVector<QVector<double> >& points);

  //轨迹播放
  void locusPlay();

  //倍速
  void speedPlay();

  void speedPlay1();

  //特定id
  void checkId();

  //建立连接
  void onConnected();

  //断开连接
  void onDisconnected();

  //断开重连
  void reconnect();

  void startRequestCurData();


private:
  QTcpSocket* m_socket = nullptr;

  InWork *inWork = nullptr;
  OutWork *outWork = nullptr;

  QThread  threadOne;
  QThread threadTwo;

  bool sendFlag = false;

  QTimer m_reconnectTimer;

  QTimer m_Timer;

public:
  QChart *chart = nullptr;

  QLineSeries *vLineSeries = nullptr;

  QLineSeries *hLineSeries = nullptr;

  CheckIdWidget *checkIdWidget = nullptr;

};

#endif // MAINWIDGET_H
