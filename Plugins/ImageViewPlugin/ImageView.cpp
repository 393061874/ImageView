#include "ImageView.h"
#include <QWheelEvent>


ImageView::ImageView(QWidget *parent):
    QLabel(parent)
{
    // 伸缩策略
    QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(sizePolicy().hasHeightForWidth());
    setSizePolicy(sizePolicy1);

    // 跟踪鼠标位置
    setMouseTracking(true);

    // 不要边框
    setStyleSheet("padding: 0px, border: 0px");
}

void ImageView::setImage(const QImage *image)
{
    this->image = image;

    src = cv::Mat(image->height(), image->width(), CV_8UC3,
        (void *)image->constBits(), image->bytesPerLine());
    origin = cv::Point2d(0.0, 0.0);
    scale = 1.0;
    update();
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        flagDrag = true;
        sceneLastMousePos = event->position();
    }

    QLabel::mousePressEvent(event);
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        flagDrag = false;
        sceneLastMousePos = event->position();
    }

    QLabel::mouseReleaseEvent(event);
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF sceneMousePos = event->position();
    if (flagDrag)
    {
        QPointF drag_vec = sceneMousePos - sceneLastMousePos;
        origin -= cv::Point2d(drag_vec.x(), drag_vec.y()) / scale;
    }
    sceneLastMousePos = sceneMousePos;
    update();

    QLabel::mouseMoveEvent(event);
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    int angleDeltaY = event->angleDelta().y();
    double zoomFactor = qPow(1.0015, angleDeltaY);
    cv::Point2d corner(event->position().x(), event->position().y());
    origin += corner / scale * (1.0 - 1.0 / zoomFactor);
    scale *= zoomFactor;
    update();

    QLabel::wheelEvent(event);
}

void ImageView::resizeEvent(QResizeEvent *event)
{
    update();
    QLabel::resizeEvent(event);
}

void ImageView::update()
{
    if (src.empty())
        return;

    // 图像
    cv::Mat dst;
    double data[6] = {
        scale, 0.0, -origin.x * scale,
        0.0, scale, -origin.y * scale
    };
    cv::Mat M(2, 3, CV_64FC1, data);
    cv::warpAffine(src, dst, M, {size().width(), size().height()}, cv::INTER_NEAREST);

    // 显示坐标和像素值字串
    cv::Point2d corner(sceneLastMousePos.x(), sceneLastMousePos.y());
    cv::Point2d imagePos = corner / scale + origin + cv::Point2d(0.5, 0.5);
    qDebug() << imagePos.x << imagePos.y;

    // 打像素块网格

    // 在像素块上显示像素值

    // 显示
    QImage show((uchar *)dst.data, dst.cols, dst.rows, dst.cols * 3, QImage::Format_BGR888);
    setPixmap(QPixmap::fromImage(show));
}
