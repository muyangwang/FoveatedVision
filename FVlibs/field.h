#ifndef FIELD_H
#define FIELD_H

#include "color.h"

#define FIELD_SIZE 32  //size of the receptive field

/* an abstract classf of field type*/
class field_t {
private:
    fv_color_t* field;
public:
    field_t() :field(nullptr){};
    field_t(channel_t channel){
        switch (channel) {
            case channel_t::bgr:
                field = new fv_bgr_color_t[FIELD_SIZE*FIELD_SIZE]();
                break;
            case channel_t::grayscale:
                field = new fv_grayscale_color_t[FIELD_SIZE*FIELD_SIZE]();
                break;
        }
    }
    ~field_t(){delete []field;}

    fv_color_t& at(int y, int x) {
        return field[y*FIELD_SIZE+x];
    }
};
#endif
