#include<QThread>
#include<QDebug>
#include<QMap>
#include<qDebug>
#include "outwork.h"


//根据自定义任务重载run()函数
void OutWork::doWork()
{
  //  qDebug()<<"当前出队的子线程为："<<QThread::currentThread();
  while(true){

      if(!d_queue.isEmpty()){
          try{
            QByteArray recvAllMsg = d_queue.dequeue();

            int index = recvAllMsg.indexOf('\n');

            recvAllMsg.remove(index,recvAllMsg.size() - index);

            QString recvStr = QString::fromUtf8(recvAllMsg);

            //构建JSON对象

            QJsonDocument jsonDocument = QJsonDocument::fromJson(recvStr.toLocal8Bit().data());

            if(jsonDocument.isNull())
              {
                continue;
              }
            QJsonObject json = jsonDocument.object();

            //  Json转QMap
            QVariantMap map = json.toVariantMap();

            code = map["code"].toInt();

            if(code == SHOWINFO){

                QVector<Show_Info> showInfoVec;

                QMap<QString, QVariant> map1 = map["data"].toMap();

                QMap<QString, QVariant>::iterator it = map1.begin();
                while(it != map1.end())
                  {
                    Show_Info sendInfo;
                    sendInfo.id = it.key();
                    sendInfo.x = it.value().toJsonObject()["x"].toDouble();
                    sendInfo.y = it.value().toJsonObject()["y"].toDouble();
                    showInfoVec.push_back(sendInfo);
                    it++;
                  }

                emit mySignalCurData(showInfoVec);
              }
          }
          catch(std::exception &ex)
          {
            continue ;
          }

        }
      QThread::msleep(100);

    }
}
