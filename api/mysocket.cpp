#include "mysocket.h"

MySocket::MySocket(QObject *parent)
  : QTcpSocket(parent)
{

  Ip = "192.168.4.2";

  //去掉代理
  setProxy(QNetworkProxy::NoProxy);

  //ip和端口号
  connectToHost(QHostAddress(Ip),Port);

  if(waitForConnected())
    {
      qDebug() << "connect success";
    }else{
      qDebug() << "connect failed";
    }

  m_reconnectTimer = new QTimer;

  m_reconnectTimer->setSingleShot(true);

  m_reconnectTimer->setInterval(10000);

  connect(this,&QTcpSocket::connected,this,&MySocket::onConnected);

  connect(this,&QTcpSocket::disconnected,this,&MySocket::onDisconnected);

  connect(m_reconnectTimer,&QTimer::timeout,this,&MySocket::reconnect);

  connect(this, &QTcpSocket::readyRead,this,&MySocket::readMessage);


  m_Timer.setInterval(300);

  //开启定时器
  m_Timer.start();

  //监听定时器发送的信号
  connect(&m_Timer,&QTimer::timeout,[=](){

      //请求已连接状态的靶标信息
      //      updateHoles();

    });

}

//发送信息
void MySocket::sendData(QString msg)
{

  write(msg.toUtf8().data());
}

void MySocket::closeSocket()
{
  close();
}

//读取一帧数据
void MySocket::readMessage()
{
  while(true)
    {
      QByteArray temp =read(1);
      if (temp.size()>0){
          recvAllMsg.append(temp[0]);
          if(temp[0] == '\n')
            {
              manageData();

              recvAllMsg.clear();
              return ;
            }
        }else{
          break;
        }
    }
}

void MySocket::manageData()
{

  //  int index = recvAllMsg.indexOf('\n');

  //  recvAllMsg.remove(index,recvAllMsg.size() - index);

  //  qDebug()<<"接收数据大小:"<<recvAllMsg.size();

  //  QString recvStr = QString::fromUtf8(recvAllMsg);

  //  //  构建JSON对象
  //  QJsonObject json = QstringToJson(recvStr);
  //  //  Json转QMap
  //  QVariantMap map = json.toVariantMap();

  //  code = map["code"].toInt();

}


void MySocket::onConnected()
{
  qDebug()<<"Connected to server";
  m_reconnectTimer->stop();
}

void MySocket::onDisconnected()
{
  qDebug()<<"Disconnect from server";
  m_reconnectTimer->start();
}

void MySocket::reconnect()
{
  qDebug()<<"Reconnecting...";
  //ip和端口号
  connectToHost(QHostAddress(Ip),Port);
}

QString MySocket::getMyIpString()
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







