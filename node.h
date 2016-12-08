#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

//! [0]
class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget,QString qstr);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;
    QString name;


    enum { Type = UserType + 1 };
    int type() const Q_DECL_OVERRIDE { return Type; }

    void calculateForces();
    bool advance();

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;
};
//! [0]

#endif // NODE_H
