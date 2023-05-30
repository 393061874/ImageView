#ifndef MEDIAN_FILTER_PLUGIN_H
#define MEDIAN_FILTER_PLUGIN_H

#include "MedianFilterPlugin_global.h"
#include "../ImageProcessPluginInterface.h"


class MEDIAN_FILTER_PLUGIN_EXPORT MedianFilterPlugin:
    public QObject, public CvPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.amin.cvplugininterface")
    Q_INTERFACES(CvPluginInterface)

public:
    MedianFilterPlugin();
    ~MedianFilterPlugin();
    QString description();
    void processImage(const QImage &inputImage, QImage &outputImage);
};

#endif // MEDIAN_FILTER_PLUGIN_H
