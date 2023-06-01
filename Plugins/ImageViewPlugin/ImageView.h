#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QLabel>
#include <opencv2/opencv.hpp>


class ImageView : public QLabel
{
public:
    ImageView(QWidget *parent = nullptr);
    void setImage(const QImage *image);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    // 视角操作
    bool flagDrag = false;
    QPointF sceneLastMousePos;

    // 图片
    const QImage *image;

    // 显示
    cv::Mat src;
    cv::Point2d origin;  // 视窗左上角点
    double scale;  // 放大倍数
    void update();
};

#endif // IMAGEVIEW_H
