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
        embeddedReconstrcutedImage(nullptr)
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
    if (this->embeddedReconstrcutedImage != nullptr) {
        this->freeEmbeddedReconstructedImage();
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
    if (this->embeddedReconstrcutedImage != nullptr) {
        delete this->embeddedReconstrcutedImage;
        this->createEmbeddedFoveatedImage();
    }
}

cv::Mat* foveatedImage_t::createReconstructedImage() {
    int imageSize = FIELD_SIZE*pow(2, LAYER_NUMBER-1);
    this->reconstructedImage = new cv::Mat(imageSize, imageSize,CV_8UC3, cv::Scalar(0,0,0));
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
                                this->reconstructedImage->at<cv::Vec3b>(cv::Point(xStartIndex+m,yStartInIndex+l)) 
                                    = dynamic_cast<fv_bgr_color_t*>(&this->field[layer]->at(j,k))->getColor();
                                break;
                            case channel_t::grayscale:
                                this->reconstructedImage->at<cv::Vec3b>(cv::Point(xStartIndex+m,yStartInIndex+l)) 
                                    = dynamic_cast<fv_grayscale_color_t*>(&this->field[layer]->at(j,k))->getColor();
                                break;
                        }
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

cv::Mat* foveatedImage_t::createEmbeddedFoveatedImage() {
    return this->embeddedReconstrcutedImage;
}

cv::Mat* foveatedImage_t::getReconstructedEmbeddedImage() {
    if (this->embeddedReconstrcutedImage != nullptr) {
        return this->embeddedReconstrcutedImage;
    }
    else {
        return this->createEmbeddedFoveatedImage();
    }
}

void foveatedImage_t::freeEmbeddedReconstructedImage() {
    if (this->embeddedReconstrcutedImage != nullptr) {
        delete this->embeddedReconstrcutedImage;
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

        //        pos_y+blockSize-1 < imHeight &&
        //        pos_x >= 0 &&
        //        pos_y+blockSize-1 < imWidth) {
            // the entire block is in range.
            // Set block color to a random pixel
            
            
        //    return c;
        //}
        
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


