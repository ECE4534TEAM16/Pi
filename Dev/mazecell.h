#ifndef MAZECELL_H
#define MAZECELL_H

#include <QGraphicsItem>
#include <QPainter>
#include <qdebug.h>

enum ROLE {START, END, NORMAL};
enum INTERSECTION
{
    INIT_START,
    STANDARD,
    LEFT_ONLY,
    RIGHT_ONLY,
    LEFT_FORWARD,
    LEFT_RIGHT,
    RIGHT_FORWARD,
    ALL_THREE,
    DEAD_END
};


class mazecell : public QGraphicsItem
{
public:
    mazecell();


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setpos(int x, int y, int size);
    void setRole(ROLE role);
    void setIntersection(INTERSECTION type);

    bool isMaze;
    bool isNode;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);



private:
    int x_pos;
    int y_pos;
    int recSize;
    ROLE cellRole;
    INTERSECTION intersectionType;

//signals:

//public slots:
};

#endif // MAZECELL_H
