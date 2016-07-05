#ifndef COEFFPLANE_H
#define COEFFPLANE_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QSplineSeries>
#include <QLineSeries>
#include <QScatterSeries>
#include <QMouseEvent>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>
#include <QSlider>
#include <QKeyEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QValidator>

#include "shared.h"
#include "geomath.h"
#include "functions.h"


using namespace QtCharts;

//const int MAX_HISTORY_ITEMS = 5;
const int LOCAL_FLAG = 0;
const int GLOBAL_FLAG = 1;
//const int HISTORY_ITEM_SIZE = 60;


class CoeffPlaneView : public QChartView {
    Q_OBJECT
public:
    CoeffPlaneView(QChart *chart, QScatterSeries *coordinateSeries) : QChartView(chart) { this->chart = chart; this->coordinateSeries = coordinateSeries; setMouseTracking(false);}
    
protected:
    void mouseReleaseEvent(QMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton)
        {
            // qDebug() << "Clicked on: " << event->pos();
            coordinateSeries->replace(0, chart->mapToValue(event->pos(), coordinateSeries));
            mouseMoving = false;
        }
    };
    
    void mousePressEvent(QMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton)
        {
            // qDebug() << "Clicked on: " << event->pos();
            coordinateSeries->replace(0, chart->mapToValue(event->pos(), coordinateSeries));
            mouseMoving = true;
        }
    }
    
    void mouseMoveEvent(QMouseEvent *event)
    {
        // qDebug() << "in move event " << event->pos();;
        if(mouseMoving)
        {
            // qDebug() << "Clicked on: " << event->pos();
            coordinateSeries->replace(0, chart->mapToValue(event->pos(), coordinateSeries));
        }
    };
    
private:
    QScatterSeries* coordinateSeries;
    QChart *chart;
    bool mouseMoving;
};



class CoeffPlane : public QWidget
{
    Q_OBJECT
public:
    CoeffPlane(QWidget *parent = 0) : QWidget(parent) { }
    explicit CoeffPlane(AbstractFunction *currFunction, unsigned int *termIndex);
    ~CoeffPlane() { }
    
signals:
    void setPolarCoordinates(int coeffFlag, const QString &radius, const QString &angle);
    
private:
    QWidget *coeffPlanePopUp;
    QGroupBox *polarCoordinatesBox;
    QHBoxLayout *coeffPlanePopUpLayout;
    QVBoxLayout *polarCoordinatesLayout;
    QHBoxLayout *actionButtonLayout;
    QHBoxLayout *zoomButtonLayout;
    QVBoxLayout *polarPlaneWithZoomLayout;
    CoeffPlaneView *graphDisplay;
    QChart *graph;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QLabel *radiusLabel;
    QLabel *angleLabel;
    QLineEdit *radiusEdit;
    QLineEdit *angleEdit;
    QPushButton *confirmButton;
    QPushButton *resetButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QSpacerItem *planeSpacer1;
    QSpacerItem *planeSpacer2;
    QLineSeries *series;
    QLineSeries *series2;
    QScatterSeries *coordinateSeries;
    QLineSeries *xSeries;
    QLineSeries *ySeries;
    int coeffFlag;
    
    QDoubleValidator *doubleValidate;
    QDoubleValidator *angleValidate;
    
    void updatePolarCoordinates(QPointF point);
    
    AbstractFunction *currFunction;
    unsigned int *termIndex;
    
    private slots:
    void showPlanePopUp(int flag);
    void updatePolarCoordinatesWithIndex(const int &index);
    void updatePolarCoordinates();
    void polarPlaneZoomIn();
    void polarPlaneZoomOut();
    
    void setPolarCoordinates();
    void resetPolarCoordinates();
    
    
    
    
    
};

#endif // COEFFPLANE_H