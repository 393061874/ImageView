#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QLabel>


class ImageView : public QGraphicsView
{
public:
    ImageView(QWidget *parent = nullptr);

    void bindLabelPos(QLabel *p_labelPos);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    // 视角操作
    bool flagDrag = false;
    QPointF sceneLastMousePos;
    QPointF sceneMousePos;

    // 信息显示
    QLabel *p_labelPos = nullptr;
};

#endif // IMAGEVIEW_H
