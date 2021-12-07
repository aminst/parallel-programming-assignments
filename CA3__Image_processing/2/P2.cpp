#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>

#include "utility.hpp"

using namespace std;

timeval serial(cv::Mat img1, cv::Mat img2)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    cv::Mat img_out(img1.rows, img1.cols, CV_8U);
    
    unsigned char* img1_data = (unsigned char*) img1.data;
    unsigned char* img2_data = (unsigned char*) img2.data;
    unsigned char* img_out_data = (unsigned char*) img_out.data;

    for (int i = 0; i < img1.rows * img1.cols; i++) {
        img_out_data[i] = img2_data[i] + img1_data[i];
        if (img_out_data[i] < img2_data[i])
            img_out_data[i] = -1;
    }

    gettimeofday(&end, NULL);
    print_time(start, end, false);

    cv::imwrite("serial.png", img_out);

    return end - start;
}

timeval parallel(cv::Mat img1, cv::Mat img2)
{
    struct timeval start, end;
    gettimeofday(&start, NULL);

    __m128i *img1_src = (__m128i *)img1.data;
    __m128i *img2_src = (__m128i *)img2.data;

    __m128i *img_out = (__m128i*) malloc(img1.rows * img1.cols * sizeof(__m128i) / 16);

    unsigned int img1_width = img1.cols;
    unsigned int img1_height = img1.rows;
    unsigned int img2_width = img2.cols;
    unsigned int img2_height = img2.rows;

    for (unsigned int i = 0; i < img1_height * img1_width / 16; i++)
    {
        __m128i img1_pixel = img1_src[i];
        __m128i img2_pixel = img2_src[i];

        __m128i sum_pixel = _mm_adds_epu8(img1_pixel, img2_pixel);
        img_out[i] = sum_pixel;
    }

    char* temp = (char*)img_out;
    cv::Mat img_out_mat(img1.rows, img1.cols, CV_8UC1, temp);

    gettimeofday(&end, NULL);
    print_time(start, end, true);


    cv::imwrite("parallel.png", img_out_mat);

    return end - start;
}

int main()
{
    cout << "##########################" << endl;
    cout << "Group Members:" << endl;
    cout << "Mahyar Karimi: 810197690" << endl;
    cout << "Amin Setayesh: 810197523" << endl;
    cout << "##########################" << endl << endl;

    cv::Mat img1 = cv::imread("1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread("2.png", cv::IMREAD_GRAYSCALE);
    img2 = img2 * 0.5;
    
    timeval serial_time = serial(img1, img2);
    timeval parallel_time =  parallel(img1, img2);

    print_speedup(serial_time, parallel_time);

}