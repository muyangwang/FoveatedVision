#include "foveatedImage.h"

#include "tools.h"
#include <cstring>
#include <iostream>

using namespace std;

foveatedImage_t::foveatedImage_t(cv::Mat* rawImage, cv::Point centerPosition, channel_t channel_in)
        :channel(channel_in),
        centerPosition(centerPosition),
        origin(rawImage),
        reconstructedImage(nullptr),
        foveatedSeries(nullptr)
{
    for (int i = 0; i < LAYER_NUMBER; ++i) {
        field[i] = new field_t(channel);
    }
    updateFV(this->centerPosition);
}

void foveatedImage_t::updateFV(cv::Point centerPosition) {
    this->centerPosition = centerPosition;
    for (int layer=0; layer < LAYER_NUMBER; ++layer) {
        int blockSize = pow(2, layer);
        for (int i = 0; i < FIELD_SIZE; ++i) {
            for (int j = 0; j < FIELD_SIZE; ++j) {
                int pos_y = centerPosition.y + (i-16)*blockSize;
                int pos_x = centerPosition.x + (j-16)*blockSize;
                colorSelector(pos_y, pos_x, layer, this->field[layer]->at(i,j));
            }
        }
    }
}

foveatedImage_t::~foveatedImage_t() {
    if (this->reconstructedImage != nullptr) {
        this->freeReconstructedImage();
    }
    if (this->foveatedSeries != nullptr) {
        this->freeFoveatedSeries();
    }
    for (int i = 0; i < LAYER_NUMBER; ++i) {
        delete field[i];
    }
};

void foveatedImage_t::resetCenter(cv::Point newCenter) {
    this->centerPosition = newCenter;
    this->updateFV(newCenter);
    if (this->reconstructedImage != nullptr) {
        delete this->reconstructedImage;
        this->createReconstructedImage();
    }
    if (this->foveatedSeries != nullptr) {
        delete this->foveatedSeries;
        this->createFoveatedSeries();
    }
}

cv::Mat* foveatedImage_t::createReconstructedImage() {
    int imageSize = FIELD_SIZE*pow(2, LAYER_NUMBER-1);
    
    switch (channel) {
        case channel_t::bgr:
            this->reconstructedImage = new cv::Mat(imageSize, imageSize,CV_8UC3, cv::Scalar(0,0,0));
            break;
        case channel_t::grayscale:
            this->reconstructedImage = new cv::Mat(imageSize, imageSize, CV_8UC1, cv::Scalar(0));
            break;
    }
    
    cv::Vec3b black1;
    black1[0] = 0;
    black1[1] = 0;
    black1[2] = 0;

    uchar black2 = 0;

    for (int i = 0; i< LAYER_NUMBER; ++i) {
        int layer = LAYER_NUMBER-i-1;
        int blockSize = pow(2, layer);
        for (int j = 0; j < FIELD_SIZE; ++j) {
            for (int k = 0; k < FIELD_SIZE; ++k) {
                int yStartInIndex = imageSize/2+(j-FIELD_SIZE/2)*blockSize;
                int xStartIndex = imageSize/2+(k-FIELD_SIZE/2)*blockSize;
                for (int l = 0; l < blockSize; ++l) {
                    for (int m = 0; m < blockSize; ++m) {
                        switch(channel) {
                            case channel_t::bgr:
                                if (!this->field[layer]->at(j,k).isValid()) {
                                    this->reconstructedImage->at<cv::Vec3b>(cv::Point(xStartIndex+m,yStartInIndex+l)) = black1;
                                    continue;
                                }
                                this->reconstructedImage->at<cv::Vec3b>(cv::Point(xStartIndex+m,yStartInIndex+l)) 
                                    = dynamic_cast<fv_bgr_color_t*>(&this->field[layer]->at(j,k))->getColor();
                                break;
                            case channel_t::grayscale:
                                if (!this->field[layer]->at(j,k).isValid()) {
                                    this->reconstructedImage->at<uchar>(cv::Point(xStartIndex+m,yStartInIndex+l)) = black2;
                                }
                                this->reconstructedImage->at<uchar>(cv::Point(xStartIndex+m,yStartInIndex+l)) 
                                    = dynamic_cast<fv_grayscale_color_t*>(&this->field[layer]->at(j,k))->getColor();
                                break;
                        }
                    }
                }
            }
        }
        
        /* set all layers' border to white if ifReconHasBorder is set to true */
        if (ifReconHasBorder) {
            for (int i = 1; i < LAYER_NUMBER; ++i) {
                /*
                int topLeftX = FOVEATED_IMAGE_SIZE/2-FIELD_SIZE*i/2;
                int topLeftY = FOVEATED_IMAGE_SIZE/2-FIELD_SIZE*i/2;

                int topRightX = FOVEATED_IMAGE_SIZE/2+FIELD_SIZE*i/2-1;
                int topRightY = FOVEATED_IMAGE_SIZE/2-FIELD_SIZE*i/2;

                int botLeftX = FOVEATED_IMAGE_SIZE/2-FIELD_SIZE*i/2;
                int botLeftY = FOVEATED_IMAGE_SIZE/2+FIELD_SIZE*i/2-1;

                int botRightX = FOVEATED_IMAGE_SIZE/2+FIELD_SIZE*i/2-1;
                int botRightY = FOVEATED_IMAGE_SIZE/2+FIELD_SIZE*i/2-1;*/

                for (int j = 0; j < FIELD_SIZE*i; ++j) {
                    switch (channel) {
                        case channel_t::bgr:
                            break;
                        case channel_t::grayscale:
                            break;
                    }
                }

            }
        }
    }


    return this->reconstructedImage;
}

