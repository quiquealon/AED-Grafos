#include "graphwidget.h"

#include "node.h"


#include <math.h>

#include <QKeyEvent>

#include <QDebug>
#include <QtMath>
#include <time.h>
#include <algorithm>



//! [0]
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-400, -400, 600, 600);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(500, 500);

    alfabeto.append("A");alfabeto.append("B");alfabeto.append("C");alfabeto.append("D");alfabeto.append("E");
    alfabeto.append("F");alfabeto.append("G");alfabeto.append("H");alfabeto.append("I");alfabeto.append("J");
    alfabeto.append("K");alfabeto.append("L");alfabeto.append("M");alfabeto.append("N");alfabeto.append("O");
    alfabeto.append("P");alfabeto.append("Q");alfabeto.append("R");alfabeto.append("S");alfabeto.append("T");
    alfabeto.append("U");alfabeto.append("V");alfabeto.append("W");alfabeto.append("X");alfabeto.append("Y");
    alfabeto.append("Z");
    alfabeto.append("AA");alfabeto.append("BB");alfabeto.append("CC");alfabeto.append("DD");alfabeto.append("EE");
    alfabeto.append("FF");alfabeto.append("GG");alfabeto.append("HH");alfabeto.append("II");alfabeto.append("JJ");
    alfabeto.append("KK");alfabeto.append("LL");alfabeto.append("MM");alfabeto.append("NN");alfabeto.append("OO");
    alfabeto.append("PP");alfabeto.append("QQ");alfabeto.append("RR");alfabeto.append("SS");alfabeto.append("TT");
    alfabeto.append("UU");alfabeto.append("VV");alfabeto.append("WW");alfabeto.append("XX");alfabeto.append("YY");
    alfabeto.append("ZZ");

    actual=0;


//! [0]



}
//! [1]

//! [2]
void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}
//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
        addNode();
        break;

    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:

        zoomOut();
        break;

    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene->items()) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }

    foreach (Node *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes) {
        if (node->advance())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

#ifndef QT_NO_WHEELEVENT
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);


}
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene->items()) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + qrand() % 300, -150 + qrand() % 300);
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::addNode()
{
  qsrand(time(NULL));
  Node *node = new Node(this,alfabeto.at(actual));
  actual++;
  node->setPos(mapToScene(mapFromGlobal(QCursor::pos())));
  scene->addItem(node);
  foreach (QGraphicsItem *item, scene->items()) {
      if ( qgraphicsitem_cast<Node *>(item))
          if(distancia(node->pos(), qgraphicsitem_cast<Node *>(item)->pos())<100 && qgraphicsitem_cast<Node *>(item)!=node)
          {
                float value = qrand()%100;
                Edge *temp=new Edge(node, qgraphicsitem_cast<Node *>(item),value);
                edgelist.append(temp);
                scene->addItem(temp);

          }
      }

}

qreal GraphWidget::distancia(QPointF p, QPointF p1)

  {
    qreal x1=p.x();
    qreal y1=p.y();

    qreal x2=p1.x();
    qreal y2=p1.y();

    qreal norm = sqrt(qPow((x1-x2),2) + qPow((y1-y2),2));

    return norm;


  }


