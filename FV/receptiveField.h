/* receptiveField.h defines the foveated image structure.
 * By default, a foveated image includes 5 layers of 32*32 images.
 * The i-th layer corresponding to a 2^(i-1) * 2^(i-1) area of 
 * original image. 
 * */

#ifndef RECEPTIVE_FIELD_H
#define RECEPTIVE_FIELD_H

#define LAYER_NUMBER 5; // #layers in each foveated image
#define FIELD_SIZE 32;  //size of the receptive field


/* color structure used in foveated project. color is stored in BGR format, represented by a uint8_t(0-255).
 * 
 */
typedef struct {
    uint8_t B;
    uint8_t G;
    uint8_t R;
}color_t;

typedef struct {
    color_t field[FIELD_SIZE][FIELD_SIZE];
} field_t;

typedef struct{
    int centerPosition;
    field_t im[LAYER_NUMBER];

} receptiveField_t;

/* Creates a foveatedImage (aka receptiveField) from a raw 
 * Image.
 */
receptiveField_t* createFoveatedImageFromRawImage(void* rawImage);

/* Destroy a foveatedImage instance.]
 */

void destroyFoveatedImage(receptiveField_t* foveatedImage);

/* Reconstruct a 512*512 matrix of color_t;
 * The image is stored as opencv::Mat, and returns a void* point as reference.
 * Raw Image generation is specified in openCV/image.h.
 */
void* createReconstructedImage(receptiveField_t* foveatedImage);

/* Destroy the reconstructed matrix created by 
 * createFoveatedImageFromRawImage()
 */
void destroyReconstructedImage(void* reconstructedImage);




#endif
