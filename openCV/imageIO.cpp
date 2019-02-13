#include "imageIO.h"

using namespace cv;

Mat* imageRead(char* imageName) {
    Mat* image = new Mat();
    *image = imread(imageName, IMREAD_COLOR);
    return image;
}

void printImage(cv::Mat* image, char* imageName) {
    namedWindow(imageName, WINDOW_AUTOSIZE);
    imshow( imageName, *image);
    waitKey(0);
}

void getPixelValue(cv::Mat* image, int y, int x) {
}

