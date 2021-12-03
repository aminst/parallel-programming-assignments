#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>

int main()
{
    cv::Mat img1 = cv::imread("1.png");
    cv::Mat img2 = cv::imread("2.png");
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
    cv::imshow("image", img2);
    cv::waitKey(0);

}