/*define the foveated vision inteface*/

#ifndef PYRAMID_H
#define PYRAMID_H

#define FIELD_SIZE 32; // define the size of receptive field.

typedef receptive_color char; // define color for each square.

// receptive field is a block size
typedef struct {
	receptive_color imageField[FIELD_SIZE][FIELD_SIZE];
}receptive_field;

typedef struct{
	int center_point[3];
	receptive_field pyramid[3];
}pyramid_t;



#endif
