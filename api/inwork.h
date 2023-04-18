#ifndef SOCKETREADER_H
#define SOCKETREADER_H




#include <QTcpSocket>
QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE
#include<qDebug>

#include"api.h"



class InWork : public QObject
{
  Q_OBJECT

public:
  void setSocket(QTcpSocket *socket);

public slots:
  void readMessage();

private:
  QTcpSocket *m_socket = nullptr;

  bool flag = true;
};

#endif // SOCKETREADER_H
