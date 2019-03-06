#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include<iostream>
#include<cstdlib>
#include<chrono>
#include<string>

#include "foveatedImage.h"

using namespace cv;
using namespace std;

struct mouse_data_t{
    Point* curserPos;
    const char* imageName;
    const char* reconName;
    const char* seriesName;
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
    Mat* se = mouse_data->fv->getFoveatedSeries();
    imshow(mouse_data->reconName, *re);
    imshow(mouse_data->seriesName, *se);
}

int main(int argc, char** argv) {
    char* imageName = argv[1];
    char* c = argv[2];
    int colorType = atoi(c);
    
    cv::CommandLineParser parser(argc, argv,"{help h | | show help message}{@image|fruits.jpg| input image}");
    if (parser.has("help")) {
        parser.printMessage();
        return 0;
    }
    
    //set seed for random number
    srand(time(NULL));

    Mat image, gImage;
    int xRange, yRange;

    image = imread(imageName, IMREAD_COLOR);

    cv::cvtColor(image, gImage, COLOR_BGR2GRAY);

    if (!image.data) {
        cout << "no image data" << endl;
        return -1;
    }
    if (colorType !=0 || colorType != 1) {
        cout << "invalid color type" << colorType<< endl;
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
    mouse_data.seriesName = "series";


    createTrackbar("curserPos_x", imageName, &curserPos.x, xRange, 0);
    createTrackbar("curserPos_y", imageName, &curserPos.y, yRange, 0);
    setTrackbarPos("curserPos_x", imageName, xRange/2);
    setTrackbarPos("curserPos_y", imageName, yRange/2);

    foveatedImage_t* fvImage;
    auto start = chrono::steady_clock::now();
    //foveatedImage_t fvImage(&gImage, curserPos, grayscale);
    if (colorType == 0) {
        fvImage = new foveatedImage_t(&image, curserPos, bgr);
    }
    else {
        fvImage = new foveatedImage_t(&gImage, curserPos, grayscale);
    }
    auto end = chrono::steady_clock::now();
    auto diff = end-start;
    cout << "fv obj generation time" << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    mouse_data.fv = fvImage;

    start = chrono::steady_clock::now();
    Mat* re = fvImage->getReconstructedImage();
    end = chrono::steady_clock::now();
    diff = end-start;
    cout << "recon time " << chrono::duration<double, milli> (diff).count() << " ms" << endl;

    start = chrono::steady_clock::now();
    Mat* se = fvImage->getFoveatedSeries();
    end = chrono::steady_clock::now();
    diff = end-start;
    cout << "series creation time " << chrono::duration<double, milli> (diff).count() << " ms" << endl;

    setMouseCallback(imageName, onMouse, &mouse_data);

    imshow(imageName, image);
    imshow("recon", *re);
    imshow("series", *se);
    while(1) {
        imshow(imageName, image);
        char c = (char)waitKey(0);
        if (c == 27) {
           cout << "End program" << endl;
            break;
        }
        else if (c == 'b') {
            fvImage->setBorderedWindow();
        }
        else if (c == 'd') {
            fvImage->setBorderlessWindow();
        }
    }
    waitKey(0);
    delete fvImage;
    return 0;
}
