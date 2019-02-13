#include "receptiveField.h"
#include "../openCV/image.h"

#include <stdlib.h>

receptiveField_t* createFoveatedImageFromRawImage(void* rawImage){
    receptiveField_t* foveatedImage = (receptiveField_t*) malloc(sizeof(receptiveField_t));

    return foveatedImage;
}

void destroyFoveatedImage(receptiveField_t* foveatedImage){
    free(foveatedImage);
}

void* createReconstructedImage(receptiveField_t* foveatedImage){
    reconstructedImage = imageFromPixels();
    return reconstructedImage;
}

void destroyReconstructedImage(void* reconstructedImage){

}

