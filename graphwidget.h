#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QList>
#include "edge.h"

class Node;

//! [0]
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);
    QGraphicsScene *scene;
    QList<Edge*> edgelist;
    QList<QString> alfabeto;
    int actual;

    void itemMoved();
    void addNode();
    qreal distancia(QPointF p, QPointF p1);

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) Q_DECL_OVERRIDE;

    void scaleView(qreal scaleFactor);

private:
    int timerId;

};
//! [0]

#endif // GRAPHWIDGET_H
