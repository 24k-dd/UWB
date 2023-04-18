#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include<QPixmap>
#include<QLabel>
#include<QMessageBox>

#include"mainwindow.h"
#include<windows.h>

#include<tlhelp32.h>

#include<comdef.h>


class LoginWidget : public QWidget
{
  Q_OBJECT

public:
  explicit LoginWidget(QWidget *parent = nullptr);
  ~LoginWidget();

   void create();

signals:

private slots:

  void login_clicked();


private:
  QImage loginImage;

  MainWindow *mainWindow = NULL;
  QLineEdit *lineEdit_username = NULL;
  QLineEdit *lineEdit_password = NULL;
  QString username;
  QString password;

};

#endif // LOGINWIDGET_H
