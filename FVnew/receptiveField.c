#include "receptiveField.h"
#include "../openCV/image.h"

#include <stdlib.h>
#include<math.h>
#include<string.h>

#define TTT 1
#define square(x) ((x)*(x))

foveatedImage_t* createFoveatedImageFromRawImage(void* rawImage, pos_t centerPosition){
    foveatedImage_t* foveatedImage = (foveatedImage_t*) malloc(sizeof(foveatedImage_t));
    memcpy(&foveatedImage->centerPosition, &centerPosition, sizeof(pos_t));
    foveatedImage->centerPosition = centerPosition;
    int layer = 0, i = 0, j = 0;
    int blockSize = 0;
    for (layer  = 0; layer <= LAYER_NUMBER; ++layer) {
        blockSize = pow(2, layer-1);
        for (i = 0; i <= FIELD_SIZE; ++i) {
            for (j = 0; j <= FIELD_SIZE; ++j) {
                // select a color for the the block
                color_t c;
                int valid;

                // set color to [0, 0, 0] and block is valid by default
                c.B = 0;
                c.G = 0;
                c.R = 0;
                valid = 1;

                int pos_y = centerPosition.y + (i-FIELD_SIZE/2)*blockSize;
                int pos_x = centerPosition.x + (j-FIELD_SIZE/2)*blockSize;

                int imHeight = getHeight(rawImage);
                int imWidth = getWidth(rawImage);
                
                if (layer == 1) {
                    // The most detailed layer, set color directly from raw image.
                    // If pixel position is out of range, remain black and set valid t= 0;
                    if (pos_y >= 0 && pos_y < imHeight
                            && pos_x >= 0 && pos_x< imWidth) {
                        c = getPixelColor(rawImage, pos_x, pos_y);
                    }
                    else {
                        valid = 0;
                    }
                }
                else {
                    if (pos_y >= imHeight || pos_y+blockSize-1 <= 0 ||
                            pos_x >= imWidth || pos_x+blockSize-1) {
                        // The block is fully out of range, set the block to invalid;
                        valid = 0;
                    }

                    if (pos_y >= 0 && pos_y+blockSize-1 < imHeight &&
                            pos_x >= 0 && pos_x+blockSize-1 < imWidth) {
                        // The block is fully in range, select a random color from the block.
                        // TODO: Since c dont generate true random numbers, use current time tick to generate a random number;
                    }
                    
                    // color Selector if the block is half out of range. Select a random color from the valid range.
                    int topBorder = 0, leftBorder = 0, botBorder = 0, rightBorder = 0;
                    if (pos_y < 0) 
                        topBorder = 0;
                    else
                        topBorder = pos_y;

                    if (pos_y+blockSize-1 >= imHeight)
                        botBorder = imHeight-1;
                    else
                        botBorder = pos_y+blockSize-1;

                    if (pos_x < 0)
                        leftBorder = 1;
                    else
                        leftBorder = pos_x;

                    if (pos_x+blockSize-1>imWidth)
                        rightBorder = imWidth-1;
                    else
                        rightBorder = pos_x+blockSize-1;

                        // TODO: Since c dont generate true random numbers, use current time tick to generate a random number;
                }

                foveatedImage->image[layer].field[i][j] = c;
                foveatedImage->image[layer].valid[i][j] = valid;
            }
        }
    }
    return foveatedImage;
}

void destroyFoveatedImage(foveatedImage_t* foveatedImage){
    free(foveatedImage);
}

void* createReconstructedImage(foveatedImage_t* foveatedImage){
    color_t** im = (color_t**) malloc(sizeof(color_t*));
    void* reconstructedImage = (void *) imageFromPixels(im);
    free(im);
    return reconstructedImage;
}

void destroyReconstructedImage(void* reconstructedImage){
    opencvDestroyImage(reconstructedImage);
}

