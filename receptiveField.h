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
    field_t im[5];

} receptiveField_t;



#endif
