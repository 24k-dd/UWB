#ifndef SQLITETHREAD_H
#define SQLITETHREAD_H

#include <QTimer>
#include <QObject>
#include <QThread>
#include <QPoint>
#include <QDebug>
#include <QMetaType>
#include <QList>
#include <QMutex>

#include "sqlitetools.h"



class SQLiteThread : public QThread
{
  Q_OBJECT

signals:
  mySignal(const QVector<QVector<double>>&); //自定义信号函数,msg参数可以省略

public:
  explicit SQLiteThread(QString connectName,QObject *parent = nullptr);
  ~SQLiteThread();

public slots:

private:
  void run() override; //QThread的虚函数，线程处理函数,不能直接调用，通过start()间接调用

private:
  QVector<QVector<double>> curDate;


  SQLiteTools *sqliteTools = nullptr;

  QString dbConnect;

  QMutex mutex;
};

#endif // SQLITETHREAD_H
