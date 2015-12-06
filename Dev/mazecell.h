#ifndef MAZECELL_H
#define MAZECELL_H

#include <QGraphicsItem>
#include <QPainter>
#include <qdebug.h>
#include <QGraphicsSceneMouseEvent>

enum ROLE {START, END, NORMAL, NONMAZE};
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


class mazecell :  public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    mazecell();


    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setpos(int x, int y, int size);
    void setRole(ROLE role);
    void setIntersection(INTERSECTION type);

    bool isMaze;
    bool isNode;
    bool isPath;
    bool visited;
    INTERSECTION intersectionType;

    ROLE cellRole;
    int x_pos;
    int y_pos;
    int recSize;
    double distToEnd;
    double distToStart;
    double F;
    int parent_col;
    int parent_row;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void StartChange();
    void EndChange();

private slots:
    void cellDialogStartChange();
    void cellDialogEndChange();

//private:


};


#endif // MAZECELL_H
