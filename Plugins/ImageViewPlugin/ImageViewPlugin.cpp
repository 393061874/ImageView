#include "ImageViewPlugin.h"
#include "ui_viewform.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "ImageView.h"


ImageViewPlugin::ImageViewPlugin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewForm)
{
    ui->setupUi(this);
    // 删除占位窗口
    ui->gridLayout->removeWidget(ui->graphicsView);
    delete ui->graphicsView;
    // 添加实际要用的窗口
    ImageView *image_view = new ImageView(this);
    image_view->setObjectName("imageView");
    image_view->bindLabelPos(ui->label_local);

    ui->gridLayout->addWidget(image_view, 1, 0, 1, 1);
    image_view->setAcceptDrops(false);
    image_view->setScene(&scene);
}

ImageViewPlugin::~ImageViewPlugin()
{
    delete ui;
}

QWidget *ImageViewPlugin::createWidget()
{
    return this;
}

void ImageViewPlugin::showImage(const QImage &image)
{
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene.clear();
    scene.addItem(item);  // the item will be take over by scene
}

QRectF ImageViewPlugin::getWinRect()
{
    return QRectF();
}

QRectF ImageViewPlugin::getRoiRect()
{
    return QRectF();
}
