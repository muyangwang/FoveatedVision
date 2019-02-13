#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <opencv2/opencv.hpp>
#include "../FV/receptiveField.h"

/*
 * imageRead takes image name as input, and
 * load an image into memory.
 * The image is of type cv::
 */
cv::Mat* imageRead(char* imageName);

void printImage(cv::Mat* image, char* imageName);

void getPixelValue(cv::Mat* image, int y, int x);

void writeAndDisplayImage(cv::Mat* image, char* imageName);

void videoRead(char* videoName);

// TODO: read frame or read next frame?
cv::Mat* readNextFramefromVideo();

#endif
