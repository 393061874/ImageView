#include "ImageViewPlugin.h"
#include <QPixmap>
#include <QGridLayout>
#include "ImageView.h"


ImageViewPlugin::ImageViewPlugin(QWidget *parent) : QTabWidget(parent)
{


//    // 删除占位窗口
//    ui->gridLayout->removeWidget(ui->label);
//    delete ui->label;

//    // 添加实际要用的窗口
//    ImageView *image_view = new ImageView(this);
//    image_view->setObjectName("imageView");
//    ui->gridLayout->addWidget(image_view, 0, 0, 1, 1);

//    // 设置占位策略
//    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
//    sizePolicy.setHeightForWidth(image_view->sizePolicy().hasHeightForWidth());
//    image_view->setSizePolicy(sizePolicy);

//    // 不接收拖放事件 由主程序处理
//    image_view->setAcceptDrops(false);

    // 初始化自定义功能
    //image_view->bindLabelPos(ui->label_local);
    //image_view->setScene(&scene);
}

ImageViewPlugin::~ImageViewPlugin()
{
    //delete ui;
}

QWidget *ImageViewPlugin::toWidget()
{
    return this;
}

void ImageViewPlugin::append(const QImage &image)
{
    // 添加到图片列表
    imageList.append(image);

    // 添加一页用于显示图片
    QWidget *tab = new QWidget();
    QGridLayout *layout = new QGridLayout(tab);
    ImageView *image_view = new ImageView(tab);
    layout->addWidget(image_view);
    addTab(tab, QString("1"));
    image_view->setImage(&image);

    //tab_Source = new QWidget();
    //tab_Source->setObjectName("tab_Source");
    //gridLayout_Source = new QGridLayout(tab_Source);
    //gridLayout_Source->setObjectName("gridLayout_Source");
    //label_Image = new QLabel(tab_Source);
    //label_Image->setObjectName("label_Image");

    //gridLayout_Source->addWidget(label_Image, 0, 0, 1, 1);

    //tabWidget_ImageView->addTab(tab_Source, QString());


    //    QPixmap image("image.jpeg");
    //    QLabel *label_Source = new QLabel(ui->tab_Source);
    //    label_Source->setObjectName("label_Source");
    //    ui->gridLayout_Source->addWidget(label_Source, 0, 0, 1, 1);

    //    QSize show_size = label_Source->size();
    //    label_Source->setPixmap(image.scaled(image.size() / 3));
    //    label_Source->setScaledContents(true);


    //ui->setupUi(this);

    //QGraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    //scene.clear();
    //scene.addItem(item);  // the item will be take over by scene
}

QList<QImage> &ImageViewPlugin::getImageList()
{
    return imageList;
}

int ImageViewPlugin::getCurrentIndex() const
{
    return currentIndex;
}

void ImageViewPlugin::showIndex(int index)
{
    ;
}

QRectF ImageViewPlugin::getWinRect()
{
    return QRectF();
}

QRectF ImageViewPlugin::getRoiRect()
{
    return QRectF();
}
