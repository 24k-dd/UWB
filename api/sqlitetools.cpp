#include "sqlitetools.h"



#include <QDate>
#include<QString>
#include<QVector>

//带参数的构造函数，进行私有属性的初始化
SQLiteTools::SQLiteTools(QString dbName, QString connName)
{
  dataBaseName = dbName;
  connectionName = connName;
}

SQLiteTools::~SQLiteTools()
{

}

void SQLiteTools::initDataBase()
{
  //qDebug()<<QSqlDatabase::drivers();//打印驱动列表
  //检测已连接的方式 - 自定义连接名
  if(QSqlDatabase::contains(connectionName))
    db = QSqlDatabase::database(connectionName);
  else
    db = QSqlDatabase::addDatabase("QSQLITE",connectionName);

  //设置数据库路径，不存在则创建
  db.setDatabaseName("./uwb.db");
  //db.setUserName("gongjianbo");  //SQLite不需要用户名和密码
  //db.setPassword("qq654344883");



  //打开数据库，验证是否成功
  if(db.open()){
      qDebug()<<"open success";
      //关闭数据库
      //
    }else{
      db.close();
    }
}

bool SQLiteTools::openDateBase()
{
  if(!db.open())
    {
      qDebug() << "Error: Failed to open database." << db.lastError();
      return false;
    }
  return true;
}

void SQLiteTools::closeDataBase()
{
  db.close();
}

void SQLiteTools::createTable()
{
  //如果不存在则创建my_table表,id自增,name唯一
  const QString sql=R"(
                    CREATE TABLE IF NOT EXISTS  my_table (
                    ID   INTEGER   PRIMARY KEY   NOT NULL,
                    PX   REAL   NOT NULL,
                    PY   REAL   NOT NULL
                    );)";
  //QSqlQuery构造前，需要db已打开并连接
  //未指定db或者db无效时使用默认连接进行操作
  QSqlQuery query(db);
  if(query.exec(sql)){
      qDebug()<<"init table success";
    }else{
      //打印sql语句错误信息
      qDebug()<<"init table error"<<query.lastError();
    }
}

//插入数据
void SQLiteTools::insertRecord(int id, qreal px, qreal py)
{
  //方式一，绑定值，待定变量默认用问号占位,注意字符串也没有引号
  //query.prepare(R"(INSERT INTO my_table(name,age) VALUES(?,?);)");
  //query.addBindValue(name);
  //query.addBindValue(age);
  //query.exec();

  QSqlQuery query(db);
  QString sql = QString(R"(INSERT INTO my_table(ID, PX, PY) VALUES(%1, %2, %3);)")
      .arg(id).arg(px).arg(py);
  query.prepare(sql);
  if(!query.exec())
    {
      qDebug() << query.lastError();
    }
  else
    {
      qDebug() << "inserted OK!";
    }
}

//删除数据
void SQLiteTools::deleteRecord(int id)
{
  //方式一，直接执行SQL语句
  //query.exec(QString(R"(DELETE FROM my_table WHERE name='%1';)")
  //           .arg(name));
  //方式二，绑定值，待定变量默认用问号占位
  /*query.prepare(R"(DELETE FROM my_table WHERE name=?;)");
    query.addBindValue(name);
    query.exec();*/

  QSqlQuery query(db);
  QString sql = QString(R"(DELETE FROM my_table WHERE ID=%1;)").arg(id);
  query.prepare(sql);
  if(!query.exec())
    {
      qDebug() << query.lastError();
    }
  else
    {
      qDebug() << "deleted OK!";
    }
}

//更新数据
void SQLiteTools::updateRecord(int id, qreal px, qreal py)
{
  //方式一，绑定值，待定变量默认问号，可自定义
  /*query.prepare(R"(UPDATE my_table SET age=:age WHERE name=:name;)");
    query.bindValue(":name",name);//通过自定义的别名来替代
    query.bindValue(":age",age);
    query.exec();*/

  QSqlQuery query(db);
  QString sql = QString(R"(UPDATE my_table SET PX=%2, PY=%3 WHERE ID=%1;)").arg(id).arg(px).arg(py);
  query.prepare(sql);
  if(!query.exec())
    {
      qDebug() << query.lastError();
    }
  else
    {
      qDebug() << "updated OK!";
    }
}

//查询数据
QVector<QVector<double>> SQLiteTools::searchCurrentDate(QString id,QString begin,QString over)
{
  //获取查询结果，如果结果是多行数据，可用while(query.next()){}遍历每一行
  QSqlQuery query(db);
  QString sql = QString(R"(SELECT * FROM all_points WHERE date BETWEEN '%1' AND '%2' AND id = '%3';)").arg(begin).arg(over).arg(id);

  query.prepare(sql);
  QVector<QVector<double>> allPoints;
  if(!query.exec())
    {
      qDebug()<<query.lastError();
    }
  else
    {
      while(query.next())
        {

          QVector<double> point;
          point.append(query.value(1).toDouble());
          point.append(query.value(2).toDouble());
          allPoints.append(point);
        }
    }
  return allPoints;
}


//获取记录行数
int SQLiteTools::getRowCounts(QString tableName)
{
  int counts = -1;
  QSqlQuery query(db);
  QString sql = QString("SELECT count(*) FROM %1").arg(tableName);
  query.prepare(sql);
  if(!query.exec())
    {
      qDebug() << query.lastError();
    }
  else
    {
      query.next();
      counts = query.value(0).toInt();
    }
  return counts;
}
