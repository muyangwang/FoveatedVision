#include<opencv2/opencv.hpp>

using namespace cv;

void on_mouse(int event, int x, int y, int flags, void* userdata){
}

int main(int argc, char *argv[]) {
    int value = 50;
    int value2 = 0;


    namedWindow("main1",CV_WINDOW_NORMAL);
    namedWindow("main2",CV_WINDOW_AUTOSIZE | CV_GUI_NORMAL);


    cvDestroyAllWindows();
    return 0;
}


