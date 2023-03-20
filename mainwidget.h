#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QChart>
#include <QLineSeries>
#include <QVector>
#include <QTimer>
#include<QTime>

#include "chartview.h"
#include "callout.h"
#include "config.h"

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
    QLineSeries *series,*series1;

    QTimer *timer;

    quint16 count;

    bool isStopping;

    bool  gridFlag = false;
    bool locusPlayFlag = false;



private slots:
    void timerSlot();
    void buttonSlot();
    void tipSlot(QPointF position, bool isHovering);

    //网格化
    void showGrid();

    //轨迹播放
    void locusPlay();

};

#endif // MAINWIDGET_H
