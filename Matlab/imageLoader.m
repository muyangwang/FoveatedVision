%%% This function loads a sequence of saccade images into matlab
%%% return: a seuqence of images and the size of loaded images.

function [images, size] = imageLoader(pictureNames)
numPictures = size(pictureNames);
im = double(imread(pcitrureNames(1)))/255;
[h, w, ~] = size(im);
images = zeros(h, w, 3, numPictures);
for i = 1:numPictures
    images(:,:,:,i) = double(imread(pcitrureNames(i)))/255;
end
[images, [h,w]];
end