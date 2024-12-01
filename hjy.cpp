#include <opencv2/opencv.hpp>
#include <iostream>
int main() {
    cv::VideoCapture cap("video/ballvideo.mp4");
    cv::Mat hjy;
    while (true) {
        cap >> hjy;
        auto start = std::chrono::high_resolution_clock::now();
        cv::Scalar lower_blue(172, 146, 12); 
        cv::Scalar upper_blue(252, 255, 28);
        cv::Mat mask;
        cv::inRange(hjy, lower_blue, upper_blue, mask);
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        for (size_t i = 0; i < contours.size(); i++) {
            cv::Rect boundingRect = cv::boundingRect(contours[i]);
            boundingRect.width += 15; 
            boundingRect.height += 15;
            cv::rectangle(hjy, boundingRect, cv::Scalar(0, 255, 0), 4, 8, 0);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "Time taken to process frame: " << elapsed.count() << " ms" << std::endl;
        cv::imshow("hjy", hjy);
        if (cv::waitKey(30) >= 0) { 
            break; 
        }
    }
    return 0;
}