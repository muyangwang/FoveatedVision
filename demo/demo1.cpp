#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<iostream>
#include<cstdlib>

#include "../FVnew/receptiveField.h"

using namespace cv;
using namespace std;

struct mouse_data_t{
    Point* curserPos;
    const char* imageName;
    const char* reconName;
    foveatedImage_t* fv;
};


static void help() {
    cout << "\n demo of the creation of foveatedImage." << endl;

    cout << "Hot keys: \n"
        "\tESC -quit the program" << endl;
}

static void onMouse(int event, int x, int y, int, void* data) {
    if (event != EVENT_LBUTTONDOWN)
        return;
    mouse_data_t* mouse_data = (mouse_data_t*) data;
    *(mouse_data->curserPos) = Point(x, y);
    setTrackbarPos("curserPos_x", mouse_data->imageName, x);
    setTrackbarPos("curserPos_y", mouse_data->imageName, y);

    mouse_data->fv->resetCenter(Point(x, y));
    Mat* re = mouse_data->fv->getReconstructedImage();
    imshow(mouse_data->reconName, *re);
}

int main(int argc, char** argv) {
    char* imageName = argv[1];
    
    cv::CommandLineParser parser(argc, argv,"{help h | | show help message}{@image|fruits.jpg| input image}");
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }
    
    //set seed for random number
    srand(time(NULL));

    Mat image;
    int xRange, yRange;

    image = imread(imageName, IMREAD_COLOR);
    if (argc != 2 || !image.data) {
        cout << "no image data" << endl;
        return -1;
    }
    help();
    xRange = image.cols;
    yRange = image.rows;

    namedWindow(imageName, WINDOW_AUTOSIZE);
    Point curserPos;

    mouse_data_t mouse_data;
    mouse_data.curserPos = &curserPos;
    mouse_data.imageName = imageName;
    mouse_data.reconName = "recon";


    createTrackbar("curserPos_x", imageName, &curserPos.x, xRange, 0);
    createTrackbar("curserPos_y", imageName, &curserPos.y, yRange, 0);
    setTrackbarPos("curserPos_x", imageName, xRange/2);
    setTrackbarPos("curserPos_y", imageName, yRange/2);

    foveatedImage_t fvImage(&image, curserPos);
    mouse_data.fv = &fvImage;


    Mat* re = fvImage.getReconstructedImage();

    setMouseCallback(imageName, onMouse, &mouse_data);

    imshow(imageName, image);
    imshow("recon", *re);
    while(0) {
        imshow(imageName, image);
        char c = (char)waitKey(0);
        if (c == 27) {
           cout << "End program" << endl;
            break;
        }
    }
    waitKey(0);
    return 0;
}
