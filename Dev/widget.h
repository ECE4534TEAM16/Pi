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
<<<<<<< HEAD


#define test        true
=======
#include "mazecell.h"
#include <QVector>
#include <QList>


#define TEST            true
#define GRID_SIZE       76
#define CELL_SIZE       10
>>>>>>> temp

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
<<<<<<< HEAD
=======
    void cell_init();
>>>>>>> temp

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
    SerialPort *mapper;
    SerialPort *user;
    QStringList mapperDat;
    QStringList userDat;
    int mapperList_count;
<<<<<<< HEAD
=======
    mazecell *cell;
    QList<QList<mazecell*> >  *mazeArray;//2d array of mazecell graphics items
    int mazeRow;
    int mazeCol;




>>>>>>> temp
};

#endif // WIDGET_H
