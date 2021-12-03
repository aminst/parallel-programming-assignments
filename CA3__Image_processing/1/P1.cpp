#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>

using namespace std;

void show_image(cv::Mat image, string name) {
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    cv::imshow(name, image);
    cv::waitKey(0);
}

int main()
{
    cv::Mat img1 = cv::imread("1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread("2.png", cv::IMREAD_GRAYSCALE);
    
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

        __m128i diff1 = _mm_subs_epu8(img1_pixel, img2_pixel);
        __m128i diff2 = _mm_subs_epu8(img2_pixel, img1_pixel);

        img_out[i] = _mm_or_si128(diff1, diff2);
    }
    char* temp = (char*)img_out;
    cv::Mat img_out_mat(img1.rows, img1.cols, CV_8UC1, temp);
    show_image(img_out_mat, "diff");
}