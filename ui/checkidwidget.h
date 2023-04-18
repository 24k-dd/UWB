#ifndef CHECKIDWIDGET_H
#define CHECKIDWIDGET_H

#include <QWidget>
#include <QDateEdit>
#include <QDate>
#include <QLineEdit>

#include"sqlitetools.h"
class CheckIdWidget : public QWidget
{
  Q_OBJECT
public:
  explicit CheckIdWidget(QWidget *parent = nullptr);

  void closeEvent(QCloseEvent *event);

signals:

  mySignalPoints(const QVector<QVector<double>>& points);

  mySignalClose();

public slots:

  void checkIdBtn();

private:
  QDateEdit *dateEditBegin = nullptr;
  QDateEdit *dateEditOver = nullptr;

  QString dateBeign;
  QString dateOver;

  SQLiteTools *sqliteTools = nullptr;
  QLineEdit *lineEdit = nullptr;
};

#endif // CHECKIDWIDGET_H
