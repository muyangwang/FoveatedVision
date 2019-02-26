#include "color.h"

fv_color_t::fv_color_t(fv_color_t& rhs) {
    this->valid = rhs.valid;
}

fv_color_t::fv_color_t(fv_color_t&& rhs) {
    this->valid = rhs.valid;
}

fv_bgr_color_t& fv_bgr_color_t::operator=(const fv_bgr_color_t& rhs) noexcept {
    this->color = rhs.color;
    this->setValid(rhs.isValid());
    return *this;
}

fv_bgr_color_t& fv_bgr_color_t::operator=(const fv_bgr_color_t&& rhs) noexcept {
    this->color = rhs.color;
    this->setValid(rhs.isValid());
    return *this;
}

fv_bgr_color_t& fv_bgr_color_t::operator=(const fv_bgr_color_t rhs) noexcept {
    this->color = rhs.color;
    this->setValid(rhs.isValid());
    return *this;
}

fv_grayscale_color_t& fv_grayscale_color_t::operator=(const fv_grayscale_color_t& rhs) noexcept {
    this->color = rhs.color;
    this->setValid(rhs.isValid());
    return *this;
}

fv_grayscale_color_t& fv_grayscale_color_t::operator=(const fv_grayscale_color_t&& rhs) noexcept {
    this->color = rhs.color;
    this->setValid(rhs.isValid());
    return *this;
}


fv_grayscale_color_t& fv_grayscale_color_t::operator=(const fv_grayscale_color_t rhs) noexcept {
    this->color = rhs.color;
    this->setValid(rhs.isValid());
    return *this;
}






