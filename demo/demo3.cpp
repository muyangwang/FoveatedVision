/* In this demo, we simulate camera with still objects. Our goal is to move Center Position of the foveated Image to sacade through salient objects.
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <vector>
#include <deque>


#include "foveatedImage.h"

using namespace cv;
using namespace std;

struct salientPos_t{
    Point curserPos;
    int searchLayer;
};

int getSize(int layer);

int main(int argc, char** argv) {
    char * imageName = argv[1];
    srand(time(NULL));

    Mat image1, image;
    image1 = imread(imageName, IMREAD_COLOR);
    imshow(imageName, image1);
    
    if (argc != 2 || !image1.data) {
        cout << "please input valid image" << endl;
        return -1;
    }

    cvtColor(image1, image, CV_BGR2GRAY);
    namedWindow(imageName, WINDOW_AUTOSIZE);

    int xRange = image.cols;
    int yRange = image.rows;


    Point startPos;
    startPos.x = xRange/2;
    startPos.y = yRange/2;
    deque<salientPos_t> searchSet;
    deque<salientPos_t> comfirmedSet;
    vector<vector<bool>> exclusionSet(yRange, vector<bool>(xRange, false));
    
    salientPos_t sfirst;
    sfirst.curserPos = startPos;
    sfirst.searchLayer = 4;

    searchSet.push_back(sfirst);
    
    int detection = 0;
    while (1) {
        if (searchSet.empty()) {
            cout << "no more candicate. exit" << endl;
            break;
        }
        cout << "waitKey" << endl;
        waitKey(0);
        
        // get a random salient candidate from the search set.
        int index = rand() % searchSet.size();
        salientPos_t s = searchSet[index];
        searchSet.erase(searchSet.begin()+index);


        foveatedImage_t fvImage(&image, s.curserPos, grayscale);
        Mat m = fvImage.getLayer(s.searchLayer);
        
        cout << endl;
        cout << "-----------" << endl;
        cout << "detection #" << detection << endl;
        ++detection;
        cout << "fvImage centerPosition: " << endl;
        cout << "      x: " << s.curserPos.x << endl;
        cout << "      y: " << s.curserPos.y << endl;
        Mat Recon = *fvImage.getReconstructedImage();
        
        string line = "x: " + to_string(s.curserPos.x) + "\ny: " + to_string(s.curserPos.y);
        cv::putText( Recon, line.c_str(), cvPoint(30,30), 
                FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(200,200,250), 1, CV_AA);
        imshow("fvImage", Recon);
        

        for (int i = 0; i < m.rows-1; ++i){
            for (int j = 0; j < m.cols-1; ++j) {
                if (m.at<uchar>(i,j) < 100) {
                    // a possible salient obj
                    if (m.at<uchar>(i,j+1) < 100 &&
                            m.at<uchar>(i+1,j) < 100 &&
                            m.at<uchar>(i+1,j+1) < 100) {
                            // A confirmed salient, save it to confirmed set,
                            // and print out the foveatedImage.
                            imshow("Layer image", m);
                            cout << "  Layer: " << s.searchLayer << endl;
                    }
                    else {
                        // otherewise, we add this to search set if searchLayer is not yet 0.
                        if (s.searchLayer != 1) {
                            salientPos_t sc;
                            sc.curserPos.x = s.curserPos.x +(j-15)*getSize(s.searchLayer);
                            sc.curserPos.y = s.curserPos.y+(i-15)*getSize(s.searchLayer);
                            sc.searchLayer = s.searchLayer-1;
                            searchSet.push_back(sc);
                        }
                    }
                    // do nothing, not a good block
                }
            }
        }
    }
    waitKey(0);
}

int getSize(int layer) {
    int val = 1;
    for (int i = 0; i < layer; ++i){
        val*=2;
    }
    return val;
}

