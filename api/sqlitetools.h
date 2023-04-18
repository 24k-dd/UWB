#ifndef SQLITECLASS_H
#define SQLITECLASS_H
#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

class SQLiteTools
{
private:
  QSqlDatabase    db;                 //定义一个私有的数据库连接对象
  QString         connectionName;     //定义数据库连接名
  QString         dataBaseName;       //定义用于建立连接的数据库名或路径

public:
  SQLiteTools(QString dbName, QString connName);
  ~SQLiteTools();

  /**
         * @brief initDataBase 初始化数据库连接
         * @param
         */
  void initDataBase(void);
  /**
         * @brief openDateBase 打开数据库
         * @param
         */
  bool openDateBase(void);
  /**
         * @brief closeDataBase 关闭数据库
         * @param
         */
  void closeDataBase(void);
  /**
         * @brief createTable 创建数据表
         * @param
         */
  void createTable(void);
  /**
         * @brief insertRecord 插入记录
         * @param
         */
  void insertRecord(int id, qreal px, qreal py);
  /**
         * @brief deleteRecord 删除记录
         * @param
         */
  void deleteRecord(int id);
  /**
         * @brief updateRecord 更新记录
         * @param
         */
  void updateRecord(int id, qreal px, qreal py);
  /**
         * @brief searchRecord 查询记录
         * @param
         */
  QVector<QVector<double>> searchCurrentDate(QString id,QString begin,QString over);
  /**
         * @brief getRowCounts 获取所有记录数目
         * @param
         */

  int getRowCounts(QString tableName);

};

#endif // SQLITECLASS_H
