#ifndef EDGE_H
#define EDGE_H


#include <QGraphicsItem>
#include <QLabel>
#include <QString>
#include <QDebug>

class Node;

//! [0]
class Edge : public QGraphicsItem
{
public:
    Edge(Node *sourceNode, Node *destNode,float valor);

    Node *sourceNode() const;
    Node *destNode() const;
    float value;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const Q_DECL_OVERRIDE { return Type; }

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

private:
    Node *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};


#endif // EDGE_H
