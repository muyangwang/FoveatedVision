#ifndef FIELD_H
#define FIELD_H

#include "color.h"


/* an abstract classf of field type*/
class field_t {
public:
    field_t(){}
    ~field_t(){}
    virtual fv_color_t& at(int y, int x);
};

class bgr_field_t : public field_t{
private:
    fv_bgr_color_t field[FIELD_SIZE][FIELD_SIZE];
public:
    fv_bgr_color_t& at(int y, int x) {
        return field[y][x];
    }
};

class grayscale_field_t : public field_t {
private:
    fv_grayscale_color_t field[FIELD_SIZE][FIELD_SIZE];
public:
    fv_color_t& at(int y, int x) {
        return field[y][x];
    }
};

#endif
