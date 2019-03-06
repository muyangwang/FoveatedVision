#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstdlib>

#include "foveatedImage.h"

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

    int frame_width =  cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

    VideoWriter videoRaw("rawStream.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height),true);
    VideoWriter videoFv("FvStream.avi",CV_FOURCC('M','J','P','G'),10, Size(512,512),true);

    while(true){
        cap >> image;
        if(image.empty()){
            cerr << "Frame invalid and skipped!" << endl;
            continue;
        }
        imshow("webcam", image);
        videoRaw.write(image);
        foveatedImage_t fv(&image, curserPos, bgr);
        Mat* fvRecon = fv.getReconstructedImage();
        cout << fvRecon->rows << fvRecon->cols<< endl;
        imshow("foveatedVideo", *fvRecon);
        videoFv.write(*fvRecon);
        char c = (char)waitKey(33);
        if( c == 27 ) break;
   }

   return 0;
}
