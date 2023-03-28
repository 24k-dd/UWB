#ifndef MODEL_H
#define MODEL_H

#include<QString>
#include <QMetaType>
#include <QDate>
#include<QProcess>
#include<QVariantList>
#include<QJsonArray>
#include<QJsonDocument>
#include<QByteArray>
#include<QApplication>
#include<QJsonObject>
#include<QVector>
#include<QDataStream>
#include<qDebug>

const int beginX = 0;
const int overX = 16;

const int beginY = 0;
const int overY = 16;

const int rangeSize = 16;

//类别1
const int CategoryOnePersonOne = 10001;

const int CategoryOnePersonTwo = 10002;

//类别2
const int CategoryTwoPersonOne = 20001;

const int CategoryTwoPersonTwo = 20002;

typedef struct Target_Info_Table
{
  int addr;
  double x;
  double y;
  int cylinder_number;
  int direction;
  QString user_name;
}targetInfoTable;
Q_DECLARE_METATYPE(Target_Info_Table)

typedef struct Check_Target_Table
{
  int addr;
  int group_number;
  int cylinder_number;
  QString user_name;

}checkInfoTable;
Q_DECLARE_METATYPE(Check_Target_Table)
//这个宏是为了让QMetaType知道Type这个数据类型，并提供一个默认的拷贝构造函数和析构函数。QVariant需要使用Q_DECLARE_METATYPE这个宏来定制类型。

//发送信息格式
typedef struct Send_Info{
 int code;
 QMap<QString,QString> msg;
 QMap<QString,int> data;
}sendInfo;



#endif // MODEL_H
