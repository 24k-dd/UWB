#ifndef OUTTHREAD_H
#define OUTTHREAD_H

#include<QJsonObject>
#include<QVariantMap>
#include<QJsonDocument>
#include<QByteArray>
#include<QThread>
#include<QMutex>
#include<QMutexLocker>
#include<QThread>

#include"model/model.h"

#include"pkg/config.h"

class OutWork : public QObject
{
  Q_OBJECT

public:

signals:
  mySignalCurData(const QVector<Show_Info>&);

private slots:
  void doWork();

private:

  //区分数据
  int code = 1;

  //信息
  QString msg;
};






#endif // OUTTHREAD_H
