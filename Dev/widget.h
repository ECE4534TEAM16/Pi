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


#define test        true

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
};

#endif // WIDGET_H
