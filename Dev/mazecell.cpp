#include "mazecell.h"
#include "celldialog.h"
#include <QDebug>



mazecell::mazecell()
{
    isMaze = false;
    isNode = false;
}

QRectF mazecell::boundingRect() const
{

    return QRectF(x_pos,y_pos,recSize,recSize);
}

void mazecell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::black);


    if(isNode)
    {
        if(cellRole == START)
        {
            brush.setColor(Qt::darkGreen);
        }
        else if(cellRole == END)
        {
            brush.setColor(Qt::darkRed);
        }
        else
        {
            brush.setColor(Qt::white);
        }
    }
    else
    {
        if(isMaze)
        {
            brush.setColor(Qt::white);
        }
        else
            brush.setColor(Qt::black);
    }
    painter->fillRect(rec, brush);
    painter->drawRect(rec);



}

void mazecell::setpos(int x, int y, int size)
{
    x_pos = x;
    y_pos = y;
    recSize = size;
}

//allows widget.cpp to define roles and intersection types
void mazecell::setRole(ROLE role)
{
    cellRole = role;
    update();
}

void mazecell::setIntersection(INTERSECTION type)
{
    intersectionType = type;
    if(type == STANDARD)
    {
        isNode = false;
    }
    else
    {
        isNode = true;
    }
}

void mazecell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    if(event->button() == Qt::RightButton)
    {
        if(isNode) //allow this to be picked as start or stop point
        {
            CellDialog *cd = new CellDialog(*this);
            connect(cd, SIGNAL(cellStartChange()), this, SLOT(cellDialogStartChange()));
            connect(cd, SIGNAL(cellEndChange()), this, SLOT(cellDialogEndChange()));
            cd->show();
        }
    }
    update();


}

void mazecell::cellDialogStartChange()
{
    qDebug() << "start Slot working";
    emit StartChange(); //emits a signal to a slot in widget.cpp
}

void mazecell::cellDialogEndChange()
{
    qDebug() << "end Slot working";
    emit EndChange(); //emits a signal to a slot in widget.cpp
}




























