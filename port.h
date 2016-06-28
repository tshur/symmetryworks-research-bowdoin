#ifndef PORT_H
#define PORT_H


#include "display.h"

// #include "renderthread.h"
#include "controllerthread.h"
#include <QThread>

#define NUM_THREADS 4

// TODO: move this to its own source file?
class HistoryItem : public QObject
{
    Q_OBJECT

public:
    
    HistoryItem(QObject *parent = 0) : QObject(parent) { }
    
    QImage *getImage() { return preview->getImage(); }
    
    QVBoxLayout *layoutWithLabelItem;
    QHBoxLayout *layoutItem;
    QVBoxLayout *buttonLayoutItem;
    Display *preview;
    QPushButton *viewButton;
    QPushButton *removeButton;
    QLabel *labelItem;
    QString filePathName;
    // QStringList settings;
    QDateTime savedTime;
    // Port *port;
};

class Port : public QObject
{
    Q_OBJECT
    
public:
    
    // CONSTRUCTOR
    Port(AbstractFunction *currFunction, ColorWheel *currColorWheel, int width, int height, Settings *currSettings);
    
    virtual ~Port(){;}
    
    // ACTIONS
    QString exportImage(QImage *output, const QString &fileName);
    void paintToDisplay(Display *disp);
    void paintHistoryIcon(HistoryItem *item);

protected:
    
    AbstractFunction *currFunction;
    ColorWheel *currColorWheel;
    
    Settings *currSettings;
    
    int width, height;
    //double XCorner, YCorner, setWidth, setHeight;

// private slots:
//     void checkProgress();
    
private:
    void render(QImage *output);
    
    QVector<RenderThread *> threads;

    // ControllerThread *controller;

    // int numThreadsFinished;

};




#endif // PORT_H
