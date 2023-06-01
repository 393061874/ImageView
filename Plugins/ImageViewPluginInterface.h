#ifndef IMAGE_VIEW_PLUGIN_INTERFACE_H
#define IMAGE_VIEW_PLUGIN_INTERFACE_H

#include <QObject>


class ImageViewPluginInterface
{
public:
    virtual ~ImageViewPluginInterface() {}
    virtual QWidget *toWidget() = 0;

    // 图片列表操作
    virtual void append(const QImage &image) = 0;
    virtual QList<QImage> &getImageList() = 0;
    virtual int getCurrentIndex() const = 0;
    virtual void showIndex(int index) = 0;

    // 图形操作
    virtual QRectF getWinRect() = 0;
    virtual QRectF getRoiRect() = 0;
};

#define IMAGEVIEWPLUGININTERFACE_IID "com.Interface.ImageViewPluginInterface"
Q_DECLARE_INTERFACE(ImageViewPluginInterface, IMAGEVIEWPLUGININTERFACE_IID)

#endif // IMAGE_VIEW_PLUGIN_INTERFACE_H
