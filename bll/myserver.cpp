
#include"myserver.h"

#include"pkg/config.h"

QByteArray resCurDataApi()
{
  Send_Info sendDataInfo;
  sendDataInfo.code = SHOWINFO;
  QByteArray data = structToJson(sendDataInfo);
  return data;
}
