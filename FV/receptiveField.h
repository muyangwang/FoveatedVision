/* receptiveField.h defines the foveated image structure.
 * By default, a foveated image includes 5 layers of 32*32 images.
 * The i-th layer corresponding to a 2^(i-1) * 2^(i-1) area of 
 * original image. 
 * */

#ifndef RECEPTIVE_FIELD_H
#define RECEPTIVE_FIELD_H

#define LAYER_NUMBER 5 // #layers in each foveated image
#define FIELD_SIZE 32  //size of the receptive field

#define FOVEATED_IMAGE_SIZE 512 // size of reconstructed image


/* color structure used in foveated project. color is stored in BGR format, represented by a uint8_t(0-255).
 * 
 */
typedef struct {
    unsigned char B;
    unsigned char G;
    unsigned char R;
}color_t;


// TODO: copy raw image from raw opencv data may be expensive.
// deprecate it if possible.
typedef struct {
    int height;
    int length;
    color_t** im;
} image_t;

// each field layer consist of 32*32 pixel values
typedef struct {
    color_t field[FIELD_SIZE][FIELD_SIZE];
} field_t;

// definition of a pixel location
typedef struct {
    int y;
    int x;
} pos_t;

// definition of foveated image.
typedef struct{
    pos_t centerPosition;
    field_t image[LAYER_NUMBER];
} foveatedImage_t;


/* Creates a foveatedImage (aka receptiveField) from a raw 
 * Image.
 */
foveatedImage_t* createFoveatedImageFromRawImage(image_t* im);

/* Destroy a foveatedImage instance.]
 */
void destroyFoveatedImage(foveatedImage_t* foveatedImage);

/* Reconstruct a 512*512 matrix of color_t;
 * The image is stored in openCV cv::Mat format, and this function returns a void* point to the object.
 * Raw Image conversion is defined in openCV/image.h
 */
void* createReconstructedImage(foveatedImage_t* foveatedImage);

/* Destroy the reconstructed matrix created by 
 * createFoveatedImageFromRawImage()
 */
void destroyReconstructedImage(void* reconstructedImage);


/* Create an image with foveated area embedded;
 * The image is stored in openCV cv::Mat format, and this function returns a void* point to the object.
 */
void* createEmbeddedFoveatedImage(image_t* rawImage, foveatedImage_t* foveatedImage);




#endif
