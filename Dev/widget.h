#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QTextStream>
#include <QGraphicsScene>
#include <QStringList>
#include <QString>
#include <QColor>
#include "serialport.h"
#include "mazecell.h"
#include <QVector>
#include <QList>
#include <QQueue>
#include <QTime>


#define TEST            false
#define DEBUG           true
#define GRID_SIZE       75
#define CELL_SIZE       10


enum CURRENT_DIRECTION          //will state the rovers current direction with respect to where it initialy pointed
{                               //Rover will always have an initial direction of UP
    UP,
    LEFT,
    RIGHT,
    DOWN
};



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QStringList parseM_dat(QStringList dat);
    void drawStandard();
    void checkBounds(int pos);
    void updateDir(QString newDir);
    void drawIntersection(QString intersection);
    void mazeBuild();


public slots:
    void on_RoleStartChange();
    void on_RoleEndChange();
    void mapper_recieveData();

private slots:
    void on_mapperStart_button_clicked();
    void on_userStart_button_clicked();
    void on_mazeSolve_button_clicked();
    void on_constraints_button_clicked();
    void on_exit_button_clicked();



private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    SerialPort *ports;
    QStringList mapperDat;
    QStringList userDat;
    int mapperList_count;
    mazecell *cell;
    QList<QList<mazecell*> >  *mazeArray;           //2d array of mazecell graphics items
    int mazeRow;
    int mazeCol;
    int mapperSec;
    int mapperMin;
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    CURRENT_DIRECTION currDir;
    QQueue<QString> mapperQueue;
    QStringList buildList;
    QTime mapperTime;
    bool mapper_completed;



};

#endif // WIDGET_H
