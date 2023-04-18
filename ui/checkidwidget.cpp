#include "checkidwidget.h"

#include<QHBoxLayout>
#include<QLabel>
#include<QPushButton>
CheckIdWidget::CheckIdWidget(QWidget *parent) : QWidget(parent)
{

  setWindowTitle("查询id");
  lineEdit = new QLineEdit(this);

  QPushButton *checkBtn = new QPushButton(this);
  checkBtn->setText("查询");

  dateEditBegin = new QDateEdit(this);
  dateEditBegin->setDate(QDate::currentDate());
  dateEditOver = new QDateEdit(this);
  dateEditOver->setDate(QDate::currentDate());

  QLabel *labelBegin = new QLabel("起始时间:");
  QLabel *labelOver = new QLabel("结束时间:");

  QHBoxLayout *h_layout1 = new QHBoxLayout;
  h_layout1->addWidget(labelBegin);
  h_layout1->addWidget(dateEditBegin);

  QHBoxLayout *h_layout2 = new QHBoxLayout;
  h_layout2->addWidget(labelOver);
  h_layout2->addWidget(dateEditOver);

  QHBoxLayout *h_layout3 = new QHBoxLayout;
  h_layout3->addWidget(lineEdit);
  h_layout3->addWidget(checkBtn);

  QVBoxLayout *v_layout = new QVBoxLayout(this);
  v_layout->addLayout(h_layout1);
  v_layout->addLayout(h_layout2);
  v_layout->addLayout(h_layout3);
  setLayout(v_layout);

  connect(checkBtn,SIGNAL(clicked()),this,SLOT(checkIdBtn()));

  sqliteTools = new SQLiteTools(":/uwb.db","conn_02");
  sqliteTools->initDataBase();
}

void CheckIdWidget::closeEvent(QCloseEvent *event)
{
  emit mySignalClose();
}

void CheckIdWidget::checkIdBtn()
{
  QString id = lineEdit->text();
  QDate m_date = dateEditBegin->date();
  dateBeign = m_date.toString("yyyy-MM-dd");

  QDate f_date = dateEditOver->date();
  dateOver = f_date.toString("yyyy-MM-dd");

  QVector<QVector<double>> curData =  sqliteTools->searchCurrentDate(id,dateBeign,dateOver);

  emit mySignalPoints(curData);
}
