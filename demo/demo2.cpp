#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdlib>

#include "../FVnew/receptiveField.h"

using namespace cv;
using namespace std;

//static void onMouse(int event, int x, int y, int, void* data) {
//    if (event != EVENT_LBUTTONDOWN)
//        return;
//}

int main( int argc, const char** argv )
{
    // set seed for random numbers
    srand(time(NULL));

    Mat image;

    // raw stream size
    int xRange, yRange;
    
    // center position for foveated image
    Point curserPos;

    VideoCapture cap(0);
    if(!cap.isOpened()){
        cerr << "No camera detected on this system" << endl;
        return -1;
    }

    cap >> image;
    xRange = image.cols;
    yRange = image.rows;
    curserPos.x = xRange/2;
    curserPos.y = yRange/2;

    namedWindow("webcam", WINDOW_AUTOSIZE);
    namedWindow("foveatedVideo", WINDOW_AUTOSIZE);

    while(true){
        cap >> image;
        if(image.empty()){
            cerr << "Frame invalid and skipped!" << endl;
            continue;
        }
        imshow("webcam", image);
        foveatedImage_t fv(&image, curserPos);
        Mat* fvRecon = fv.getReconstructedImage();
        imshow("foveatedVideo", *fvRecon);
        waitKey(5);
   }

   return 0;
}
