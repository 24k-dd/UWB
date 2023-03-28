#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QTcpSocket>
#include<QString>
#include<QJsonValue>
#include<QJsonObject>
#include<QVariantMap>
#include<QJsonDocument>
#include<QByteArray>
#include<QNetworkProxy>
#include<QHostAddress>
#include<QJsonArray>
#include<QVariant>
#include<QVector>
#include<QTimer>
#include<QDate>
#include<QNetworkInterface>

#include"api.h"

class MySocket : public QTcpSocket
{
  Q_OBJECT

public:
  explicit MySocket(QObject *parent = nullptr);

  //发m送数据
  void sendData(QString msg);

  //关闭通信
  void closeSocket();

  //操作管理数据
  void manageData();

  //获取本机ip
  QString getMyIpString();

signals:


public slots:

  //连接成功
  void onConnected();

  //断开连接
  void onDisconnected();

  //断开重连
  void reconnect();

  //读取数据
  void readMessage();

private:
  int Port = 32728;

  QString Ip;

  QTimer m_Timer;

  QTimer *m_reconnectTimer;

  //区分数据
  int code = 1;

  //信息
  QString msg;

  QByteArray recvAllMsg = "";

};

#endif // MYSOCKET_H
