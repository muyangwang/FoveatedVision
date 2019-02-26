#ifndef COLOR_H
#define COLOR_H

#include<opencv2/opencv.hpp>

/* supported channels*/
enum channel_t {
    grayscale = 0, bgr = 1
};

/* color structure used in foveated project.
 * a layer might have some parts out of range of the original image.
 * valid is the indicator variable to show whether the value is blank or generated by real value*/
class fv_color_t {
    bool valid;
public:
    fv_color_t(){}
    virtual ~fv_color_t(){}
    fv_color_t(int v):valid(v){}
    fv_color_t(fv_color_t& rhs);
    fv_color_t(fv_color_t&& rhs);

    bool isValid() const {return valid;}
    void setValid(bool v){valid = v;}

    fv_color_t& operator=(const fv_color_t& rhs) noexcept = delete;
    fv_color_t& operator=(const fv_color_t&& rhs) noexcept = delete;
};

class fv_bgr_color_t : public fv_color_t{
    cv::Vec3b color;
public:
    fv_bgr_color_t():fv_color_t(){}
    ~fv_bgr_color_t(){}
    fv_bgr_color_t(int v, cv::Vec3b c) :fv_color_t(v),color(c){}

    fv_bgr_color_t& operator=(const fv_bgr_color_t& rhs) noexcept;
    fv_bgr_color_t& operator=(const fv_bgr_color_t&& rhs) noexcept;
    void setColor(cv::Vec3b c){color = c;}

    cv::Vec3b getColor() const {return color;}

};

class fv_grayscale_color_t : public fv_color_t {
    uchar color;
public:
    fv_grayscale_color_t():fv_color_t(){}
    ~fv_grayscale_color_t(){}
    fv_grayscale_color_t(int v, uchar c) :fv_color_t(v),color(c){}

    fv_grayscale_color_t& operator=(const fv_grayscale_color_t& rhs) noexcept;
    fv_grayscale_color_t& operator=(const fv_grayscale_color_t&& rhs) noexcept;
    
    void setColor(uchar c){color=c;}
    uchar getColor() const {return color;}
};

#endif
