
#include"inwork.h"

#include<QThread>
#include"model/model.h"

void InWork::readMessage()
{
  QByteArray recvAllMsg;
  while(true)
    {
      QByteArray temp = m_socket->read(1);
      try{
        if (temp.size()>0){
            recvAllMsg.append(temp[0]);
            if(temp[0] == '\n')
              {
                qDebug()<<"recv:"<<recvAllMsg;
                d_queue.enqueue(recvAllMsg);
                recvAllMsg.clear();
              }
          }else{
            return ;
          }
      }
      catch(std::exception &ex)
      {
        return ;
      }
    }
}

void InWork::setSocket(QTcpSocket *socket)
{
  m_socket = socket;
}





