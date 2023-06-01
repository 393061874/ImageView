#ifndef VIEWFORM_H
#define VIEWFORM_H

#include "ImageViewPlugin_global.h"
#include "../ImageViewPluginInterface.h"
#include <QTabWidget>


namespace Ui {
class ViewForm;
}

class IMAGEVIEWPLUGIN_EXPORT ImageViewPlugin :
    public QTabWidget, public ImageViewPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.Interface.ImageViewPluginInterface")
    Q_INTERFACES(ImageViewPluginInterface)

public:
    explicit ImageViewPlugin(QWidget *parent = nullptr);
    ~ImageViewPlugin();
    QWidget *toWidget();

    // 图片列表操作
    void append(const QImage &image);
    QList<QImage> &getImageList();
    int getCurrentIndex() const;
    void showIndex(int index);

    // 图形操作
    QRectF getWinRect();
    QRectF getRoiRect();

private:
    int currentIndex;
    QList<QImage> imageList;
    //Ui::ViewForm *ui;
    //QGraphicsScene scene;
};

#endif // VIEWFORM_H
