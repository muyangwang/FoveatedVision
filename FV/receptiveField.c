#include "receptiveField.h"
#include "../openCV/image.h"

#include <stdlib.h>

#define TTT 1

receptiveField_t* createFoveatedImageFromRawImage(void* rawImage){
    receptiveField_t* foveatedImage = (receptiveField_t*) malloc(sizeof(receptiveField_t));

    return foveatedImage;
}

void destroyFoveatedImage(receptiveField_t* foveatedImage){
    free(foveatedImage);
}

void* createReconstructedImage(receptiveField_t* foveatedImage){
    color_t** im = (color_t**) malloc(sizeof(color_t*));
    int a[TTT];
    void* reconstructedImage = (void *) imageFromPixels(im);
    free(im);
    return reconstructedImage;
}

void destroyReconstructedImage(void* reconstructedImage){
    opencvDestroyImage(reconstructedImage);
}

