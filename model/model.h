#ifndef MODEL_H
#define MODEL_H

#include<QString>
#include<QByteArray>
#include<QMap>
#include<QQueue>
#include <QMetaType>

const int beginX = 0;
const int overX = 16;

const int beginY = 0;
const int overY = 16;

//网格数量
const int rangeSize = 16;

//线段数量
const int lineNumber = 50;

//刷新点的间隔
const int updatetime = 500;

//类别1
const int SHOWINFO = 10001;

//ip
const QString ip = "192.168.43.6";
//const QString ip = "192.168.43.250";
//const QString ip = "192.168.137.1";

//port
const int port = 31000;

typedef struct Show_Info
{
  QString id;
  double x;
  double y;
}showInfo;
Q_DECLARE_METATYPE(Show_Info)


//发送信息格式
typedef struct Send_Info{
  int code;
  QMap<QString,QString> msg;
  QMap<QString,int> data;
}sendInfo;
Q_DECLARE_METATYPE(Send_Info)

extern QQueue<QByteArray> d_queue;

#endif // MODEL_H
