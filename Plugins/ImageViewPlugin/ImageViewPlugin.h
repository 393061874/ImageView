#ifndef VIEWFORM_H
#define VIEWFORM_H

#include "ImageViewPlugin_global.h"
#include "../ImageViewPluginInterface.h"
#include <QWidget>
#include <QGraphicsScene>


namespace Ui {
class ViewForm;
}

class IMAGEVIEWPLUGIN_EXPORT ImageViewPlugin :
    public QWidget, public ImageViewPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.Interface.ImageViewPluginInterface")
    Q_INTERFACES(ImageViewPluginInterface)

public:
    explicit ImageViewPlugin(QWidget *parent = nullptr);
    ~ImageViewPlugin();
    QWidget *createWidget();
    void showImage(const QImage &image);
    QRectF getWinRect();
    QRectF getRoiRect();

private:
    Ui::ViewForm *ui;
    QGraphicsScene scene;
};

#endif // VIEWFORM_H
