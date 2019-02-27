#ifndef FOVEAREDVIDEO_H
#define FOVEAREDVIDEO_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "foveatedImage.h"

class foveatedVideo {
public:
    foveatedVideo() = delete;
    ~foveatedVideo();

    /*Start a window of foveated video stream*/
    void startFoveatedStream();
private:
    char* windowName;
    VideoCapture cap;
    foveatedImage_t* fv_frame;
};


#endif
