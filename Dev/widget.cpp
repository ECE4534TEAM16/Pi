#include "widget.h"
#include "ui_widget.h"



QTextStream erout(stderr);

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->mazeView->setScene(scene);

    QBrush redBrush(Qt::red);
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);


    for(int j = 0; j < 75; j++)
    {
        for(int i = 0; i < 75; i++)
        {
            rectangle = scene->addRect(i*10,j*10,10,10,blackPen,whiteBrush);
        }
    }

    mapper = new SerialPort;
    mapperList_count = 0;
}





Widget::~Widget()
{
    delete ui;
}

QStringList Widget::parseM_dat(QStringList dat)
{
    QString temp;
    QString returnTemp;
    QStringList templist;

    for(int i = 0; i < dat.size(); i++)
    {
        temp = dat.at(i);
        if(temp.size() == 5) // this is an instruction for the maze
        {
            returnTemp.append("Dist: ");
            returnTemp.append(temp.at(0)); //should be a distance
            returnTemp.append(" | Intersection: ");
            returnTemp.append(temp.at(1)); //intersection type
            returnTemp.append(temp.at(2));
            returnTemp.append(temp.at(3));
            returnTemp.append(" | Dir: ");
            returnTemp.append(temp.at(4)); //direction taken
            templist.append(returnTemp);
            returnTemp.clear();
        }
        else //this is the end character
        {
            if(temp.size() == 1)
                templist.append("At end of maze");
            else
            {
                templist.append(temp);
            }
        }

    }
    return templist;

}



//need to send start signal first, then wait for signal from serial port to recieve data as it comes in
void Widget::on_mapperStart_button_clicked()
{
    QString temp;
    if(test)
        mapperDat = mapper->readline("test1.dat");
    else
    {
        //need to implement serial port recieve here.
    }

    mapperDat = parseM_dat(mapperDat);
    for(int i = 0; i < mapperDat.size(); i++)
    {
        temp = mapperDat.at(i);
        if(temp.at(0) == 'W')//warning
        {
            ui->mapperList->addItem(mapperDat.at(i));
            ui->mapperList->item(mapperList_count)->setTextColor(QColor(255,165,0));
            mapperList_count++;
        }
        else if(temp.at(0) == 'E')//warning
        {
            ui->mapperList->addItem(mapperDat.at(i));
            ui->mapperList->item(mapperList_count)->setTextColor(Qt::darkRed);
            mapperList_count++;
        }
        else
        {
            ui->mapperList->addItem(mapperDat.at(i));
            mapperList_count++;
        }
    }
}

void Widget::on_userStart_button_clicked()
{

}

void Widget::on_mazeSolve_button_clicked()
{

}




//following buttons do not need signals
//they simply output text in the from of QMessageBox
void Widget::on_constraints_button_clicked()
{
    QMessageBox constraints(this);
    constraints.setText(" - The maze must be confined to a 9x9 foot box\n - The mapper rover must be run before the user rover");
    constraints.setIcon(QMessageBox::Information);
    constraints.setStandardButtons(QMessageBox::Ok);
    constraints.setDefaultButton(QMessageBox::Ok);
    constraints.setWindowTitle("Application Constraints");
    int ret = constraints.exec();
    switch(ret)
    {
    case QMessageBox::Ok:
        break;
    default:
        erout << "Error, Reached default case in Widget::on_constraints_button_clicked";
        exit(EXIT_FAILURE);
    }

}

void Widget::on_exit_button_clicked()
{
    QMessageBox quits(this);
    quits.setText("Are you sure you want to exit the program?");
    quits.setIcon(QMessageBox::Question);
    quits.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    quits.setDefaultButton(QMessageBox::No);
    quits.setWindowTitle("Quit?");
    int ret = quits.exec();
    switch (ret)
    {
    case QMessageBox::No:
          // dont quit program
        break;
    case QMessageBox::Yes:
          // Quit the program

        QApplication::quit();
        break;
    default:
          // should never be reached
        erout << "Error, Reached default case in Widget::on_exit_button_clicked";
        exit(EXIT_FAILURE);
    }
}



