#include "mytool.h"

MyTool::MyTool(QWidget *parent)
  : QWidget(parent)
{
//  resize(300,400);
  btn = new QPushButton("医生");
  btn->setStyleSheet("background-color:#e9e9e9;");

  btn->setIcon(QIcon(":/new/prefix1/source/img/down.png"));


  tableWidget = new QTableWidget();

  tableWidget->setColumnCount(4);
  tableWidget->setRowCount(10);

  //隐藏垂直表头
  QHeaderView *header1 =   tableWidget->verticalHeader();
  header1->setHidden(true);

//   tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:13pt '宋体';};");

  QStringList strList;
  strList<<tr("id")<<tr("姓名")<<tr("标识")<<tr("坐标");
  tableWidget->setHorizontalHeaderLabels(strList);

  //弹簧
  QSpacerItem *h_spacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Minimum);
  QSpacerItem *v_spacer = new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding);


  QVBoxLayout *v_layout = new QVBoxLayout;
  v_layout->addWidget(btn);
  v_layout->addWidget(tableWidget);
  v_layout->addItem(v_spacer);

  setLayout(v_layout);

  connect(btn,SIGNAL(clicked()),this,SLOT(showTableWidget()));

}

MyTool::~MyTool()
{
}

void MyTool::setButtonName(QString name)
{
  btn->setText(name);
}

void MyTool::showTableWidget()
{
  tableWidget->setHidden(showFlag);

  if(showFlag)
    {
        btn->setIcon(QIcon(":/new/prefix1/source/img/left.png"));
    }else{
          btn->setIcon(QIcon(":/new/prefix1/source/img/down.png"));
    }

      showFlag = !showFlag;
}

