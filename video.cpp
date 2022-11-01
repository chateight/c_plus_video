#include <opencv2/opencv.hpp>

int main() {
    cv::Mat img = cv::imread("sample.jpeg");
    if(img.empty()) {
        return -1;
    }
    cv::namedWindow("test", cv::WINDOW_AUTOSIZE);
    cv::imshow("test", img);
    cv::waitKey(0);
    cv::destroyWindow("test");
    return 0;
}
