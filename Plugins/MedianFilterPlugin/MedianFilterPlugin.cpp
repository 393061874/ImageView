#include "MedianFilterPlugin.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QImage>
#include <QDebug>

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
    Mat src = Mat(inputImage.height(), inputImage.width(), CV_8UC3, (void *)inputImage.bits(), inputImage.bytesPerLine());
    Mat dst;
    medianBlur(src, dst, 15);
    imwrite("src.png", src);
    imwrite("dst.png", dst);
    outputImage = QImage(dst.data, dst.cols, dst.rows, dst.step, QImage::Format_BGR888).copy();
}
