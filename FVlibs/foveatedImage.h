/* receptiveField.h defines the foveated image structure.
 * By default, a foveated image includes 5 layers of 32*32 images.
 * The i-th layer corresponding to a 2^(i-1) * 2^(i-1) area of 
 * original image. 
 * */

#ifndef FOVEATED_IMAGE_H
#define FOVEATED_IMAGE_H

#include<opencv2/opencv.hpp>

#include "color.h"
#include "field.h"

#define LAYER_NUMBER 5 // #layers in each foveated image

#define FOVEATED_IMAGE_SIZE 512 // size of reconstructed image

#define COLOR_LEN_GRAYSCALE 1
#define COLOR_LEN_BGR 3



class foveatedImage_t {
private:
    channel_t channel;
    
    cv::Point centerPosition;

    /* pointer to original image*/
    cv::Mat* origin;
    
    /* pointers to all fields */
    field_t* field[LAYER_NUMBER];

    /* pointers to reconstructedImages*/
    cv::Mat* reconstructedImage;
    cv::Mat* foveatedSeries;

    /*if recon image has border on each layer*/
    bool ifReconHasBorder;


    /* select a color for a block, and store it in target*/
    void colorSelector(int pos_y, int pos_x, int layer, fv_color_t& target);
    
    /* update foveated image with a new center position*/
    void updateFV(cv::Point centerPosition);

public:
    foveatedImage_t() = delete;

    /* constructor for foveated image.
     * Must be created from a raw image with a given center position.
     * default constructor is disabled.
     */
    foveatedImage_t(cv::Mat* rawImage, cv::Point centerPosition, channel_t channel);


    /* destructor. Will also destroy the reconstructed image if its not freed properly before.*/
    ~foveatedImage_t();

    void resetCenter(cv::Point newCenter);

    /* Reconstruct a raw openCV format(cv::Mat) image from the foveatedImage. The image is stored in a seperated allocated memory space; Need to be freed after use. We provide a private pointer to locate that reconstructed image. Will try to free the reconstructed image for safety in destructor.
     */
    cv::Mat* createReconstructedImage();

    /* return the reconstrcuted image if it's already created by createRecontructedImage().
     * call createReconstructedImage() if not created.
     */
    cv::Mat* getReconstructedImage();

    /* free the space for reconstructed image.*/
    void freeReconstructedImage();
    
    /* create an image that consists of all 5 layers.*/
    cv::Mat* createFoveatedSeries();

     /* call createFoveatedSeries() if not yet created.
     */
    cv::Mat* getFoveatedSeries();
    
    /* free the embedded version of image*/
    void freeFoveatedSeries();

    cv::Point getCenterPos() const {
        return this->centerPosition;
    }

    void setBorderedWindow();

    void setBorderlessWindow();

    bool ifReconBordered() const;


};

#endif