cv::Mat* foveatedImage_t::getReconstructedImage() {
    if (this->reconstructedImage != nullptr) {
        return this->reconstructedImage;
    }
    else {
        return this->createReconstructedImage();
    }
}

void foveatedImage_t::freeReconstructedImage() {
    if (this->reconstructedImage != nullptr) {
        delete this->reconstructedImage;
    }
}

cv::Mat* foveatedImage_t::createFoveatedSeries() {
    switch (channel) {
        case channel_t::bgr:
            this->foveatedSeries = new cv::Mat(FIELD_SIZE*LAYER_NUMBER, FIELD_SIZE,CV_8UC3, cv::Scalar(0,0,0));
            break;
        case channel_t::grayscale:
            this->foveatedSeries = new cv::Mat(FIELD_SIZE*LAYER_NUMBER, FIELD_SIZE, CV_8UC1, cv::Scalar(0));
            break;
    }

    for (int i = 0; i < LAYER_NUMBER; ++i) {
        for (int j = 0; j < FIELD_SIZE; ++j) {
            for (int k = 0; k < FIELD_SIZE; ++k) {
                switch (channel) {
                    case channel_t::bgr:
                        cout << (int)dynamic_cast<fv_bgr_color_t*>(&field[i]->at(j,k))->getColor().val[0] << endl;
                        cout << "x: " << k << "y: " << i*FIELD_SIZE+j << endl;
                        
                        cout << "test" << endl;
                        foveatedSeries->at<cv::Vec3b>(cv::Point(k,i*FIELD_SIZE+j)) 
                            = dynamic_cast<fv_bgr_color_t*>(&field[i]->at(j,k))->getColor();
                        break;
                    case channel_t::grayscale:
                        foveatedSeries->at<uchar>(cv::Point(k, i*FIELD_SIZE+j))
                            = dynamic_cast<fv_grayscale_color_t*>(&field[i]->at(j,k))->getColor();
                        break;
                }
            }
        }
    }

    return this->foveatedSeries;
}

cv::Mat* foveatedImage_t::getFoveatedSeries() {
    if (this->foveatedSeries != nullptr) {
        return this->foveatedSeries;
    }
    else {
        return this->createFoveatedSeries();
    }
}

void foveatedImage_t::freeFoveatedSeries() {
    if (this->foveatedSeries != nullptr) {
        delete this->foveatedSeries;
    }
}

void foveatedImage_t::colorSelector(int pos_y, int pos_x, int layer, fv_color_t& target) {

    int imHeight = this->origin->rows;
    int imWidth = this->origin->cols;

    if (layer == 1) {
        if (pos_y >= 0 && 
                pos_y < imHeight &&
                pos_x >= 0 &&
                pos_x < imWidth) {
            // the pixel is in the range of original picture
            
            switch (channel) {
                case channel_t::bgr:
                    dynamic_cast<fv_bgr_color_t&>(target).setColor(origin->at<cv::Vec3b>(pos_y, pos_x));
                    break;
                case channel_t::grayscale:
                    dynamic_cast<fv_grayscale_color_t&>(target).setColor(origin->at<uchar>(pos_y, pos_x));
                    break;
            }
            target.setValid(true);
            return;
        }
    }
    else {
        int blockSize = pow(2, layer);
        if (pos_y >= imHeight ||
                pos_y+blockSize-1 < 0 ||
                pos_x >= imWidth ||
                pos_x+blockSize-1<0) {
            //cout << "completely out of range" << endl;
            // the block is completely out of range.
            // set valid param to 0.
            target.setValid(false);
            return;
        }
        
        // The block has at least part in range.
        // we select a random pixel for the inrange part.
        int topBorder, leftBorder, rightBorder, botBorder;
        if (pos_y < 0) {
            topBorder = 0;
        } else {
            topBorder = pos_y;
        }
        if (pos_y+blockSize-1>= imHeight) {
            botBorder = imHeight-1;
        } else {
            botBorder = pos_y+blockSize-1;
        }
        if (pos_x < 0) {
            leftBorder = 0;
        } else {
            leftBorder = pos_x;
        }
        if (pos_x+blockSize-1>=imWidth) {
            rightBorder = imWidth-1;
        } else {
            rightBorder = pos_x+blockSize-1;
        }
        int sizeH = botBorder-topBorder+1;
        int sizeW = rightBorder-leftBorder+1;
        int y = randomNumberGen(sizeH);
        int x = randomNumberGen(sizeW);
        switch(channel){
            case channel_t::bgr:
                dynamic_cast<fv_bgr_color_t&>(target).setColor(this->origin->at<cv::Vec3b>(topBorder+y, leftBorder+x));
                break;
            case channel_t::grayscale:
                dynamic_cast<fv_grayscale_color_t&>(target).setColor(this->origin->at<uchar>(topBorder+y, leftBorder+x));
                break;
        }
        target.setValid(true);
        return;
    }
    return;
}

void foveatedImage_t::setBorderedWindow() {
    if (ifReconHasBorder) return;
    ifReconHasBorder = true;
    delete reconstructedImage;
    createReconstructedImage();
}

void foveatedImage_t::setBorderlessWindow() {
    if (!ifReconHasBorder) return;
    ifReconHasBorder = false;
    delete reconstructedImage;
    createReconstructedImage();
}

bool foveatedImage_t::ifReconBordered() const {
    return ifReconHasBorder;
}

