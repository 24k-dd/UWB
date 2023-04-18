#ifndef CONFIG_H
#define CONFIG_H

#include<QJsonArray>
#include<QJsonDocument>
#include<QByteArray>
#include<QJsonObject>
#include<QDataStream>


#include"model/Model.h"

//转为json格式数据
//QByteArray structToJson(const Send_Info &sendDataInfo);

inline QByteArray structToJson(const Send_Info &sendDataInfo)
{
  QJsonObject jsonObject;
  jsonObject["code"] = sendDataInfo.code;
  QJsonObject jo1;
  for(auto it = sendDataInfo.msg.begin();it != sendDataInfo.msg.end();++it)
    jo1[it.key()] = it.value();
  jsonObject["msg"] = jo1;
  QJsonObject jo2;
  for(auto it = sendDataInfo.data.begin();it != sendDataInfo.data.end();++it)
    jo2[it.key()] = it.value();
  jsonObject["data"] = jo2;

  QJsonDocument jsonDocu(jsonObject);
  QString jsonStr = jsonDocu.toJson();

  jsonStr.replace("\n","");
  jsonStr.replace(" ","");
  jsonStr.append('\n');

  QByteArray sendData = jsonStr.toUtf8();
  return sendData;
}



#endif // CONFIG_H
