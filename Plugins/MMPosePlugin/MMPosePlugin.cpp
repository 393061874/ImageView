#include "MMPosePlugin.h"

MMPosePlugin::MMPosePlugin()
{
}




//#include "mmdeploy/pose_detector.hpp"

//#include <iostream>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/imgproc.hpp>
//#include <string>

//int main()
//{
//    std::string model_path = "/media/tianshu/fastdata/project/mmlab/mmdeploy/work-dirs/mmpose/topdown/hrnet/trt";
//    std::string image_path = "/media/tianshu/fastdata/project/mmlab/mmdeploy/demo/resources/human-pose.jpg";

//    cv::Mat img = cv::imread(image_path);
//    if (!img.data) {
//        fprintf(stderr, "failed to load image: %s\n", image_path.c_str());
//        return 1;
//    }

//    using namespace mmdeploy;

//    PoseDetector detector{Model(model_path), Device("cuda")};
//    auto res = detector.Apply(img);

//    for (int i = 0; i < res[0].length; i++) {
//        cv::circle(img, {(int)res[0].point[i].x, (int)res[0].point[i].y}, 1, {0, 255, 0}, 2);
//    }
//    cv::imwrite("output_pose.png", img);

//    return 0;
//}
