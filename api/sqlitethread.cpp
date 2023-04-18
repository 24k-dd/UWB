#include "sqlitethread.h"



//构造函数初始化
SQLiteThread::SQLiteThread(QString connectName,QObject *parent):QThread(parent)
{
  //使用qRegisterMetaType对自定义类型 QList<QPoint> 进行注册


  dbConnect = connectName;

}

SQLiteThread::~SQLiteThread()
{
  delete sqliteTools;
  sqliteTools = nullptr;
}


//根据自定义任务重载run()函数
void SQLiteThread::run()
{

  sqliteTools = new SQLiteTools(":/autoTarget.db",dbConnect);

  sqliteTools->initDataBase();

  while(true)
    {
      curDate = {};

      mutex.lock();


//          curDate= sqliteTools->searchCurrentDate(groupNumber,i);

//          emit mySignal(curDate,i);


      mutex.unlock();
      msleep(500);

    }

}
