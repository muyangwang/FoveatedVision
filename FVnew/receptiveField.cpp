#include "receptiveField.h"

#include "../utilities/tools.h"
#include <cstring>

foveatedImage_t::foveatedImage_t(cv::Mat* rawImage, pixel_loc_t centerPosition) {
    this->origin = rawImage;
    this->centerPosition = centerPosition;

    for (int layer=0; layer < LAYER_NUMBER; ++layer) {
        int blockSize = pow(2, layer-1);
        for (int i = 0; i < FIELD_SIZE; ++i) {
            for (int j = 0; j < FIELD_SIZE; ++j) {
                int pos_y = centerPosition.y + (i-16)*blockSize;
                int pos_x = centerPosition.x + (j-16)*blockSize;
                this->field[layer].field[i][j] =this->colorSelector(pos_y, pos_x, layer);
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
};

cv::Mat* foveatedImage_t::createReconstructedImage() {
    this->reconstructedImage = new cv::Mat();
    int imageSize = FIELD_SIZE*pow(2, LAYER_NUMBER-1);
    for (int i = 0; i< LAYER_NUMBER; ++i) {
        int layer = LAYER_NUMBER-i-1;
        int blockSize = pow(2, layer-1);
        for (int j = 0; j < FIELD_SIZE; ++j) {
            for (int k = 0; k < FIELD_SIZE; ++k) {
                int yStartInIndex = imageSize/2+(j-FIELD_SIZE/2-1)*blockSize;
                int xStartIndex = imageSize/2+(k-FIELD_SIZE/2-1)*blockSize;
                for (int l = 0; l < blockSize; ++l) {
                    for (int m = 0; m < blockSize; ++m) {
                        this->reconstructedImage->at<cv::Vec3b>(yStartInIndex+l, xStartIndex+m) = this->field->field[j][k].c;
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

fv_color_t foveatedImage_t::colorSelector(int pos_y, int pos_x, int layer) {
    fv_color_t c;
    int imHeight = this->origin->rows;
    int imWidth = this->origin->cols;
    
    c.c[0] = 0;
    c.c[1] = 0;
    c.c[2] = 0;
    c.valid = false;

    if (layer == 1) {
        if (pos_y >= 0 && 
                pos_y < imHeight &&
                pos_x >= 0 &&
                pos_x < imWidth) {
            // the pixel is in the range of original picture
            c.c = this->origin->at<cv::Vec3b>(pos_y, pos_x);
            c.valid = true;
            return c;
        }
    }
    else {
        int blockSize = pow(2, layer-1);
        if (pos_y >= imHeight ||
                pos_y+blockSize-1 < 0 ||
                pos_x >= imWidth ||
                pos_x+blockSize-1<0) {
            // the block is completely out of range.
            // set valid param to 0.
            c.valid = false;
            return c;
        }

        if (pos_y >= 0 &&
                pos_y+blockSize-1 < imHeight &&
                pos_x >= 0 &&
                pos_y+blockSize-1 < imWidth) {
            // the entire block is in range.
            // Set block color to a random pixel
            
            return c;
        }
        
        // The block is half in range and half out of range.
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
        c.c = this->origin->at<cv::Vec3b>(y, x);
        c.valid = true;
        return c;
    }
    return c;
}




}
