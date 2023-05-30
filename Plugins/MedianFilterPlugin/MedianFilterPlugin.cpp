#include "MedianFilterPlugin.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


MedianFilterPlugin::MedianFilterPlugin()
{
}

MedianFilterPlugin::~MedianFilterPlugin()
{
}

QString MedianFilterPlugin::description()
{
    return "This plugin applies median blur filters to any image."
           " This plugin's goal is to make us more familiar with the"
           " concept of plugins in general.";
}

void MedianFilterPlugin::processImage(const QImage &inputImage, QImage &outputImage)
{
    //medianBlur(inputImage, outputImage, 5);

    //cv::Mat &image = imageList[0];
    //plugin->processImage(image, image);

    //QImage q_image(image.data, image.cols, image.rows, image.step, QImage::Format_BGR888);
    //GraphicsPixmapItem *item = new QGraphicsPixmapItem(QPixmap::fromImage(q_image));
    //scene.clear();
    //scene.addItem(item);  // the item will be take over by scene

    //if (imageViewPlugin)
    //    imageViewPlugin->showImage(q_image);
}
