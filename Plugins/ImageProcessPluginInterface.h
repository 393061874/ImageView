#ifndef CVPLUGININTERFACE_H
#define CVPLUGININTERFACE_H

#include <QObject>
#include <QString>


class CvPluginInterface
{
public:
    virtual ~CvPluginInterface() {}
    virtual QString description() = 0;
    virtual void processImage(const QImage &inputImage, QImage &outputImage) = 0;
};

#define CVPLUGININTERFACE_IID "com.amin.cvplugininterface"
Q_DECLARE_INTERFACE(CvPluginInterface, CVPLUGININTERFACE_IID)


#endif // CVPLUGININTERFACE_H
