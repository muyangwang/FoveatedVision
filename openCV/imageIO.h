#ifndef IMAGEIO_H
#define IMAGEIO_H

#include<opencv2/opencv.hpp>

/*
 * imageRead takes image name as input, and
 * load an image into memory.
 * The image is of type cv::
 */
cv::Mat* imageRead(char* imageName);

#endif
