#include "ImageView.h"
#include <QWheelEvent>


ImageView::ImageView(QWidget *parent):
    QGraphicsView(parent)
{
    // 跟踪鼠标位置
    setMouseTracking(true);

    // 不要边框
    setStyleSheet("padding: 0px, border: 0px");

    // 取消锚点
    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);

    // 不要对齐
    //setAlignment(0);

    // 不要滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ImageView::bindLabelPos(QLabel *p_labelPos)
{
    this->p_labelPos = p_labelPos;
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        flagDrag = true;
        sceneLastMousePos = mapToScene(event->pos());
    }

    QGraphicsView::mousePressEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        flagDrag = false;
        sceneLastMousePos = mapToScene(event->pos());
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    sceneMousePos = this->mapToScene(event->pos());
    if (flagDrag)
    {
        QPointF drag_vec = sceneMousePos - sceneLastMousePos;
        QTransform move(1.0, 0,   0,
                        0,   1.0, 0,
                        0.01,   0.01,   1);
        qDebug() << " -------";
        qDebug() << move;
        setTransform(move, true);
        qDebug() << transform();
        //translate(drag_vec.x(), drag_vec.y());
        sceneMousePos = sceneLastMousePos;
    }
    if (p_labelPos)
    {
        QPoint p2i = sceneMousePos.toPoint();  // 只显示整数坐标
        p_labelPos->setText(QString("%1, %2").arg(p2i.x()).arg(p2i.y()));
    }

    sceneLastMousePos = sceneMousePos;

    QGraphicsView::mouseMoveEvent(event);
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    int angleDeltaY = event->angleDelta().y();
    double zoomFactor = qPow(1.0015, angleDeltaY);
    //qDebug() << zoomFactor;
    scale(zoomFactor, zoomFactor);
    //this->centerOn(sceneMousePos * (1.0 - zoomFactor));
    this->viewport()->update();
    event->accept();
}

