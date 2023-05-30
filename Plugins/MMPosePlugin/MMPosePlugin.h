#ifndef MMPOSEPLUGIN_H
#define MMPOSEPLUGIN_H

#include "MMPosePlugin_global.h"
#include "../ImageProcessPluginInterface.h"


class MMPOSEAPI_EXPORT MMPosePlugin:
    public QObject, public ImageProcessPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.amin.imageprocessplugininterface")
    Q_INTERFACES(ImageProcessPluginInterface)

public:
    MMPosePlugin();
    ~MMPosePlugin();
    QString description();
    void processImage(const QImage &inputImage, QImage &outputImage);
};

#endif // MMPOSEAPI_H
