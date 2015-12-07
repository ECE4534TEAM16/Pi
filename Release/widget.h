/*
    Tyler Olson
    Virginia Tech ECE 4534 Embedded System Design
    widget.h & widget.cpp

    DESCRIPTION:
        These files are the main catalyst within the program.  The ui is set up here, all other classes are
        used within this class as helpers.  The A* search algorithm is implemented in this class as well.
*/

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
#include <QPair>
#include <QList>
#include <QQueue>
#include <QTime>
#include <math.h>
#include <QtAlgorithms>


#define TEST            false
#define GRID_SIZE       75
#define CELL_SIZE       10


enum CURRENT_DIRECTION          //will state the rovers current direction with respect to where it initialy pointed
{                               //Rover will always have an initial direction of UP
    UP,
    LEFT,
    RIGHT,
    DOWN
};

struct listDat
{
    int col;
    int row;
    int cost;

    bool operator<(const listDat& other) const
    {
        return cost < other.cost;
    }
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
    void setDists(int col, int row);
    void A_star(int col, int row);
    void findAdjacent(int col, int row);
    void parsePath(int pos);
    QString IntersectionInstr(int col, int row, int futureCol, int futureRow);
    void createPathList();


public slots:
    void on_RoleStartChange();
    void on_RoleEndChange();
    void mapper_recieveData();
    void user_ui_update();
    void mapper_ui_update();
    void mapper_finished();

private slots:
    void on_mapperStart_button_clicked();
    void on_userStart_button_clicked();
    void on_mazeSolve_button_clicked();
    void on_constraints_button_clicked();
    void on_exit_button_clicked();



private:
    //ui
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;

    //classes
    SerialPort *ports;
    mazecell *cell;

    //QString & QStringLists
    QStringList mapperDat;
    QStringList userDat;
    QStringList userInstr;
    QStringList buildList;

    //ints
    int mapperList_count;
    int userList_count;
    int mazeRow;
    int mazeCol;
    int mapperSec;
    int mapperMin;
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    int count;

    //enums
    CURRENT_DIRECTION currDir;
    CURRENT_DIRECTION UserDir;

    //containers
    QQueue<QString> mapperQueue;
    QList<listDat> openList;
    QList<QPair<int,int> > closedList;
    QList<QList<mazecell*> >  *mazeArray;           //2d array of mazecell graphics items

    //bools
    bool mapper_completed;
    bool end_exists;
    bool solved;



};

#endif // WIDGET_H
