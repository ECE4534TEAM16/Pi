#include "mazecell.h"

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
        else
        {
            brush.setColor(Qt::darkRed);
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
    isMaze = true;
    update();
    QGraphicsItem::mousePressEvent(event);

}

void mazecell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    isMaze = false;
    update();
    QGraphicsItem::mousePressEvent(event);
}

