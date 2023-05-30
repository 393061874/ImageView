#include "MMPosePlugin.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QImage>
#include <QDebug>
#include "mmdeploy/pose_detector.hpp"
#include <string>

using namespace std;
using namespace cv;


MMPosePlugin::MMPosePlugin()
{
}

MMPosePlugin::~MMPosePlugin()
{
}

QString MMPosePlugin::description()
{
    return "This plugin applies mmpose filters to any image."
           " This plugin's goal is to make us more familiar with the"
           " concept of plugins in general.";
}

void MMPosePlugin::processImage(const QImage &inputImage, QImage &outputImage)
{
    // 推理引擎
    string model_path = "/media/tianshu/fastdata/project/mmlab/mmdeploy/work-dirs/mmpose/topdown/hrnet/trt";
    mmdeploy::PoseDetector detector{mmdeploy::Model(model_path), mmdeploy::Device("cuda")};

    // 输入输出图片
    Mat src = Mat(inputImage.height(), inputImage.width(), CV_8UC3, (void *)inputImage.constBits(), inputImage.bytesPerLine());
    Mat dst = src.clone();

    // 推理并绘制结果
    cvtColor(dst, dst, COLOR_BGR2RGB);
    auto res = detector.Apply(dst);
    for (int i = 0; i < res[0].length; i++) {
        cv::circle(dst, {(int)res[0].point[i].x, (int)res[0].point[i].y}, 1, {0, 255, 0}, 2);
    }
    outputImage = QImage(dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888).copy();
}
