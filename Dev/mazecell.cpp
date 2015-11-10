#include "mazecell.h"

mazecell::mazecell()
{
    Pressed = false;

}

QRectF mazecell::boundingRect() const
{

    return QRectF(x_pos,y_pos,recSize,recSize);
}

void mazecell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::black);

    if(Pressed)
    {
        brush.setColor(Qt::white);
    }
    else
    {
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

void mazecell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);

}

void mazecell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mousePressEvent(event);
}

