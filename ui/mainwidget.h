#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include<QTime>
#include<QValueAxis>
#include<QLineEdit>
#include<QPushButton>

#include "chartview.h"
#include "callout.h"
#include "model/Model.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();


  void showGrid();

private:
    void wheelEvent(QWheelEvent *event);

    void initUI();
    void initChart();
    void initSlot();

    void updateData();

    Ui::MainWidget *ui;

    ChartView *chartView;
    QChart *chart;
    Callout *tip;
    QLineSeries *series;

    QTimer *timer;

    quint16 count;

    bool isStopping;

    bool  gridFlag = true;

    bool locusPlayFlag = false;

    bool s_Flag = false;

private slots:
    void timerSlot();
    void buttonSlot();
    void tipSlot(QPointF position, bool isHovering);

    //网格化
    void showGridSlot();

    //轨迹播放
    void locusPlay();

    //倍速
    void speedPlay();

        void speedPlay1();

        //特定id
        void checkId();

};

#endif // MAINWIDGET_H
