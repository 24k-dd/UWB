#ifndef MYTOOL_H
#define MYTOOL_H

#include <QWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QStringList>
#include <QVBoxLayout>
#include <QSpacerItem>

class MyTool : public QWidget
{
  Q_OBJECT

public:
  MyTool(QWidget *parent = nullptr);
  ~MyTool();

  void setButtonName(QString name);


 public slots:
  void showTableWidget();


private:
  QTableWidget  *tableWidget;

  bool showFlag = true;

  QPushButton  *btn;
};



#endif // MYTOOL_H
