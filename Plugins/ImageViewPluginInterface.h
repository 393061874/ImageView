#ifndef IMAGE_VIEW_PLUGIN_INTERFACE_H
#define IMAGE_VIEW_PLUGIN_INTERFACE_H

#include <QObject>


class ImageViewPluginInterface
{
public:
    virtual ~ImageViewPluginInterface() {}
    virtual QWidget *createWidget() = 0;
    virtual void showImage(const QImage &image) = 0;
    virtual QRectF getWinRect() = 0;
    virtual QRectF getRoiRect() = 0;
};

#define IMAGEVIEWPLUGININTERFACE_IID "com.Interface.ImageViewPluginInterface"
Q_DECLARE_INTERFACE(ImageViewPluginInterface, IMAGEVIEWPLUGININTERFACE_IID)

#endif // IMAGE_VIEW_PLUGIN_INTERFACE_H
