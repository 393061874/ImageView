#ifndef IMAGEPROCESSPLUGININTERFACE_H
#define IMAGEPROCESSPLUGININTERFACE_H

#include <QObject>


class ImageProcessPluginInterface
{
public:
    virtual ~ImageProcessPluginInterface() {}
    virtual QString description() = 0;
    virtual void processImage(const QImage &inputImage, QImage &outputImage) = 0;
};

#define IMAGEPROCESSPLUGININTERFACE_IID "com.amin.imageprocessplugininterface"
Q_DECLARE_INTERFACE(ImageProcessPluginInterface, IMAGEPROCESSPLUGININTERFACE_IID)


#endif // IMAGEPROCESSPLUGININTERFACE_H
